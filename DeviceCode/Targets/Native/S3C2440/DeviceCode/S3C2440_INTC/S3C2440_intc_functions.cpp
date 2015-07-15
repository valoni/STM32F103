/*
 * S3C2440_intc_functions.cpp
 *
 *  Created on: 18.4.2011
 *      Author: Matti Eerola
 */


#include <cores\arm\include\cpu.h>
#include <tinyhal.h>
#include "..\S3C2440.h"

void CPU_INTC_Initialize()
{
    S3C2440_AIC_Driver::Initialize();
}

BOOL CPU_INTC_ActivateInterrupt( UINT32 Irq_Index, HAL_CALLBACK_FPN ISR, void* ISR_Param )
{
    return S3C2440_AIC_Driver::ActivateInterrupt( Irq_Index, FALSE, ISR, ISR_Param);
}

BOOL CPU_INTC_DeactivateInterrupt( UINT32 Irq_Index )
{
    return S3C2440_AIC_Driver::DeactivateInterrupt( Irq_Index );
}

BOOL CPU_INTC_InterruptEnable( UINT32 Irq_Index )
{
    return S3C2440_AIC_Driver::InterruptEnable( Irq_Index );
}

BOOL CPU_INTC_InterruptDisable( UINT32 Irq_Index )
{
    return S3C2440_AIC_Driver::InterruptDisable( Irq_Index );
}

BOOL CPU_INTC_InterruptEnableState( UINT32 Irq_Index )
{
    return S3C2440_AIC_Driver::InterruptEnableState( Irq_Index );
}

BOOL CPU_INTC_InterruptState( UINT32 Irq_Index )
{
    return S3C2440_AIC_Driver::InterruptState( Irq_Index );
}
