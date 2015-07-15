////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Implementation for STM32F103ZET board (STM32): Copyright (c) Oberon microsystems, Inc.
//
//  *** Block Storage AddDevice Configuration ***
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>


extern struct BlockStorageDevice  g_STM32_BS;
extern struct IBlockStorageDevice g_STM32_Flash_DeviceTable;
extern struct BLOCK_CONFIG        g_STM32_BS_Config;

extern struct BlockStorageDevice  g_W25Q64_BS;
extern struct IBlockStorageDevice g_W25Q64_Flash_DeviceTable;
extern struct BLOCK_CONFIG        g_W25Q64_BS_Config;

extern struct BlockStorageDevice  g_Nor_Device;
extern struct IBlockStorageDevice g_Nor_DeviceTable;
extern struct BLOCK_CONFIG        g_MX29LV160CBTC_Config;

void BlockStorage_AddDevices()
{
    BlockStorageList::AddDevice( &g_STM32_BS, &g_STM32_Flash_DeviceTable, &g_STM32_BS_Config, FALSE );
	BlockStorageList::AddDevice( &g_W25Q64_BS,&g_W25Q64_Flash_DeviceTable,&g_W25Q64_BS_Config, FALSE );
	//BlockStorageList::AddDevice( &g_Nor_Device, &g_Nor_DeviceTable, &g_MX29LV160CBTC_Config, FALSE );
}

