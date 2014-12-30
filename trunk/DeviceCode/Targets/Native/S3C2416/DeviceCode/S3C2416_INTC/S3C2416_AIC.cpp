
#include <tinyhal.h>
#include "..\S3C2416.h"

#define DEFINE_IRQ(index, priority) { priority, { NULL, (void*)(size_t)index } }

S3C2416_AIC_Driver::IRQ_VECTORING S3C2416_AIC_Driver::s_IsrTableGroup1[] =
{
	    DEFINE_IRQ(0,   0),     // External interrupt 0
	    DEFINE_IRQ(1,   0),     // External interrupt 1
	    DEFINE_IRQ(2,   0),     // External interrupt 2
	    DEFINE_IRQ(3,   0),     // External interrupt 3
	    DEFINE_IRQ(4,   0),     // External interrupt 4_7
	    DEFINE_IRQ(5,   0),		// External interrupt 8_23

	    DEFINE_IRQ(7,   0),     // Battery Fault interrupt
	    DEFINE_IRQ(8,   0),     // RTC Time tick interrupt
	    DEFINE_IRQ(9,   0),     // Watch-Dog timer interrupt(INT_WDT, INT_AC97)
	    DEFINE_IRQ(10,  0),     // Timer0 interrupt
	    DEFINE_IRQ(11,  0),     // Timer1 interrupt
	    DEFINE_IRQ(12,  0),     // Timer2 interrupt
	    DEFINE_IRQ(13,  0),     // Timer3 interrupt
	    DEFINE_IRQ(14,  0),     // Timer4 interrupt
	    DEFINE_IRQ(15,  0),     // UART2 Interrupt (ERR, RXD, and TXD)
	    DEFINE_IRQ(16,  0),     // LCD interrupt (INT_FrSyn and INT_FiCnt)
	    DEFINE_IRQ(17,  0),     // DMA channel 0 interrupt
	    DEFINE_IRQ(18,  0),     // UART 3 interrupt

	    DEFINE_IRQ(20,  0),     // SDI 1 interrupt
	    DEFINE_IRQ(21,  0),     // SDI 0 interrupt
	    DEFINE_IRQ(22,  0),     // SPI0 interrupt
	    DEFINE_IRQ(23,  0),     // UART1 Interrupt (ERR, RXD, and TXD)
	    DEFINE_IRQ(24,  0),     // Nand Flash Control Interrupt
	    DEFINE_IRQ(25,  0),     // USB Device interrupt
	    DEFINE_IRQ(26,  0),     // USB Host interrupt
	    DEFINE_IRQ(27,  0),     // IIC interrupt
	    DEFINE_IRQ(28,  0),     // UART0 Interrupt (ERR, RXD, and TXD)
		
	    DEFINE_IRQ(30,  0),     // RTC alarm interrupt
	    DEFINE_IRQ(31,  0),     // ADC EOC and Touch interrupt (INT_ADC_S/INT_TC)

};

S3C2416_AIC_Driver::IRQ_VECTORING S3C2416_AIC_Driver::s_IsrTableGroup2[] =
{	

		DEFINE_IRQ(0,  0),     // 2D alarm interrupt
		DEFINE_IRQ(4,  0),     // PCM0 interrupt
		DEFINE_IRQ(6,  0),     // I2S0 interrupt
};

void S3C2416_AIC_Driver::Initialize()
{
	S3C2416::Debug_printf("S3C2416_AIC_Driver::Initialize\r\n");
	S3C2416_AIC &aic = S3C2416::AIC();
   
	aic.INTMOD1 = 0x0;			
	aic.INTMOD2 = 0x0;   // All=IRQ mode
	aic.INTMSK1 = 0xffffffff;	// All interrupt is masked.
	aic.INTMSK2 = 0xffffffff;	// All interrupt is masked.
	aic.INTSUBMSK = 0xffffffff;		// Sub interrupts masked

    // set all priorities to the lowest
    IRQ_VECTORING* IsrVector = s_IsrTableGroup1;

    // set the priority level for each IRQ and stub the IRQ callback
    for (int i=0; i<c_VECTORING_GUARD;i++)
    {
    	//TODO: set priority
        //AITC.SetPriority( IsrVector->Index, S3C2416_AITC::c_IRQ_Priority_0 );

    	IsrVector[i].Handler.Initialize( STUB_ISRVector, (void*)(size_t)i );
    }
	  // set the priority level for each IRQ and stub the IRQ callback
	 IsrVector = s_IsrTableGroup2; 
    for (int i=0; i<c_VECTORING_GUARD;i++)
    {
    	//TODO: set priority
        //AITC.SetPriority( IsrVector->Index, S3C2416_AITC::c_IRQ_Priority_0 );

    	IsrVector[i].Handler.Initialize( STUB_ISRVector, (void*)(size_t)i );
    }
}

