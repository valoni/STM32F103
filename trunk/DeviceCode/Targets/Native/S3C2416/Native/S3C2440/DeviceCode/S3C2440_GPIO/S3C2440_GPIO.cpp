/*
 * S3C2440_GPIO.cpp
 *
 *  Created on: 1.6.2011
 *      Author: Matti Eerola
 */

#include <tinyhal.h>
#include "..\S3C2440.h"

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata = "c_Gpio_Attributes_S3C2440"
#endif

const UINT8 __section(rodata) S3C2440_GPIO_Driver::c_Gpio_Attributes[S3C2440_GPIO_Driver::c_MaxPins] =
{
		GPIO_ATTRIBUTE_NONE                         , // 0,  GPA0  :  Output only  / ADDR0
		GPIO_ATTRIBUTE_NONE                         , // 1,  GPA1  :  Output only  / ADDR16
		GPIO_ATTRIBUTE_NONE                         , // 2,  GPA2  :  Output only  / ADDR17
		GPIO_ATTRIBUTE_NONE                         , // 3,  GPA3  :  Output only  / ADDR18
		GPIO_ATTRIBUTE_NONE                         , // 4,  GPA4  :  Output only  / ADDR19
		GPIO_ATTRIBUTE_NONE                         , // 5,  GPA5  :  Output only  / ADDR20
		GPIO_ATTRIBUTE_NONE                         , // 6,  GPA6  :  Output only  / ADDR21
		GPIO_ATTRIBUTE_NONE                         , // 7,  GPA7  :  Output only  / ADDR22
		GPIO_ATTRIBUTE_NONE                         , // 8,  GPA8  :  Output only  / ADDR23
		GPIO_ATTRIBUTE_NONE                         , // 9,  GPA9  :  Output only  / ADDR24
		GPIO_ATTRIBUTE_NONE                         , // 10,  GPA10  :  Output only  / ADDR25
		GPIO_ATTRIBUTE_NONE                         , // 11,  GPA11  :  Output only  / ADDR26
		GPIO_ATTRIBUTE_NONE                         , // 12,  GPA12  :  Output only  / nGCS1
		GPIO_ATTRIBUTE_NONE                         , // 13,  GPA13  :  Output only  / nGCS2
		GPIO_ATTRIBUTE_NONE                         , // 14,  GPA14  :  Output only  / nGCS3
		GPIO_ATTRIBUTE_NONE                         , // 15,  GPA15  :  Output only  / nGCS4
		GPIO_ATTRIBUTE_NONE                         , // 16,  GPA16  :  Output only  / nGCS5
		GPIO_ATTRIBUTE_NONE                         , // 17,  GPA17  :  Output only  / CLE
		GPIO_ATTRIBUTE_NONE                         , // 18,  GPA18  :  Output only  / ALE
		GPIO_ATTRIBUTE_NONE                         , // 19,  GPA19  :  Output only  / nFWE
		GPIO_ATTRIBUTE_NONE                         , // 20,  GPA20  :  Output only  / nFRE
		GPIO_ATTRIBUTE_NONE                         , // 21,  GPA21  :  Output only  / nRSTOUT
		GPIO_ATTRIBUTE_NONE                         , // 22,  GPA22  :  Output only  / nFCE
		GPIO_ATTRIBUTE_NONE                         , // 23,  GPB0  :  Input/output  / TOUT0
		GPIO_ATTRIBUTE_NONE                         , // 24,  GPB1  :  Input/output  / TOUT1
		GPIO_ATTRIBUTE_NONE                         , // 25,  GPB2  :  Input/output  / TOUT2
		GPIO_ATTRIBUTE_NONE                         , // 26,  GPB3  :  Input/output  / TOUT3
		GPIO_ATTRIBUTE_NONE                         , // 27,  GPB4  :  Input/output  / TCLK0
		GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 28,  GPB5  :  Input/output  / nXBACK
		GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 29,  GPB6  :  Input/output  / nXBREQ
		GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 30,  GPB7  :  Input/output  / nXDACK1
		GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 31,  GPB8  :  Input/output  / nXDREQ1
		GPIO_ATTRIBUTE_NONE                         , // 32,  GPB9  :  Input/output  / nXDACK0
		GPIO_ATTRIBUTE_NONE                         , // 33,  GPB10  :  Input/output  / nXDREQ0
		GPIO_ATTRIBUTE_NONE                         , // 34,  GPC0  :  Input/output  / LEND
		GPIO_ATTRIBUTE_NONE                         , // 35,  GPC1  :  Input/output  / VCLK
		GPIO_ATTRIBUTE_NONE                         , // 36,  GPC2  :  Input/output  / VLINE
		GPIO_ATTRIBUTE_NONE                         , // 37,  GPC3  :  Input/output  / VFRAME
		GPIO_ATTRIBUTE_NONE                         , // 38,  GPC4  :  Input/output  / VM
		GPIO_ATTRIBUTE_NONE                         , // 39,  GPC5  :  Input/output  / LCD_LPCOE
		GPIO_ATTRIBUTE_NONE                         , // 40,  GPC6  :  Input/output  / LCD_LPCREV
		GPIO_ATTRIBUTE_NONE                         , // 41,  GPC7  :  Input/output  / LCD_LPCREVB
		GPIO_ATTRIBUTE_NONE                         , // 42,  GPC8  :  Input/output  / VD0
		GPIO_ATTRIBUTE_NONE                         , // 43,  GPC9  :  Input/output  / VD1
		GPIO_ATTRIBUTE_NONE                         , // 44,  GPC10  :  Input/output  / VD2
		GPIO_ATTRIBUTE_NONE                         , // 45,  GPC11  :  Input/output  / VD3
		GPIO_ATTRIBUTE_NONE                         , // 46,  GPC12  :  Input/output  / VD4
		GPIO_ATTRIBUTE_NONE                         , // 47,  GPC13  :  Input/output  / VD5
		GPIO_ATTRIBUTE_NONE                         , // 48,  GPC14  :  Input/output  / VD6
		GPIO_ATTRIBUTE_NONE                         , // 49,  GPC15  :  Input/output  / VD7
		GPIO_ATTRIBUTE_NONE                         , // 50,  GPD0  :  Input/output  / VD8
		GPIO_ATTRIBUTE_NONE                         , // 51,  GPD1  :  Input/output  / VD9
		GPIO_ATTRIBUTE_NONE                         , // 52,  GPD2  :  Input/output  / VD10
		GPIO_ATTRIBUTE_NONE                         , // 53,  GPD3  :  Input/output  / VD11
		GPIO_ATTRIBUTE_NONE                         , // 54,  GPD4  :  Input/output  / VD12
		GPIO_ATTRIBUTE_NONE                         , // 55,  GPD5  :  Input/output  / VD13
		GPIO_ATTRIBUTE_NONE                         , // 56,  GPD6  :  Input/output  / VD14
		GPIO_ATTRIBUTE_NONE                         , // 57,  GPD7  :  Input/output  / VD15
		GPIO_ATTRIBUTE_NONE                         , // 58,  GPD8  :  Input/output  / VD16  / SPIMISO1
		GPIO_ATTRIBUTE_NONE                         , // 59,  GPD9  :  Input/output  / VD17  / SPIMOSI1
		GPIO_ATTRIBUTE_NONE                         , // 60,  GPD10  :  Input/output  / VD18  / SPICLK1
		GPIO_ATTRIBUTE_NONE                         , // 61,  GPD11  :  Input/output  / VD19
		GPIO_ATTRIBUTE_NONE                         , // 62,  GPD12  :  Input/output  / VD20
		GPIO_ATTRIBUTE_NONE                         , // 63,  GPD13  :  Input/output  / VD21
		GPIO_ATTRIBUTE_NONE                         , // 64,  GPD14  :  Input/output  / VD22  / nSS1
		GPIO_ATTRIBUTE_NONE                         , // 65,  GPD15  :  Input/output  / VD23  / nSS0
		GPIO_ATTRIBUTE_NONE                         , // 66,  GPE0  :  Input/output  / I2SLRCK  / AC_SYNC
		GPIO_ATTRIBUTE_NONE                         , // 67,  GPE1  :  Input/output  / I2SSCLK  / AC_BIT_CLK
		GPIO_ATTRIBUTE_NONE                         , // 68,  GPE2  :  Input/output  / CDCLK  / AC_nRESET
		GPIO_ATTRIBUTE_NONE                         , // 69,  GPE3  :  Input/output  / I2SSDI  / AC_SDATA_IN
		GPIO_ATTRIBUTE_NONE                         , // 70,  GPE4  :  Input/output  / I2SSDO  / AC_SDATA_OUT
		GPIO_ATTRIBUTE_NONE                         , // 71,  GPE5  :  Input/output  / SDCLK
		GPIO_ATTRIBUTE_NONE                         , // 72,  GPE6  :  Input/output  / SDCMD
		GPIO_ATTRIBUTE_NONE                         , // 73,  GPE7  :  Input/output  / SDDAT0
		GPIO_ATTRIBUTE_NONE                         , // 74,  GPE8  :  Input/output  / SDDAT1
		GPIO_ATTRIBUTE_NONE                         , // 75,  GPE9  :  Input/output  / SDDAT2
		GPIO_ATTRIBUTE_NONE                         , // 76,  GPE10  :  Input/output  / SDDAT3
		GPIO_ATTRIBUTE_NONE                         , // 77,  GPE11  :  Input/output  / SPIMISO0
		GPIO_ATTRIBUTE_NONE                         , // 78,  GPE12  :  Input/output  / SPIMOSI0
		GPIO_ATTRIBUTE_NONE                         , // 79,  GPE13  :  Input/output  / SPICLK0
		GPIO_ATTRIBUTE_NONE                         , // 80,  GPE14  :  Input/output  / IICSCL
		GPIO_ATTRIBUTE_NONE                         , // 81,  GPE15  :  Input/output  / IICSDA
		GPIO_ATTRIBUTE_NONE                         , // 82,  GPF0  :  Input/output  / EINT0  //NOTICE! EINT[15:0] are used for wakeup sources.
		GPIO_ATTRIBUTE_NONE                         , // 83,  GPF1  :  Input/output  / EINT1
		GPIO_ATTRIBUTE_NONE                         , // 84,  GPF2  :  Input/output  / EINT2
		GPIO_ATTRIBUTE_NONE                         , // 85,  GPF3  :  Input/output  / EINT3
		GPIO_ATTRIBUTE_NONE                         , // 86,  GPF4  :  Input/output  / EINT4
		GPIO_ATTRIBUTE_NONE                         , // 87,  GPF5  :  Input/output  / EINT5
		GPIO_ATTRIBUTE_NONE                         , // 88,  GPF6  :  Input/output  / EINT6
		GPIO_ATTRIBUTE_NONE                         , // 89,  GPF7  :  Input/output  / EINT7
		GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 90,  GPG0  :  Input/output  / EINT8
		GPIO_ATTRIBUTE_NONE                         , // 91,  GPG1  :  Input/output  / EINT9
		GPIO_ATTRIBUTE_NONE                         , // 92,  GPG2  :  Input/output  / EINT10  / nSS0
		GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 93,  GPG3  :  Input/output  / EINT11  / nSS1
		GPIO_ATTRIBUTE_NONE                         , // 94,  GPG4  :  Input/output  / EINT12  / LCD_PWREN
		GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 95,  GPG5  :  Input/output  / EINT13  / SPIMISO1
		GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 96,  GPG6  :  Input/output  / EINT14  / SPIMOSI1
		GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 97,  GPG7  :  Input/output  / EINT15  / SPICLK1
		GPIO_ATTRIBUTE_NONE                         , // 98,  GPG8  :  Input/output  / EINT16
		GPIO_ATTRIBUTE_NONE                         , // 99,  GPG9  :  Input/output  / EINT17  / nRTS1
		GPIO_ATTRIBUTE_NONE                         , // 100,  GPG10  :  Input/output  / EINT18  / nCTS1
		GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, // 101,  GPG11  :  Input/output  / EINT19  / TCLK1
		GPIO_ATTRIBUTE_NONE                         , // 102,  GPG12  :  Input/output  / EINT20
		GPIO_ATTRIBUTE_NONE                         , // 103,  GPG13  :  Input/output  / EINT21
		GPIO_ATTRIBUTE_NONE                         , // 104,  GPG14  :  Input/output  / EINT22
		GPIO_ATTRIBUTE_NONE                         , // 105,  GPG15  :  Input/output  / EINT23
		GPIO_ATTRIBUTE_NONE                         , // 106,  GPH0  :  Input/output  / nCTS0
		GPIO_ATTRIBUTE_NONE                         , // 107,  GPH1  :  Input/output  / nRTS0
		GPIO_ATTRIBUTE_NONE                         , // 108,  GPH2  :  Input/output  / TXD0
		GPIO_ATTRIBUTE_NONE                         , // 109,  GPH3  :  Input/output  / RXD0
		GPIO_ATTRIBUTE_NONE                         , // 110,  GPH4  :  Input/output  / TXD1
		GPIO_ATTRIBUTE_NONE                         , // 111,  GPH5  :  Input/output  / RXD1
		GPIO_ATTRIBUTE_NONE                         , // 112,  GPH6  :  Input/output  / TXD2  / nRTS1
		GPIO_ATTRIBUTE_NONE                         , // 113,  GPH7  :  Input/output  / RXD2  / nCTS1
		GPIO_ATTRIBUTE_NONE                         , // 114,  GPH8  :  Input/output  / UEXTCLK
		GPIO_ATTRIBUTE_NONE                         , // 115,  GPH9  :  Input/output  / CLKOUT0
		GPIO_ATTRIBUTE_NONE                         , // 116,  GPH10  :  Input/output  / CLKOUT1
		GPIO_ATTRIBUTE_NONE                         , // 117,  GPJ0  :  Input/output  / CAMDATA0
		GPIO_ATTRIBUTE_NONE                         , // 118,  GPJ1  :  Input/output  / CAMDATA1
		GPIO_ATTRIBUTE_NONE                         , // 119,  GPJ2  :  Input/output  / CAMDATA2
		GPIO_ATTRIBUTE_NONE                         , // 120,  GPJ3  :  Input/output  / CAMDATA3
		GPIO_ATTRIBUTE_NONE                         , // 121,  GPJ4  :  Input/output  / CAMDATA4
		GPIO_ATTRIBUTE_NONE                         , // 122,  GPJ5  :  Input/output  / CAMDATA5
		GPIO_ATTRIBUTE_NONE                         , // 123,  GPJ6  :  Input/output  / CAMDATA6
		GPIO_ATTRIBUTE_NONE                         , // 124,  GPJ7  :  Input/output  / CAMDATA7
		GPIO_ATTRIBUTE_NONE                         , // 125,  GPJ8  :  Input/output  / CAMPCLK
		GPIO_ATTRIBUTE_NONE                         , // 126,  GPJ9  :  Input/output  / CAMVSYNC
		GPIO_ATTRIBUTE_NONE                         , // 127,  GPJ10  :  Input/output  / CAMHREF
		GPIO_ATTRIBUTE_NONE                         , // 128,  GPJ11  :  Input/output  / CAMCLKOUT
		GPIO_ATTRIBUTE_NONE                           // 129,  GPJ12  :  Input/output  / CAMRESET
};

