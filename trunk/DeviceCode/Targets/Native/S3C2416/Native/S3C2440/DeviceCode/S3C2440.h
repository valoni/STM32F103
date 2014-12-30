/*
 * S3C2440.h
 *
 *  Created on: 9.4.2011
 *      Author: Matti Eerola
 */

#ifndef S3C2440_H_
#define S3C2440_H_

//////////////////////////////////////////////////////////////////////////////
// S3C2440_POWER (CLOCK & POWER MANAGEMENT, see manual chapter 7)
//
struct S3C2440_POWER {
	static const UINT32 c_Base = 0x4C000000;

	// LOCK TIME COUNT REGISTER (LOCKTIME)
	/****/ volatile UINT32 LOCKTIME;

	// MPLL CONTROL REGISTER
	/****/ volatile UINT32 MPLLCON;

	// UPLL CONTROL REGISTER
	/****/ volatile UINT32 UPLLCON;

	// CLOCK CONTROL REGISTER (CLKCON)
	/****/ volatile UINT32 CLKCON;

	// CLOCK SLOW CONTROL
	/****/ volatile UINT32 CLKSLOW;

	// CLOCK DIVIDER CONTROL
	/****/ volatile UINT32 CLKDIVN;

	// CAMERA CLOCK DIVIDER
	/****/ volatile UINT32 CAMDIVN;
};
//
// S3C2440_POWER
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// S3C2440_AIC (see manual chapter 14)
//
struct S3C2440_AIC {
	static const UINT32 INT_INDEX_INT_ADC  = 31;
	static const UINT32 INT_INDEX_INT_RTC  = 30;
	static const UINT32 INT_INDEX_INT_SPI1  = 29;
	static const UINT32 INT_INDEX_INT_UART0  = 28;
	static const UINT32 INT_INDEX_INT_IIC  = 27;
	static const UINT32 INT_INDEX_INT_USBH  = 26;
	static const UINT32 INT_INDEX_INT_USBD  = 25;
	static const UINT32 INT_INDEX_INT_NFCON  = 24;
	static const UINT32 INT_INDEX_INT_UART1  = 23;
	static const UINT32 INT_INDEX_INT_SPI0  = 22;
	static const UINT32 INT_INDEX_INT_SDI  = 21;
	static const UINT32 INT_INDEX_INT_DMA3  = 20;
	static const UINT32 INT_INDEX_INT_DMA2  = 19;
	static const UINT32 INT_INDEX_INT_DMA1  = 18;
	static const UINT32 INT_INDEX_INT_DMA0  = 17;
	static const UINT32 INT_INDEX_INT_LCD  = 16;
	static const UINT32 INT_INDEX_INT_UART2  = 15;
	static const UINT32 INT_INDEX_INT_TIMER4  = 14;
	static const UINT32 INT_INDEX_INT_TIMER3  = 13;
	static const UINT32 INT_INDEX_INT_TIMER2  = 12;
	static const UINT32 INT_INDEX_INT_TIMER1  = 11;
	static const UINT32 INT_INDEX_INT_TIMER0  = 10;
	static const UINT32 INT_INDEX_INT_WDT_AC97  = 9;
	static const UINT32 INT_INDEX_INT_TICK  = 8;
	static const UINT32 INT_INDEX_nBATT_FLT  = 7;
	static const UINT32 INT_INDEX_INT_CAM  = 6;
	static const UINT32 INT_INDEX_EINT8_23  = 5;
	static const UINT32 INT_INDEX_EINT4_7  = 4;
	static const UINT32 INT_INDEX_EINT3  = 3;
	static const UINT32 INT_INDEX_EINT2  = 2;
	static const UINT32 INT_INDEX_EINT1  = 1;
	static const UINT32 INT_INDEX_EINT0  = 0;

	static const UINT32 c_Base = 0x4A000000;

	// SOURCE PENDING (SRCPND) REGISTER
	/****/ volatile UINT32 SRCPND;

	// INTERRUPT MODE (INTMOD) REGISTER
	/****/ volatile UINT32 INTMOD;

