#include "INTC_Adapter.h"
#include "core_cm3.h"

//---------------------------------------------------------
//Extern value
extern UINT32 Vectors_Handler_Function;
extern UINT32 Vectors_Handler_Parameter;
extern UINT32 ARM_Vectors;
extern UINT32 ARM_Vectors_End;

//---------------------------------------------------------
//Global variable
UINT32 *g_pHandlerFun = NULL;
UINT32 *g_pHandlerParam = NULL;

//---------------------------------------------------------

BOOL INTC_Initialize()
{
	//The vector size could be calculated by address.
	const UINT32 VECTOR_SIZE = reinterpret_cast<UINT32>(&ARM_Vectors_End) - reinterpret_cast<UINT32>(&ARM_Vectors);

	/* 
	//ERROR:The following code can not compile.
	g_pHandlerFun = new UINT32[VECTOR_SIZE / sizeof(UINT32)];
	if(g_pHandlerFun == NULL)
	{
		return FALSE;
	}
	
	g_pHandlerParam = new UINT32[VECTOR_SIZE / sizeof(UINT32)];
	if(g_pHandlerParam == NULL)
	{
		return FALSE;
	}	
		
	*/
	
		
	g_pHandlerFun = reinterpret_cast<UINT32 *>(&Vectors_Handler_Function);
	g_pHandlerParam = reinterpret_cast<UINT32 *>(&Vectors_Handler_Parameter);

	memset(g_pHandlerFun,0,VECTOR_SIZE);
	memset(g_pHandlerParam,0,VECTOR_SIZE);
	
	return TRUE;
}

BOOL INTC_ActivateInterrupt(UINT32 Irq_Index, HAL_CALLBACK_FPN ISR, void* ISR_Param)
{	
	if(g_pHandlerFun == NULL ||
		g_pHandlerParam == NULL)
	{
		return FALSE;
	}
	
	g_pHandlerFun[Irq_Index] = reinterpret_cast<UINT32>(ISR);
	g_pHandlerParam[Irq_Index] = reinterpret_cast<UINT32>(ISR_Param);
	
	__DSB();
	
	return TRUE;
}

BOOL INTC_DeactivateInterrupt(UINT32 Irq_Index)
{	
	return INTC_ActivateInterrupt(Irq_Index,NULL,NULL);
}

BOOL INTC_InterruptEnableState( UINT32 Irq_Index )
{
	IRQn_Type channel;
	if(IrqToChannel(Irq_Index,channel) == FALSE)
	{
		return FALSE;
	}
	
	uint32_t RegVal = NVIC->ISER[channel >> 0x05];
	uint32_t MaskBit = (uint32_t)0x01 << (channel & (uint8_t)0x1F);
  if((RegVal & MaskBit) != 0)
  {
  	return TRUE;
  }
  else
  {
  	return FALSE;
  }
}

BOOL IrqToChannel(UINT32 dwIrq,IRQn_Type &channel)
{
	if(dwIrq == IRQ_StackTop ||
			dwIrq == IRQ_Reset ||
			dwIrq == IRQ_HardFault)
	{
		//There aren't the channels index suitable for the vector table,so return FALSE.
		return FALSE;
	}

		
	switch(dwIrq)
	{
		case IRQ_NMI:
			channel = NonMaskableInt_IRQn;
			break;
		case IRQ_MemManage:
			channel = MemoryManagement_IRQn;
			break;
		case IRQ_BusFault:
			channel = BusFault_IRQn;
			break;
		case IRQ_UsageFault:
			channel = UsageFault_IRQn;
			break;
		case IRQ_SVC:
			channel = SVCall_IRQn;
			break;
		case IRQ_DebugMon:
			channel = DebugMonitor_IRQn;
			break;
		case IRQ_PendSV:
			channel = PendSV_IRQn;
			break;
		case IRQ_SysTick:
			channel = SysTick_IRQn;
			break;
		default:
			channel = static_cast<IRQn_Type>(dwIrq - 16);
			break;
	}
	
	return TRUE;
}

