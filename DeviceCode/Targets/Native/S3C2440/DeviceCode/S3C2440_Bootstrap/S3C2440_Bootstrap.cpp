/*
 * S3C2440_Bootstrap.cpp
 *
 *  Created on: 16.4.2011
 *      Author: Matti Eerola
 */

#include <tinyhal.h>
#include <Cores\arm\Include\cpu.h>
#include "..\S3C2440.h"

static const UINT32  c_Bootstrap_Register_Begin =   0x48000000;
static const UINT32  c_Bootstrap_Register_End   =   0x60000000;
static const UINT32  c_Bootstrap_SDRAM_Begin    =   SDRAM_MEMORY_Base;
static const UINT32  c_Bootstrap_SDRAM_End      =   SDRAM_MEMORY_Base + SDRAM_MEMORY_Size;
static const UINT32  c_Bootstrap_SRAM_Begin     =   SRAM_MEMORY_Base; //not used for now
static const UINT32  c_Bootstrap_SRAM_End       =   SRAM_MEMORY_Base + SRAM_MEMORY_Size; //not used for now
static const UINT32  c_Bootstrap_FLASH_Begin    =   FLASH_MEMORY_Base;
static const UINT32  c_Bootstrap_FLASH_End      =   FLASH_MEMORY_Base + FLASH_MEMORY_Size;
static UINT32* const c_Bootstrap_BaseOfTTBs     =   (UINT32*)(c_Bootstrap_SDRAM_End - ARM9_MMU::c_TTB_size);

void S3C2440::Debug_SendByte(unsigned char data)
{
	while(!((*(volatile unsigned *)0x50000010) & 0x2));   //Wait until THR is empty.
	(*(volatile unsigned char *)0x50000020)=(unsigned char)(data);
}


void S3C2440::Debug_printf( const char* format, ... )
{
	char    buffer[256];
	va_list arg_ptr;

	va_start( arg_ptr, format );

	int len = hal_vsnprintf( buffer, sizeof(buffer)-1, format, arg_ptr );
	int i;
	for (i = 0; i < len; i++)
		S3C2440::Debug_SendByte((unsigned char)buffer[i]);
}

void BootstrapCode_MMU()
{
	S3C2440::Debug_printf("Bootstrap - CPU_IsMMUEnabled: %1d\r\n", CPU_IsMMUEnabled());

	// Fill Translation table with faults.
	ARM9_MMU::InitializeL1(c_Bootstrap_BaseOfTTBs);

	// Direct map for the APB registers (0x48000000 ~ 0x60000000)
	ARM9_MMU::GenerateL1_Sections(
			c_Bootstrap_BaseOfTTBs,                                 // base of TTBs
			c_Bootstrap_Register_Begin,                             // mapped address
			c_Bootstrap_Register_Begin,                             // physical address
			c_Bootstrap_Register_End - c_Bootstrap_Register_Begin,  // length to be mapped
			ARM9_MMU::c_AP__Manager,                                // AP
			0,                                                      // Domain
			FALSE,                                                  // Cacheable
			FALSE,                                                  // Buffered
			FALSE);                                                 // Extended

	// Direct map SDRAM (cachable)
	ARM9_MMU::GenerateL1_Sections(
			c_Bootstrap_BaseOfTTBs,                                 // base of TTBs
			c_Bootstrap_SDRAM_Begin,                                // mapped address
			c_Bootstrap_SDRAM_Begin,                                // physical address
			c_Bootstrap_SDRAM_End - c_Bootstrap_SDRAM_Begin,        // length to be mapped
			ARM9_MMU::c_AP__Manager,                                // AP
			0,                                                      // Domain
			TRUE,                                                   // Cacheable
			FALSE,                                                  // Buffered
			FALSE);                                                 // Extended

	// The last 1MB of RAM (0x3000000 ~ 0x33FFFFFF) is double-mapped to (0x0 ~ 0xFFFFF)
	ARM9_MMU::GenerateL1_Sections(
			c_Bootstrap_BaseOfTTBs,             // base of TTBs
			0x00000000,                         // mapped address
			c_Bootstrap_SDRAM_End - 0x100000,   // physical address
			0x100000,                           // length to be mapped
			ARM9_MMU::c_AP__Manager,            // AP
			0,                                  // Domain
			TRUE,                               // Cacheable
			FALSE);                             // Buffered


	// Direct map for the FLASH (uncachable)
	ARM9_MMU::GenerateL1_Sections(
			c_Bootstrap_BaseOfTTBs,                                 // base of TTBs
			c_Bootstrap_FLASH_Begin,                                // mapped address
			c_Bootstrap_FLASH_Begin,                                // physical address
			c_Bootstrap_FLASH_End - c_Bootstrap_FLASH_Begin,        // length to be mapped
			ARM9_MMU::c_AP__Manager,                                // AP
			0,                                                      // Domain
			FALSE,                                                  // Cacheable
			FALSE,                                                  // Buffered
			FALSE);                                                 // Extended


	CPU_FlushCaches();
	CPU_EnableMMU( c_Bootstrap_BaseOfTTBs );

	S3C2440::Debug_printf("Bootstrap - CPU_IsMMUEnabled: %1d\r\n", CPU_IsMMUEnabled());
}


void BootstrapCode ()
{
	CPU_ARM9_BootstrapCode();

	BootstrapCode_MMU();

	PrepareImageRegions();

	CPU_EnableCaches();

	CPU_INTC_Initialize(); //TODO: Not the right place.. should be somewhere in power driver
}
