/*
 * S3C2416_TIME.cpp
 *
 *  Created on: 7.5.2011
 *      Author: Matti Eerola
 */

#include <tinyhal.h>
#include "S3C2416_TIME.h"
#include "..\S3C2416.h"

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_S3C2416_TIME_Driver"
#endif

S3C2416_TIME_Driver g_S3C2416_TIME_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif

//--//


BOOL S3C2416_TIME_Driver::Initialize  ()
{
	if (!S3C2416_AIC_Driver::ActivateInterrupt(S3C2416_AIC::INT_INDEX_INT_TICK, FALSE, S3C2416_TIME_Driver::ISR, NULL))
		return FALSE;

	g_S3C2416_TIME_Driver.m_lastRead    = 0;
	g_S3C2416_TIME_Driver.m_nextCompare = 64;

	S3C2416_RTC& RTC = S3C2416::RTC();
	RTC.RTCCON |= 1 << 0; //enable RTC
	//RTC.RTCCON |= 1 << 3; //enable RTC clock counter reset
	RTC.RTCCON |= 0x4 << 5; //clock period of 1/128 second select
	RTC.TICNT0 |= 0x80; //enable tick
	RTC.TICNT1 = 0x1; //Tick Time Count = 1
	return TRUE;
}

BOOL S3C2416_TIME_Driver::Uninitialize()
{
	if (!S3C2416_AIC_Driver::DeactivateInterrupt(S3C2416_AIC::INT_INDEX_INT_TICK))
		return FALSE;

	S3C2416_RTC& RTC = S3C2416::RTC();
	//RTC.RTCCON |= 1 << 0; //enable write
	RTC.TICNT0 &= ~0x80; //enable tick 
	RTC.RTCCON &= ~(1<<0); //disable write

	return TRUE;
}

UINT64 S3C2416_TIME_Driver::CounterValue()
{
	return g_S3C2416_TIME_Driver.m_lastRead;
}

void S3C2416_TIME_Driver::SetCompareValue( UINT64 CompareValue )
{
	GLOBAL_LOCK(irq);
	g_S3C2416_TIME_Driver.m_nextCompare = CompareValue;

	if(CounterValue() >= g_S3C2416_TIME_Driver.m_nextCompare)
	{
		S3C2416_AIC_Driver::ForceInterrupt(S3C2416_AIC::INT_INDEX_INT_TICK);
	}
}

INT64 S3C2416_TIME_Driver::CurrentTime()
{
	return CPU_TicksToTime( CounterValue() );
}

void S3C2416_TIME_Driver::Sleep_uSec( UINT32 uSec )
{
	Sleep_uSec_Loop(uSec);
}

void S3C2416_TIME_Driver::Sleep_uSec_Loop( UINT32 uSec )
{
    uSec *= (SYSTEM_CYCLE_CLOCK_HZ / CLOCK_COMMON_FACTOR);
    uSec /= (ONE_MHZ               / CLOCK_COMMON_FACTOR);

    // iterations is equal to the number of CPU instruction cycles in the required time minus
    // overhead cycles required to call this subroutine.
    int iterations = (int)uSec - 14;      // Subtract off call & calculation overhead

    CYCLE_DELAY_LOOP2(iterations);
}

void S3C2416_TIME_Driver::ISR( void* Param )
{
	g_S3C2416_TIME_Driver.m_lastRead++;

    if(CounterValue() >= g_S3C2416_TIME_Driver.m_nextCompare)
    {
        // this also schedules the next one, if there is one
        HAL_COMPLETION::DequeueAndExec();
    }
}

UINT32 S3C2416_TIME_Driver::SystemClock()
{
	return SYSTEM_CLOCK_HZ;
}

UINT32 S3C2416_TIME_Driver::HighPerformanceBusClock()
{
	if (!g_S3C2416_TIME_Driver.m_clockLoaded)
		g_S3C2416_TIME_Driver.loadClocks();

	return g_S3C2416_TIME_Driver.m_highPerformanceBusClock;
}

UINT32 S3C2416_TIME_Driver::PeripheralBusClock()
{
	if (!g_S3C2416_TIME_Driver.m_clockLoaded)
		g_S3C2416_TIME_Driver.loadClocks();

	return g_S3C2416_TIME_Driver.m_peripheralBusClock;
}

void S3C2416_TIME_Driver::loadClocks()
{
	//from page 7-8
	UINT8 HDIVN,PDIVN,HCLK4_HALF,HCLK3_HALF;
	S3C2416_POWER &pow = S3C2416::POWER();
	HDIVN = (pow.CLKDIVN >> 1) & 0x03; //[2:1]
	PDIVN = pow.CLKDIVN & 0x01; //[0]
	HCLK3_HALF = (pow.CAMDIVN >> 8) & 0x01; //[8]
	HCLK4_HALF = (pow.CAMDIVN >> 9) & 0x01; //[9]

	UINT32 sysClock = SystemClock();
	switch (HDIVN) {
	case 0:
		m_highPerformanceBusClock = sysClock;
		break;
	case 1:
		m_highPerformanceBusClock = sysClock / 2;
		break;
	case 3:
		m_highPerformanceBusClock = sysClock / 3;
		break;
	case 2:
		m_highPerformanceBusClock = sysClock / 4;
		break;
	}
	if ((HDIVN < 2) && (HCLK3_HALF == 1 || HCLK4_HALF == 1))
		m_highPerformanceBusClock /= 2;

	if (PDIVN == 1)
		m_peripheralBusClock = m_highPerformanceBusClock / 2;
	else
		m_peripheralBusClock = m_highPerformanceBusClock;

	m_clockLoaded = true;
}