	// INTERRUPT MASK (INTMSK) REGISTER
	/****/ volatile UINT32 INTMSK;

	// PRIORITY REGISTER (PRIORITY)
	/****/ volatile UINT32 PRIORITY;

	// INTERRUPT PENDING (INTPND) REGISTER
	/****/ volatile UINT32 INTPND;

	// INTERRUPT OFFSET (INTOFFSET) REGISTER
	/****/ volatile UINT32 INTOFFSET;

	// SUB SOURCE PENDING (SUBSRCPND) REGISTER
	/****/ volatile UINT32 SUBSRCPND;

	// INTERRUPT SUB MASK (INTSUBMSK) REGISTER
	/****/ volatile UINT32 INTSUBMSK;

    void SubInterruptEnable(UINT32 SubIrq_Index) { INTSUBMSK &= ~(1 << SubIrq_Index); }
    void SubInterruptDisable(UINT32 SubIrq_Index) { INTSUBMSK |= (1 << SubIrq_Index); }
};

//
// S3C2440_AIC
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// S3C2440_USART (see manual chapter 11)
//
struct S3C2440_USART {
	static const UINT32 c_Base = 0x50000000;
	static const UINT32 c_Base_offset = 0x4000;

	// UART LINE CONTROL REGISTER
	/****/ volatile UINT32 ULCON;

	// UART CONTROL REGISTER
	/****/ volatile UINT32 UCON;

	// UART FIFO CONTROL REGISTER
	/****/ volatile UINT32 UFCON;

	// UART MODEM CONTROL REGISTER
	/****/ volatile UINT32 UMCON;

	// UART TX/RX STATUS REGISTER
	/****/ volatile UINT32 UTRSTAT;

	// UART ERROR STATUS REGISTER
	/****/ volatile UINT32 UERSTAT;

	// UART FIFO STATUS REGISTER
	/****/ volatile UINT32 UFSTAT;

	// UART MODEM STATUS REGISTER
	/****/ volatile UINT32 UMSTAT;

#ifdef __BIG_ENDIAN
	/****/ volatile UINT8 res1[3];

	// UART TRANSMIT BUFFER REGISTER (HOLDING REGISTER & FIFO REGISTER)
	/****/ volatile UINT8 UTXH;

	/****/ volatile UINT8 res2[3];

	// UART RECEIVE BUFFER REGISTER (HOLDING REGISTER & FIFO REGISTER)
	/****/ volatile UINT8 URXH;

#else // Little Endian
	// UART TRANSMIT BUFFER REGISTER (HOLDING REGISTER & FIFO REGISTER)
	/****/ volatile UINT8 UTXH;

	/****/ volatile UINT8 res1[3];

	// UART RECEIVE BUFFER REGISTER (HOLDING REGISTER & FIFO REGISTER)
	/****/ volatile UINT8 URXH;

	/****/ volatile UINT8 res2[3];
#endif
	// UART BAUD RATE DIVISOR REGISTER
	/****/ volatile UINT32 UBRDIV;
};
//
// S3C2440_USART
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// S3C2440_TIMER (PWM TIMER, see manual chapter 10)
//
struct S3C2440_TIMER_COUNT {
	// Timer count buffer register
	/****/ volatile UINT32 TCNTB;

	// Timer compare buffer register
	/****/ volatile UINT32 TCMPB;

	// Timer count observation register
	/****/ volatile UINT32 TCNTO;
};

struct S3C2440_TIMER {
	static const UINT32 c_Base = 0x51000000;

	// TIMER CONFIGURATION REGISTER0 (TCFG0)
	/****/ volatile UINT32 TCFG0;

	// TIMER CONFIGURATION REGISTER1 (TCFG1)
	/****/ volatile UINT32 TCFG1;

	// TIMER CONTROL (TCON) REGISTER
	/****/ volatile UINT32 TCON;

	// TIMER CONTROL (TCON) REGISTER
	/****/ volatile S3C2440_TIMER_COUNT TIMER[4];

