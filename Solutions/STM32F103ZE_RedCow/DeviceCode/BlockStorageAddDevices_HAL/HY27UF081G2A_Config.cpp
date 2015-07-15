#include <tinyhal.h>
#include "fsmc_nand.h"
#include "BlockStorageDriver_NAND.h"
#include "AvailableNandID.h"
//--------------------------------------------------------------------------
//Macro
#define FLASH_SECTOR_WRITE_TYPICAL_TIME_USEC				200			//It writed in the datasheet is just like as follows: Page program time: 200us
#define FLASH_BLOCK_ERASE_ACTUAL_TIME_USEC					2000		//It writed in the datasheet is just like as follows: Block erase time: 2ms (Typ.)
#define FLASH_BIT_WIDTH															8				//HY27UF081G2A is 128Mx8bit,so it's 8bit width
#define FLASH_MEMORY_SIZE														(NAND_PAGE_SIZE * NAND_BLOCK_SIZE * NAND_ZONE_SIZE * NAND_MAX_ZONE)


//--------------------------------------------------------------------------
//Global variable

BlockStorageDevice  g_Nand_Device;


const BlockRange g_HY27UF081G2A_BlockRange[] =
{
	{ BlockRange::BLOCKTYPE_CONFIG    ,   0,   7 },
	{ BlockRange::BLOCKTYPE_DEPLOYMENT,   8,  47 },
	{ BlockRange::BLOCKTYPE_DEPLOYMENT,  48,  87 },
	{ BlockRange::BLOCKTYPE_DEPLOYMENT, 128, 167 },
	{ BlockRange::BLOCKTYPE_DEPLOYMENT, 208, 247 },
	{ BlockRange::BLOCKTYPE_DEPLOYMENT, 288, 327 },
	{ BlockRange::BLOCKTYPE_DEPLOYMENT, 328, 1007 },
	{ BlockRange::BLOCKTYPE_STORAGE_A , 1008,1015 },
	{ BlockRange::BLOCKTYPE_STORAGE_B , 1016,1023 },
};

const BlockRegionInfo  g_HY27UF081G2A_BlockRegionInfo[NAND_MAX_ZONE] = 
{
	NAND_FLASH_BASE_ADDRESS,   // ByteAddress   Start;              // Starting Sector address
	NAND_ZONE_SIZE,                 		 // UINT32          NumBlocks;          // total number of blocks in this region
	NAND_BLOCK_SIZE * NAND_PAGE_SIZE,              // UINT32        BytesPerBlock;      // Total number of bytes per block (MUST be SectorsPerBlock * DataBytesPerSector)
	
	ARRAYSIZE_CONST_EXPR(g_HY27UF081G2A_BlockRange),
	g_HY27UF081G2A_BlockRange,
};


BlockDeviceInfo g_HY27UF081G2A_DeviceInfo =
{
	{  
		FALSE,                     // BOOL Removable;
		FALSE,                     // BOOL SupportsXIP;
		FALSE,                 		 // BOOL WriteProtected
	},
	
	FLASH_SECTOR_WRITE_TYPICAL_TIME_USEC,           // UINT32 Duration_Max_WordWrite_uSec;
	FLASH_BLOCK_ERASE_ACTUAL_TIME_USEC,             // UINT32 Duration_Max_SectorErase_uSec;
	NAND_PAGE_SIZE,                         // UINT32 BytesPerSector; // Bytes Per Sector
	
	FLASH_MEMORY_SIZE,     // UINT32 Size;
	
	NAND_MAX_ZONE,                      // UINT32 NumRegions;
	g_HY27UF081G2A_BlockRegionInfo,                      //const BlockRegionInfo* pRegions;
};

struct BLOCK_CONFIG g_HY27UF081G2A_Config = 
{
	{
		GPIO_PIN_NONE,                       // GPIO_PIN             Pin;
		FALSE,                         // BOOL                 ActiveState;
	},
	&g_HY27UF081G2A_DeviceInfo,
};

/*
struct MEMORY_MAPPED_NOR_BLOCK_CONFIG g_SST39VF320_16_BS_Config =
{
	{ // BLOCK_CONFIG
		{
			GPIO_PIN_NONE,                       // GPIO_PIN             Pin;
			FALSE,                         // BOOL                 ActiveState;
		},
		&g_HY27UF081G2A_DeviceInfo,                        // BlockDeviceinfo
	},
	
	{
		0,                     // UINT8  CPU_MEMORY_CONFIG::ChipSelect;
		FALSE,                                           // UINT8  CPU_MEMORY_CONFIG::ReadOnly;
		0,                     // UINT32 CPU_MEMORY_CONFIG::WaitStates;
		0,                  // UINT32 CPU_MEMORY_CONFIG::ReleaseCounts;
		FLASH_BIT_WIDTH,                       // UINT32 CPU_MEMORY_CONFIG::BitWidth;
		NAND_FLASH_BASE_ADDRESS,                    // UINT32 CPU_MEMORY_CONFIG::BaseAddress;
		FLASH_MEMORY_SIZE,                   // UINT32 CPU_MEMORY_CONFIG::SizeInBytes;
		0,0,0,
	},
	 
	0,                                      // UINT32  ChipProtection;
	NAND_HY27UF081G2A_MAKER_ID,                // FLASH_WORD ManufacturerCode;
	NAND_HY27UF081G2A_DEVICE_ID,                      // FLASH_WORD DeviceCode;
};
    */