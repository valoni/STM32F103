

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
	if (!g_S3C2416_TIME_Driver.m_clockLoaded)
		g_S3C2416_TIME_Driver.loadClocks();

	return g_S3C2416_TIME_Driver.m_systemClock;
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
	UINT16 MDIV;
	UINT8 HCLKDIV,PCLKDIV,PREDIV;
	S3C2416_CLOCK &clock = S3C2416::CLOCK();
	
	MDIV = (clock.MPLLCON >> 14 )& 0x3FF;
	m_systemClock = SYSTME_CRYSTAL_CLOCK * (MDIV/ 6);
	HCLKDIV = clock.CLKDIV0 & 0x03; //[1:0]
	PREDIV = (clock.CLKDIV0 >> 4) &0x3;//[5:4]
	PCLKDIV = (clock.CLKDIV0 >> 2) & 0x01; //[2]

	m_highPerformanceBusClock = m_systemClock/((HCLKDIV+1)*(PREDIV +1));

	if (PCLKDIV == 1)
		m_peripheralBusClock = m_highPerformanceBusClock / 2;
	else
		m_peripheralBusClock = m_highPerformanceBusClock;
	m_clockLoaded = true;
	S3C2416::Debug_printf("Fclk = %dMHz, Hclk = %dMHz, Pclk = %dMHz\r\n",m_systemClock/1000000,m_highPerformanceBusClock/1000000,m_peripheralBusClock/1000000);
}
