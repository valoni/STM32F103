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
#define NAND_WRITE_BUFFER_SIZE			530
#define NAND_WRITE_ADDRESS_1				(NAND_FLASH_BASE_ADDRESS + 511)
#define NAND_WRITE_ADDRESS_2				(NAND_WRITE_ADDRESS_1 + NAND_WRITE_BUFFER_SIZE)
#define NAND_MEMSET_ADDRESS					(NAND_WRITE_ADDRESS_2 + NAND_WRITE_BUFFER_SIZE)
#define NAND_MEMSET_SIZE						20
#define NAND_MEMSET_VALUE						0xAB
#define NAND_READ_BUFFER_SIZE				(NAND_PAGE_SIZE * 2)
#define NAND_READ_ADDRESS						(NAND_FLASH_BASE_ADDRESS + 0)

#define NOR_WRITE_BUFFER_SIZE				12
#define NOR_WRITE_ADDRESS_1					(NOR_FLASH_BASE_ADDRESS + 10)
#define NOR_WRITE_ADDRESS_2					(NOR_WRITE_ADDRESS_1 + NOR_WRITE_BUFFER_SIZE)
#define NOR_MEMSET_ADDRESS					(NOR_WRITE_ADDRESS_2 + NOR_WRITE_BUFFER_SIZE)
#define NOR_MEMSET_SIZE							20
#define NOR_MEMSET_VALUE						0xCD
#define NOR_READ_BUFFER_SIZE				(NOR_WRITE_BUFFER_SIZE * 10)
#define NOR_READ_ADDRESS						(NOR_FLASH_BASE_ADDRESS + 0)