const UINT8 __section(rodata) S3C2440_GPIO_Driver::c_PinsInPort[S3C2440_GPIO_Driver::c_MaxPorts] = {
		23, // — Port A/0(GPA): 25-output port (2 ports are only reserved registers)
		11, // — Port B/1(GPB): 11-input/out port
		16, // — Port C/2(GPC): 16-input/output port
		16, // — Port D/3(GPD): 16-input/output port
		16, // — Port E/4(GPE): 16-input/output port
		8,  // — Port F/5(GPF): 8-input/output port
		16, // — Port G/6(GPG): 16-input/output port
		9,  // — Port H/7(GPH): 9-input/output port
		13  // — Port J/8(GPJ): 13-input/output port
};

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_S3C2440_GPIO_Driver"
#endif

S3C2440_GPIO_Driver g_S3C2440_GPIO_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif

BOOL S3C2440_GPIO_Driver::Initialize()
{
	NATIVE_PROFILE_HAL_PROCESSOR_GPIO();

    int i;

    // initialize the interrupt information for all pins
    {
        PIN_ISR_DESCRIPTOR* pinIsr = g_S3C2440_GPIO_Driver.m_PinIsr;

        for(i = 0; i < c_MaxPins; i++)
        {
            pinIsr->m_pin     = i;
            pinIsr->m_intEdge = GPIO_INT_NONE;
            pinIsr->m_isr     = STUB_GPIOISRVector;
            pinIsr->m_param   = NULL;

            pinIsr->m_completion.InitializeForISR( &PIN_ISR_DESCRIPTOR::Fire, pinIsr );

            pinIsr++;
        }
    }

    // Because each external interrupt pin has a digital filter,
    // the interrupt controller can recognize the request signal that is longer than 3 clocks.
    //SetDebounce( 20 );

    for(i = 0; i < (c_MaxPins >> 5)+1; i++)
    {
        // initialize pins as free
        g_S3C2440_GPIO_Driver.m_PinReservationInfo[i] = 0;
    }

    // register interrupt handler for all ports
    if(!CPU_INTC_ActivateInterrupt( S3C2440_AIC::INT_INDEX_EINT0, ISR, NULL)) return FALSE;
    if(!CPU_INTC_ActivateInterrupt( S3C2440_AIC::INT_INDEX_EINT1, ISR, NULL)) return FALSE;
    if(!CPU_INTC_ActivateInterrupt( S3C2440_AIC::INT_INDEX_EINT2, ISR, NULL)) return FALSE;
    if(!CPU_INTC_ActivateInterrupt( S3C2440_AIC::INT_INDEX_EINT3, ISR, NULL)) return FALSE;
    if(!CPU_INTC_ActivateInterrupt( S3C2440_AIC::INT_INDEX_EINT4_7, ISR, NULL)) return FALSE;
    if(!CPU_INTC_ActivateInterrupt( S3C2440_AIC::INT_INDEX_EINT8_23, ISR, NULL)) return FALSE;


    S3C2440_GPIO& gpio = S3C2440::GPIO();
    gpio.EINTMASK = 0; //enable all external interrupts

    return TRUE;
}