	// TODO: timer 4
};
//
// S3C2440_TIMER
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// S3C2440_RTC (see manual chapter 17)
//
struct S3C2440_RTC {
	static const UINT32 c_Base = 0x57000040;

#ifdef __BIG_ENDIAN
	/****/ volatile UINT8 res1[3];
	// REAL TIME CLOCK CONTROL (RTCCON) REGISTER
	/****/ volatile UINT8 RTCCON;
#else // Little Endian
	// REAL TIME CLOCK CONTROL (RTCCON) REGISTER
	/****/ volatile UINT8 RTCCON;
	/****/ volatile UINT8 res1[3];
#endif

#ifdef __BIG_ENDIAN
	/****/ volatile UINT8 res2[3];
	// TICK TIME COUNT (TICNT) REGISTER
	/****/ volatile UINT32 TICNT;
#else // Little Endian
	// TICK TIME COUNT (TICNT) REGISTER
	/****/ volatile UINT32 TICNT;
	/****/ volatile UINT8 res2[3];
#endif


	//ETC..
};

//
// S3C2440_RTC
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// GP I/O
//
// S3C2440A has 130 multi-functional input/output port pins and there are eight ports as shown below:
// — Port A/0(GPA): 25-output port
// — Port B/1(GPB): 11-input/out port
// — Port C/2(GPC): 16-input/output port
// — Port D/3(GPD): 16-input/output port
// — Port E/4(GPE): 16-input/output port
// — Port F/5(GPF): 8-input/output port
// — Port G/6(GPG): 16-input/output port
// — Port H/7(GPH): 9-input/output port
// — Port J/8(GPJ): 13-input/output port

struct S3C2440_GPIO_PORT
{
	// Pin mode configuration
	/****/ volatile UINT32 GPCON;
	// Data register
	/****/ volatile UINT32 GPDAT;
	// Pull-up disable register
	/****/ volatile UINT32 GPUP;

	/****/ volatile UINT32 reserved1;

};

struct S3C2440_GPIO
{
	static const UINT32 c_Base = 0x56000000;

	// Ports A ~ J
	/****/ S3C2440_GPIO_PORT PORTS[9];

	// Miscellaneous control
	/****/ volatile UINT32 MISCCR;

	// DCLK0/1 control
	/****/ volatile UINT32 DCLKCON;

	// External interrupt control register
	/****/ volatile UINT32 EXTINT[3];

	// External interrupt filter control
	/****/ volatile UINT32 EINTFLT[4];

	// External interrupt mask
	/****/ volatile UINT32 EINTMASK;

	// External interrupt pending
	/****/ volatile UINT32 EINTPEND;

};

//
// GP I/O
//////////////////////////////////////////////////////////////////////////////

struct S3C2440
{
    static S3C2440_POWER	& POWER()             { return *(S3C2440_POWER*)(size_t)(S3C2440_POWER::c_Base);}
    static S3C2440_AIC	& AIC()             { return *(S3C2440_AIC*)(size_t)(S3C2440_AIC::c_Base);}
    static S3C2440_USART   & USART( int sel )  { return *(S3C2440_USART*)(size_t)(S3C2440_USART::c_Base + (sel * S3C2440_USART::c_Base_offset));}
    static S3C2440_TIMER	& TIMER()             { return *(S3C2440_TIMER*)(size_t)(S3C2440_TIMER::c_Base);}
    static S3C2440_RTC	& RTC()             { return *(S3C2440_RTC*)(size_t)(S3C2440_RTC::c_Base);}
    static S3C2440_GPIO	& GPIO()             { return *(S3C2440_GPIO*)(size_t)(S3C2440_GPIO::c_Base);}

    // Debug utils (Send data to COM1 that is initialized by U-Boot)

    //Send byte to COM1
    static void Debug_SendByte(unsigned char data);
    static void Debug_printf( const char* format, ... );
};



// DRIVER DEFINITIONS

