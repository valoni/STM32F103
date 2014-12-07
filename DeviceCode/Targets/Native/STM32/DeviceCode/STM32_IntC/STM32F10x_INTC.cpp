////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "INTC_Adapter.h"
#include "..\stm32f10x.h"

//--//


void CPU_INTC_Initialize()
{
	INTC_Initialize();
}



BOOL CPU_INTC_ActivateInterrupt( UINT32 Irq_Index, HAL_CALLBACK_FPN ISR, void* ISR_Param )
{	
	return INTC_ActivateInterrupt(Irq_Index,ISR,ISR_Param);
}

BOOL CPU_INTC_DeactivateInterrupt( UINT32 Irq_Index )
{
    return INTC_DeactivateInterrupt(Irq_Index);
}

BOOL CPU_INTC_InterruptEnable( UINT32 Irq_Index )
{
    return EnableIrq(Irq_Index,TRUE);
}

BOOL CPU_INTC_InterruptDisable( UINT32 Irq_Index )
{
    return EnableIrq(Irq_Index,FALSE);
}

BOOL CPU_INTC_InterruptEnableState( UINT32 Irq_Index )
{
  return INTC_InterruptEnableState(Irq_Index);
}

BOOL CPU_INTC_InterruptState( UINT32 Irq_Index )
{
	IRQn_Type channel;
	if(IrqToChannel(Irq_Index,channel) == FALSE)
	{
		return FALSE;
	}
	
  return NVIC_GetPendingIRQ(channel);
}


