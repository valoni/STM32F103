////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "INTC_Adapter.h"
//--//

//------------------------------------------------------------------------------------------------
//micro
#define TICKS_PER_MILLISECOND														(SystemFrequency / 1000ULL)
#define TIME_CONVERSION__TO_MICROSECONDS								10

//-------------------------------------------------------------------------------------------------
//External variable
extern HAL_DblLinkedList<HAL_CONTINUATION> g_HAL_Completion_List;

//-------------------------------------------------------------------------------------------------
//The global variable
volatile UINT64 g_Ticks = 0;
volatile UINT64 g_TicksLastRead = 0;
volatile UINT64 g_TicksCompare = 0x0000FFFFFFFFFFFFull;

//-----------------------------------------------------------
//Front declare
void SysTickInterruptHandler(void *pParam);

//------------------------------------------------------------
//Description:
//	Count the value
//------------------------------------------------------------
UINT64 CounterValue()
{
  GLOBAL_LOCK(irq);

  UINT32 value = (SysTick->LOAD - SysTick->VAL);
  if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG)
  {
    g_Ticks += SysTick->LOAD;
  }
  return  g_Ticks + value;   
}

//------------------------------------------------------------
//Description:
//	Set compare
//------------------------------------------------------------
void SetCompare(UINT32 CompareValue)
{
  UINT32 value = (SysTick->LOAD - SysTick->VAL);
  if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG)
  {
    g_Ticks += SysTick->LOAD;
  }
  
  g_Ticks += value;
  g_TicksLastRead = g_Ticks;
  SysTick->LOAD = CompareValue;
  SysTick->VAL = 0x00;
}

//------------------------------------------------------------
//Description:
//	Set compare value
//------------------------------------------------------------
void SetCompareValue( UINT64 CompareValue )
{
  GLOBAL_LOCK(irq);

  g_TicksCompare = CompareValue;

  bool bForceInterrupt = false;

  UINT64 CntrValue = CounterValue();

  if(CompareValue <= CntrValue)
  {
    bForceInterrupt = true;
  }
  else
  {
    UINT32 diff;

    if((CompareValue - CntrValue) > SYSTICK_MAXCOUNT)
    {
      diff = SYSTICK_MAXCOUNT;
    }
    else
    {
      diff = (UINT32)(CompareValue - CntrValue);
    }        

    SetCompare(diff);

    if(CounterValue() > CompareValue)
    {
      bForceInterrupt = true;
    }
  }

  if(bForceInterrupt)
  {
    // Force interrupt to process this.
    
    //NVIC_SetPendingIRQ(SysTick_IRQn); //It would cause the hard_fault!
    
    SysTickInterruptHandler(NULL); //Call the interrupt function directly here!
  }
  
  //lcd_printf("C:0x%x,T:0x%x\r\n",g_TicksCompare,g_Ticks);//temp
}


//------------------------------------------------------------
//Description:
//	Set the load ticks for the next interrupt.
//------------------------------------------------------------
BOOL SetLoadTicksToReg(UINT32 dwLoadTicks)
{
	if(dwLoadTicks > SYSTICK_MAXCOUNT)
	{
		return FALSE;
	}
	
	//set reload register.I don't know why sub 1, but the original source code in core_cm3.h is just like that. 
	SysTick->LOAD  =  (dwLoadTicks & SYSTICK_MAXCOUNT) - 1; 
	
	//Load the SysTick Counter Value
	SysTick->VAL   =  (0x00);
}

//------------------------------------------------------------
//Description:
//	Get the load ticks from the registry
//------------------------------------------------------------
UINT32 GetLoadTicksFromReg()
{
	return (SysTick->LOAD & SYSTICK_MAXCOUNT);
}

//------------------------------------------------------------
//Description:
//	Get the elapse ticks 
//------------------------------------------------------------
UINT32 GetElapseTicksFromReg()
{
	return (SysTick->LOAD & SYSTICK_MAXCOUNT) - (SysTick->VAL & SYSTICK_MAXCOUNT);
}