//////////////////////////////////////////////////////////////////////////////
// S3C2440_AIC  driver
//
struct S3C2440_AIC_Driver
{
    static const UINT32 c_VECTORING_GUARD = 32;
    static const UINT32 c_MaxInterruptIndex = 32;

    //--//
    struct IRQ_VECTORING
    {
        UINT32       Priority;
        HAL_CALLBACK Handler;
    };

    //--//
    static IRQ_VECTORING s_IsrTable[];

    //--//
    static void Initialize();
    static BOOL ActivateInterrupt(UINT32 Irq_Index, BOOL Fast, HAL_CALLBACK_FPN ISR, void* ISR_Param);
    static BOOL DeactivateInterrupt(UINT32 Irq_Index);
    static BOOL InterruptEnable(UINT32 Irq_Index);
    static BOOL InterruptDisable(UINT32 Irq_Index );
    static BOOL InterruptEnableState( UINT32 Irq_Index );
    static BOOL InterruptState(UINT32 Irq_Index );
    static void /*__irq*/ IRQ_Handler(void);
    static IRQ_VECTORING* IRQToIRQVector( UINT32 IRQ );

    static void ForceInterrupt(UINT32 Irq_Index )
    {
    	ASSERT(FALSE); //TODO: implement this
    }

    static void RemoveForcedInterrupt(UINT32 Irq_Index )
    {
    	S3C2440_AIC &aic = S3C2440::AIC();
    	unsigned int clearBit = (1 << Irq_Index);
        aic.SRCPND = clearBit;
        aic.INTPND = clearBit;
        aic.SUBSRCPND = aic.SUBSRCPND;
    }

private:
    static void STUB_ISRVector( void* Param );
};
//
// S3C2440_AIC  driver
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// S3C2440 TIMER driver
//
//TODO: Implement this. I created this for TIME driver, but it didn't need timers..
struct S3C2440_TIMER_Driver
{
	const static UINT32 TIMER_DIV2 = 0;
	const static UINT32 TIMER_DIV4 = 1;
	const static UINT32 TIMER_DIV8 = 2;
	const static UINT32 TIMER_DIV16 = 3;

    const static UINT32 c_MaxTimers = 4; // timer 4 is special so leave it out from this (use only timers 0~3)
#if defined(FIQ_SAMPLING_PROFILER)
    HAL_COMPLETION m_dump;
#endif

    //--//

    BOOL m_configured[c_MaxTimers];

    static BOOL   Initialize   ( UINT32 Timer, BOOL FreeRunning, UINT32 ClkSource, HAL_CALLBACK_FPN ISR, void* ISR_Param );
    static BOOL   Uninitialize ( UINT32 Timer );
    static UINT32 ReadCounter  ( UINT32 Timer );

};

extern S3C2440_TIMER_Driver g_S3C2440_TIMER_Driver;

//
// TIMER driver
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// GP I/O driver
// S3C2440A has 130 multi-functional input/output port pins and there are eight ports as shown below:
// — Port A/0(GPA): 25-output port
// — Port B/1(GPB): 11-input/out port
// — Port C/2(GPC): 16-input/output port
// — Port D/3(GPD): 16-input/output port
// — Port E/4(GPE): 16-input/output port
// — Port F/5(GPF): 8-input/output port
// — Port G/6(GPG): 16-input/output port
// — Port H/7(GPH): 9-input/output port
// — Port J/8(GPJ): 13-input/output port

struct S3C2440_GPIO_Driver
{
    struct PIN_ISR_DESCRIPTOR
    {
        HAL_COMPLETION                 m_completion;
        GPIO_INTERRUPT_SERVICE_ROUTINE m_isr;
        void*                          m_param;
        GPIO_PIN                       m_pin;
        GPIO_INT_EDGE                  m_intEdge;
        UINT8                          m_flags;
        UINT8                          m_status;

        //--//

        static const UINT8 c_Flags_Debounce        = 0x01;
        static const UINT8 c_Flags_RequireLowEdge  = 0x02;
        static const UINT8 c_Flags_RequireHighEdge = 0x04;

