////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <Tests.h>
#include "nativesample.h"
#include "GPIO_Adapter.h"
#include "usart.h"
#include "INTC_Adapter.h"

 
//--//

HAL_DECLARE_NULL_HEAP();


int GetLength(char *pszVal)
{
	if(pszVal == NULL)
	{
		return 0;
	}
	
	int iLen = 0;
	while(pszVal[iLen] != '\0')
	{
		++ iLen;
	}
	
	return iLen;
}
			

void ApplicationEntryPoint()
{
	
	//不要删除下面这个语句，否则会编译出错。该函数会输出.NetMF的相关信息
	UART        usartTest  ( COMTestPort, 9600, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );

	const int USART_PORT = ConvertCOM_ComPort(COM2);//ConvertCOM_ComPort(COM2);
	USART_Initialize(USART_PORT,115200, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );
	
	char szHello[] = "Hello,.Net Micro Framework!\r\n"; 	
	USART_Write(USART_PORT,szHello,GetLength(szHello));	
	
	
	BOOL bGetChar = FALSE;
	while(TRUE)     
	{      
		
		if(Events_WaitForEvents(SYSTEM_EVENT_FLAG_COM_IN,200))
		{   
			Events_Clear(SYSTEM_EVENT_FLAG_COM_IN);  
			bGetChar = TRUE; 			       			
			continue;
		}
		
		
		if(bGetChar != FALSE)
		{	
			bGetChar = FALSE;
			
			char bytData[512] = {0};
			int iSize = USART_BytesInBuffer(USART_PORT,TRUE);
			USART_Read(USART_PORT,&bytData[0],iSize);
			
			USART_Write(USART_PORT,bytData,iSize);	
		}
		
		
	}	
}