BOOL EnableIrq(UINT32 dwIrq,BOOL bEnable)
{	
	switch(dwIrq)
	{
		case IRQ_MemManage:
		{
			if(bEnable == FALSE)
			{
				SCB->SHCSR &= ~(1 << SCB_SHCSR_MEMFAULTENA);
			}
			else
			{
				SCB->SHCSR |= (1 << SCB_SHCSR_MEMFAULTENA);
			}
			break;
		}
		case IRQ_BusFault:
		{
			if(bEnable == FALSE)
			{
				SCB->SHCSR &= ~(1 << SCB_SHCSR_BUSFAULTENA);
			}
			else
			{
				SCB->SHCSR |= (1 << SCB_SHCSR_BUSFAULTENA);
			}
			break;
		}
		case IRQ_UsageFault:
		{
			if(bEnable == FALSE)
			{
				SCB->SHCSR &= ~(1 << SCB_SHCSR_USGFAULTENA);
			}
			else
			{
				SCB->SHCSR |= (1 << SCB_SHCSR_USGFAULTENA);
			}
			break;
		}		
		case IRQ_SysTick:
		{
			if(bEnable == FALSE)
			{
				SysTick->CTRL &= ~(1 << SYSTICK_ENABLE);
			}
			else
			{
				SysTick->CTRL |= (1 << SYSTICK_ENABLE);
			}
			break;
		}
		default:
		{
			//Convert to channel
			IRQn_Type channel;
			if(IrqToChannel(dwIrq,channel) == FALSE)
			{
				return FALSE;
			}
			
			//Enable or disable
			if(bEnable == FALSE)
			{
				NVIC_DisableIRQ(channel);
			}
			else
			{
				NVIC_EnableIRQ(channel);
			}
			break;
		}
	}
	

	
	//Ensure completion of memory access
	__DSB(); 
	
	return TRUE;
}

#pragma arm section code = "SectionForInterruptHandler" //Begin

BOOL CallRealHandler(DWORD dwIrq)
{
	if(dwIrq == IRQ_StackTop ||
		dwIrq == IRQ_Reset)
	{
		//The two IRQ should not be  changed.
		return FALSE;
	}
	
	if(g_pHandlerFun == NULL ||
		g_pHandlerParam == NULL)
	{
		return FALSE;
	}
	
	HAL_CALLBACK_FPN pFunc = reinterpret_cast<HAL_CALLBACK_FPN>(g_pHandlerFun[dwIrq]);
	if(pFunc == NULL)
	{
		return FALSE;
	}
	
	(*pFunc)(reinterpret_cast<void *>(g_pHandlerParam[dwIrq]));
	
	return TRUE;
}

extern "C" void NMI_Handler()
{
	//It's easy to find the problem when dead loop here
	while(TRUE);
	
	//CallRealHandler(IRQ_NMI);
}
      
extern "C" void HardFault_Handler()
{
	//It's easy to find the problem when dead loop here
	while(TRUE);
	
	//CallRealHandler(IRQ_HardFault);
}
       
extern "C" void MemManage_Handler()
{
	//It's easy to find the problem when dead loop here
	while(TRUE);
	
	//CallRealHandler(IRQ_MemManage);
}
      
extern "C" void BusFault_Handler()
{
	//It's easy to find the problem when dead loop here
	while(TRUE);
	
	//CallRealHandler(IRQ_BusFault);
}
      
extern "C" void UsageFault_Handler()
{
	while(TRUE);
	//CallRealHandler(IRQ_UsageFault);
}
    
extern "C" void SVC_Handler()
{
	CallRealHandler(IRQ_SVC);
}
            
extern "C" void DebugMon_Handler()
{
	CallRealHandler(IRQ_DebugMon);
}

extern "C" void PendSV_Handler()
{
	CallRealHandler(IRQ_PendSV);
}
         
extern "C" void SysTick_Handler()
{
	CallRealHandler(IRQ_SysTick);
}

extern "C" void WWDG_IRQHandler()
{
	CallRealHandler(IRQ_WWDG);
}
        
extern "C" void PVD_IRQHandler()
{
	CallRealHandler(IRQ_PVD);
}
         
extern "C" void TAMPER_IRQHandler()
{
	CallRealHandler(IRQ_TAMPER);
}
     
extern "C" void RTC_IRQHandler()
{
	CallRealHandler(IRQ_RTC);
}
       
extern "C" void FLASH_IRQHandler()
{
	CallRealHandler(IRQ_FLASH);
}
        
extern "C" void RCC_IRQHandler()
{
	CallRealHandler(IRQ_RCC);
}
       
extern "C" void EXTI0_IRQHandler()
{
	CallRealHandler(IRQ_EXTI0);
}
      
