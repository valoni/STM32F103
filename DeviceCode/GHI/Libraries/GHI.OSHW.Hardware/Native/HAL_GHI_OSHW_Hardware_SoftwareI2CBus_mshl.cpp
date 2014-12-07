//-----------------------------------------------------------------------------
//
//    ** DO NOT EDIT THIS FILE! **
//    This file was generated by a tool
//    re-running the tool will overwrite this file.
//
//-----------------------------------------------------------------------------


#include "HAL.h"
#include "HAL_GHI_OSHW_Hardware_SoftwareI2CBus.h"

using namespace GHI::OSHW::Hardware;


HRESULT Library_HAL_GHI_OSHW_Hardware_SoftwareI2CBus::NativeI2CWriteRead___STATIC__BOOLEAN__I4__I4__I4__U2__SZARRAY_U1__I4__I4__SZARRAY_U1__I4__I4__BYREF_I4__BYREF_I4( CLR_RT_StackFrame& stack )
{
    TINYCLR_HEADER(); hr = S_OK;
    {
        INT32 param0;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 0, param0 ) );

        INT32 param1;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 1, param1 ) );

        INT32 param2;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 2, param2 ) );

        UINT16 param3;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT16( stack, 3, param3 ) );

        CLR_RT_TypedArray_UINT8 param4;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT8_ARRAY( stack, 4, param4 ) );

        INT32 param5;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 5, param5 ) );

        INT32 param6;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 6, param6 ) );

        CLR_RT_TypedArray_UINT8 param7;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT8_ARRAY( stack, 7, param7 ) );

        INT32 param8;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 8, param8 ) );

        INT32 param9;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 9, param9 ) );

        INT32 * param10;
        UINT8 heapblock10[CLR_RT_HEAP_BLOCK_SIZE];
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32_ByRef( stack, heapblock10, 10, param10 ) );

        INT32 * param11;
        UINT8 heapblock11[CLR_RT_HEAP_BLOCK_SIZE];
        TINYCLR_CHECK_HRESULT( Interop_Marshal_INT32_ByRef( stack, heapblock11, 11, param11 ) );

        INT8 retVal = SoftwareI2CBus::NativeI2CWriteRead( param0, param1, param2, param3, param4, param5, param6, param7, param8, param9, param10, param11, hr );
        TINYCLR_CHECK_HRESULT( hr );
        SetResult_INT8( stack, retVal );

        TINYCLR_CHECK_HRESULT( Interop_Marshal_StoreRef( stack, heapblock10, 10 ) );
        TINYCLR_CHECK_HRESULT( Interop_Marshal_StoreRef( stack, heapblock11, 11 ) );
    }
    TINYCLR_NOCLEANUP();
}