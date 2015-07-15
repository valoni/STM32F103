////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "BlockStorageDriver_Nor.h"
#include "stm3210e_eval_fsmc_nor.h"

//--------------------------------------------------------------------------

BOOL BlockStorageDriver_Nor::ChipInitialize( void* context )
{
	/* Configure FSMC Bank1 NOR/SRAM2 */
	NOR_Init();
  
	return TRUE;
}

BOOL BlockStorageDriver_Nor::ChipUnInitialize( void* context )
{
	return TRUE;
}

const BlockDeviceInfo* BlockStorageDriver_Nor::GetDeviceInfo( void* context )
{
	BLOCK_CONFIG* pConfig = (BLOCK_CONFIG* )context;
  
  if(pConfig == NULL)
  {
  	return NULL;
  }
  
	return pConfig->BlockDeviceInformation;  
}

BOOL  BlockStorageDriver_Nor::ChipReadOnly( void* context, BOOL On, UINT32 ProtectionKey )
{
	return TRUE;
}


BOOL  BlockStorageDriver_Nor::Read( void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff)
{	
	uint32_t norAddr = 0;
	if(ConvertToNorAddress(context,Address,norAddr) == FALSE)
	{
		return FALSE;
	}
	
	DWORD dwIndex = 0;
	if(norAddr % 2 != 0)
	{
		uint16_t buf;
		NOR_ReadBuffer(&buf, norAddr - 1, 1);
		
		pSectorBuff[dwIndex ++] = buf;
	}
	
	DWORD dwReadWord = (NumBytes - dwIndex)/ 2;
	if(dwReadWord != 0)
	{
		NOR_ReadBuffer(reinterpret_cast<uint16_t *>(pSectorBuff), norAddr + dwIndex, dwReadWord);
	}
	
	if(NumBytes % 2 != 0)
	{
		//Read the last word
		uint16_t buf = 0;
		NOR_ReadBuffer(&buf, norAddr + dwReadWord + dwIndex, 1);
		pSectorBuff[NumBytes - 1] = buf >> 8;
	}

	return TRUE;

}


BOOL BlockStorageDriver_Nor::Write(void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff, BOOL ReadModifyWrite)
{
	uint32_t norAddr = 0;
	if(ConvertToNorAddress(context,Address,norAddr) == FALSE)
	{
		return FALSE;
	}
	
	DWORD dwIndex = 0;
	if(norAddr % 2 != 0)
	{
		uint16_t buf;
		NOR_ReadBuffer(&buf, norAddr - 1, 1);
		
		buf = buf & 0xFF00 + pSectorBuff[dwIndex ++];
		NOR_WriteBuffer(&buf, norAddr, 1);
	}
	
	DWORD dwWriteWord = (NumBytes - dwIndex)/ 2;
	if(dwWriteWord != 0)
	{
		NOR_WriteBuffer(reinterpret_cast<uint16_t *>(pSectorBuff), norAddr + dwIndex, dwWriteWord);
	}
	
	if(NumBytes % 2 != 0)
	{
		//Read the last word
		uint16_t buf = 0;
		NOR_ReadBuffer(&buf, norAddr + dwWriteWord + dwIndex, 1);
		
		//If you write the code is just like : buf = (buf & 0x00FF) + static_cast<uint16_t >(pSectorBuff[NumBytes - 1]) << 8;
		//the result would be wrong! How bad the compiler is! So I only separate the source code.
		buf = (buf & 0x00FF);
		buf += pSectorBuff[NumBytes - 1] << 8;
		NOR_WriteBuffer(&buf, norAddr + dwWriteWord + dwIndex, 1);
	}
	
	return TRUE;
}

BOOL BlockStorageDriver_Nor::Memset(void* context, ByteAddress Address, UINT8 Data, UINT32 NumBytes)
{
	for(DWORD i = 0; i < NumBytes; i ++)
	{
		Write(context,Address + i,1,&Data,TRUE);
	}
	return TRUE;
}