BOOL S3C2440_GPIO_Driver::Uninitialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    GLOBAL_LOCK(irq);

    S3C2440_GPIO& gpio = S3C2440::GPIO();
    gpio.EINTMASK = 0x000fffff; //disable all external interrupts

    if(!CPU_INTC_DeactivateInterrupt( S3C2440_AIC::INT_INDEX_EINT0 )) return FALSE;
    if(!CPU_INTC_DeactivateInterrupt( S3C2440_AIC::INT_INDEX_EINT1 )) return FALSE;
    if(!CPU_INTC_DeactivateInterrupt( S3C2440_AIC::INT_INDEX_EINT2 )) return FALSE;
    if(!CPU_INTC_DeactivateInterrupt( S3C2440_AIC::INT_INDEX_EINT3 )) return FALSE;
    if(!CPU_INTC_DeactivateInterrupt( S3C2440_AIC::INT_INDEX_EINT4_7 )) return FALSE;
    if(!CPU_INTC_DeactivateInterrupt( S3C2440_AIC::INT_INDEX_EINT8_23 )) return FALSE;

    return TRUE;
}

UINT32 S3C2440_GPIO_Driver::Attributes( GPIO_PIN Pin )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    if(Pin < c_MaxPins)
    {
        return c_Gpio_Attributes[Pin];
    }

    return GPIO_ATTRIBUTE_NONE;
}

