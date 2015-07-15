////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "BlockStorageDriver_Nand.h"
#include "fsmc_nand.h"

//--------------------------------------------------------------------------

BOOL BlockStorageDriver_Nand::ChipInitialize( void* context )
{
	//Becareful: The JP11 jumper must be 1-2
	
 	/* FSMC Initialization */
	FSMC_NAND_Init();
	
	return TRUE;
}

BOOL BlockStorageDriver_Nand::ChipUnInitialize( void* context )
{
	return TRUE;
}

const BlockDeviceInfo* BlockStorageDriver_Nand::GetDeviceInfo( void* context )
{
	BLOCK_CONFIG* pBlockConfig = (BLOCK_CONFIG* )context;
  
  if(pBlockConfig == NULL)
  {
  	return NULL;
  }
  
	return pBlockConfig->BlockDeviceInformation;  
}

BOOL  BlockStorageDriver_Nand::ChipReadOnly( void* context, BOOL On, UINT32 ProtectionKey )
{
	return TRUE;
}


BOOL  BlockStorageDriver_Nand::Read( void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff)
{	
	if(pSectorBuff == NULL)
	{
		return FALSE;
	}

	NAND_ADDRESS NandAddress = {0};
	DWORD dwBeginOffset = 0; 
	DWORD dwEndOffset = 0; 
	if(ConvertToNandAddress(context,Address,NumBytes,NandAddress,dwBeginOffset,dwEndOffset) == FALSE)
	{
		return FALSE;
	}
	
	uint32_t addressStatus = NAND_VALID_ADDRESS;
	DWORD dwIndex = 0;
	if(dwBeginOffset != 0)
	{
		//Need to read the offset value
		BYTE szBuf[NAND_PAGE_SIZE] = {0};
		FSMC_NAND_ReadSmallPage(szBuf,NandAddress,1);
		
		//Calculate page address 
    addressStatus = FSMC_NAND_AddressIncrement(&NandAddress);
    
    //Copy the value
		DWORD dwCopy = (NAND_PAGE_SIZE - dwBeginOffset > NumBytes) ? NumBytes : (NAND_PAGE_SIZE - dwBeginOffset);
    for(DWORD i = 0; i < dwCopy; i ++)
    {
    	pSectorBuff[dwIndex ++] = szBuf[dwBeginOffset + i];
    }
    
    //To check whether read all data
		if(NumBytes == dwIndex)
		{
			//Finish reading
			return TRUE;
		}
		
		//To check the increased address is invalidate or not
		if(addressStatus == NAND_INVALID_ADDRESS)
		{
				return FALSE;	
		}
	}
	

	
	//Read the next value in page unit
	DWORD dwReadSize = NumBytes - dwIndex - dwEndOffset;
	DWORD dwReadPage = dwReadSize / NAND_PAGE_SIZE;
	if(dwReadPage != 0)
	{
		FSMC_NAND_ReadSmallPage(&pSectorBuff[dwIndex],NandAddress,dwReadPage);
		
		//Increase the flag
		dwIndex += dwReadSize;
		
		//To check the increased address is invalidate or not
		if(IncreaseNandAddress(context,NandAddress,dwReadSize) == FALSE  && dwEndOffset != 0)
		{
			return FALSE;
		}
	}
	
	if(dwEndOffset != 0)
	{
		//Need to read the end offset value
		BYTE szBuf[NAND_PAGE_SIZE] = {0};
		FSMC_NAND_ReadSmallPage(szBuf,NandAddress,1);
		
		//Copy the value
	  for(DWORD i = 0; i < dwEndOffset; i ++)
	  {
	  	pSectorBuff[dwIndex ++] = szBuf[i];
	  }
	}
	
	return TRUE;

}


