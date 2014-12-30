////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <Tests.h>
#include "nativesample.h"
#include "../DeviceCode/Blockstorage/RAM/RAM_driver.h"
#include <DeviceCode/S3C2440.h>

//--//

HAL_DECLARE_NULL_HEAP();


void ApplicationEntryPoint()
{
    BOOL result;
   
    TimedEvents eventsTest;
    UART        usartTest  ( COMTestPort, 9600, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );
    GPIO        gpioTest   ( GPIOTestPin );

    do
    {    
        result = eventsTest.Execute( STREAM__DEFAULT_DEBUG_CHANNEL ); //STREAM__LCD
        Events_WaitForEvents( 0, 2000 ); //some delay for manual input
        result = usartTest.Execute ( STREAM__DEFAULT_DEBUG_CHANNEL );
        result = gpioTest.Execute  ( STREAM__DEFAULT_DEBUG_CHANNEL );

        if (result)
        	debug_printf("\r\nAll tests passed!\r\n");

    } while(FALSE); // run only once!

    debug_printf("\r\nSome extra tests:\r\n");

    debug_printf("\r\n=== S3C2440_GPIO_Driver test ===\r\n");
    UINT8 resultPort = S3C2440_GPIO_Driver::PinToPort(31);
    UINT32 resultBit = S3C2440_GPIO_Driver::PinToBit(31);
    BOOL gpioTestPassed = TRUE;
    if (resultPort != 1)
    {
    	debug_printf("FAIL: Pin 31 port is 1. Got %d.\r\n", resultPort);
    	gpioTestPassed = FALSE;
    }
    if (resultBit != 8)
    {
    	debug_printf("FAIL: Pin 31 bit is 8. Got %d.\r\n", resultBit);
    	gpioTestPassed = FALSE;
    }

    if (gpioTestPassed)
    	debug_printf("S3C2440_GPIO_Driver test PASSED\r\n");
    else
    	debug_printf("S3C2440_GPIO_Driver test FAILED\r\n");

    debug_printf("\r\n=== Block storage test ===\r\n");
    BYTE bl_expected[8];
    BYTE bl_result[8];
    memcpy(bl_expected, (const void*)0x30300000, 8);
    debug_printf("bl_expected: %02x %02x %02x %02x  %02x %02x %02x %02x\r\n", bl_expected[0], bl_expected[1], bl_expected[2], bl_expected[3], bl_expected[4], bl_expected[5], bl_expected[6], bl_expected[7]);
    RAM_BS_Driver::Read(NULL, (ByteAddress)0x30300000, 8, bl_result);
    debug_printf("bl_result: %02x %02x %02x %02x  %02x %02x %02x %02x\r\n", bl_result[0], bl_result[1], bl_result[2], bl_result[3], bl_result[4], bl_result[5], bl_result[6], bl_result[7]);
    BOOL bl_testpassed = TRUE;

    for (int i = 0; i < 8; i++)
    {
    	if (bl_result[i] != bl_expected[i])
    		bl_testpassed = FALSE;
    }
    if (bl_testpassed)
    	debug_printf("Block storage test PASSED\r\n");
    else
    	debug_printf("Block storage test FAILED\r\n");

    while(TRUE);
}