BOOL BlockStorageDriver_Nor::GetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata)
{
	uint32_t norAddr = 0;
	if(ConvertToNorAddress(context,SectorStart,norAddr) == FALSE)
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL BlockStorageDriver_Nor::SetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata)
{
	uint32_t norAddr = 0;
	if(ConvertToNorAddress(context,SectorStart,norAddr) == FALSE)
	{
		return FALSE;
	}
	
	return TRUE;
}



BOOL BlockStorageDriver_Nor::IsBlockErased( void* context, ByteAddress Address, UINT32 BlockLength )
{
	BOOL bRes = TRUE;
	for(DWORD i = 0; i < BlockLength; i ++)
	{
		BYTE byteRead = 0;
		Read(context,Address + i,1,&byteRead);
		
		if(byteRead != 0xFF)
		{
			bRes = FALSE;
			break;
		}
		
	}
	
	return bRes;
}


BOOL BlockStorageDriver_Nor::EraseBlock( void* context, ByteAddress Sector )
{
	uint32_t norAddr = 0;
	if(ConvertToNorAddress(context,Sector,norAddr) == FALSE)
	{
		return FALSE;
	}
	
	NOR_EraseBlock(norAddr);
	return TRUE;

}

void  BlockStorageDriver_Nor::SetPowerState( void* context, UINT32 State )
{
	return;
}

//--//

// Public functions

BOOL BlockStorageDriver_Nor::ReadProductID( void* context, FLASH_WORD& ManufacturerCode, FLASH_WORD& DeviceCode )
{
	/* Read NOR memory ID */
  NOR_IDTypeDef NOR_ID = {0};
  NOR_ReadID(&NOR_ID);
  
  ManufacturerCode = NOR_ID.Manufacturer_Code;
  DeviceCode = NOR_ID.Device_Code1;
	
  NOR_ReturnToReadMode();
  
	return TRUE;
}

BOOL BlockStorageDriver_Nor::ConvertToNorAddress(void* context,ByteAddress byteAddress,uint32_t &norAddress)
{
	#ifdef NOR_FLASH_MODE_WORD
		norAddress = (byteAddress - NOR_FLASH_BASE_ADDRESS) / 2;
	#else
		norAddress = byteAddress - NOR_FLASH_BASE_ADDRESS;
	#endif
	
	return TRUE;
}


//--// ---------------------------------------------------

#if defined(arm) || defined(__arm)
#pragma arm section code = "SectionForFlashOperations"
#endif

UINT32 BlockStorageDriver_Nor::MaxSectorWrite_uSec( void* context )
{
	BLOCK_CONFIG* pConfig = (BLOCK_CONFIG*)context;
	if(pConfig == NULL)
	{
		//Return 100ms
		return 100;
	}
	
	return pConfig->BlockDeviceInformation->MaxSectorWrite_uSec;
}


UINT32 BlockStorageDriver_Nor::MaxBlockErase_uSec( void* context )
{
	BLOCK_CONFIG* pConfig = (BLOCK_CONFIG*)context;
	if(pConfig == NULL)
	{
		//Return 100ms
		return 100;
	}
	
	return pConfig->BlockDeviceInformation->MaxBlockErase_uSec;
    
}

#if defined(arm) || defined(__arm)
#pragma arm section code 
#endif


//--// 

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata = "g_I28F_16_BS_DeviceTable"
#endif

struct IBlockStorageDevice g_Nor_DeviceTable = 
{                          
    &BlockStorageDriver_Nor::ChipInitialize,
    &BlockStorageDriver_Nor::ChipUnInitialize,
    &BlockStorageDriver_Nor::GetDeviceInfo,
    &BlockStorageDriver_Nor::Read,
    &BlockStorageDriver_Nor::Write,
    &BlockStorageDriver_Nor::Memset,
    &BlockStorageDriver_Nor::GetSectorMetadata,
    &BlockStorageDriver_Nor::SetSectorMetadata,
    &BlockStorageDriver_Nor::IsBlockErased,
    &BlockStorageDriver_Nor::EraseBlock,
    &BlockStorageDriver_Nor::SetPowerState,
    &BlockStorageDriver_Nor::MaxSectorWrite_uSec,
    &BlockStorageDriver_Nor::MaxBlockErase_uSec,    
};

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata 
#endif 



