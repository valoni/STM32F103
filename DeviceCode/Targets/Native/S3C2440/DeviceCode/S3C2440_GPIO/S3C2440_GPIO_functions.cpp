/*
 * S3C2440_GPIO_functions.cpp
 *
 *  Created on: 1.6.2011
 *      Author: Matti Eerola
 */


#include <tinyhal.h>
#include "..\S3C2440.h"

BOOL CPU_GPIO_Initialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return S3C2440_GPIO_Driver::Initialize();
}

BOOL CPU_GPIO_Uninitialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return S3C2440_GPIO_Driver::Uninitialize();
}

UINT32 CPU_GPIO_Attributes( GPIO_PIN Pin )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return S3C2440_GPIO_Driver::Attributes( Pin );
}

void CPU_GPIO_DisablePin( GPIO_PIN Pin, GPIO_RESISTOR ResistorState, UINT32 Direction, GPIO_ALT_MODE AltFunction )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    S3C2440_GPIO_Driver::DisablePin( Pin, ResistorState, Direction, AltFunction );
}

void CPU_GPIO_EnableOutputPin( GPIO_PIN Pin, BOOL InitialState )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    S3C2440_GPIO_Driver::EnableOutputPin( Pin, InitialState );
}

BOOL CPU_GPIO_EnableInputPin( GPIO_PIN Pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR, GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return S3C2440_GPIO_Driver::EnableInputPin( Pin, GlitchFilterEnable, ISR, 0, IntEdge, ResistorState );
}

BOOL CPU_GPIO_EnableInputPin2( GPIO_PIN Pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR, void* ISR_Param, GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return S3C2440_GPIO_Driver::EnableInputPin( Pin, GlitchFilterEnable, ISR, ISR_Param, IntEdge, ResistorState );
}

BOOL CPU_GPIO_GetPinState( GPIO_PIN Pin )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return S3C2440_GPIO_Driver::GetPinState( Pin );
}

void CPU_GPIO_SetPinState( GPIO_PIN Pin, BOOL PinState )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    S3C2440_GPIO_Driver::SetPinState( Pin, PinState );
}

//--//

BOOL CPU_GPIO_PinIsBusy( GPIO_PIN Pin )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return S3C2440_GPIO_Driver::PinIsBusy( Pin );
}

BOOL CPU_GPIO_ReservePin( GPIO_PIN Pin, BOOL fReserve )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return S3C2440_GPIO_Driver::ReservePin( Pin, fReserve );
}

UINT32 CPU_GPIO_GetDebounce()
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return S3C2440_GPIO_Driver::GetDebounce();
}

BOOL CPU_GPIO_SetDebounce( INT64 debounceTimeMilliseconds )
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return S3C2440_GPIO_Driver::SetDebounce( debounceTimeMilliseconds );
}

INT32 CPU_GPIO_GetPinCount()
{
    NATIVE_PROFILE_HAL_PROCESSOR_GPIO();
    return S3C2440_GPIO_Driver::c_MaxPins;
}

void CPU_GPIO_GetPinsMap( UINT8* pins, size_t size )
{
    S3C2440_GPIO_Driver::GetPinsMap( pins, size );
}

UINT8 CPU_GPIO_GetSupportedResistorModes(GPIO_PIN pin )
{
    return S3C2440_GPIO_Driver::GetSupportedResistorModes( pin);
}

UINT8 CPU_GPIO_GetSupportedInterruptModes(GPIO_PIN pin)
{
    return S3C2440_GPIO_Driver::GetSupportedInterruptModes( pin);
}

