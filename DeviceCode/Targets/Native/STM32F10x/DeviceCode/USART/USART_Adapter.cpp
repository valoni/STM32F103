#include "USART_Adapter.h"
#include "INTC_Adapter.h"



BOOL ConvertFlowControl(int iInput,uint16_t &wConverted)
{
	const uint16_t INVALID_VAL = 0xFFFF;
	uint16_t wCvrtBuf = INVALID_VAL;
	
	if(iInput == USART_FLOW_NONE)
	{
		wCvrtBuf = USART_HardwareFlowControl_None;
	}	
	else if((iInput & USART_FLOW_HW_IN_EN) &&  (iInput & USART_FLOW_HW_OUT_EN))
	{
		wCvrtBuf = USART_HardwareFlowControl_RTS_CTS;
	}
	else if((iInput & USART_FLOW_HW_IN_EN) &&  !(iInput & USART_FLOW_HW_OUT_EN))
	{
		wCvrtBuf = USART_HardwareFlowControl_RTS;
	}
	else if(!(iInput & USART_FLOW_HW_IN_EN) &&  (iInput & USART_FLOW_HW_OUT_EN))
	{
		wCvrtBuf = USART_HardwareFlowControl_CTS;
	}
	

	
	if(wCvrtBuf != INVALID_VAL)
	{
		wConverted = wCvrtBuf;
		return TRUE;
	}
	else
	{
		wConverted = USART_HardwareFlowControl_None;
		return FALSE;
	}
}

BOOL ConvertParity(int iInput,uint16_t &wConverted)
{
	switch(iInput)
	{
		case USART_PARITY_NONE:
			wConverted = USART_Parity_No;
			break;
		case USART_PARITY_ODD:
			wConverted = USART_Parity_Odd;
			break;
		case USART_PARITY_EVEN:
			wConverted = USART_Parity_Even;
			break;
		default:
			wConverted = USART_Parity_No;
			return FALSE;
	}
	
	return TRUE;
}

BOOL ConvertStopBits(int iInput,uint16_t &wConverted)
{
	switch(iInput)
	{
		case USART_STOP_BITS_ONE:
			wConverted = USART_StopBits_1;
			break;
		case USART_STOP_BITS_TWO:
			wConverted = USART_StopBits_2;
			break;
		case USART_STOP_BITS_ONEPOINTFIVE:
			wConverted = USART_StopBits_1_5;
			break;
		default:
			wConverted = USART_StopBits_1;
			return FALSE;
	}
	
	return TRUE;
}

USART_TypeDef* ConvertPort(int iInput)
{	
	switch(iInput)
	{
		case COM_PORT_BASE_NUMBER:
			return USART1;
		case COM_PORT_BASE_NUMBER + 1:
			return USART2;
		case COM_PORT_BASE_NUMBER + 2:
			return USART3;
		default:
			return NULL;
	}
}

BOOL GetTxInitInfo(USART_TypeDef* pPort,GPIO_InitTypeDef &initInfo)
{	
	if(pPort == USART1)
	{
		initInfo.GPIO_Pin = GPIO_Pin_9;   		
	}
	else if(pPort == USART2)
	{
		initInfo.GPIO_Pin = GPIO_Pin_2;   		
	}
	else if(pPort == USART3)
	{
		initInfo.GPIO_Pin = GPIO_Pin_10;   		
	}
	else
	{
		return FALSE;
	}
	
	
	initInfo.GPIO_Speed = GPIO_Speed_50MHz;   
	initInfo.GPIO_Mode = GPIO_Mode_AF_PP;
		
	return TRUE;

}

BOOL GetRxInitInfo(USART_TypeDef* pPort,GPIO_InitTypeDef &initInfo)
{	
	if(pPort == USART1)
	{
		initInfo.GPIO_Pin = GPIO_Pin_10;   		
	}
	else if(pPort == USART2)
	{
		initInfo.GPIO_Pin = GPIO_Pin_3;   		
	}
	else if(pPort == USART3)
	{
		initInfo.GPIO_Pin = GPIO_Pin_11;   		
	}
	else
	{
		return FALSE;
	}
	
	
	initInfo.GPIO_Speed = GPIO_Speed_50MHz;   
	initInfo.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	return TRUE;

}

BOOL GetNVICInitInfo(USART_TypeDef* pPort,NVIC_InitTypeDef &initInfo)
{	
	if(pPort == USART1)
	{
		initInfo.NVIC_IRQChannel = USART1_IRQn;   		
	}
	else if(pPort == USART2)
	{
		initInfo.NVIC_IRQChannel = USART2_IRQn;   
	}
	else if(pPort == USART3)
	{
		initInfo.NVIC_IRQChannel = USART3_IRQn;   
	}
	else
	{
		return FALSE;
	}
	
	initInfo.NVIC_IRQChannelSubPriority = 0;   
	initInfo.NVIC_IRQChannelCmd = ENABLE;
		
	return TRUE;

}

BOOL GetPeripheralInfo(USART_TypeDef* pPort,PeripheralInfo &PeriphInfo)
{	
	if(pPort == USART1)
	{
		PeriphInfo.PeriphVal = RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA;
		PeriphInfo.PeriphFunc = RCC_APB2PeriphClockCmd;
	}
	else if(pPort == USART2)
	{
		PeriphInfo.PeriphVal = RCC_APB1Periph_USART2 | RCC_APB2Periph_GPIOA;
		PeriphInfo.PeriphFunc = RCC_APB1PeriphClockCmd;
	}
	else if(pPort == USART3)
	{
		PeriphInfo.PeriphVal = RCC_APB1Periph_USART3 | RCC_APB2Periph_GPIOB;
		PeriphInfo.PeriphFunc = RCC_APB1PeriphClockCmd;
	}
	else
	{
		return FALSE;
	}
	
	return TRUE;

}

GPIO_TypeDef* GetPort(USART_TypeDef* pPort)
{
	if(pPort == USART1)
	{
		return GPIOA;
	}
	else if(pPort == USART2)
	{
		return GPIOA;
	}
	else if(pPort == USART3)
	{
		return GPIOB;
	}
	else
	{
		return NULL;
	}
}

BOOL ConvertWordLength(int iInput,uint16_t &wConverted)
{
	switch(iInput)
	{
		case 8:
			wConverted = USART_WordLength_8b;
			break;
		case 9:
			wConverted = USART_WordLength_9b;
			break;
		default:
			wConverted = USART_WordLength_8b;
			return FALSE;
	}
	
	return TRUE;
}

BOOL PortToIRQ(int ComPortNum,DWORD &dwIrq)
{
	switch(ComPortNum)
	{
		case COM_PORT_BASE_NUMBER:
			dwIrq = IRQ_USART1;
			break;
		case COM_PORT_BASE_NUMBER + 1:
			dwIrq = IRQ_USART2;
			break;
		case COM_PORT_BASE_NUMBER + 2:
			dwIrq = IRQ_USART3;
			break;
		default:
			return FALSE;
	}
	
	return TRUE;
}