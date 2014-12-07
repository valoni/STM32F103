////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "GPIO_Adapter.h"
#include "INTC_Adapter.h"

struct PinISRDescriptor
{
	GPIO_INTERRUPT_SERVICE_ROUTINE pISR;
	
	//Parameters for the ISR function 
	GPIO_PIN pin;
	BOOL pinState;
	void *pParam;
	
	//The index in the vector table
	DWORD dwIRQ;
	
	//The EXTI line
	uint32_t dwEXTILine;
};

//There is 16 interrupt line for the stm32f10x
PinISRDescriptor g_PinISRDescriptor[16];

//--------------------------------------------------------
//Description:
//	The function for EXTI0 to EXTI4 handling
//--------------------------------------------------------
void InterruptHandler0_4(void *pParam)
{
	PinISRDescriptor *pPinISRDescriptor = reinterpret_cast<PinISRDescriptor *>(pParam);
	if(pPinISRDescriptor == NULL)
	{
		//Error,it should not get here!
		return;
	}
	
	//Get the current pin state
	pPinISRDescriptor->pinState = CPU_GPIO_GetPinState(pPinISRDescriptor->pinState);
	
	//Call the callback function
	(*pPinISRDescriptor->pISR)(pPinISRDescriptor->pin,pPinISRDescriptor->pinState,pPinISRDescriptor->pParam);
	
	//Clear the flag bit
	EXTI_ClearITPendingBit(pPinISRDescriptor->dwEXTILine);
}

//--------------------------------------------------------
//Description:
//	The function for EXTI5 to EXTI15 handling
//--------------------------------------------------------
void InterruptHandler5_15(void *pParam)
{
	//The begin and end searching index
	const int START_SEARCH_INDEX = 5;
	const int END_SEARCH_INDEX = 15;
	
	//Point to ISR descriptor
	PinISRDescriptor *pPinISRDescriptor = NULL;
	
	
	for(int i = START_SEARCH_INDEX; i <= END_SEARCH_INDEX; ++ i)
	{		 
		if(g_PinISRDescriptor[i].pISR == NULL)
		{
			//No ISR function,so continue next loop
			continue;
		}
		
		if(EXTI_GetITStatus(g_PinISRDescriptor[i].dwEXTILine) == SET)
		{
			//It's the EXTI line occurs£¬so break.
			pPinISRDescriptor = &g_PinISRDescriptor[i];
			break;
		}
	}
	
	if(pPinISRDescriptor == NULL)
	{
		//Error,it should not get here!
		return;
	}
	
	//Get the current pin state
	pPinISRDescriptor->pinState = CPU_GPIO_GetPinState(pPinISRDescriptor->pinState);
	
	//Call the callback function
	(*pPinISRDescriptor->pISR)(pPinISRDescriptor->pin,pPinISRDescriptor->pinState,pPinISRDescriptor->pParam);
	
	//Clear the flag bit
	EXTI_ClearITPendingBit(pPinISRDescriptor->dwEXTILine);
}

//--------------------------------------------------------
//Description:
//	Convert the pin value to the index in the global table
//
//Parameters:
//	pin : [in] The input pin
//	dwIndex : [out] The index in the global table
//--------------------------------------------------------
BOOL PinToDescriptorIndex(GPIO_PIN pin,DWORD &dwIndex)
{
	dwIndex = pin % PIN_COUNT_EACH_PORT;	
	return TRUE;
}


//--//
BOOL CPU_GPIO_Initialize()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF, ENABLE);
                         
	return TRUE;
}

BOOL CPU_GPIO_Uninitialize()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF, DISABLE);
                         
	return TRUE;
}

UINT32 CPU_GPIO_Attributes( GPIO_PIN Pin )
{
	if(IsValidPin(Pin) != FALSE)
	{
		return (GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT);
	}
	else
	{
		return GPIO_ATTRIBUTE_NONE;
	}
}

void CPU_GPIO_DisablePin( GPIO_PIN Pin, GPIO_RESISTOR ResistorState, UINT32 Direction, GPIO_ALT_MODE AltFunction )
{
}

void CPU_GPIO_EnableOutputPin( GPIO_PIN Pin, BOOL InitialState )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//Set the pin index
	if(PinToBit(Pin,GPIO_InitStructure.GPIO_Pin) == FALSE)
	{
		//Do nothing
		return ;
	}
	
	
	//Set the default frequency as 50MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	
	//Output mode
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	
	//Initialize
	GPIO_Init(PinToPort(Pin), &GPIO_InitStructure);
	
	//Set the pin initial state
	CPU_GPIO_SetPinState(Pin,InitialState);
}

BOOL CPU_GPIO_EnableInputPin( GPIO_PIN Pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE PIN_ISR, GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState )
{
	return CPU_GPIO_EnableInputPin2( Pin, GlitchFilterEnable, PIN_ISR, NULL, IntEdge, ResistorState );
}

