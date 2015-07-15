////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <Tests.h>
#include "nativesample.h"
#include "GPIO_Adapter.h"
#include "usart.h"
#include "INTC_Adapter.h"
#include "ILI932x.h"
#include "FSMC_NOR.h"

//--//

HAL_DECLARE_NULL_HEAP();

//--------------------------------------------------------------------------
//Macro
#define BUFFER_SIZE        10
#define WRITE_READ_ADDR    0x2000

//--------------------------------------------------------------------------
void ApplicationEntryPoint()
{
	
	//不要删除下面这个语句，否则会编译出错
	UART        usartTest  ( COMTestPort, 9600, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );

 
	/* Configure FSMC Bank1 NOR/SRAM2 */
  FSMC_NOR_Init();
 
  /* Read NOR memory ID */
  NOR_IDTypeDef NOR_ID = {0};
  FSMC_NOR_ReadID(&NOR_ID);
	
  FSMC_NOR_ReturnToReadMode();

  /* Erase the NOR memory block to write on */
  FSMC_NOR_EraseBlock(WRITE_READ_ADDR);

	//Initilaize the write buffer value
  u16 TxBuffer[BUFFER_SIZE] = {0};
  for(u16 i = 0; i < BUFFER_SIZE; i ++)
	{
		TxBuffer[i] = i;
	}
  
  /* Write data to FSMC NOR memory */
  /* Fill the buffer to send */
  FSMC_NOR_WriteBuffer(TxBuffer, WRITE_READ_ADDR, BUFFER_SIZE);

  /* Read data from FSMC NOR memory */
  u16 RxBuffer[BUFFER_SIZE] = {0};
  FSMC_NOR_ReadBuffer(RxBuffer, WRITE_READ_ADDR, BUFFER_SIZE);
  
  u16 wErrorCount = 0;
  for(u16 i = 0; i < BUFFER_SIZE; i ++)
  {
  	if(RxBuffer[i] != TxBuffer[i])
  	{
  		//The value is not equal,so increase the count.
  		wErrorCount ++;
  	}
  }
	while(true);
}