void S3C2440_GPIO_Driver::GetPinsMap( UINT8* pins, size_t size )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();

    const UINT8*    src = c_Gpio_Attributes;
    UINT8* dst = pins;
    UINT32 maxpin = c_MaxPins;

    if ( size ==0 ) return;
    while ((size--) && (maxpin --))
    {
        *dst = *src;
        ++dst; ++src;
    }
}

UINT8 S3C2440_GPIO_Driver::GetSupportedResistorModes( GPIO_PIN pin)
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    if (!(Attributes(pin) & GPIO_ATTRIBUTE_INPUT)) return 1 << RESISTOR_DISABLED;
    return S3C2440_GPIO_Driver::c_GPIO_ResistorMode;
}


UINT8 S3C2440_GPIO_Driver::GetSupportedInterruptModes( GPIO_PIN pin)
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    if (pin < 82 || pin > 105) return GPIO_INT_NONE;
    return S3C2440_GPIO_Driver::c_GPIO_InterruptMode;
}

void S3C2440_GPIO_Driver::DisablePin( GPIO_PIN pin, GPIO_RESISTOR resistorState, UINT32 direction, GPIO_ALT_MODE AltFunction )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    ASSERT(pin < c_MaxPins);
    ASSERT(AltFunction < S3C2440_GPIO_Driver::c_Alt_Max_Mode);

    GLOBAL_LOCK(irq);
    S3C2440_GPIO_Driver::PORT_HANDLER port = GetPort(PinToPort(pin));
    UINT32 bit = PinToBit(pin);


    if (AltFunction != GPIO_ALT_PRIMARY)
    	port.SetAltFunction(bit, AltFunction);
    else if (direction)
    	port.SetOutput(bit);//output
    else
    	port.SetInput(bit); //input


    PIN_ISR_DESCRIPTOR& pinIsr = g_S3C2440_GPIO_Driver.m_PinIsr[ pin ];

    pinIsr.m_intEdge = GPIO_INT_NONE;
    pinIsr.m_isr     = STUB_GPIOISRVector;
    pinIsr.m_param   = NULL;
}