#pragma arm section code = "SectionForInterruptHandler"

//--------------------------------------------------------
//Description:
//	The function for SysTick handle
//--------------------------------------------------------
void SysTickInterruptHandler(void *pParam)
{
	g_TicksLastRead = CounterValue();
	
	if(g_TicksLastRead >= g_TicksCompare)
	{
		// this also schedules the next one, if there is one
		HAL_COMPLETION::DequeueAndExec();
			
		//If the ptrNext is NULL,it wouldn't call HAL_Time_SetCompare() in DequeueAndExec() function
		//which means the main thread may not get the time to run when the systick reload value is very small and
		//systick interrupt occurs frequently. So I reset the systick reload value here by calling HAL_Time_SetCompare function 
		HAL_COMPLETION* ptr     = (HAL_COMPLETION*)g_HAL_Completion_List.FirstNode();
		HAL_COMPLETION* ptrNext = (HAL_COMPLETION*)ptr->Next();
		if(ptrNext == NULL)
		{
			//0x0000FFFFFFFFFFFFull is used by the HAL_Completion_IdleValue variable which defined in the completions.cpp file.
			HAL_Time_SetCompare(0x0000FFFFFFFFFFFFull);
		}
	}
	else
	{
		//
		// Because we are limited in the resolution of timer,
		// resetting the compare will properly configure the next interrupt.
		//
		// You mustn't comment the source code, or it would not boot normally.
		SetCompareValue( g_TicksCompare );
	}
}

void HAL_Time_SetCompare( UINT64 CompareValue )
{
	SetCompareValue( CompareValue );
}

#pragma arm section code //End

BOOL HAL_Time_Initialize()
{
	g_TicksLastRead = 0;
	g_TicksCompare = 0x0000FFFFFFFFFFFFull;

	CPU_INTC_ActivateInterrupt(IRQ_SysTick,SysTickInterruptHandler,NULL);
	SysTick_Config(SYSTICK_MAXCOUNT);
	
	return TRUE;
}

BOOL HAL_Time_Uninitialize()
{
	//Disable the systick
	SysTick->CTRL &= ~SYSTICK_ENABLE;
	
	return TRUE;
}

UINT64 HAL_Time_CurrentTicks()
{
	return CounterValue();
}

INT64 HAL_Time_TicksToTime( UINT64 Ticks )
{
	//The function is (Ticks / (TICKS_PER_MILLISECOND / TIME_CONVERSION__TO_MILLISECONDS))
	//return TIME_CONVERSION__TO_MILLISECONDS * Ticks / TICKS_PER_MILLISECOND;
	
	return CPU_TicksToTime(Ticks);
}

INT64 HAL_Time_CurrentTime()
{
	//return HAL_Time_TicksToTime(HAL_Time_CurrentTicks());
	
	
	//return HAL_Time_TicksToTime(Time_CurrentTicks());
	// we collapse the above to improve perf on a high hit function
	INT64 Time = CPU_TicksToTime( CounterValue() );

#if defined(HAL_TIMEWARP)
    return s_timewarp_compensate + Time;
#else
    return Time;
#endif

}


void HAL_Time_Sleep_MicroSeconds( UINT32 uSec )
{
	GLOBAL_LOCK(irq);
	
	HAL_Time_Sleep_MicroSeconds_InterruptEnabled(uSec);
}

void HAL_Time_Sleep_MicroSeconds_InterruptEnabled( UINT32 uSec )
{
	UINT64 u64BeginTime = HAL_Time_CurrentTime();
	UINT64 u64EndTimeCount = uSec * TIME_CONVERSION__TO_MICROSECONDS;
	while(HAL_Time_CurrentTime() - u64BeginTime < u64EndTimeCount);
}

void HAL_Time_GetDriftParameters  ( INT32* a, INT32* b, INT64* c )
{
    *a = 1;
    *b = 1;
    *c = 0;
}

