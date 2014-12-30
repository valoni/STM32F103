//-----------------------------------------------------------------------------
//
//                   ** WARNING! ** 
//    This file was generated automatically by a tool.
//    Re-running the tool will overwrite this file.
//    You should copy this file to a custom location
//    before adding any customization in the copy to
//    prevent loss of your changes when the tool is
//    re-run.
//
//-----------------------------------------------------------------------------


#include "NXP_SPOT_Interop.h"
#include "NXP_SPOT_Interop_NXP_SPOT_Interop_ReadAndWriteMemory.h"

using namespace NXP_SPOT_Interop;

UINT32 ReadAndWriteMemory::Read( UINT32 param0, HRESULT &hr )
{
    return *(UINT32*)param0;
}

void ReadAndWriteMemory::Wirte( UINT32 param0, UINT32 param1, HRESULT &hr )
{
	*(UINT32*)param0 = param1;
}