void S3C2440_GPIO_Driver::EnableOutputPin( GPIO_PIN pin, BOOL initialState )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    ASSERT(pin < c_MaxPins);

    S3C2440_GPIO_Driver::PORT_HANDLER port = GetPort(PinToPort(pin));
    UINT32 bit = PinToBit(pin);

    GLOBAL_LOCK(irq);

    port.SetBitState(bit, initialState);
    port.SetOutput(bit);
}


BOOL S3C2440_GPIO_Driver::EnableInputPin( GPIO_PIN pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR, void* pinIsrParam, GPIO_INT_EDGE intEdge, GPIO_RESISTOR resistorState )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    ASSERT(pin < c_MaxPins);

    S3C2440_GPIO_Driver::PORT_HANDLER port = GetPort(PinToPort(pin));
    UINT32 bit = PinToBit(pin);

    GLOBAL_LOCK(irq);

    port.SetInput(bit);

    PIN_ISR_DESCRIPTOR& pinIsr = g_S3C2440_GPIO_Driver.m_PinIsr[ pin ];

    pinIsr.m_intEdge = intEdge;
    pinIsr.m_isr     = (ISR != NULL) ? ISR : STUB_GPIOISRVector;
    pinIsr.m_param   = pinIsrParam;
    pinIsr.m_flags   = 0;
    pinIsr.m_status  = 0;
    pinIsr.m_completion.Abort();
    pinIsr.m_completion.Initialize();

    return TRUE;
}