        static const UINT8 c_Status_AllowLowEdge   = 0x01;
        static const UINT8 c_Status_AllowHighEdge  = 0x02;

        //--//

        static void Fire( void* arg );

        void HandleDebounce( BOOL edge );
    };

    struct PORT_HANDLER
    {
    	BOOL OnlyOutput;
    	S3C2440_GPIO_PORT& port;

        //--//

    	BOOL SetInput(UINT32 bit);
    	void SetOutput(UINT32 bit);
    	void SetAltFunction(UINT32 bit, GPIO_ALT_MODE AltFunction);
    	void SetBitState(UINT32 bit, BOOL state);
    	BOOL GetBitState(UINT32 bit);
    };

    //--//

    static const UINT32 c_MaxPins           = 130;
    static const UINT32 c_MaxPorts          =   9;
    static const UINT8  c_PinsInPort[c_MaxPorts];

    static const INT32  c_MinDebounceTimeMs =    1; // 1 ms
    static const INT32  c_MaxDebounceTimeMs = 5000; // 5  s

    //--//

    static const UINT8 c_Gpio_Attributes[c_MaxPins];

    // this applies to all GPIO pins
    static const UINT8 c_NumberofResistorMode = 2;
    static const UINT8 c_GPIO_ResistorMode=(1<<RESISTOR_DISABLED) | (1<<RESISTOR_PULLUP);

    static const UINT8 c_NumberofInterruptMode = 5;
    static const UINT8 c_GPIO_InterruptMode=(1<<GPIO_INT_EDGE_LOW) | (1<<GPIO_INT_EDGE_HIGH ) | (1<<GPIO_INT_EDGE_BOTH) | (1<<GPIO_INT_LEVEL_HIGH) | (1<<GPIO_INT_LEVEL_LOW);

    static const UINT32 c_Alt_Max_Mode       = 7;

    static const UINT32 GPIO_MODE_TO_S3C2440_MODE[c_Alt_Max_Mode];
    // --//

    PIN_ISR_DESCRIPTOR m_PinIsr            [c_MaxPins ];
    UINT32             m_PinReservationInfo[(c_MaxPins >> 5)+1];
    UINT32             m_DebounceTicks;

    //--//

    static BOOL Initialize  ();

    static BOOL Uninitialize();

    static UINT32 Attributes( GPIO_PIN Pin );

    static void DisablePin( GPIO_PIN Pin, GPIO_RESISTOR ResistorState, UINT32 direction, GPIO_ALT_MODE AltFunction );

    static void EnableOutputPin( GPIO_PIN Pin, BOOL InitialState );

    static BOOL EnableInputPin( GPIO_PIN Pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR, void* ISR_Param, GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState );

    static BOOL GetPinState( GPIO_PIN Pin );

    static void SetPinState( GPIO_PIN Pin, BOOL PinState );

    static void ISR( void* Param );

    static void SetResistor( GPIO_PIN Pin, GPIO_RESISTOR ResistorState );

    static BOOL PinIsBusy( GPIO_PIN Pin );

    static BOOL ReservePin( GPIO_PIN Pin, BOOL fReserve );

    static UINT32 GetDebounce();

    static BOOL SetDebounce( INT64 debounceTimeMilliseconds );

    static void GetPinsMap( UINT8* pins, size_t size );

    static UINT8 GetSupportedResistorModes( GPIO_PIN pin );

    static UINT8 GetSupportedInterruptModes( GPIO_PIN pin );

    // public for testing
    static UINT8 PinToPort( GPIO_PIN pin );
    static UINT32 PinToBit( GPIO_PIN pin );
    static UINT32 BitToPin( UINT32 bit, UINT8 port );

private:


    static void STUB_GPIOISRVector( GPIO_PIN Pin, BOOL PinState, void* Param );

    static S3C2440_GPIO_Driver::PORT_HANDLER GetPort(UINT8 port);
};

extern S3C2440_GPIO_Driver g_S3C2440_GPIO_Driver;

//
// GP I/O driver
//////////////////////////////////////////////////////////////////////////////


#endif /* S3C2440_H_ */
