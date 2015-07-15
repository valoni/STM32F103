////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <Tests.h>
#include "nativesample.h"


#define GPBCON		(*(volatile UINT32 *)(0x56000010))
#define GPBDAT		(*(volatile UINT32 *)(0x56000014))
#define GPBPU		  (*(volatile UINT32 *)(0x56000018))
//--//

HAL_DECLARE_NULL_HEAP();

void ApplicationEntryPoint()
{
    BOOL result;
    UINT32 i;
	  UINT8 j=0;
    TimedEvents eventsTest;
    UART        usartTest  ( COMTestPort, 115200, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );
    GPIO        gpioTest   ( GPIOTestPin );

    do
    {    
        result = eventsTest.Execute( STREAM__DEFAULT_DEBUG_CHANNEL );
        result = usartTest.Execute ( STREAM__DEFAULT_DEBUG_CHANNEL );
        result = gpioTest.Execute  ( STREAM__DEFAULT_DEBUG_CHANNEL );

    } while(FALSE); // run only once!

		CPU_GPIO_EnableOutputPin(33,FALSE);
		CPU_USART_Initialize(COMTestPort,9600,USART_PARITY_NONE,8,USART_STOP_BITS_ONE,USART_FLOW_NONE);
    while(TRUE)
		{
			CPU_USART_WriteCharToTxBuffer(COMTestPort,j);
     CPU_GPIO_SetPinState(33,TRUE);
			for(i = 0; i < 1000000;i++);
     CPU_GPIO_SetPinState(33,FALSE);
			for(i = 0; i < 1000000;i++);
			j++;
		}
}

