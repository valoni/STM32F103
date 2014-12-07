////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////#include <tinyhal.h>
#pragma once

#include <tinyhal.h>
#include "stm32f10x.h"

//---------------------------------------------------------------------
//Macro

//The flash mode.
#define	NOR_FLASH_MODE_WORD
//#define	NOR_FLASH_MODE_BYTE
//---------------------------------------------------------------------

struct BlockStorageDriver_Nor
{

    //--//

    static BOOL ChipInitialize( void* context );

    static BOOL ChipUnInitialize( void* context );

    static const BlockDeviceInfo* GetDeviceInfo( void* context );

    static BOOL Read( void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff);
    
    static BOOL Write( void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff, BOOL ReadModifyWrite);

    static BOOL Memset( void* context, ByteAddress Address, UINT8 Data, UINT32 NumBytes );

    static BOOL GetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata);

    static BOOL SetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata);

    static BOOL IsBlockErased( void* context, ByteAddress Address, UINT32 BlockLength );

    static BOOL EraseBlock( void* context, ByteAddress Address );

    static void SetPowerState( void* context, UINT32 State );

    static UINT32 MaxSectorWrite_uSec(void* context);

    static UINT32 MaxBlockErase_uSec(void* context);

    static BOOL ChipReadOnly( void* context, BOOL On, UINT32 ProtectionKey );

    static BOOL ReadProductID( void* context, FLASH_WORD& ManufacturerCode, FLASH_WORD& DeviceCode );
    

private:
		//--------------------------------------------------------------------------------------------------------------------
		//Description:
		//	Convert the input address to NOR_ADDRESS
		//
		//Parameters:
		//	context : [in] The input parameter
		//	Address : [in] The address for converting
		//	norAddress : [in] The buffer for storing the converted nor flash
		//----------------------------------------------------------------------------------------------------------------------
		static BOOL ConvertToNorAddress(void* context,ByteAddress byteAddress,uint32_t &norAddress);
};



