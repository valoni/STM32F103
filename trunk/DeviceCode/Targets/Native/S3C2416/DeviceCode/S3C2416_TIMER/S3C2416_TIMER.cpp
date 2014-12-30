/*
 * S3C2416_TIMER.cpp
 *
 *  Created on: 27.5.2011
 *      Author: Matti Eerola
 *
 *  TODO: Implement this. I created this for TIME driver, but it didn't need timers..
 */


#include <tinyhal.h>
#include "..\S3C2416.h"

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_S3C2416_TIMER_Driver"
#endif

S3C2416_TIMER_Driver g_S3C2416_TIMER_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif


BOOL S3C2416_TIMER_Driver::Initialize( UINT32 Timer, BOOL FreeRunning, UINT32 ClkSource, HAL_CALLBACK_FPN ISR, void* ISR_Param )
{

    return FALSE;
}

BOOL S3C2416_TIMER_Driver::Uninitialize( UINT32 Timer )
{

    return FALSE;
}


#pragma arm section code = "SectionForFlashOperations"

UINT32 __section(SectionForFlashOperations) S3C2416_TIMER_Driver::ReadCounter( UINT32 Timer )
{
    return 0;
}

#pragma arm section code
