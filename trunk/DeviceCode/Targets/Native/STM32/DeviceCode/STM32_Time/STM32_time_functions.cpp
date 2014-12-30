
/*
本来固定使用TIM2、TIM3、TIM4三个定时器来处理时间，主从模式。
这样子很浪费定时器，并且因为用到了主从模式来级联，无法使用TIM5、TIM6、TIM7替代。

最后决定，采用一个定时器72分频以1M的滴答速度计数，0xFFFF=65535个滴答产生一次中断，以g_Ticks累计中断数

实际上，最合适使用RTC定时器来做系统时间

COUNTFLAG	从上次读取定时器开始，如果定时器计数到0，则返回1.读取时清零
CLKSOURCE	0=外部时钟源(STCLK)，即HCLK/8=9M  1=内核时钟(FCLK)，既HCLK=72M
TICKINT		1=SysTick 倒数到0时会导致挂起Systick处理器
			0=数到0时不会导致挂起Systick处理器。软件可以使用COUNTFLAG来判断是否计数到0
ENABLE		1=SysTick 计数器工作在连拍模式。
			即计数器装载重装值后接着开始往下计数。
			计数到0时将COUNTFLAG设为1，此时根据TICKINT的值可以选择是否挂起Systick处理器。
			接着又再次装载重装值，并重新开始计数。
			0=失能计数器
CURRENT		读取时返回当前倒计数的值，写它则使之清零，同时还会清除在SysTick控制及状态寄存器中的COUNTFLAG标志
*/

#include <cores\arm\include\cpu.h>
#include "..\stm32f10x.h"

#define DEBUG_TIME	0

#define HAL_Completion_IdleValue 0xFFFFFFFFFFFFFFFFull
#define SYSTICK_MAXCOUNT       SysTick_LOAD_RELOAD_Msk	//((1<<24) - 1)	/* SysTick MaxCount */
#define SYSTICK_ENABLE         SysTick_CTRL_ENABLE_Msk	//     0		/* Config-Bit to start or stop the SysTick Timer */

//#define RTCClockSource_LSI   /* 使用内部 32 KHz 晶振作为 RTC 时钟源 */
#define RTCClockSource_LSE   /* 使用外部 32.768 KHz 晶振作为 RTC 时钟源 */
//#define RTCClockOutput_Enable  /* RTC Clock/64 is output on tamper pin(PC.13) */

extern HAL_DblLinkedList<HAL_CONTINUATION> g_HAL_Completion_List;

static UINT64 g_nextEvent;	// 下一个计划事件的嘀嗒数
static UINT64 g_Ticks;		// 全局滴答中断数，0xFFFF次滴答一个中断。乘以0x10000，避免每次计算滴答时都需要移位
static UINT64 g_NextSaveTicks;	// 下一次保存Ticks的数值，避免频繁保存

static UINT32 TicksPerSecond;		// 每秒的时钟滴答数
static UINT32 TicksPerMillisecond;	// 每毫秒的时钟滴答数
static UINT32 TicksPerMicrosecond;	// 每微秒的时钟滴答数
//static UINT32 MicrosecondsPerTick;	// 每个滴答的微秒数
//static UINT32 SystemTimePerTick;	// 每个滴答的系统时间数
static UINT32 CycleClock_MHZ;		// 周期时钟 MHz

UINT32 CPU_SystemClock()
{
    return SYSTEM_CLOCK_HZ;
}

UINT32 CPU_TicksPerSecond()
{
    return TicksPerSecond;
}

//--//

// time_driver.cpp里面有#define TIMEUNIT_TO_MILLISECONDS    10000
// 1ms=10000ticks, 1us=10ticks
// 所以系统时间是十分之一微秒

// CPU滴答转为系统时间
UINT64 CPU_TicksToTime( UINT64 ticks )
{
    //return ticks * SystemTimePerTick;
	// 考虑到TEN_MHZ / TicksPerSecond不好整除
	// ticks / TicksPerMicrosecond就是CPU滴答所对应的微秒数，系统时间是微秒的十分之一，所以乘以10
	return ticks * 10 / TicksPerMicrosecond;
}

UINT64 CPU_TicksToTime( UINT32 ticks )
{
    //return (UINT64)ticks * SystemTimePerTick;
	// 先乘后除，在一定程度上减少误差
	return (UINT64)ticks * 10 / TicksPerMicrosecond;
}

//--//

UINT64 CPU_MillisecondsToTicks( UINT64 ms )
{
    return ms * TicksPerMillisecond;
}

UINT64 CPU_MillisecondsToTicks( UINT32 ms )
{
    return (UINT64)ms * TicksPerMillisecond;
}

//--//

