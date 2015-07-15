////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <Tests.h>
#include "nativesample.h"
#include "GPIO_Adapter.h"
#include "usart.h"
#include "TgUART.h"
#include "INTC_Adapter.h"
//--//

HAL_DECLARE_NULL_HEAP();

																				 
void InputHandler(GPIO_PIN Pin,BOOL PinState,void *pParam)
{
	CPU_GPIO_SetPinState(GPIO_F07,!CPU_GPIO_GetPinState(GPIO_F07));
}

void ApplicationEntryPoint()
{
	//不要删除下面这个语句，否则会编译出错
	UART        usartTest  ( COMTestPort, 9600, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );

	
	//Initialize the GPIO
	CPU_GPIO_Initialize();
	
	//Enable the GPIO output pin
	CPU_GPIO_EnableOutputPin(GPIO_F06,TRUE);
	CPU_GPIO_EnableOutputPin(GPIO_F07,TRUE);
	CPU_GPIO_EnableInputPin(GPIO_A08,FALSE,InputHandler,GPIO_INT_LEVEL_HIGH,RESISTOR_DISABLED);
	

	
	
	while(TRUE)
	{
		for(long i=0;i<1000000;i++);	
		
		CPU_GPIO_SetPinState(GPIO_F06,!CPU_GPIO_GetPinState(GPIO_F06));
		//CPU_GPIO_SetPinState(GPIO_F07,CPU_GPIO_GetPinState(GPIO_A08));
		
	
	}
}


