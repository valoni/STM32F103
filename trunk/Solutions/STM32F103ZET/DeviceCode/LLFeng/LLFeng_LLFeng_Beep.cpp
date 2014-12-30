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


#include "LLFeng.h"
#include "LLFeng_LLFeng_Beep.h"

using namespace LLFeng;

void Beep::beepon( HRESULT &hr )
{
	CPU_GPIO_EnableOutputPin(24,true);
}

void Beep::beepoff( HRESULT &hr )
{
	CPU_GPIO_EnableOutputPin(24,false);
}

