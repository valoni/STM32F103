#include "GPIO_Adapter.h"
#include "INTC_Adapter.h"

GPIO_TypeDef* PinToPort(GPIO_PIN pin)
{	
	int iPort = pin / PIN_COUNT_EACH_PORT;
	switch(iPort)
	{
		case 00:
			return GPIOA;
		case 01:
			return GPIOB;
		case 02:
			return GPIOC;
		case 03:
			return GPIOD;
		case 04:
			return GPIOE;
		case 05:
			return GPIOF;
		case 06:
			return GPIOG;
		default:
			return NULL;
	}
}

BOOL PinToBit(GPIO_PIN pin,uint16_t &wBit)
{
	int iVal = pin % PIN_COUNT_EACH_PORT;
	switch(iVal)
	{
		case 0:
			wBit = GPIO_Pin_0;
			break;
		case 1:
			wBit = GPIO_Pin_1;
			break;
		case 2:
			wBit = GPIO_Pin_2;
			break;
		case 3:
			wBit = GPIO_Pin_3;
			break;
		case 4:
			wBit = GPIO_Pin_4;
			break;
		case 5:
			wBit = GPIO_Pin_5;
			break;
		case 6:
			wBit = GPIO_Pin_6;
			break;
		case 7:
			wBit = GPIO_Pin_7;
			break;
		case 8:
			wBit = GPIO_Pin_8;
			break;
		case 9:
			wBit = GPIO_Pin_9;
		case 10:
			wBit = GPIO_Pin_10;
			break;
		case 11:
			wBit = GPIO_Pin_11;
			break;
		case 12:
			wBit = GPIO_Pin_12;
			break;
		case 13:
			wBit = GPIO_Pin_13;
			break;
		case 14:
			wBit = GPIO_Pin_14;
			break;
		case 15:
			wBit = GPIO_Pin_15;
			break;
		default:
			return FALSE;
	}
	
	return TRUE;
}

BOOL IsValidPin(GPIO_PIN pin)
{
	uint16_t wBit = 0;
	if(PinToBit(pin,wBit) == FALSE)
	{
		return FALSE;
	}
	
	if(IS_GPIO_ALL_PERIPH(PinToPort(pin)) != FALSE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


BOOL PinToPortSource(GPIO_PIN pin,uint8_t &wPortSource)
{
	int iPortSource = pin / PIN_COUNT_EACH_PORT;
	switch(iPortSource)
	{
		case 00:
			wPortSource = GPIO_PortSourceGPIOA;
			break;
		case 01:
			wPortSource = GPIO_PortSourceGPIOB;
			break;
		case 02:
			wPortSource = GPIO_PortSourceGPIOC;
			break;
		case 03:
			wPortSource = GPIO_PortSourceGPIOD;
			break;
		case 04:
			wPortSource = GPIO_PortSourceGPIOE;
			break;
		case 05:
			wPortSource = GPIO_PortSourceGPIOF;
			break;
		case 06:
			wPortSource = GPIO_PortSourceGPIOG;
			break;
		default:
			return FALSE;
	}
	
	return TRUE;
}


BOOL PinToPinSource(GPIO_PIN pin,uint8_t &wPinSource)
{
	int iPinSource = pin % PIN_COUNT_EACH_PORT;
	switch(iPinSource)
	{
		case 0:
			wPinSource = GPIO_PinSource0;
			break;
		case 1:
			wPinSource = GPIO_PinSource1;
			break;
		case 2:
			wPinSource = GPIO_PinSource2;
			break;
		case 3:
			wPinSource = GPIO_PinSource3;
			break;
		case 4:
			wPinSource = GPIO_PinSource4;
			break;
		case 5:
			wPinSource = GPIO_PinSource5;
			break;
		case 6:
			wPinSource = GPIO_PinSource6;
			break;
		case 7:
			wPinSource = GPIO_PinSource7;
			break;
		case 8:
			wPinSource = GPIO_PinSource8;
			break;
		case 9:
			wPinSource = GPIO_PinSource9;
			break;
		case 10:
			wPinSource = GPIO_PinSource10;
			break;
		case 11:
			wPinSource = GPIO_PinSource11;
			break;
		case 12:
			wPinSource = GPIO_PinSource12;
			break;
		case 13:
			wPinSource = GPIO_PinSource13;
			break;
		case 14:
			wPinSource = GPIO_PinSource14;
			break;
		case 15:
			wPinSource = GPIO_PinSource15;
			break;
		default:
			return FALSE;
	}
	
	return TRUE;
}


BOOL PinToLine(GPIO_PIN pin,uint32_t &dwLine)
{
	int iLine = pin % PIN_COUNT_EACH_PORT;
	switch(iLine)
	{
		case 0:
			dwLine = EXTI_Line0;
			break;
		case 1:
			dwLine = EXTI_Line1;
			break;
		case 2:
			dwLine = EXTI_Line2;
			break;
		case 3:
			dwLine = EXTI_Line3;
			break;
		case 4:
			dwLine = EXTI_Line4;
			break;
		case 5:
			dwLine = EXTI_Line5;
			break;
		case 6:
			dwLine = EXTI_Line6;
			break;
		case 7:
			dwLine = EXTI_Line7;
			break;
		case 8:
			dwLine = EXTI_Line8;
			break;
		case 9:
			dwLine = EXTI_Line9;
			break;
		case 10:
			dwLine = EXTI_Line10;
			break;
		case 11:
			dwLine = EXTI_Line11;
			break;
		case 12:
			dwLine = EXTI_Line12;
			break;
		case 13:
			dwLine = EXTI_Line13;
			break;
		case 14:
			dwLine = EXTI_Line14;
			break;
		case 15:
			dwLine = EXTI_Line15;
			break;
		default:
			return FALSE;
	}
	
	return TRUE;
}


BOOL PinToIRQ(GPIO_PIN pin,DWORD &dwIrq)
{
	int iIRQ = pin % PIN_COUNT_EACH_PORT;
	switch(iIRQ)
	{
		case 0:
			dwIrq = IRQ_EXTI0;
			break;
		case 1:
			dwIrq = IRQ_EXTI1;
			break;
		case 2:
			dwIrq = IRQ_EXTI2;
			break;
		case 3:
			dwIrq = IRQ_EXTI3;
			break;
		case 4:
			dwIrq = IRQ_EXTI4;
			break;
		case 5:			
		case 6:			
		case 7:			
		case 8:			
		case 9:
			dwIrq = IRQ_EXTI9_5;
			break;
		case 10:			
		case 11:			
		case 12:			
		case 13:			
		case 14:			
		case 15:
			dwIrq = IRQ_EXTI15_10;
			break;
		default:
			return FALSE;
	}
	
	return TRUE;
}