BOOL BlockStorageDriver_Nand::Write(void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff, BOOL ReadModifyWrite)
{
	if(pSectorBuff == NULL)
	{
		return FALSE;
	}

	NAND_ADDRESS NandAddress = {0};
	DWORD dwBeginOffset = 0; 
	DWORD dwEndOffset = 0; 
	if(ConvertToNandAddress(context,Address,NumBytes,NandAddress,dwBeginOffset,dwEndOffset) == FALSE)
	{
		return FALSE;
	}
	
	//The begin offset address.Read the page,and modify,last write to the flash
	uint32_t addressStatus = NAND_VALID_ADDRESS;
	DWORD dwIndex = 0;
	if(dwBeginOffset != 0)
	{
		//Read the page value
		BYTE szBuf[NAND_PAGE_SIZE] = {0};
		FSMC_NAND_ReadSmallPage(szBuf,NandAddress,1);
		
		DWORD dwModifyCount = (NAND_PAGE_SIZE - dwBeginOffset > NumBytes) ? NumBytes : (NAND_PAGE_SIZE - dwBeginOffset);
		
		//Modify the buffer
		for(DWORD i = 0; i < dwModifyCount; i ++)
		{
			szBuf[dwBeginOffset + i] = pSectorBuff[dwIndex ++];
		}
		
		//Write to the flash
		FSMC_NAND_WriteSmallPage(szBuf,NandAddress,1);
		
		//Increase the address
		addressStatus = FSMC_NAND_AddressIncrement(&NandAddress);
		
		//To check whether write all data
		if(NumBytes == dwIndex)
		{
			//Finish writing
			return TRUE;
		}
		
		
		//To check the increased address is invalidate or not
		if(addressStatus == NAND_INVALID_ADDRESS)
		{
			return FALSE;	
		}
		
	}
		
	
	//Write the next value in page unit
	DWORD dwWriteSize = NumBytes - dwIndex - dwEndOffset;
	DWORD dwWritePage = dwWriteSize / NAND_PAGE_SIZE;
	if(dwWritePage != 0)
	{
		FSMC_NAND_WriteSmallPage(&pSectorBuff[dwIndex],NandAddress,dwWritePage);
		
		//Increase the flag
		dwIndex += dwWriteSize;
		
		//To check the increased address is invalidate or not
		if(IncreaseNandAddress(context,NandAddress,dwWriteSize) == FALSE && dwEndOffset != 0)
		{
			return FALSE;
		}
	}
	
	if(dwEndOffset != 0)
	{
		//Need to read the end offset value
		BYTE szBuf[NAND_PAGE_SIZE] = {0};
		FSMC_NAND_ReadSmallPage(szBuf,NandAddress,1);
		
		//Modify the buffer
		for(DWORD i = 0; i < dwEndOffset; i ++)
		{
			szBuf[i] = pSectorBuff[dwIndex ++];
		}
		
		//Write to the flash
		FSMC_NAND_WriteSmallPage(szBuf,NandAddress,1);
	}
	
	return TRUE;
}

BOOL BlockStorageDriver_Nand::Memset(void* context, ByteAddress Address, UINT8 Data, UINT32 NumBytes)
{
	if(NumBytes == 0)
	{
		return FALSE;
	}
	
	UINT8 szBuf[NAND_PAGE_SIZE] = {0};
	memset(szBuf,Data,NumBytes);
	
	BOOL bRes = TRUE;
	DWORD dwWriteCount = 0;
	while(TRUE)
	{
		//Check the write range.
		if(dwWriteCount >= NumBytes)
		{
			break;
		}

		//Write the data
		DWORD dwWrite = (dwWriteCount + NAND_PAGE_SIZE > NumBytes) ? (NumBytes - dwWriteCount) : NAND_PAGE_SIZE;
		bRes = Write(context,Address,dwWrite,szBuf,TRUE);
		if(bRes == FALSE)
		{
			break;
		}
			
		//Increase the flag
		dwWriteCount += dwWrite;
		Address += dwWrite;
	}
	
	return bRes;
}

BOOL BlockStorageDriver_Nand::GetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata)
{
	return TRUE;
}

BOOL BlockStorageDriver_Nand::SetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata)
{
	return TRUE;
}