UINT32 CPU_MicrosecondsToSystemClocks( UINT32 us )
{
    return us * TicksPerMicrosecond;
}

//--//

int CPU_SystemClocksToMicroseconds( int ticks )
{
    //return ticks * MicrosecondsPerTick;
	// 考虑到ONE_MHZ / TicksPerSecond不好整除
	return ticks / TicksPerMicrosecond;
}

//--//

//#define RTC_CODE
#ifdef RTC_CODE
void RTC_Configuration(void)
{
	/* 备份寄存器模块复位，将BKP的全部寄存器重设为缺省值 */
	BKP_DeInit();

#ifdef RTCClockSource_LSI
	/* Enable LSI */ 
	RCC_LSICmd(ENABLE);
	/* 等待稳定 */
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{
	}

	/* Select LSI as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);  
#elif defined	RTCClockSource_LSE  
	/* 设置外部低速晶振(LSE)32.768K  参数指定LSE的状态，可以是：RCC_LSE_ON：LSE晶振ON */
	RCC_LSEConfig(RCC_LSE_ON);
	/* 等待稳定 */
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{
	}

	/* RTC时钟源配置成LSE（外部32.768K） */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);  
#endif

	/* 使能RTC时钟 */
	RCC_RTCCLKCmd(ENABLE);

#ifdef RTCClockOutput_Enable  
	/* Disable the Tamper Pin */
	BKP_TamperPinCmd(DISABLE); /* To output RTCCLK/64 on Tamper pin, the tamper
							   functionality must be disabled */
							   
	/* Enable RTC Clock Output on Tamper Pin */
	BKP_RTCCalibrationClockOutputCmd(ENABLE);
#endif 

	/* 开启后需要等待APB1时钟与RTC时钟同步，才能读写寄存器 */
	RTC_WaitForSynchro();

	/* 每一次读写寄存器前，要确定上一个操作已经结束 */
	RTC_WaitForLastTask();

	/* 使能秒中断 */  
	//RTC_ITConfig(RTC_IT_SEC, ENABLE);

	/* 每一次读写寄存器前，要确定上一个操作已经结束 */
	//RTC_WaitForLastTask();

	/* 设置RTC分频器，使RTC时钟为1Hz */
#ifdef RTCClockSource_LSI
	RTC_SetPrescaler(31999); /* RTC period = RTCCLK/RTC_PR = (32.000 KHz)/(31999+1) */
#elif defined	RTCClockSource_LSE
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
#endif

	/* 每一次读写寄存器前，要确定上一个操作已经结束 */
	RTC_WaitForLastTask();
}

#if DEBUG_TIME
	static UINT32 g_Counter = 0;
#endif

void LoadTicks()
{
	// 加上计数器的值，注意计数器的单位是秒。注意必须转INT64，否则溢出
	UINT32 counter = RTC_GetCounter();
#if DEBUG_TIME
	g_Counter = counter;
#endif
	g_Ticks = CPU_MillisecondsToTicks(1000ull * (UINT64)counter);
}

void SaveTicks()
{
	/* 等待最近一次对RTC寄存器的写操作完成，也即等待RTC寄存器同步 */
	RTC_WaitForSynchro();

	UINT64 ms = g_Ticks / TicksPerMillisecond;
	// 设置计数器
	RTC_SetCounter(ms / 1000);

	// 必须打开时钟和后备域，否则写不进去时间
	// Check if the Power On Reset flag is set
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to BKP Domain */
    //PWR_BackupAccessCmd(ENABLE); 

	// 这里对时间要求非常苛刻，不能等待
	RTC_WaitForLastTask();
}
#endif

// 定时器事件
void Timer_Interrupt (void* param)
{
    INTERRUPT_START

	// 累加计数
	if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG)
	{
		g_Ticks += SysTick->LOAD;
	}
	// 定期保存Ticks到后备RTC寄存器
	if( g_Ticks >= g_NextSaveTicks)
	{
#if DEBUG_TIME
		if(g_Counter > 0)
		{
			debug_printf("LoadTicks 0x%08x\r\n", g_Counter);
			SYSTEMTIME st;
			Time_ToSystemTime( (INT64)g_Counter * 10000000 + TIME_ZONE_OFFSET, &st );
			debug_printf("LoadTime %4d-%02d-%02d %02d:%02d:%02d.%03d\r\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
			g_Counter = 0;
		}
#endif
	//	SaveTicks();
		// 每秒钟保存一次
		g_NextSaveTicks = g_Ticks + CPU_MillisecondsToTicks(1000ull);
	}

	// 检查是否已经超过了某一个将要发生的时间，如果有，马上安排执行
    if (HAL_Time_CurrentTicks() >= g_nextEvent) {
		HAL_COMPLETION::DequeueAndExec();
    }

    INTERRUPT_END
}

