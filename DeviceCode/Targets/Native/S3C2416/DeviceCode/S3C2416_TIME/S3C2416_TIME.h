

#ifndef S3C2416_TIME_H_
#define S3C2416_TIME_H_

struct S3C2416_TIME_Driver
{
	BOOL m_clockLoaded; // Set to false if you want to refresh Clock rates from registers
    UINT64 m_lastRead;
    UINT64 m_nextCompare;

    static BOOL Initialize  ();
    static BOOL Uninitialize();
    static UINT64 CounterValue();
    static void SetCompareValue( UINT64 CompareValue );
    static INT64 CurrentTime();
    static void Sleep_uSec( UINT32 uSec );
    static void Sleep_uSec_Loop( UINT32 uSec );
    static void ISR( void* Param );

    static UINT32 SystemClock();
    static UINT32 HighPerformanceBusClock();
    static UINT32 PeripheralBusClock();

private:
    UINT32 m_systemClock;
    UINT32 m_highPerformanceBusClock;
    UINT32 m_peripheralBusClock;

    void loadClocks();
};

extern S3C2416_TIME_Driver g_S3C2416_TIME_Driver;

#endif /* S3C2416_TIME_H_ */