BOOL BlockStorageDriver_Nand::IsBlockErased( void* context, ByteAddress Address, UINT32 BlockLength )
{
	BOOL bRes = TRUE;
		
	DWORD dwLenCount = 0;
	while(TRUE)
	{
		DWORD dwChkLen = dwLenCount + NAND_PAGE_SIZE > BlockLength ? BlockLength - dwLenCount : NAND_PAGE_SIZE;
		
		BYTE szBuf[NAND_PAGE_SIZE] = {0};
		Read(context,Address,dwChkLen,szBuf);
		
		for(DWORD i = 0; i < dwChkLen; i ++)
		{
			if(szBuf[i] != 0xFF)
			{
				//The byte isn't erased,so set the flag.
				bRes = FALSE;
				break;
			}
		}
		
		//If the flag is FALSE,needn't to check,so break.
		if(bRes == FALSE)
		{
			break;
		}
		
		Address += dwChkLen;
		dwLenCount += dwChkLen;
		
		if(dwLenCount == BlockLength)
		{
			break;
		}
		
	}
	
	return bRes;
}


BOOL BlockStorageDriver_Nand::EraseBlock( void* context, ByteAddress Sector )
{
	NAND_ADDRESS NandAddress = {0};
	DWORD dwBeginOffset = 0; 
	DWORD dwEndOffset = 0; 
	if(ConvertToNandAddress(context,Sector,1,NandAddress,dwBeginOffset,dwEndOffset) == FALSE)
	{
		return FALSE;
	}
	
	FSMC_NAND_EraseBlock(NandAddress);
	
	return TRUE;
}

void  BlockStorageDriver_Nand::SetPowerState( void* context, UINT32 State )
{
	return;
}

//--//

// Public functions

BOOL BlockStorageDriver_Nand::ReadProductID( void* context, FLASH_WORD& ManufacturerCode, FLASH_WORD& DeviceCode )
{
	NAND_IDTypeDef NAND_ID;
	FSMC_NAND_ReadID(&NAND_ID);
	
	ManufacturerCode = NAND_ID.Maker_ID;
	DeviceCode = NAND_ID.Device_ID;
	return TRUE;
}



BOOL BlockStorageDriver_Nand::ConvertToNandAddress( void* context,ByteAddress byteAddr,DWORD Length,NAND_ADDRESS &NandAddress,DWORD &dwBeginOffset,DWORD &dwEndOffset)
{
	BLOCK_CONFIG* pBlockConfig = (BLOCK_CONFIG*)context;
	if(pBlockConfig == NULL)
	{
		return FALSE;
	}
	
	UINT32 RegionIndex, RangeIndex;
	if (pBlockConfig->BlockDeviceInformation->FindRegionFromAddress( byteAddr, RegionIndex, RangeIndex) == FALSE)
	{
		return FALSE;
	}
	
	const BlockRegionInfo* pBlockRegionInfo = &pBlockConfig->BlockDeviceInformation->Regions[RegionIndex];
	
	//The begin offset in the first page
	dwBeginOffset = (byteAddr - pBlockRegionInfo->Start) % pBlockConfig->BlockDeviceInformation->BytesPerSector;
	
	//The end offset in the last page which point to the first invalid index
	dwEndOffset = (Length - (NAND_PAGE_SIZE - dwBeginOffset) ) % pBlockConfig->BlockDeviceInformation->BytesPerSector;
	
	
	//Begin star address in relatively
	DWORD dwBeginAddrRelative = byteAddr - pBlockRegionInfo->Start;
	
	//The zone
	DWORD dwZoneSize = pBlockRegionInfo->NumBlocks * pBlockRegionInfo->BytesPerBlock;	
	NandAddress.Zone = dwBeginAddrRelative / dwZoneSize;
	
	//The block
	DWORD dwLeave = dwBeginAddrRelative - (NandAddress.Zone * dwZoneSize);
	NandAddress.Block = dwLeave / pBlockRegionInfo->BytesPerBlock;
	
	//The page
	dwLeave = dwLeave - (NandAddress.Block * pBlockRegionInfo->BytesPerBlock);
	//BytesPerSector should be the same with NAND_PAGE_SIZE
	NandAddress.Page = dwLeave / pBlockConfig->BlockDeviceInformation->BytesPerSector; 	
	
	if(NandAddress.Zone > NAND_BLOCK_SIZE)
	{
		memset(&NandAddress,0,sizeof(NandAddress));
		return FALSE;
	}
	else
	{
		return TRUE;
	}
		
	
}


