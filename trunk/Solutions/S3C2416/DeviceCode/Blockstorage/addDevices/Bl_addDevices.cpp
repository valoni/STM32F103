/*
 * Bl_addDevices.cpp
 *
 *  Created on: 15.6.2011
 *      Author: Matti Eerola
 */

#include <tinyhal.h>

extern struct BlockStorageDevice  g_RAM_BS;
extern struct IBlockStorageDevice g_RAM_BS_DeviceTable;
extern struct BLOCK_CONFIG        g_RAM_BS_Config;

void BlockStorage_AddDevices()
{
    BlockStorageList::AddDevice( &g_RAM_BS, &g_RAM_BS_DeviceTable, &g_RAM_BS_Config, FALSE );
}
