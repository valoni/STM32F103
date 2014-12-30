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
    TimedEvents eventsTest;
    UART        usartTest  ( COMTestPort, 115200, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );
 //   GPIO        gpioTest   ( GPIOTestPin );

    do
    {    
        result = eventsTest.Execute( STREAM__DEFAULT_DEBUG_CHANNEL );
        result = usartTest.Execute ( STREAM__DEFAULT_DEBUG_CHANNEL );
  //      result = gpioTest.Execute  ( STREAM__LCD );

    } while(FALSE); // run only once!

    while(TRUE)
		{
			GPBCON=0x00000104;
		  GPBDAT = 0x00000010;
			for(i = 0; i < 10000000;i++);
			  GPBDAT = 0x00000012;
			for(i = 0; i < 10000000;i++);
		}
}

