////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

//--//


//#define USE_WEAR_LEVELING

extern struct BlockStorageDevice     g_K9F2G_8_BS;

#ifdef USE_WEAR_LEVELING
extern struct IBlockStorageDevice    g_BS_WearLeveling_DeviceTable;
extern struct BS_WearLeveling_Config g_K9F2G_8_WearLeveling_Config;
#else
extern struct IBlockStorageDevice    g_K9F2G08_BS_DeviceTable; 
extern struct BLOCK_CONFIG           g_K9F2G_8_BS_Config;
#endif
extern struct BlockStorageDevice     g_RAM_BS;
extern struct IBlockStorageDevice    g_RAM_BS_DeviceTable;
extern struct BLOCK_CONFIG           g_RAM_BS_Config;

//--//

void BlockStorage_AddDevices()
{
	 BlockStorageList::AddDevice( &g_RAM_BS, &g_RAM_BS_DeviceTable, &g_RAM_BS_Config, FALSE );
	 /*
#ifdef USE_WEAR_LEVELING
   // BlockStorageList::AddDevice( &g_K9F2G_8_BS, &g_BS_WearLeveling_DeviceTable, &g_K9F2G_8_WearLeveling_Config, FALSE );
#else
    BlockStorageList::AddDevice( &g_K9F2G_8_BS, &g_K9F2G08_BS_DeviceTable, &g_K9F2G_8_BS_Config, FALSE );
#endif
  //  BlockStorageList::AddDevice( &g_K9F2G_8_BS, &g_K9F2G08_BS_DeviceTable, &g_K9F2G_8_BS_Config, FALSE );
  */
}

//--//