extern "C" void EXTI1_IRQHandler()
{
	CallRealHandler(IRQ_EXTI1);
}
        
extern "C" void EXTI2_IRQHandler()
{
	CallRealHandler(IRQ_EXTI2);
}
      
extern "C" void EXTI3_IRQHandler()
{
	CallRealHandler(IRQ_EXTI3);
}
       
extern "C" void EXTI4_IRQHandler()
{
	CallRealHandler(IRQ_EXTI4);
}

extern "C" void DMAChannel1_IRQHandler()
{
	CallRealHandler(IRQ_DMAChannel1);
}
 

extern "C" void DMAChannel3_IRQHandler()
{
	CallRealHandler(IRQ_DMAChannel3);
}
  
extern "C" void DMAChannel4_IRQHandler()
{
	CallRealHandler(IRQ_DMAChannel4);
}
  
extern "C" void DMAChannel5_IRQHandler()
{
	CallRealHandler(IRQ_DMAChannel5);
}
  
extern "C" void DMAChannel6_IRQHandler()
{
	CallRealHandler(IRQ_DMAChannel6);
}
   
extern "C" void DMAChannel7_IRQHandler()
{
	CallRealHandler(IRQ_DMAChannel7);
}
  
extern "C" void ADC_IRQHandler()
{
	CallRealHandler(IRQ_ADC);
}
       
extern "C" void USB_HP_CAN_TX_IRQHandler()
{
	CallRealHandler(IRQ_USB_HP_CAN_TX);
}

extern "C" void USB_LP_CAN_RX0_IRQHandler()
{
	CallRealHandler(IRQ_USB_LP_CAN_RX0);
}

extern "C" void CAN_RX1_IRQHandler()
{
	CallRealHandler(IRQ_CAN_RX1);
}
   
extern "C" void CAN_SCE_IRQHandler()
{
	CallRealHandler(IRQ_CAN_SCE);
}
  
extern "C" void EXTI9_5_IRQHandler()
{
	CallRealHandler(IRQ_EXTI9_5);
}
    
extern "C" void TIM1_BRK_IRQHandler()
{
	CallRealHandler(IRQ_TIM1_BRK);
}

extern "C" void TIM1_UP_IRQHandler()
{
	CallRealHandler(IRQ_TIM1_UP);
}
     
extern "C" void TIM1_TRG_COM_IRQHandler()
{
	CallRealHandler(IRQ_TIM1_TRG_COM);
}

extern "C" void TIM1_CC_IRQHandler()
{
	CallRealHandler(IRQ_TIM1_CC);
}
     
extern "C" void TIM2_IRQHandler()
{
	CallRealHandler(IRQ_TIM2);
}
       
extern "C" void TIM3_IRQHandler()
{
	CallRealHandler(IRQ_TIM3);
}
       
extern "C" void TIM4_IRQHandler()
{
	CallRealHandler(IRQ_TIM4);
}
          
extern "C" void I2C1_EV_IRQHandler()
{
	CallRealHandler(IRQ_I2C1_EV);
}
      
extern "C" void I2C1_ER_IRQHandler()
{
	CallRealHandler(IRQ_I2C1_ER);
}
  
extern "C" void I2C2_EV_IRQHandler()
{
	CallRealHandler(IRQ_I2C2_EV);
}
      
extern "C" void I2C2_ER_IRQHandler()
{
	CallRealHandler(IRQ_I2C2_ER);
}
     
extern "C" void SPI1_IRQHandler()
{
	CallRealHandler(IRQ_SPI1);
}
          
extern "C" void SPI2_IRQHandler()
{
	CallRealHandler(IRQ_SPI2);
}
         
extern "C" void USART1_IRQHandler()
{
	CallRealHandler(IRQ_USART1);
}
     
extern "C" void USART2_IRQHandler()
{
	CallRealHandler(IRQ_USART2);
}
      
extern "C" void USART3_IRQHandler()
{
	CallRealHandler(IRQ_USART3);
}
      
extern "C" void EXTI15_10_IRQHandler()
{
	CallRealHandler(IRQ_EXTI15_10);
}

extern "C" void RTCAlarm_IRQHandler()
{
	CallRealHandler(IRQ_RTCAlarm);
}
  
extern "C" void USBWakeUp_IRQHandler()
{
	CallRealHandler(IRQ_USBWakeUp);
}

#pragma arm section code //End