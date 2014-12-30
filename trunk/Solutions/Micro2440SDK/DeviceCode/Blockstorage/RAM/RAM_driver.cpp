/*
 * RAM_driver.cpp
 *
 *  Created on: 15.6.2011
 *      Author: Matti Eerola
 */

#include <tinyhal.h>
#include "RAM_driver.h"

//--//

BOOL RAM_BS_Driver::ChipInitialize( void* context )
{
    return TRUE;
}

BOOL RAM_BS_Driver::ChipUnInitialize( void* context )
{
    return TRUE;
}

const BlockDeviceInfo* RAM_BS_Driver::GetDeviceInfo( void* context )
{
    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*)context;

    return config->BlockConfig.BlockDeviceInformation;
}

BOOL  RAM_BS_Driver::ChipReadOnly( void* context, BOOL On, UINT32 ProtectionKey )
{
    return FALSE;
}


BOOL  RAM_BS_Driver::Read( void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff)
{
    if (pSectorBuff == NULL) return FALSE;

    Address = CPU_GetUncachableAddress(Address);

    CHIP_WORD* ChipAddress = (CHIP_WORD *)Address;
    CHIP_WORD* EndAddress  = (CHIP_WORD *)(Address + NumBytes);
    CHIP_WORD *pBuf        = (CHIP_WORD *)pSectorBuff;

    while(ChipAddress < EndAddress)
    {
        *pBuf++ = *ChipAddress++;
    }

    return TRUE;
}


BOOL RAM_BS_Driver::Write(void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff, BOOL ReadModifyWrite)
{
    if (pSectorBuff == NULL) return FALSE;

    Address = CPU_GetUncachableAddress(Address);

    CHIP_WORD* ChipAddress = (CHIP_WORD *)Address;
    CHIP_WORD* EndAddress  = (CHIP_WORD *)(Address + NumBytes);
    CHIP_WORD *pBuf        = (CHIP_WORD *)pSectorBuff;

    while(ChipAddress < EndAddress)
    {
        *ChipAddress++ = *pBuf++;
    }

    return TRUE;
}

BOOL RAM_BS_Driver::Memset(void* context, ByteAddress Address, UINT8 Data, UINT32 NumBytes)
{
    CHIP_WORD chipData;
    memset(&chipData, Data, sizeof(CHIP_WORD));

    Address = CPU_GetUncachableAddress(Address);

    CHIP_WORD* ChipAddress = (CHIP_WORD *)Address;
    CHIP_WORD* EndAddress  = (CHIP_WORD *)(Address + NumBytes);

    while(ChipAddress < EndAddress)
    {
        *ChipAddress++ = chipData;
    }

    return TRUE;
}

BOOL RAM_BS_Driver::GetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata)
{
    return FALSE;
}

BOOL RAM_BS_Driver::SetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata)
{
    return FALSE;
}



BOOL RAM_BS_Driver::IsBlockErased( void* context, ByteAddress Address, UINT32 BlockLength )
{
	Address = CPU_GetUncachableAddress(Address);

    CHIP_WORD* ChipAddress = (CHIP_WORD *) Address;
    CHIP_WORD* EndAddress  = (CHIP_WORD *)(Address + BlockLength);

    while(ChipAddress < EndAddress)
    {
        if(*ChipAddress != 0x00)
        {
            return FALSE;
        }
        ChipAddress++;
    }

    return TRUE;
}


BOOL RAM_BS_Driver::EraseBlock( void* context, ByteAddress Sector )
{
	MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*)context;
    return Memset(context, Sector, 0x00, config->BlockConfig.BlockDeviceInformation->BytesPerSector);
}

void  RAM_BS_Driver::SetPowerState( void* context, UINT32 State )
{
    return;
}

//--//

// Public functions

BOOL RAM_BS_Driver::ReadProductID( void* context, FLASH_WORD& ManufacturerCode, FLASH_WORD& DeviceCode )
{
	ManufacturerCode = 0;
	DeviceCode = 0;
    return TRUE;
}



//--// ---------------------------------------------------

#if defined(arm) || defined(__arm)
#pragma arm section code = "SectionForFlashOperations"
#endif

UINT32 RAM_BS_Driver::MaxSectorWrite_uSec( void* context )
{
    return 1;
}


UINT32 RAM_BS_Driver::MaxBlockErase_uSec( void* context )
{
    return 1;

}

#if defined(arm) || defined(__arm)
#pragma arm section code
#endif


//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata = "g_RAM_BS_DeviceTable"
#endif

struct IBlockStorageDevice g_RAM_BS_DeviceTable =
{
    &RAM_BS_Driver::ChipInitialize,
    &RAM_BS_Driver::ChipUnInitialize,
    &RAM_BS_Driver::GetDeviceInfo,
    &RAM_BS_Driver::Read,
    &RAM_BS_Driver::Write,
    &RAM_BS_Driver::Memset,
    &RAM_BS_Driver::GetSectorMetadata,
    &RAM_BS_Driver::SetSectorMetadata,
    &RAM_BS_Driver::IsBlockErased,
    &RAM_BS_Driver::EraseBlock,
    &RAM_BS_Driver::SetPowerState,
    &RAM_BS_Driver::MaxSectorWrite_uSec,
    &RAM_BS_Driver::MaxBlockErase_uSec,
};

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata
#endif



