////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////#include <tinyhal.h>
#pragma once

#include <tinyhal.h>
#include "fsmc_nand.h"


//--//

struct BlockStorageDriver_Nand
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
		//	Convert the input address to NAND_ADDRESS
		//
		//Parameters:
		//	context : [in] The input parameter
		//	Address : [in] The address for converting
		//	Length : [in] The length of buffer to calculate the end offset
		//	NandAddress : [out] The converted address
		//	dwBeginOffset : [out] Point the begin index
		//	dwEndOffset : [out] Point to the end index.The index is invalid,and (index - 1) is valid,that means open area.
		//----------------------------------------------------------------------------------------------------------------------
		static BOOL ConvertToNandAddress(void* context,ByteAddress Address,DWORD Length,NAND_ADDRESS &NandAddress,DWORD &dwBeginOffset,DWORD &dwEndOffset);
		
		//--------------------------------------------------------------------------------------------------------------------
		//Description:
		//	Convert the input address to NAND_ADDRESS
		//
		//Parameters:
		//	context : [in] The input parameter
		//	NandAddress : [in] The current nand address
		//	dwLen : [in] The increase length.
		//--------------------------------------------------------------------------------------------------------------------
		static BOOL IncreaseNandAddress(void* context,NAND_ADDRESS &NandAddress,DWORD dwLen);
};