BOOL CPU_GPIO_EnableInputPin2( GPIO_PIN Pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE PIN_ISR, void* ISR_Param, GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//Set the pin index
	if(PinToBit(Pin,GPIO_InitStructure.GPIO_Pin) == FALSE)
	{
		return FALSE;
	}
	
	//Set the default frequency as 50MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	
	//Input mode	
	switch(ResistorState)
	{
		case RESISTOR_PULLDOWN:
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
			break;
		case RESISTOR_PULLUP:
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
			break;
		default:
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	}
	
	//Initialize
	GPIO_Init(PinToPort(Pin), &GPIO_InitStructure);
	
	
	// Connect Button EXTI Line to GPIO Pin 
	uint8_t wPortSource = 0;
	if(PinToPortSource(Pin,wPortSource) == FALSE)
	{
		return FALSE;
	}
	
	uint8_t wPinSource = 0;
	if(PinToPinSource(Pin,wPinSource) == FALSE)
	{
		return FALSE;
	}
	
  GPIO_EXTILineConfig(wPortSource, wPinSource); 
  
  
  //Begin to configure EXTI line parameters
	EXTI_InitTypeDef EXTI_InitStructure;
	if(PinToLine(Pin,EXTI_InitStructure.EXTI_Line) == FALSE)
	{
		return FALSE;
	}
	
	if(IntEdge == GPIO_INT_NONE )
	{
		//GlitchFilterEnable is GPIO_INT_NONE that needn't to detect
		EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	}
	else if(IntEdge == GPIO_INT_LEVEL_LOW || IntEdge == GPIO_INT_LEVEL_HIGH)
	{
		//Doesn't support the input edge mode,so return FALSE.
		return FALSE;
	}
	else
	{
		switch(IntEdge)
		{
			case GPIO_INT_EDGE_LOW:
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    
				break;
			case GPIO_INT_EDGE_HIGH:
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;    
				break;
			case GPIO_INT_EDGE_BOTH:
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;    
				break;
		}
		
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		
		
	}
	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_Init(&EXTI_InitStructure);
	
	
	//Get the index in the global ISR descriptor
	DWORD dwIndexDescriptor = 0;
	if(PinToDescriptorIndex(Pin,dwIndexDescriptor) == FALSE)
	{
		return FALSE;
	}
	
	//Set the parameters
	g_PinISRDescriptor[dwIndexDescriptor].pISR = PIN_ISR;
	g_PinISRDescriptor[dwIndexDescriptor].pin = Pin;
	g_PinISRDescriptor[dwIndexDescriptor].pinState = FALSE; //When the interrupt occur,it would check the value in the handler.
	g_PinISRDescriptor[dwIndexDescriptor].pParam = ISR_Param;
	if(PinToIRQ(Pin,g_PinISRDescriptor[dwIndexDescriptor].dwIRQ) == FALSE)
	{
		return FALSE;
	}
	if(PinToLine(Pin,g_PinISRDescriptor[dwIndexDescriptor].dwEXTILine) == FALSE)
	{
		return FALSE;
	}
	
	//Enable the interrupt
	if(0 <= dwIndexDescriptor && dwIndexDescriptor <= 4)
	{
		CPU_INTC_ActivateInterrupt(g_PinISRDescriptor[dwIndexDescriptor].dwIRQ,InterruptHandler0_4,&g_PinISRDescriptor[dwIndexDescriptor]);
	}
	else
	{
		CPU_INTC_ActivateInterrupt(g_PinISRDescriptor[dwIndexDescriptor].dwIRQ,InterruptHandler5_15,NULL);
	}
	
	CPU_INTC_InterruptEnable(g_PinISRDescriptor[dwIndexDescriptor].dwIRQ);
	return TRUE;
}

BOOL CPU_GPIO_GetPinState( GPIO_PIN Pin )
{
	uint16_t wBit = 0;
	if(PinToBit(Pin,wBit) == FALSE)
	{
		return FALSE;
	}
	
	return GPIO_ReadInputDataBit(PinToPort(Pin), wBit);
}

void CPU_GPIO_SetPinState( GPIO_PIN Pin, BOOL PinState )
{
	uint16_t wBit = 0;
	if(PinToBit(Pin,wBit) == FALSE)
	{
		//Do nothing
		return ;
	}
	
	if(PinState == FALSE)
	{
		//Output low level		
		GPIO_ResetBits(PinToPort(Pin), wBit);		
	}
	else
	{		
		//Output high level	
		GPIO_SetBits(PinToPort(Pin), wBit);			
	}
}

BOOL CPU_GPIO_PinIsBusy( GPIO_PIN Pin )
{
    return FALSE;
}

BOOL CPU_GPIO_ReservePin( GPIO_PIN Pin, BOOL fReserve )
{
    return TRUE;
}

UINT32 CPU_GPIO_GetDebounce()
{
    return 0;
}

BOOL CPU_GPIO_SetDebounce( INT64 debounceTimeMilliseconds )
{
    return FALSE;
}

INT32 CPU_GPIO_GetPinCount()
{
    return ALL_PIN_COUNT; 
} 

void CPU_GPIO_GetPinsMap( UINT8* pins, size_t size )
{
    DWORD dwMaxPin = ALL_PIN_COUNT;
    while(dwMaxPin-- && size--)
    {
    	*pins = GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT;
    }
}

UINT8 CPU_GPIO_GetSupportedResistorModes( GPIO_PIN pin )
{
    // as it is stub, return 0;
   return 0;
}
UINT8 CPU_GPIO_GetSupportedInterruptModes( GPIO_PIN pin )
{
    // as it is stub, return 0;
    return 0;
}

