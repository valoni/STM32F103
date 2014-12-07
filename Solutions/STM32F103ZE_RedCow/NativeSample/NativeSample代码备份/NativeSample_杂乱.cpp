////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include <Tests.h>
#include "nativesample.h"
#include "GPIO_Adapter.h"
#include "usart.h"
#include "TgUART.h"
#include "INTC_Adapter.h"
//--//

HAL_DECLARE_NULL_HEAP();

extern uint32_t ARM_Vectors;

uint32_t  GetMinInterval()
{
	//The minimum is 1ms
	return 1;
}

uint32_t  GetMaxInterval()
{
	//The reload tick count in the register is SYSTICK_MAXCOUNT,and (SystemFrequency / 1000)  means 1ms.
	return SYSTICK_MAXCOUNT / (SystemFrequency / 1000);
}

bool ConvertToTick(uint32_t  uiInterval,uint32_t  &uiTick)
{
	if(uiInterval >= GetMinInterval() && uiInterval <= GetMaxInterval())
	{
		//The algorithm of 	(SystemFrequency / 1000)  means 1ms which is in SysTick_Config function of the core_cm3.h file.
		uiTick = SystemFrequency / 1000 * uiInterval;
		return true;
	}
	else
	{
		return false;
	}
	
	
}

void  SendData(u8 data)   
{   
  while (!(USART1->SR & USART_FLAG_TXE));   
  USART1->DR = (data & (uint16_t)0x01FF);   
}

extern "C" void SysTickHandler(void *pParam)
{
	//CPU_GPIO_SetPinState(GPIO_F07,!CPU_GPIO_GetPinState(GPIO_F07));
	//CPU_GPIO_SetPinState(GPIO_F07,CPU_GPIO_GetPinState(GPIO_A08));
	int *piBuf = reinterpret_cast<int *>(pParam);
	
	*piBuf += 1;
	
	if(*piBuf %2 == 0)
	{
		CPU_GPIO_SetPinState(GPIO_F07,TRUE);
	}
	else
	{
		CPU_GPIO_SetPinState(GPIO_F07,FALSE);
	}
}


void ApplicationEntryPoint()
{
	//不要删除下面这个语句，否则会编译出错
	UART        usartTest  ( COMTestPort, 9600, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );

	
	
	//temp test------------------------------str
	/*
	USART_Driver::Initialize(1,115200,USART_PARITY_NONE,8,USART_StopBits_1,USART_FLOW_NONE);
	char szVal[] = "Hello, .Net Micro Framework";
	USART_Driver::Write(1,szVal,10);
	*/
	//temp test------------------------------end
	

	
	//temp test------------------------------str
	/*
	char szVal[] = "Hello, .Net Micro Framework";
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);  
	
		// 配置中断寄存器的优先级   
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);   
	  
	//初始化数据                   
	NVIC_InitTypeDef NVIC_InitInfo;   
	NVIC_InitInfo.NVIC_IRQChannel = USART1_IRQn;   
	NVIC_InitInfo.NVIC_IRQChannelSubPriority = 0;   
	NVIC_InitInfo.NVIC_IRQChannelCmd = ENABLE;   
	  
	//写中断寄存器   
	//NVIC_Init(&NVIC_InitInfo);  


	//初始化数据    
	GPIO_InitTypeDef GPIO_InitInfo;   
	GPIO_InitInfo.GPIO_Pin = GPIO_Pin_9;   
	GPIO_InitInfo.GPIO_Speed = GPIO_Speed_50MHz;   
	GPIO_InitInfo.GPIO_Mode = GPIO_Mode_AF_PP;   
	  
	//写寄存器   
	GPIO_Init(GPIOA,&GPIO_InitInfo);  

	USART_Cmd(USART1,ENABLE);  
	
	USART_InitTypeDef  USART_InitInfo;     
  
 //波特率   
	USART_InitInfo.USART_BaudRate = 9600;   
	  
	//数据位   
	USART_InitInfo.USART_WordLength = USART_WordLength_8b;   
	  
	//无奇偶校验   
	USART_InitInfo.USART_Parity = USART_Parity_No;    
	  
	//一个停止位   
	USART_InitInfo.USART_StopBits = USART_StopBits_1;   
	  
	//无流控制   
	USART_InitInfo.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   
	  
	//接收发送标志   
	USART_InitInfo.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   
	  
	//更新到寄存器   
	USART_Init(USART1,&USART_InitInfo);   
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); 
	


	for(int i = 0; i < 20; i ++)
	{
		SendData(szVal[i]);
	}
	*/
	

	//temp test------------------------------end
	
		//temp test-------------------------------------------str
	//直接跑的话，第二个SendData会一直等待。要先跑一次用MDK建立的工程才正常，奇怪。
	/*
		InitRCC(USART1);
	InitNVIC(USART1);
	InitGPIO(USART1);
	EnablePort(USART1,ENABLE);

	USART_InitTypeDef	 USART_InitInfo;	
	USART_InitInfo.USART_BaudRate = 115200;
	USART_InitInfo.USART_WordLength = USART_WordLength_8b;
	USART_InitInfo.USART_Parity = USART_Parity_No;
	USART_InitInfo.USART_StopBits = USART_StopBits_1;
	USART_InitInfo.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitInfo.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1,&USART_InitInfo);

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

	char *pszTxt = "Hello,NativeSample!\r\n";
	while(true)
	{
		SendData(USART1,*pszTxt);
		
		++ pszTxt;
		if(*pszTxt == 0)
		{
			break;
		}
	}
	*/
	
	//temp test-------------------------------------------end
	
	//Initialize the GPIO
	CPU_GPIO_Initialize();
	
	//Enable the GPIO output pin
	CPU_GPIO_EnableOutputPin(GPIO_F06,TRUE);
	CPU_GPIO_EnableOutputPin(GPIO_F07,TRUE);
	CPU_GPIO_EnableInputPin(GPIO_A08,FALSE,NULL,GPIO_INT_NONE,RESISTOR_DISABLED);
	

	
	//temp test------------------------------str
	CPU_INTC_Initialize();
	int iBuf = 0;
	CPU_INTC_ActivateInterrupt(IRQ_SysTick,SysTickHandler,&iBuf);
	
	uint32_t dwInterval = 100;
	ConvertToTick(dwInterval,dwInterval);
	SysTick_Config(dwInterval);
	
	//CPU_INTC_InterruptDisable(IRQ_SysTick);
	//CPU_INTC_InterruptEnable(IRQ_SysTick);
	//temp test------------------------------end
	

	
	
	while(TRUE)
	{
		for(long i=0;i<1000000;i++);	
		
		CPU_GPIO_SetPinState(GPIO_F06,!CPU_GPIO_GetPinState(GPIO_F06));
		//CPU_GPIO_SetPinState(GPIO_F07,CPU_GPIO_GetPinState(GPIO_A08));
		
	
	}
}


