#include <tinyhal.h>
#include "fsmc_NOR.h"
#include "BlockStorageDriver_NOR.h"
#include "AvailableNorID.h"

//----------------------------------------------------------------------------------
//Macro
#define MX29LV160CBTC_REGIONS_COUNT         			4
#define FLASH_MEMORY_SIZE													0x200000
#define FLASH_SECTOR_WRITE_TYPICAL_TIME_USEC			360				//I use actual byte as sector,so the time is the byte time,which is declared:360 us  
#define FLASH_BLOCK_ERASE_ACTUAL_TIME_USEC				15000000			//I use actual sector as block,so the time is the sector time,which is declared:15 sec  

#define REGION1_START_ADDRESS			NOR_FLASH_BASE_ADDRESS					
#define REGION1_BLOCK_COUNT				1
#define REGION1_BLOCK_SIZE				0x4000	//16KB

#define REGION2_START_ADDRESS			(REGION1_START_ADDRESS + REGION1_BLOCK_SIZE * REGION1_BLOCK_COUNT)			
#define REGION2_BLOCK_COUNT				2
#define REGION2_BLOCK_SIZE				0x2000	//8KB

#define REGION3_START_ADDRESS			(REGION2_START_ADDRESS + REGION2_BLOCK_SIZE * REGION2_BLOCK_COUNT)									
#define REGION3_BLOCK_COUNT				1
#define REGION3_BLOCK_SIZE				0x8000 //32KB


#define REGION4_START_ADDRESS			(REGION3_START_ADDRESS + REGION3_BLOCK_SIZE * REGION3_BLOCK_COUNT)						
#define REGION4_BLOCK_COUNT				31
#define REGION4_BLOCK_SIZE			  0x10000	//64KB
//----------------------------------------------------------------------------------
//Global variable

struct BlockStorageDevice  g_Nor_Device;


const BlockRange g_MX29LV160CBTC_BlockRange1[] =
{
	{ BlockRange::BLOCKTYPE_CONFIG    ,   0,   0 },	// SA0
};

const BlockRange g_MX29LV160CBTC_BlockRange2[] =
{
	{ BlockRange::BLOCKTYPE_CONFIG    ,   0,   1 },	// SA1 ~ SA2
};

const BlockRange g_MX29LV160CBTC_BlockRange3[] =
{
	{ BlockRange::BLOCKTYPE_CONFIG    ,   0,   0 },	// SA3
};

const BlockRange g_MX29LV160CBTC_BlockRange4[] =
{
	{ BlockRange::BLOCKTYPE_DEPLOYMENT,   0,  7 },	//SA4 ~ SA10
	{ BlockRange::BLOCKTYPE_DEPLOYMENT,  8,  13 }, 	//SA11 ~ SA17
	{ BlockRange::BLOCKTYPE_DEPLOYMENT, 14, 23 }, 	//SA18 ~ SA28
	{ BlockRange::BLOCKTYPE_STORAGE_A, 24, 27 }, 		//SA29 ~ SA31
	{ BlockRange::BLOCKTYPE_STORAGE_B , 28,30 }, 		//SA32 ~ SA34
};


const BlockRegionInfo  g_MX29LV160CBTC_BlockRegionInfo[MX29LV160CBTC_REGIONS_COUNT] = 
{
	{
		REGION1_START_ADDRESS,   // ByteAddress   Start;              // Starting Sector address
		REGION1_BLOCK_COUNT,                 		 // UINT32          NumBlocks;          // total number of blocks in this region
		REGION1_BLOCK_SIZE,              // UINT32        BytesPerBlock;      // Total number of bytes per block (MUST be SectorsPerBlock * DataBytesPerSector)
		
		ARRAYSIZE_CONST_EXPR(g_MX29LV160CBTC_BlockRange1),
		g_MX29LV160CBTC_BlockRange1,
	},
	{
		REGION2_START_ADDRESS,   // ByteAddress   Start;              // Starting Sector address
		REGION2_BLOCK_COUNT,                 		 // UINT32          NumBlocks;          // total number of blocks in this region
		REGION2_BLOCK_SIZE,              // UINT32        BytesPerBlock;      // Total number of bytes per block (MUST be SectorsPerBlock * DataBytesPerSector)
		
		ARRAYSIZE_CONST_EXPR(g_MX29LV160CBTC_BlockRange2),
		g_MX29LV160CBTC_BlockRange2,
	},
	{
		REGION3_START_ADDRESS,   // ByteAddress   Start;              // Starting Sector address
		REGION3_BLOCK_COUNT,                 		 // UINT32          NumBlocks;          // total number of blocks in this region
		REGION3_BLOCK_SIZE,              // UINT32        BytesPerBlock;      // Total number of bytes per block (MUST be SectorsPerBlock * DataBytesPerSector)
		
		ARRAYSIZE_CONST_EXPR(g_MX29LV160CBTC_BlockRange3),
		g_MX29LV160CBTC_BlockRange3,
	},
	{
		REGION4_START_ADDRESS,   // ByteAddress   Start;              // Starting Sector address
		REGION4_BLOCK_COUNT,                 		 // UINT32          NumBlocks;          // total number of blocks in this region
		REGION4_BLOCK_SIZE,              // UINT32        BytesPerBlock;      // Total number of bytes per block (MUST be SectorsPerBlock * DataBytesPerSector)
		
		ARRAYSIZE_CONST_EXPR(g_MX29LV160CBTC_BlockRange4),
		g_MX29LV160CBTC_BlockRange4,
	},
};


BlockDeviceInfo g_MX29LV160CBTC_DeviceInfo =
{
	{  
		FALSE,                     // BOOL Removable;
		FALSE,                     // BOOL SupportsXIP;
		FALSE,                 		 // BOOL WriteProtected
	},
	
	FLASH_SECTOR_WRITE_TYPICAL_TIME_USEC,           // UINT32 Duration_Max_WordWrite_uSec;
	FLASH_BLOCK_ERASE_ACTUAL_TIME_USEC,             // UINT32 Duration_Max_SectorErase_uSec;
	1,                         // UINT32 BytesPerSector; // Bytes Per Sector
	
	FLASH_MEMORY_SIZE,     // UINT32 Size;
	
	MX29LV160CBTC_REGIONS_COUNT,                      // UINT32 NumRegions;
	g_MX29LV160CBTC_BlockRegionInfo,                      //const BlockRegionInfo* pRegions;
};


struct BLOCK_CONFIG g_MX29LV160CBTC_Config = 
{
	{
		GPIO_PIN_NONE,                       // GPIO_PIN             Pin;
		FALSE,                         // BOOL                 ActiveState;
	},
	&g_MX29LV160CBTC_DeviceInfo,
};

