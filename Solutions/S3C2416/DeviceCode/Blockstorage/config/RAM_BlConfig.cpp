/*
 * RAM_BlConfig.cpp
 *
 *  Created on: 15.6.2011
 *      Author: Matti Eerola
 */


#include <tinyhal.h>

//--//

#define RAM_BS__BASE_ADDRESS                 0x33000000
#define FLASH_MANUFACTURER_CODE              0x0000
#define FLASH_DEVICE_CODE                    0x0000
#define FLASH_BLOCK_COUNT                    64
#define FLASH_BYTES_PER_SECTOR               4
#define FLASH_BYTES_PER_BLOCK                0x4000
#define FLASH_BLOCK_ERASE_TYPICAL_TIME_USEC  1000000
#define FLASH_SECTOR_WRITE_TYPICAL_TIME_USEC 210
#define FLASH_BLOCK_ERASE_MAX_TIME_USEC      4000000
#define FLASH_SECTOR_WRITE_MAX_TIME_USEC     630
//
// The real max time should be 4,000,000 uSec, but the chip has independent partitions, it's not critical to avoid radio collisions.
//
#define FLASH_BLOCK_ERASE_ACTUAL_TIME_USEC   400000
//--//


//--//



// BlockDeviceInformation

#define RAM_BS__IS_REMOVABLE      FALSE
#define RAM_BS__SUPPORTS_XIP      TRUE
#define RAM_BS__WRITE_PROTECTED   FALSE
#define RAM_BS__NUM_REGIONS       1
#define RAM_BS__SIZE              0x100000


const BlockRange g_RAM_BS_BlockRange[] =
{
		{ BlockRange::BLOCKTYPE_CONFIG , 0, 0 },
		{ BlockRange::BLOCKTYPE_DEPLOYMENT , 1, 63 }    // g_ConfigurationSector
};


/*const*/ BlockRegionInfo  g_RAM_BS_BlkRegion[RAM_BS__NUM_REGIONS] =
{
    {
    	RAM_BS__BASE_ADDRESS,               // ByteAddress   Start;              // Starting Sector address
        FLASH_BLOCK_COUNT,                  // UINT32        NumBlocks;          // total number of blocks in this region
        FLASH_BYTES_PER_BLOCK,              // UINT32        BytesPerBlock;      // Total number of bytes per block


        ARRAYSIZE_CONST_EXPR(g_RAM_BS_BlockRange),
        g_RAM_BS_BlockRange,
    },
};



BlockDeviceInfo g_RAM_BS_DeviceInfo=
{
    {
    		RAM_BS__IS_REMOVABLE,         // BOOL Removable;
    		RAM_BS__SUPPORTS_XIP,         // BOOL SupportsXIP;
    		RAM_BS__WRITE_PROTECTED,
    },
    FLASH_SECTOR_WRITE_TYPICAL_TIME_USEC,   // UINT32 Duration_Max_WordWrite_uSec;
    FLASH_BLOCK_ERASE_ACTUAL_TIME_USEC,     // UINT32 Duration_Max_SectorErase_uSec;
    FLASH_BYTES_PER_SECTOR,                 // UINT32 BytesPerSector;

    FLASH_MEMORY_Size,                      // UINT32 Size;

    RAM_BS__NUM_REGIONS,              // UINT32 NumRegions;
    g_RAM_BS_BlkRegion,               //const BlockRegionInfo* pRegions;
};


struct MEMORY_MAPPED_NOR_BLOCK_CONFIG g_RAM_BS_Config =
{
    { // BLOCK_CONFIG
        {
        	GPIO_PIN_NONE,      // GPIO_PIN             Pin;
        	FALSE,              // BOOL                 ActiveState;
        },

        &g_RAM_BS_DeviceInfo,         // BlockDeviceinfo
    },

    { // CPU_MEMORY_CONFIG
        0,                                  // UINT8  CPU_MEMORY_CONFIG::ChipSelect;
        TRUE,                               // UINT8  CPU_MEMORY_CONFIG::ReadOnly;
        0,                                  // UINT32 CPU_MEMORY_CONFIG::WaitStates;
        0,                                  // UINT32 CPU_MEMORY_CONFIG::ReleaseCounts;
        32,                                 // UINT32 CPU_MEMORY_CONFIG::BitWidth;
        RAM_BS__BASE_ADDRESS,               // UINT32 CPU_MEMORY_CONFIG::BaseAddress;
        RAM_BS__SIZE,                       // UINT32 CPU_MEMORY_CONFIG::SizeInBytes;
        0,                                  // UINT8                CPU_MEMORY_CONFIG::XREADYEnable
        0,                                  // UINT8                CPU_MEMORY_CONFIG::ByteSignalsForRead
        0,                                  // UINT8                CPU_MEMORY_CONFIG::ExternalBufferEnable
    },

    0,                                      // UINT32  ChipProtection;
    FLASH_MANUFACTURER_CODE,                // FLASH_WORD ManufacturerCode;
    FLASH_DEVICE_CODE,                      // FLASH_WORD DeviceCode;
};

//--//


#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata = "g_RAM_BS"
#endif

struct BlockStorageDevice g_RAM_BS;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata
#endif

//--//
