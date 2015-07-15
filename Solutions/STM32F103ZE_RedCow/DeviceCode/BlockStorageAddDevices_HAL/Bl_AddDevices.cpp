////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

//--//

extern struct BlockStorageDevice  g_Nand_Device;
extern struct IBlockStorageDevice g_Nand_DeviceTable;
extern struct BLOCK_CONFIG        g_HY27UF081G2A_Config;

extern struct BlockStorageDevice  g_Nor_Device;
extern struct IBlockStorageDevice g_Nor_DeviceTable;
extern struct BLOCK_CONFIG        g_MX29LV160CBTC_Config;

void BlockStorage_AddDevices()
{
	BlockStorageList::AddDevice( &g_Nand_Device, &g_Nand_DeviceTable, &g_HY27UF081G2A_Config, FALSE );
	//BlockStorageList::AddDevice( &g_Nor_Device, &g_Nor_DeviceTable, &g_MX29LV160CBTC_Config, FALSE );
}