BOOL S3C2416_AIC_Driver::ActivateInterrupt(UINT32 Irq_Index, BOOL Fast, HAL_CALLBACK_FPN ISR, void* ISR_Param)
{
    // figure out the interrupt
    IRQ_VECTORING* IsrVector = IRQToIRQVector( Irq_Index );
    if(!IsrVector)
        return FALSE;

    S3C2416_AIC &aic = S3C2416::AIC();

    GLOBAL_LOCK(irq);
if(Irq_Index <32)  //if Index >32 ,INT is Group2
{
    // disable this interrupt while we change it
    aic.INTMSK1 |= (0x01 << Irq_Index);
}
else
{
    // disable this interrupt while we change it
    aic.INTMSK2 |= (0x01 << (Irq_Index-32));
}
    // Clear the interrupt on the interrupt controller
    RemoveForcedInterrupt( Irq_Index );

    // set the vector
    IsrVector->Handler.Initialize( ISR, ISR_Param );
if(Irq_Index <32)  //if Index >32 ,INT is Group2
{
    // enable the interrupt if we have a vector
    aic.INTMSK1 &= ~(0x01 << Irq_Index);
}
else
{
    // enable the interrupt if we have a vector
    aic.INTMSK2 &= ~(0x01 << (Irq_Index-32));
}
S3C2416::Debug_printf("Irq_Index is %d and IRQ Entry Point is %x \r\n", Irq_Index,IsrVector->Handler.GetEntryPoint());
    return TRUE;
}

BOOL S3C2416_AIC_Driver::DeactivateInterrupt( UINT32 Irq_Index )
{

    return FALSE;
}

void /*__irq*/ S3C2416_AIC_Driver::IRQ_Handler(void)
{
	unsigned int index;
	S3C2416_AIC &aic = S3C2416::AIC();

    // set before jumping elsewhere or allowing other interrupts
    SystemState_SetNoLock( SYSTEM_STATE_ISR              );
    SystemState_SetNoLock( SYSTEM_STATE_NO_CONTINUATIONS );

    index = aic.INTOFFSET1;

 //  S3C2416::Debug_printf("S3C2416_AIC_Driver::IRQ_Handler: index: %d\r\n", index);

    //TODO: IsrVectors
    IRQ_VECTORING* IsrVector = &s_IsrTableGroup1[ index ];
 //   S3C2416::Debug_printf("INTPND before %08x (address: %08x)\r\n", aic.INTPND1, &aic.INTPND1 );
    RemoveForcedInterrupt( index );
 //   S3C2416::Debug_printf("INTPND after %08x\r\n", aic.INTPND1);
    IsrVector->Handler.Execute();

    index = aic.INTOFFSET2;

 //   S3C2416::Debug_printf("S3C2416_AIC_Driver::IRQ_Handler: index: %d\r\n", index);

    //TODO: IsrVectors
    IsrVector = &s_IsrTableGroup2[ index ];
 //   S3C2416::Debug_printf("INTPND2 before %08x (address: %08x)\r\n", aic.INTPND2, &aic.INTPND2 );
    RemoveForcedInterrupt( index );
 //   S3C2416::Debug_printf("INTPND2 after %08x\r\n", aic.INTPND2);
    IsrVector->Handler.Execute();

    SystemState_ClearNoLock( SYSTEM_STATE_NO_CONTINUATIONS ); // nestable
    SystemState_ClearNoLock( SYSTEM_STATE_ISR              ); // nestable
}

BOOL S3C2416_AIC_Driver::InterruptEnable( UINT32 Irq_Index  )
{
	return FALSE;
}


BOOL S3C2416_AIC_Driver::InterruptDisable( UINT32 Irq_Index )
{
	return FALSE;
}


BOOL S3C2416_AIC_Driver::InterruptEnableState( UINT32 Irq_Index )
{
	return FALSE;
}


BOOL S3C2416_AIC_Driver::InterruptState( UINT32 Irq_Index )
{
	return FALSE;
}

S3C2416_AIC_Driver::IRQ_VECTORING* S3C2416_AIC_Driver::IRQToIRQVector( UINT32 IRQ )
{
   if(IRQ < 32)
   	{
    IRQ_VECTORING* IsrVector = s_IsrTableGroup1;

    if (IRQ < c_VECTORING_GUARD)
    {
        return &IsrVector[IRQ];
    }
   	}
   else 
   	{
    IRQ_VECTORING* IsrVector = s_IsrTableGroup2;

    if ((IRQ -32 )< c_VECTORING_GUARD)
    {
        return &IsrVector[IRQ - 32];
    }
   	}
    return NULL;
}


void S3C2416_AIC_Driver::STUB_ISRVector( void* Param )
{
//	S3C2416::Debug_printf("STUB_ISR %d\r\n", (size_t)Param);
	//  HARD_BREAKPOINT();
}


void __irq IRQ_Handler(void)
{
    S3C2416_AIC_Driver::IRQ_Handler();
}