BOOL S3C2440_GPIO_Driver::GetPinState( GPIO_PIN pin )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    ASSERT(pin < c_MaxPins);
    S3C2440_GPIO_Driver::PORT_HANDLER port = GetPort(PinToPort(pin));
    UINT32 bit = PinToBit(pin);

    return port.GetBitState(bit);
}


void S3C2440_GPIO_Driver::SetPinState( GPIO_PIN pin, BOOL pinState )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    ASSERT(pin < c_MaxPins);
    UINT8 portIndex = PinToPort(pin);
    S3C2440_GPIO_Driver::PORT_HANDLER port = GetPort(portIndex);
    UINT32 bit = PinToBit(pin);

    port.SetBitState(bit, pinState);
}


void S3C2440_GPIO_Driver::ISR( void* Param )
{
	debug_printf("%s\r\n", __FUNCTION__);

    S3C2440_GPIO& gpio = S3C2440::GPIO();
    gpio.EINTPEND = 0;
}

void S3C2440_GPIO_Driver::SetResistor( GPIO_PIN pin, GPIO_RESISTOR resistorState )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    ASSERT(pin < c_MaxPins);

}

BOOL S3C2440_GPIO_Driver::PinIsBusy( GPIO_PIN pin )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    ASSERT(pin < c_MaxPins);

    UINT32& res  = g_S3C2440_GPIO_Driver.m_PinReservationInfo[pin >> 5];
    UINT32 bit = PinToBit(pin);
    return (res & (1u << bit)) != 0 ? TRUE : FALSE;
}

