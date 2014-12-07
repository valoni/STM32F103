////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "stm32f10x_conf.h"
#include "INTC_Adapter.h"
//--//

extern uint32_t ARM_Vectors;

//--//
// this is the first C function called after bootstrapping ourselves into ram

// these define the region to zero initialize
extern UINT32 Image$$ER_RAM_RW$$ZI$$Base;
extern UINT32 Image$$ER_RAM_RW$$ZI$$Length;

// here is the execution address/length of code to move from FLASH to RAM
#define IMAGE_RAM_RO_BASE   Image$$ER_RAM_RO$$Base
#define IMAGE_RAM_RO_LENGTH Image$$ER_RAM_RO$$Length

extern UINT32 IMAGE_RAM_RO_BASE;
extern UINT32 IMAGE_RAM_RO_LENGTH;

// here is the execution address/length of data to move from FLASH to RAM
extern UINT32 Image$$ER_RAM_RW$$Base;
extern UINT32 Image$$ER_RAM_RW$$Length;

// here is the load address of the RAM code/data
#define LOAD_RAM_RO_BASE Load$$ER_RAM_RO$$Base

extern UINT32 LOAD_RAM_RO_BASE;
extern UINT32 Load$$ER_RAM_RW$$Base;

//--//



void InitVectorTab()
{
		
	//Set the vector table address to the NVIC_VT0 register , which is definition in the xml setting file		
	volatile UINT32 *pNVIC = &SCB->VTOR;
	*pNVIC = reinterpret_cast<UINT32>(&ARM_Vectors);
	
	//Initialize the INTC which is connected with the vector table
	INTC_Initialize();
	
	//Ensure completion of memory access
	__DSB();

}

#pragma arm section code = "SectionForBootstrapOperations" //Begin

static void __section(SectionForBootstrapOperations)Prepare_Copy( UINT16* src, UINT16* dst, UINT32 len )
{
	if(dst != src)
	{
		while(len)
		{
			*dst++ = *src++;
			len -= 2;
		}
	}
}

static void __section(SectionForBootstrapOperations)Prepare_Zero( UINT16* dst, UINT32 len )
{
	while(len)
	{
		*dst++ = 0;
		len -= 2;
	}
}

//---------------------------------------------------------------------------------
//Description
//	The length in the original PrepareImageRegions function must be mulriple of 4,
//or the code would be crashed, and the IMAGE_RAM_RO_LENGTH sometimes is not mulriple of 4,
//so I rewrite the function to copy data. I copy the data 2-Byte by 2-Byte. If copy
//as Byte uint,it also crash.
//------------------------------------------------------------------------------------
void __section(SectionForBootstrapOperations) PrepareImageRegionsEx()
{
	   //
    // Copy RAM RO regions into proper location.
    //
    {
        UINT16* src = (UINT16*)&LOAD_RAM_RO_BASE; 
        UINT16* dst = (UINT16*)&IMAGE_RAM_RO_BASE;
        UINT32  len = (UINT32 )&IMAGE_RAM_RO_LENGTH; 

        Prepare_Copy( src, dst, len );
    }

    //
    // Copy RAM RW regions into proper location.
    //
    {
        UINT16* src = (UINT16*)&Load$$ER_RAM_RW$$Base; 
        UINT16* dst = (UINT16*)&Image$$ER_RAM_RW$$Base;
        UINT32  len =  (UINT32)&Image$$ER_RAM_RW$$Length; 

        Prepare_Copy( src, dst, len );
    }

    //
    // Initialize RAM ZI regions.
    //
    {
        UINT16* dst = (UINT16*)&Image$$ER_RAM_RW$$ZI$$Base;
        UINT16  len = (UINT32 )&Image$$ER_RAM_RW$$ZI$$Length;

        Prepare_Zero( dst, len );
    }
}




void __section(SectionForBootstrapOperations)BootstrapCode()
{
	//Copy some value from the image to RAM.Don't call original PrepareImageRegions() function here,
	//because the length may not be mulriple of 4.
	PrepareImageRegionsEx();
	//PrepareImageRegions();
	
	//Initialize the vector table for NVIC
	InitVectorTab();
	
	//Initialize the system
	SystemInit();
}

#pragma arm section code //End