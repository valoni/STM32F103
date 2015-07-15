////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _K9F2G_8_H_1
#define _K9F2G_8_H_1   1
#include "..\..\..\..\..\..\DeviceCode\Targets\Native\S3C2416\DeviceCode\s3c2416.h"
//--//

#define NFCONF_ECC_MLC		(1<<24)

#define NFCONF_ECC_1BIT		(0<<23)
#define NFCONF_ECC_4BIT		(2<<23)
#define NFCONF_ECC_8BIT		(1<<23)

#define NFCONT_ECC_ENC		(1<<18)
#define NFCONT_WP		(1<<16)
#define NFCONT_MECCLOCK		(1<<7)
#define NFCONT_SECCLOCK		(1<<6)
#define NFCONT_INITMECC		(1<<5)
#define NFCONT_INITSECC		(1<<4)
#define NFCONT_INITECC		(NFCONT_INITMECC | NFCONT_INITSECC)
#define NFCONT_CS_ALT		(1<<1)
#define NFCONT_CS		(1<<1)
#define NFSTAT_ECCENCDONE	(1<<7)
#define NFSTAT_ECCDECDONE	(1<<6)
#define NFSTAT_RnB		(1<<0)
#define NFESTAT0_ECCBUSY	(1<<31)

//--//

struct K9F2G_8_BS_Driver
{
    typedef UINT8 CHIP_WORD;

    //--//
    
    static BOOL ChipInitialize( void* context );
    static BOOL ChipUnInitialize( void* context );
    static BOOL ReadProductID( void* context, FLASH_WORD& ManufacturerCode, FLASH_WORD& DeviceCode );
    static const BlockDeviceInfo* GetDeviceInfo( void* context);
    static BOOL Read( void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff );
    static BOOL Write( void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff, BOOL ReadModifyWrite );
    static BOOL Memset( void* context, ByteAddress Address, UINT8 Data, UINT32 NumBytes );
    static BOOL GetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata);
    static BOOL SetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* sectorMetadata);
    static BOOL IsBlockErased( void* context, ByteAddress BlockStartAddress, UINT32 BlockLength );
    static BOOL EraseBlock( void* context, ByteAddress Sector );
    static void SetPowerState( void* context, UINT32 State );
    static UINT32 MaxSectorWrite_uSec( void* context );
    static UINT32 MaxBlockErase_uSec( void* context );

private:

    static BOOL WriteX( void* context, ByteAddress StartSector, UINT32 NumBytes, BYTE * pSectorBuff, BOOL ReadModifyWrite, BOOL fIncrementDataPtr );
    static void WaitReady();
    static void UnLocked()
		{ 
		S3C2416_NANDFLASH &nandflash = S3C2416::NANDFLASH();
		nandflash.NFCONT &= ~NFCONT_WP;
		}
				
    static void EnableCE()
		{ 
		S3C2416_NANDFLASH &nandflash = S3C2416::NANDFLASH();
		nandflash.NFCONT &= ~NFCONT_CS;
		}
	
    static void DisableCE()
		{
		S3C2416_NANDFLASH &nandflash = S3C2416::NANDFLASH();
		nandflash.NFCONT |= NFCONT_CS;
		}
	
    static void WriteCommand(UINT8 command) 
		{ 
	     S3C2416_NANDFLASH &nandflash = S3C2416::NANDFLASH();
	     nandflash.NFCMMD = command;
		}
	
    static void WriteAddress(UINT8 Address)
		{ 
	     S3C2416_NANDFLASH &nandflash = S3C2416::NANDFLASH();
	     nandflash.NFADDR= Address; 
		}
	
    static void WriteData8(UINT8 Data)
		{ 
	     S3C2416_NANDFLASH &nandflash = S3C2416::NANDFLASH();
	     nandflash.NFDATA= Data << 24;
		}
	
    static UINT8 ReadData8() 
		{
	    S3C2416_NANDFLASH &nandflash = S3C2416::NANDFLASH();
		return (UINT8)(nandflash.NFDATA>>24);
		}
	
    static BOOL ReadPage(ByteAddress StartSector, BYTE *outBuf, BYTE* inBuf, UINT32 size, UINT32 offset, UINT32 sectorSize, BOOL fIncrementDataPtr);
};

/// Nand flash commands
#define COMMAND_READ_1                  0x00
#define COMMAND_READ_2                  0x30
#define COMMAND_COPYBACK_READ_1         0x00
#define COMMAND_COPYBACK_READ_2         0x35
#define COMMAND_COPYBACK_PROGRAM_1      0x85
#define COMMAND_COPYBACK_PROGRAM_2      0x10
#define COMMAND_RANDOM_OUT              0x05
#define COMMAND_RANDOM_OUT_2            0xE0
#define COMMAND_RANDOM_IN               0x85
#define COMMAND_READID                  0x90
#define COMMAND_WRITE_1                 0x80
#define COMMAND_WRITE_2                 0x10
#define COMMAND_ERASE_1                 0x60
#define COMMAND_ERASE_2                 0xD0
#define COMMAND_STATUS                  0x70
#define COMMAND_RESET                   0xFF

/// Nand flash chip status codes
#define STATUS_READY                    (1 << 6)
#define STATUS_ERROR                    (1 << 0)

#endif // _K9F2G_8_H_1

