////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _S3C2416__GPIO_H_1
#define _S3C2416__GPIO_H_1   1


//////////////////////////////////////////////////////////////////////////////
// S3C2416_GPIO_Driver
//
typedef struct 
{
  __IO uint32_t GPIOCON ;//Configures the pins of port
  __IO uint32_t GPIODAT ;//The data register for port
  __IO uint32_t GPIOUDP ;//Pull-up/down control register for port B
  __IO uint32_t GPIOSEL ;//Selects the function of port B
  __IO uint32_t Reserved0;//
}  S3C2416_GPIO_TYPE

#define S3C2416_GPIOA_BASE  ELFIN_GPIO_BASE
#define S3C2416_GPIOB_BASE (ELFIN_GPIO_BASE + 0x10)
#define S3C2416_GPIOC_BASE (ELFIN_GPIO_BASE + 0x20)
#define S3C2416_GPIOD_BASE (ELFIN_GPIO_BASE + 0x30)
#define S3C2416_GPIOE_BASE (ELFIN_GPIO_BASE + 0x40)
#define S3C2416_GPIOF_BASE (ELFIN_GPIO_BASE + 0x50)
#define S3C2416_GPIOG_BASE (ELFIN_GPIO_BASE + 0x60)
#define S3C2416_GPIOH_BASE (ELFIN_GPIO_BASE + 0x70)
#define S3C2416_GPIOJ_BASE (ELFIN_GPIO_BASE + 0xd0)
#define S3C2416_GPIOK_BASE (ELFIN_GPIO_BASE + 0xe0)
#define S3C2416_GPIOL_BASE (ELFIN_GPIO_BASE + 0xf0)
#define S3C2416_GPIOM_BASE (ELFIN_GPIO_BASE + 0x100)

#define GPIOA  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOA_BASE)
#define GPIOB  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOB_BASE)
#define GPIOC  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOC_BASE)
#define GPIOD  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOD_BASE)
#define GPIOE  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOE_BASE)
#define GPIOF  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOF_BASE)
#define GPIOG  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOG_BASE)
#define GPIOH  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOH_BASE)
#define GPIOJ  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOJ_BASE)
#define GPIOK  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOK_BASE)
#define GPIOL  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOL_BASE)
#define GPIOM  ((S3C2416_GPIO_TYPE *) S3C2416_GPIOM_BASE)

struct S3C2416_GPIO_Driver
{
    struct PIN_ISR_DESCRIPTOR
    {

        HAL_COMPLETION                 m_completion;

        static const UINT32            c_DebounceCount = 3;

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

    //--//

    enum GPIO_NAMES {
        PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
        PA16, PA17, PA18, PA19, PA20, PA21, PA22, PA23, PA24, PA25, PA26, PA27, PA28, PA29, PA30, PA31,
        PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
        PB16, PB17, PB18, PB19, PB20, PB21, PB22, PB23, PB24, PB25, PB26, PB27, PB28, PB29, PB30, PB31,
        PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,
        PC16, PC17, PC18, PC19, PC20, PC21, PC22, PC23, PC24, PC25, PC26, PC27, PC28, PC29, PC30, PC31,     
        PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7, PD8, PD9, PD10, PD11, PD12, PD13, PD14, PD15, PD16, PD17, 
        PD18, PD19, PD20, PD21, PD22, PD23, PD24, PD25, PD26, PD27, PD28, PD29, PD30, PD31    
    };

    //--//

    static const UINT32 c_MaxPins           = S3C2416_MAX_GPIO;
    static const UINT32 c_MaxPorts          = S3C2416_MAX_PORT;
    static const UINT32 c_PinsPerPort       =  32;

    static const INT32  c_MinDebounceTimeMs =    1; // 1 ms
    static const INT32  c_MaxDebounceTimeMs = 5000; // 5  s

    //--//
    
    static const UINT8 c_Gpio_Attributes[c_MaxPins];

    // applies to all GPIO
    static const UINT8 c_NumberofResistorMode = 2;
    static const UINT8 c_GPIO_ResistorMode = (1<<RESISTOR_DISABLED) | (1<<RESISTOR_PULLUP);

    static const UINT8 c_NumberofInterruptMode = 5;
    static const UINT8 c_GPIO_InterruptMode = (1<<GPIO_INT_EDGE_LOW) | (1<<GPIO_INT_EDGE_HIGH ) | (1<<GPIO_INT_EDGE_BOTH) | (1<<GPIO_INT_LEVEL_HIGH) | (1<<GPIO_INT_LEVEL_LOW);

    PIN_ISR_DESCRIPTOR m_PinIsr[c_MaxPins ];
    UINT32             m_PinReservationInfo[c_MaxPorts];
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
	
	
    
private:

    static UINT32 PinToPort( GPIO_PIN pin )
    {
        ASSERT(pin < c_MaxPins);

        return pin / c_PinsPerPort;
    }

    static UINT32 PinToBit( GPIO_PIN pin )
    {
        ASSERT(pin < c_MaxPins);

        return pin % c_PinsPerPort;
    }

    static UINT32 BitToPin( UINT32 bit, UINT32 port )
    {
        ASSERT(bit  < c_PinsPerPort);
        ASSERT(port < c_MaxPorts);

        return bit + (port * c_PinsPerPort);
    }
   
    static UINT32 GetPort(UINT8 ports)
	{
	   switch(ports)
	   case 0 :return GPIOA;
                            	   break; 
	   case 1 :return GPIOB;
                            	   break; 
       case 2 :return GPIOC;
                            	   break; 
       case 3 :return GPIOD;
                            	   break; 
       case 4 :return GPIOE;
                            	   break; 
       case 5 :return GPIOF;
                            	   break; 
       case 6 :return GPIOG;
                            	   break; 
       case 7 :return GPIOH;
                            	   break; 
       case 8 :return GPIOJ;
                            	   break;
       case 9 :return GPIOK;
                            	   break;
       case 10:return GPIOL;
                            	   break;		
       case 11:return GPIOM;
                            	   break;	
       default:                    
	                               break;								   
	}
	
    static void STUB_GPIOISRVector( GPIO_PIN Pin, BOOL PinState, void* Param );
};

extern S3C2416_GPIO_Driver g_S3C2416_GPIO_Driver;
//
// S3C2416_GPIO_Driver
//////////////////////////////////////////////////////////////////////////////
#endif //_S3C2416__GPIO_H_1