BOOL BlockStorageDriver_Nand::IncreaseNandAddress(void* context,NAND_ADDRESS &NandAddress,DWORD dwLen)
{
	BLOCK_CONFIG* pBlockConfig = (BLOCK_CONFIG*)context;
	if(pBlockConfig == NULL)
	{
		return FALSE;
	}
	
	//Use the first block device information,so the index is 0
	const BlockRegionInfo* pBlockRegionInfo = &pBlockConfig->BlockDeviceInformation->Regions[0];
	
	//The zone
	DWORD dwZoneSize = pBlockRegionInfo->NumBlocks * pBlockRegionInfo->BytesPerBlock;	
	NandAddress.Zone += dwLen / dwZoneSize;
	
	//The block
	DWORD dwLeave = dwLen - (NandAddress.Zone * dwZoneSize);
	NandAddress.Block += dwLeave / pBlockRegionInfo->BytesPerBlock;
	
	//The page
	dwLeave = dwLeave - (NandAddress.Block * pBlockRegionInfo->BytesPerBlock);
	//BytesPerSector should be the same with NAND_PAGE_SIZE
	NandAddress.Page += dwLeave / pBlockConfig->BlockDeviceInformation->BytesPerSector; 
	
	
	//Adjust the value
	DWORD dwBlockMore = NandAddress.Page / NAND_BLOCK_SIZE;
	if(dwBlockMore != 0)
	{
		NandAddress.Block += dwBlockMore;
		NandAddress.Page -= dwBlockMore * NAND_BLOCK_SIZE;
	}
	
	DWORD dwZoneMore = NandAddress.Block / NAND_ZONE_SIZE;
	if(dwZoneMore != 0)
	{
		NandAddress.Zone += dwZoneMore;
		NandAddress.Block -= dwZoneMore * NAND_ZONE_SIZE;
	}
	
	if(NandAddress.Zone > NAND_BLOCK_SIZE)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
//--// ---------------------------------------------------

#if defined(arm) || defined(__arm)
#pragma arm section code = "SectionForFlashOperations"
#endif

UINT32 BlockStorageDriver_Nand::MaxSectorWrite_uSec( void* context )
{
	BLOCK_CONFIG* pBlockConfig = (BLOCK_CONFIG*)context;
	if(pBlockConfig == NULL)
	{
		//Return 100ms
		return 100;
	}
	
	return pBlockConfig->BlockDeviceInformation->MaxSectorWrite_uSec;
	
}


UINT32 BlockStorageDriver_Nand::MaxBlockErase_uSec( void* context )
{
	BLOCK_CONFIG* pBlockConfig = (BLOCK_CONFIG*)context;
	if(pBlockConfig == NULL)
	{
		//Return 100ms
		return 100;
	}
	
	return pBlockConfig->BlockDeviceInformation->MaxBlockErase_uSec;
}


#if defined(arm) || defined(__arm)
#pragma arm section code 
#endif


//--// 

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata = "g_I28F_16_BS_DeviceTable"
#endif

struct IBlockStorageDevice g_Nand_DeviceTable = 
{                          
    &BlockStorageDriver_Nand::ChipInitialize,
    &BlockStorageDriver_Nand::ChipUnInitialize,
    &BlockStorageDriver_Nand::GetDeviceInfo,
    &BlockStorageDriver_Nand::Read,
    &BlockStorageDriver_Nand::Write,
    &BlockStorageDriver_Nand::Memset,
    &BlockStorageDriver_Nand::GetSectorMetadata,
    &BlockStorageDriver_Nand::SetSectorMetadata,
    &BlockStorageDriver_Nand::IsBlockErased,
    &BlockStorageDriver_Nand::EraseBlock,
    &BlockStorageDriver_Nand::SetPowerState,
    &BlockStorageDriver_Nand::MaxSectorWrite_uSec,
    &BlockStorageDriver_Nand::MaxBlockErase_uSec,    
};

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata 
#endif 



