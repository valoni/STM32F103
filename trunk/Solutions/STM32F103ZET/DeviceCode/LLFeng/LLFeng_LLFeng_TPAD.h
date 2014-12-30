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


#ifndef _LLFENG_LLFENG_TPAD_H_
#define _LLFENG_LLFENG_TPAD_H_

namespace LLFeng
{
    struct TPAD
    {
        // Helper Functions to access fields of managed object
        // Declaration of stubs. These functions are implemented by Interop code developers
        static void TPAD_Reset( HRESULT &hr );
        static UINT16 TPAD_Get_Val( HRESULT &hr );
        static UINT16 TPAD_Get_MaxVal( UINT32 param0, HRESULT &hr );
        static UINT16 TPAD_Init( UINT32 param0, HRESULT &hr );
        static UINT16 TPAD_Scan( UINT32 param0, HRESULT &hr );
        static void TIM5_CH2_Cap_Init( UINT16 param0, UINT16 param1, HRESULT &hr );
    };
}
#endif  //_LLFENG_LLFENG_TPAD_H_
