/*
 * S3C2416_time_functions.cpp
 *
 *  Created on: 7.5.2011
 *      Author: Matti Eerola
 */

#include <cores\arm\include\cpu.h>
#include "S3C2416_TIME.h"

#include "..\S3C2416.h"
//--//



BOOL HAL_Time_Initialize()
{
    return S3C2416_TIME_Driver::Initialize();
}


BOOL HAL_Time_Uninitialize()
{
    return S3C2416_TIME_Driver::Uninitialize();
}

UINT64 HAL_Time_CurrentTicks()
{
    return S3C2416_TIME_Driver::CounterValue();
}

INT64 HAL_Time_TicksToTime( UINT64 Ticks )
{
    return CPU_TicksToTime(Ticks);
}

INT64 HAL_Time_CurrentTime()
{
    return S3C2416_TIME_Driver::CurrentTime();
}

void HAL_Time_SetCompare( UINT64 CompareValue )
{
	S3C2416_TIME_Driver::SetCompareValue(CompareValue);
}

#pragma arm section code = "SectionForFlashOperations"

void __section(SectionForFlashOperations) HAL_Time_Sleep_MicroSeconds( UINT32 uSec )
{
	S3C2416_TIME_Driver::Sleep_uSec( uSec );
}

#pragma arm section code

void HAL_Time_Sleep_MicroSeconds_InterruptEnabled( UINT32 uSec )
{
	S3C2416_TIME_Driver::Sleep_uSec_Loop( uSec );
}

void HAL_Time_GetDriftParameters  ( INT32* a, INT32* b, INT64* c )
{
    *a = 1;
    *b = 1;
    *c = 0;
}

UINT32 CPU_SystemClock()
{
    return SYSTEM_CLOCK_HZ;
}

UINT32 CPU_TicksPerSecond()
{
    return SLOW_CLOCKS_PER_SECOND;
}

UINT64 CPU_MillisecondsToTicks( UINT64 Ticks )
{
    return (Ticks << SLOW_CLOCKS_SHIFT) / 1000;
}

UINT64 CPU_MillisecondsToTicks( UINT32 Ticks32 )
{
	return ((UINT64)Ticks32 << SLOW_CLOCKS_SHIFT) / 1000;
}

UINT64 CPU_MicrosecondsToTicks( UINT64 uSec )
{
	return (uSec << SLOW_CLOCKS_SHIFT) / 1000000;
}

UINT32 CPU_MicrosecondsToTicks( UINT32 uSec )
{
	return ((UINT64)uSec << SLOW_CLOCKS_SHIFT) / 1000000;
}

#pragma arm section code = "SectionForFlashOperations"

UINT32 __section(SectionForFlashOperations) CPU_MicrosecondsToSystemClocks( UINT32 uSec )
{
    uSec *= (SYSTEM_CLOCK_HZ/CLOCK_COMMON_FACTOR);
    uSec /= (ONE_MHZ        /CLOCK_COMMON_FACTOR);

    return uSec;
}

#pragma arm section code

UINT64 CPU_TicksToTime( UINT64 Ticks )
{
	return (Ticks << SLOW_CLOCKS_SHIFT) / 10000000;
}

UINT64 CPU_TicksToTime( UINT32 Ticks32 )
{
	return ((UINT64)Ticks32 << SLOW_CLOCKS_SHIFT) / 10000000;
}

