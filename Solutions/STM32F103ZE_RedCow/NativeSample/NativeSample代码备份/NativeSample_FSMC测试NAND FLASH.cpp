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
#include "FSMC_Nand.h"
//--//

HAL_DECLARE_NULL_HEAP();

//--------------------------------------------------------------------------
//Macro
#define BUFFER_SIZE        (NAND_PAGE_SIZE * 2)

//--------------------------------------------------------------------------
void ApplicationEntryPoint()
{
	
	//不要删除下面这个语句，否则会编译出错
	UART        usartTest  ( COMTestPort, 9600, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );

	//Becareful: The JP11 jumper must be 1-2
	
 	/* FSMC Initialization */
	FSMC_NAND_Init();

	/* NAND read ID command */
	NAND_IDTypeDef NAND_ID;
	FSMC_NAND_ReadID(&NAND_ID);


	/* NAND memory address to write to */ 
	NAND_ADDRESS WriteReadAddr;
	WriteReadAddr.Zone = 0x00;
	WriteReadAddr.Block = 0x00;
	WriteReadAddr.Page = 0x00; 
	
	/* Erase the NAND first Block */
	u32 status = 0;
	//status = FSMC_NAND_EraseBlock(WriteReadAddr);
	
	//Initilaize the write buffer value
  u8 TxBuffer[BUFFER_SIZE] = {0};
  for(u16 i = 0; i < BUFFER_SIZE; i ++)
	{
		//TxBuffer[i] = i;
		TxBuffer[i] = i / 128;
	}
	
	
	/* Write data to FSMC NAND memory */
	u8 PageNumber = BUFFER_SIZE / NAND_PAGE_SIZE;
	//status = FSMC_NAND_WriteSmallPage(TxBuffer, WriteReadAddr, PageNumber);
	
	/* Read back the written data */
	u8 RxBuffer[BUFFER_SIZE] = {0};
	status = FSMC_NAND_ReadSmallPage (RxBuffer, WriteReadAddr, PageNumber);

  
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