UINT32 CPU_SystemClock()
{
	//return SystemFrequency;
	
	return SYSTEM_CLOCK_HZ;
}


UINT32 CPU_TicksPerSecond()
{
	//return TICKS_PER_MILLISECOND * 1000;
	
	return SLOW_CLOCKS_PER_SECOND;
}

UINT64 CPU_MillisecondsToTicks( UINT64 mSec )
{
	//return TICKS_PER_MILLISECOND * mSec;
	
	mSec *= (SLOW_CLOCKS_PER_SECOND/SLOW_CLOCKS_MILLISECOND_GCD);
	mSec /= (1000                  /SLOW_CLOCKS_MILLISECOND_GCD);

	return mSec;
}

UINT64 CPU_MillisecondsToTicks( UINT32 mSec )
{
	//return TICKS_PER_MILLISECOND * mSec;
	
	UINT64 Ticks;
	
	Ticks  = (UINT64)mSec * (SLOW_CLOCKS_PER_SECOND/SLOW_CLOCKS_MILLISECOND_GCD);
	Ticks /=                   (1000                  /SLOW_CLOCKS_MILLISECOND_GCD);
	
	return Ticks;
}

UINT64 CPU_MicrosecondsToTicks( UINT64 uSec )
{
	//return TICKS_PER_MILLISECOND * uSec / 1000;
	
#if ONE_MHZ < SLOW_CLOCKS_PER_SECOND
    return uSec * (SLOW_CLOCKS_PER_SECOND / ONE_MHZ);
#else
    return uSec / (ONE_MHZ / SLOW_CLOCKS_PER_SECOND);
#endif
}

UINT32 CPU_MicrosecondsToTicks( UINT32 uSec )
{
	//return TICKS_PER_MILLISECOND * uSec / 1000;
	
#if ONE_MHZ < SLOW_CLOCKS_PER_SECOND
    return uSec * (SLOW_CLOCKS_PER_SECOND / ONE_MHZ);
#else
    return uSec / (ONE_MHZ / SLOW_CLOCKS_PER_SECOND);
#endif
}

UINT32 CPU_MicrosecondsToSystemClocks( UINT32 uSec )
{	
	//uSec is microseconds 
	//return TICKS_PER_MILLISECOND * uSec / 1000;
	
	uSec *= (SYSTEM_CLOCK_HZ/CLOCK_COMMON_FACTOR);
	uSec /= (ONE_MHZ        /CLOCK_COMMON_FACTOR);

	return uSec;
}

UINT64 CPU_TicksToTime( UINT64 Ticks )
{
	//The function is (Ticks / (TICKS_PER_MILLISECOND / TIME_CONVERSION__TO_MILLISECONDS))
	//return TIME_CONVERSION__TO_MILLISECONDS * Ticks / TICKS_PER_MILLISECOND ;
	
	Ticks *= (TEN_MHZ               /(double)SLOW_CLOCKS_TEN_MHZ_GCD); 
	Ticks /= (SLOW_CLOCKS_PER_SECOND/(double)SLOW_CLOCKS_TEN_MHZ_GCD); 

	return Ticks;
}

UINT64 CPU_TicksToTime( UINT32 Ticks32 )
{
	//The function is (Ticks32 / (TICKS_PER_MILLISECOND / TIME_CONVERSION__TO_MILLISECONDS))
	//return TIME_CONVERSION__TO_MILLISECONDS * static_cast<UINT64>(Ticks32) / TICKS_PER_MILLISECOND;
	
	UINT64 Ticks;

	Ticks  = (UINT64)Ticks32 * (TEN_MHZ               /(double)SLOW_CLOCKS_TEN_MHZ_GCD); 
	Ticks /=                   (SLOW_CLOCKS_PER_SECOND/(double)SLOW_CLOCKS_TEN_MHZ_GCD); 

	return Ticks;
}