/* 设置比较值，下一次要从这里中断 */
void HAL_Time_SetCompare( UINT64 CompareValue )
{
    GLOBAL_LOCK(irq);
    g_nextEvent = CompareValue;

	UINT64 curTicks = HAL_Time_CurrentTicks();

	UINT32 diff;

	// 如果已经超过计划比较值，那么安排最小滴答，准备马上中断
	if(curTicks >= g_nextEvent)
		diff = 1;
	// 计算下一次中断的间隔，最大为SYSTICK_MAXCOUNT
	else if((CompareValue - curTicks) > SYSTICK_MAXCOUNT)
		diff = SYSTICK_MAXCOUNT;
	else
		diff = (UINT32)(CompareValue - curTicks);

	// 把时钟里面的剩余量累加到g_Ticks
	g_Ticks = HAL_Time_CurrentTicks();

	// 重新设定重载值，下一次将在该值处中断
	SysTick->LOAD = diff;
	SysTick->VAL = 0x00;
}

BOOL HAL_Time_Initialize()
{
	// 准备使用外部时钟，Systick时钟=HCLK/8
	// 72M时，每秒72M/8=9M个滴答，1us=9滴答
	// 96M时，每秒96M/8=12M个滴答，1us=12滴答
	Platform.TicksPerSecond = Platform.Clock / 8;

	TicksPerSecond = Platform.TicksPerSecond;		// 每秒的嘀嗒数
	TicksPerMillisecond = TicksPerSecond / 1000;	// 每毫秒的嘀嗒数
	TicksPerMicrosecond = TicksPerSecond / ONE_MHZ;	// 每微秒的时钟滴答数
	//MicrosecondsPerTick = ONE_MHZ / TicksPerSecond;	// 每个滴答的微秒数
	//SystemTimePerTick	= TEN_MHZ / TicksPerSecond;	// 每个滴答的系统时间数
	CycleClock_MHZ = Platform.CycleClock / ONE_MHZ;	// 周期时钟 MHz
	
	g_Ticks = 0;
	g_nextEvent = HAL_Completion_IdleValue;
	
	/*****************************/
	/* GD32和STM32最大的区别就是STM32给寄存器默认值，而GD32没有给默认值 */
	/* 虽然RTC靠电池工作，断电后能保持配置，但是在GD32还是得重新打开时钟 */
	
	/* 启用PWR和BKP的时钟 */
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	/* 后备域解锁 */
	//PWR_BackupAccessCmd(ENABLE);

	if(BKP_ReadBackupRegister(BKP_DR1) != 0xABCD)
	{
		RTC_Configuration();

		BKP_WriteBackupRegister(BKP_DR1, 0xABCD);    
	}
	else
	{
		/* 等待最近一次对RTC寄存器的写操作完成，也即等待ＲＴＣ寄存器同步 */
		RTC_WaitForSynchro();

		// 从RTC还原滴答
		LoadTicks();

		/* 使能RTC中断：RTC_IT_SEC秒中断、RTC_IT_OW溢出中断、RTC_IT_ALR闹钟中断 */  
		//RTC_ITConfig(RTC_IT_SEC, ENABLE);
		/* 等待最近一次对RTC寄存器的写操作完成 */
		//RTC_WaitForLastTask();
	}

	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;	// 选择外部时钟，每秒有个HCLK/8滴答
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;		// 开启定时器减到0后的中断请求

	// 加载嘀嗒数，72M时~=0x00FFFFFF/9M=1864135us，96M时~=0x00FFFFFF/12M=1398101us
	SysTick->LOAD = SYSTICK_MAXCOUNT - 1;
	SysTick->VAL = 0;
	SysTick->CTRL |= SYSTICK_ENABLE;	// SysTick使能
/*
	NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = (UINT8)SysTick_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	// 需要最高级别的中断优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
*/
	// 再次打开中断，为了设定中断函数
	CPU_INTC_ActivateInterrupt((UINT32)SysTick_IRQn, Timer_Interrupt, 0);

    return TRUE;
}

BOOL HAL_Time_Uninitialize()
{
    CPU_INTC_DeactivateInterrupt((UINT32)SysTick_IRQn);
    
    // 关闭定时器
	SysTick->CTRL &= ~SYSTICK_ENABLE;
    
    return TRUE;
}


#pragma arm section code = "SectionForFlashOperations"

UINT64 __section(SectionForFlashOperations) CPU_MicrosecondsToTicks( UINT64 uSec )
{
    return uSec * TicksPerMicrosecond;
}