BYTE bytWriteNorData[NOR_WRITE_BUFFER_SIZE] = {0};
BYTE bytReadNorData[NOR_READ_BUFFER_SIZE] = {0};
//--------------------------------------------------------------------------
void ApplicationEntryPoint()
{
	
	//不要删除下面这个语句，否则会编译出错
	UART        usartTest  ( COMTestPort, 9600, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );

	

	//In the initialize order,the first one is NAND flash
	BlockStorageDevice *device= BlockStorageList::GetFirstDevice(); 
	if(device != NULL)
	{ 	
		//Becareful: If you used NAND flash,the JP11 jumper must be 1-2		
		BOOL bRes = FALSE;		
	
		//Erase the block
		device->EraseBlock(NAND_WRITE_ADDRESS_1);
		device->EraseBlock(NAND_WRITE_ADDRESS_1 + NAND_WRITE_BUFFER_SIZE);
		device->EraseBlock(NAND_WRITE_ADDRESS_2);
		device->EraseBlock(NAND_WRITE_ADDRESS_2 + NAND_WRITE_BUFFER_SIZE);
		
		
		BYTE bytWriteNandData[NAND_WRITE_BUFFER_SIZE] = {0};
		for(int i = 0; i < NAND_WRITE_BUFFER_SIZE; i ++)  
		{
			bytWriteNandData[i] = (BYTE) (i % 256);
		}
		
		//Write the data in WRITE_ADDRESS_1
		bRes = device->Write(NAND_WRITE_ADDRESS_1,NAND_WRITE_BUFFER_SIZE,bytWriteNandData,FALSE);
		debug_printf("[NAND]Write WRITE_ADDRESS_1:%s\r\n",bRes? "OK":"ERROR");                   
			
		//Write the data in WRITE_ADDRESS_2
		bRes = device->Write(NAND_WRITE_ADDRESS_2,NAND_WRITE_BUFFER_SIZE,bytWriteNandData,FALSE);
		debug_printf("[NAND]Write WRITE_ADDRESS_2:%s\r\n",bRes? "OK":"ERROR"); 
		
		//Memset function
		device->Memset(NAND_MEMSET_ADDRESS,NAND_MEMSET_VALUE,NAND_MEMSET_SIZE);
		
		//Read the data
		BYTE bytReadNandData[NAND_READ_BUFFER_SIZE] = {0};
		bRes = device->Read(NAND_READ_ADDRESS,NAND_READ_BUFFER_SIZE,bytReadNandData);
		
		//To check the write and read value for WRITE_ADDRESS_1
		bRes = TRUE;
		for(int i = 0; i < NAND_WRITE_BUFFER_SIZE; i ++)
		{
			if(bytWriteNandData[i] != bytReadNandData[NAND_WRITE_ADDRESS_1 - NAND_READ_ADDRESS + i])
			{
				bRes = FALSE;
				break;
			}
		}
		debug_printf("[NAND]Check WRITE_ADDRESS_1:%s\r\n",bRes? "OK":"ERROR"); 
			
		//To check the write and read value for WRITE_ADDRESS_2
		bRes = TRUE;
		for(int i = 0; i < NAND_WRITE_BUFFER_SIZE; i ++)
		{
			if(bytWriteNandData[i] != bytReadNandData[NAND_WRITE_ADDRESS_2 - NAND_READ_ADDRESS + i])
			{
				bRes = FALSE;
				break;
			}
		}
		debug_printf("[NAND]Check WRITE_ADDRESS_1:%s\r\n",bRes? "OK":"ERROR"); 
		
		//To check the write and read value for MEMSET_ADDRESS
		bRes = TRUE;
		for(int i = 0; i < NAND_MEMSET_SIZE; i ++)
		{
			if(NAND_MEMSET_VALUE != bytReadNandData[NAND_MEMSET_ADDRESS - NAND_READ_ADDRESS + i])
			{
				bRes = FALSE;
				break;
			}
		}
		debug_printf("[NAND]Check MEMSET_ADDRESS:%s\r\n",bRes? "OK":"ERROR"); 
	} 	
	
	
	//In the initialize order,the second one is nor flash
	device= BlockStorageList::GetNextDevice(*device); 
	if(device != NULL)
	{
		BOOL bRes = FALSE;		
	
		//Erase the block
		device->EraseBlock(NOR_WRITE_ADDRESS_1);
		//device->EraseBlock(NOR_WRITE_ADDRESS_1 + NOR_WRITE_BUFFER_SIZE);
		device->EraseBlock(NOR_WRITE_ADDRESS_2);
		//device->EraseBlock(NOR_WRITE_ADDRESS_2 + NOR_WRITE_BUFFER_SIZE);
		device->EraseBlock(NOR_MEMSET_ADDRESS);		
		//device->EraseBlock(NOR_MEMSET_ADDRESS + NOR_MEMSET_SIZE);
		
		//BYTE bytWriteNorData[NOR_WRITE_BUFFER_SIZE] = {0};
		for(int i = 0; i < NOR_WRITE_BUFFER_SIZE; i ++)  
		{
			bytWriteNorData[i] = (BYTE) (i % 256);
		}
		
		//Memset function
		device->Memset(NOR_MEMSET_ADDRESS,NOR_MEMSET_VALUE,NOR_MEMSET_SIZE);
		
		//Write the data in WRITE_ADDRESS_1
		bRes = device->Write(NOR_WRITE_ADDRESS_1,NOR_WRITE_BUFFER_SIZE,bytWriteNorData,FALSE);
		debug_printf("[NOR]Write WRITE_ADDRESS_1:%s\r\n",bRes? "OK":"ERROR");                   
			
		//Write the data in WRITE_ADDRESS_2
		bRes = device->Write(NOR_WRITE_ADDRESS_2,NOR_WRITE_BUFFER_SIZE,bytWriteNorData,FALSE);
		debug_printf("[NOR]Write WRITE_ADDRESS_2:%s\r\n",bRes? "OK":"ERROR"); 
		
		//Read the data
		//BYTE bytReadNorData[NOR_READ_BUFFER_SIZE] = {0};
		bRes = device->Read(NOR_READ_ADDRESS,NOR_READ_BUFFER_SIZE,bytReadNorData);
		
		//To check the write and read value for WRITE_ADDRESS_1
		bRes = TRUE;
		for(int i = 0; i < NOR_WRITE_BUFFER_SIZE; i ++)
		{
			if(bytWriteNorData[i] != bytReadNorData[NOR_WRITE_ADDRESS_1 - NOR_READ_ADDRESS + i])
			{
				bRes = FALSE;
				break;
			}
		}
		debug_printf("[NOR]Check WRITE_ADDRESS_1:%s\r\n",bRes? "OK":"ERROR"); 
			
		//To check the write and read value for WRITE_ADDRESS_2
		bRes = TRUE;
		for(int i = 0; i < NOR_WRITE_BUFFER_SIZE; i ++)
		{
			if(bytWriteNorData[i] != bytReadNorData[NOR_WRITE_ADDRESS_2 - NOR_READ_ADDRESS + i])
			{
				bRes = FALSE;
				break;
			}
		}
		debug_printf("[NOR]Check WRITE_ADDRESS_1:%s\r\n",bRes? "OK":"ERROR"); 
		
		//To check the write and read value for MEMSET_ADDRESS
		bRes = TRUE;
		for(int i = 0; i < NOR_MEMSET_SIZE; i ++)
		{
			if(NOR_MEMSET_VALUE != bytReadNorData[NOR_MEMSET_ADDRESS - NOR_READ_ADDRESS + i])
			{
				bRes = FALSE;
				break;
			}
		}
		debug_printf("[NOR]Check MEMSET_ADDRESS:%s\r\n",bRes? "OK":"ERROR"); 
	}

	while(true);
}