BOOL S3C2440_GPIO_Driver::ReservePin( GPIO_PIN pin, BOOL fReserve )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    ASSERT(pin < c_MaxPins);
    GLOBAL_LOCK(irq);

    UINT32& res  = g_S3C2440_GPIO_Driver.m_PinReservationInfo[pin >> 5];
    UINT32 bit = PinToBit(pin);
    UINT32  mask = (fReserve ? 1u : 0u) << bit;

    if((res & (1u << bit)) == mask) return FALSE;

    if(fReserve)
    {
    	res |= (1u << bit);
    }
    else
    {
    	res &= ~(1u << bit);
    }

    return TRUE;
}

UINT32 S3C2440_GPIO_Driver::GetDebounce()
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return 0;
}

BOOL S3C2440_GPIO_Driver::SetDebounce( INT64 debounceTimeMilliseconds )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();

    return FALSE;
}

//--//

void S3C2440_GPIO_Driver::STUB_GPIOISRVector( GPIO_PIN Pin, BOOL PinState, void* Param )
{
    lcd_printf( "\fSTUB_GPI %04x\r\n", (size_t)Param );
    hal_printf( "\fSTUB_GPI %04x %04x\r\n", Pin,(size_t)Param );
    DEBUG_HARD_BREAKPOINT();
}

//--//


void S3C2440_GPIO_Driver::PIN_ISR_DESCRIPTOR::Fire( void* arg )
{

}

UINT8 S3C2440_GPIO_Driver::PinToPort( GPIO_PIN pin )
{
    ASSERT(pin >= 0 && pin < c_MaxPins);
    UINT32 current = 0;
    for (UINT8 i=0; i < c_MaxPorts; i++)
    {
    	current += c_PinsInPort[i];
    	if (pin < current) return i;
    }
    ASSERT(FALSE);
    return 0;
}

UINT32 S3C2440_GPIO_Driver::PinToBit( GPIO_PIN pin )
{
	ASSERT(pin < c_MaxPins);
	UINT32 current = 0;
    for (UINT8 i=0; i < c_MaxPorts; i++)
    {
    	UINT32 next = current + c_PinsInPort[i];
    	if (pin >= current && pin < next) return pin - current;
    	current = next;
    }
    ASSERT(FALSE);
    return 0;
}

UINT32 S3C2440_GPIO_Driver::BitToPin( UINT32 bit, UINT8 port )
{
	ASSERT(port < c_MaxPorts);
	UINT8 pins = c_PinsInPort[port];
	ASSERT(bit < pins);

	UINT32 sum = 0;
    for (UINT8 i=0; i < port; i++)
    {
    	sum += c_PinsInPort[i];
    }
	return sum + bit;
}

S3C2440_GPIO_Driver::PORT_HANDLER S3C2440_GPIO_Driver::GetPort(UINT8 port)
{
	ASSERT(port > 0 && port < S3C2440_GPIO_Driver::c_MaxPorts);
	S3C2440_GPIO& gpio = S3C2440::GPIO();

	S3C2440_GPIO_Driver::PORT_HANDLER result = {port == 0, *(&gpio.PORTS[port])};
	return result;
}

BOOL S3C2440_GPIO_Driver::PORT_HANDLER::SetInput(UINT32 bit)
{
	if (OnlyOutput)
		return FALSE;

	return FALSE;
}
void S3C2440_GPIO_Driver::PORT_HANDLER::SetOutput(UINT32 bit)
{

}
void S3C2440_GPIO_Driver::PORT_HANDLER::SetAltFunction(UINT32 bit, GPIO_ALT_MODE AltFunction)
{

}

void S3C2440_GPIO_Driver::PORT_HANDLER::SetBitState(UINT32 bit, BOOL state)
{
	UINT32 mask = 1 << bit;
	UINT32 value;
	if (state)
		value = port.GPDAT | mask;
	else
		value = port.GPDAT & ~mask;

	port.GPDAT = value;
}

BOOL S3C2440_GPIO_Driver::PORT_HANDLER::GetBitState(UINT32 bit)
{
	return (port.GPDAT >> bit) & 0x01;
}