UINT32 __section(SectionForFlashOperations) CPU_MicrosecondsToTicks( UINT32 uSec )
{
    return uSec * TicksPerMicrosecond;
}

UINT64 __section(SectionForFlashOperations) HAL_Time_CurrentTicks()
{
	GLOBAL_LOCK(irq);

	UINT32 value = (SysTick->LOAD - SysTick->VAL);
	if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG)
	{
		g_Ticks += SysTick->LOAD;
	}
	return  g_Ticks + value;   
}

//
// 如果想标准化该常量，可以取消注释 #define CALIBRATE_SLEEP_USEC in TinyHAL.c
//
#define STM32_SLEEP_USEC_FIXED_OVERHEAD_CLOCKS 3

void __section(SectionForFlashOperations) HAL_Time_Sleep_MicroSeconds( UINT32 uSec )
{
 	// 小于100ms，直接采用死循环获取定时时间
	/*if (uSec <= 100000)
	{
		HAL_Time_Sleep_MicroSeconds_InterruptEnabled(uSec);
		return;
	}*/

	// 自己关闭中断，简直实在找死！
    //GLOBAL_LOCK(irq);
	
	// Sleep的时候，尽量保持中断打开，否则g_Ticks无法累加，从而造成死循环
	// 记录现在的中断状态
	BOOL state = ENABLE_INTERRUPTS();

	// 时钟滴答需要采用UINT64
    UINT64 maxDiff = CPU_MicrosecondsToTicks( uSec );
    UINT64 current = HAL_Time_CurrentTicks();

	// 减去误差指令周期，在获取当前时间以后多了几个指令
    if(maxDiff <= STM32_SLEEP_USEC_FIXED_OVERHEAD_CLOCKS)
		maxDiff  = 0; 
    else
		maxDiff -= STM32_SLEEP_USEC_FIXED_OVERHEAD_CLOCKS;

	maxDiff += current;

    while(HAL_Time_CurrentTicks() <= maxDiff);
	
	// 如果之前是打开中断的，那么这里也要重新打开
	if (!state) DISABLE_INTERRUPTS();
}

void HAL_Time_Sleep_MicroSeconds_InterruptEnabled( UINT32 uSec )
{
    // 迭代次数必须是有符号的，负迭代数表示最小延迟

    uSec *= CycleClock_MHZ;

    // 迭代次数等于请求数减去调用该子程序的CPU指令周期数
    int iterations = (int)uSec - 5;      // 减去上面的调用和计算

    CYCLE_DELAY_LOOP(iterations);
}

#pragma arm section code

INT64 HAL_Time_TicksToTime( UINT64 Ticks )
{
    return CPU_TicksToTime( Ticks );
}

INT64 HAL_Time_CurrentTime()
{
    return CPU_TicksToTime( HAL_Time_CurrentTicks() );
}

/// 机器滴答到实时时钟参数
/// ax = by + c; a, b, c 是整数. x = 对齐滴答, y = 机器滴答.
/// time_driver中有time = (time * m_Ticks_b + m_Ticks_c) / m_Ticks_a;
void HAL_Time_GetDriftParameters  ( INT32* a, INT32* b, INT64* c )
{
    *a = 1;
    *b = 1;
    *c = 0;
}

INT64 Time_GetUtcTime()
{
    //return Time_GetMachineTime() + m_Utc_c;
	// 因为HAL_Time_GetDriftParameters参数110，使得Time_GetMachineTime等于HAL_Time_CurrentTime
    //return HAL_Time_CurrentTime() + INITIAL_TIME;
	// 系统时钟保存的是 2000/1/1 开始的总秒数
    return HAL_Time_CurrentTime();
}

INT64 Time_SetUtcTime( INT64 utcTime, bool calibrate )
{
#if DEBUG_TIME
	// utcTime是减去了时区偏移的，从2000/1/1算起的总时间嘀嗒
	debug_printf("utcTime = 0x%lx\r\n", utcTime);
	SYSTEMTIME st;
	Time_ToSystemTime( utcTime + TIME_ZONE_OFFSET, &st );
	debug_printf("Time_SetUtcTime %4d-%02d-%02d %02d:%02d:%02d.%03d\r\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#endif
	
	// 折算为滴答偏移
	//debug_printf(" OldTicks 0x%lx\r\n\r\n", g_Ticks);
	// 影响到g_Ticks上
	g_Ticks = utcTime * TicksPerMicrosecond / 10;
#if DEBUG_TIME
	debug_printf("SaveTicks 0x%08x\r\n", (UINT32)(utcTime / 10000000));
#endif
	// 保存到RTC
	//SaveTicks();

    return Time_GetUtcTime();
}
