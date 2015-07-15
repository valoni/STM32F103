////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "USART_Adapter.h"

//------------------------------------------------------------------------
//Macro
#define USART_COUNT			3
#define BUFFER_LENGTH		512
//------------------------------------------------------------------------
struct USART_Info
{
	USART_TypeDef *pUSART;
	int ComPortNum;
	BOOL bTxBufferEmptyInterrupt;
	BOOL bRxBufferFullInterrupt;

};

USART_Info g_USART_Info[USART_COUNT] = {0};
//------------------------------------------------------------------------


//------------------------------------------------------------------------
//Description:
//	Convert the port number to index in array. 
//
//Parameters:
//	ComPortNum : [in] The com port
//	iIndex : [out] The index in the array
//------------------------------------------------------------------------
BOOL PortToIndex(int ComPortNum,int &iIndex)
{
	//The ComPortNum is begin with 1,the index is begin with 0
	if(ComPortNum < COM_PORT_BASE_NUMBER || ComPortNum > USART_COUNT - COM_PORT_BASE_NUMBER)
	{
		return FALSE;
	}
	
	iIndex = ComPortNum - COM_PORT_BASE_NUMBER;
	return TRUE;
}


#pragma arm section code = "SectionForInterruptHandler" //Begin

//--------------------------------------------------------
//Description:
//	The function for USART1 handling
//--------------------------------------------------------
void USARTInterruptHandler(void *pParam)
{
	USART_Info *pInfo = reinterpret_cast<USART_Info *>(pParam);
	if(pInfo == NULL)
	{
		//ERROR:It should not get here!
		while(TRUE);
	}
	
	//Receive	
	if(USART_GetITStatus(pInfo->pUSART, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
		USART_AddCharToRxBuffer(pInfo->ComPortNum, USART_ReceiveData(pInfo->pUSART));
		
		Events_Set( SYSTEM_EVENT_FLAG_COM_IN );
  }
  
  //Send
  if(USART_GetITStatus(pInfo->pUSART, USART_IT_TXE) != RESET)
  {   
  	char cSend;
    if(USART_RemoveCharFromTxBuffer(pInfo->ComPortNum, cSend ))
		{    	
			//Begin to write the character
    	CPU_USART_WriteCharToTxBuffer(pInfo->ComPortNum, cSend);
		}
		else
		{
			//Disable the send interrupt
			CPU_USART_TxBufferEmptyInterruptEnable(pInfo->ComPortNum, FALSE);
		}
		
		Events_Set( SYSTEM_EVENT_FLAG_COM_OUT );   
  }
}

#pragma arm section code //End

BOOL CPU_USART_Initialize( int ComPortNum, int BaudRate, int Parity, int DataBits, int StopBits, int FlowValue )
{
	//Convert the port number to registry.
	USART_TypeDef *pUSART = ConvertPort(ComPortNum);
	if(pUSART == NULL)
	{
		return FALSE;
	}
	
	//Initialize the information
	int iIndex = 0;
	if(PortToIndex(ComPortNum,iIndex) == FALSE)
	{
		return FALSE;
	}
	g_USART_Info[iIndex].pUSART = pUSART;
	g_USART_Info[iIndex].ComPortNum = ComPortNum;
	
	//The peripheral value
	PeripheralInfo PeriphInfo = {0};
	if(GetPeripheralInfo(pUSART,PeriphInfo) == FALSE)
	{
		return FALSE;
	}
	PeriphInfo.PeriphFunc(PeriphInfo.PeriphVal,ENABLE);
	
	//The Interrupt handler function
	DWORD dwIRQ = 0;
	if(PortToIRQ(ComPortNum,dwIRQ) == FALSE)
	{
		return FALSE;
	}
	CPU_INTC_ActivateInterrupt(dwIRQ,USARTInterruptHandler,&g_USART_Info[iIndex]);
	
	//The NVIC
	NVIC_InitTypeDef NVIC_InitInfo = {0};
	GetNVICInitInfo(pUSART,NVIC_InitInfo);
	NVIC_Init(&NVIC_InitInfo);  

	//The pin
	GPIO_InitTypeDef GPIO_InitInfo = {0};
	GetTxInitInfo(pUSART,GPIO_InitInfo);
	GPIO_Init(GetPort(pUSART),&GPIO_InitInfo);  
	
	GetRxInitInfo(pUSART,GPIO_InitInfo);
	GPIO_Init(GetPort(pUSART),&GPIO_InitInfo);  
	
	//Enable the USART
	USART_Cmd(pUSART,ENABLE);
	
	//The USART initialize
	USART_InitTypeDef  USART_InitInfo;    
	
	//The BaudRate
	USART_InitInfo.USART_BaudRate = BaudRate;	  
	
	//The word length
	uint16_t wWordLen = 0;
	ConvertWordLength(DataBits,wWordLen);
	USART_InitInfo.USART_WordLength = wWordLen;	  
	
	//The Parity
	uint16_t wParity = 0;
	ConvertParity(Parity,wParity);
	USART_InitInfo.USART_Parity = wParity;	
	
	//The Stop bit 
	uint16_t wStopBit = 0;
	ConvertStopBits(StopBits,wStopBit);
	USART_InitInfo.USART_StopBits = wStopBit;	 
	
	//The flow control
	uint16_t uFlowCtrl = 0;
	ConvertFlowControl(FlowValue,uFlowCtrl);
	USART_InitInfo.USART_HardwareFlowControl = uFlowCtrl;	  
	
	//The mode
	USART_InitInfo.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	  
	
	//Write the registry
	USART_Init(pUSART,&USART_InitInfo);   
	USART_ITConfig(pUSART,USART_IT_RXNE,ENABLE);

	
	return TRUE;
}

BOOL CPU_USART_Uninitialize( int ComPortNum )
{
	/*
	//Convert the port number to registry.
	USART_TypeDef *pUSART = ConvertPort(ComPortNum);
	if(pUSART == NULL)
	{
		return FALSE;
	}
	
	//The peripheral value
	uint32_t dwPeriph = 0;
	GetPeripheralInfo(pUSART,dwPeriph);
	RCC_APB2PeriphClockCmd(dwPeriph,DISABLE);
	*/
 	return TRUE;
}

BOOL CPU_USART_TxBufferEmpty( int ComPortNum )
{
	int iIndex = 0;
	if(PortToIndex(ComPortNum,iIndex) == FALSE)
	{
		return FALSE;
	}
	
	return (USART_GetFlagStatus(g_USART_Info[iIndex].pUSART,USART_FLAG_TXE) == SET);
}

BOOL CPU_USART_TxShiftRegisterEmpty( int ComPortNum )
{
	int iIndex = 0;
	if(PortToIndex(ComPortNum,iIndex) == FALSE)
	{
		return FALSE;
	}
	
	return (USART_GetFlagStatus(g_USART_Info[iIndex].pUSART,USART_FLAG_TC) == SET);
}

void CPU_USART_WriteCharToTxBuffer( int ComPortNum, UINT8 c )
{
	int iIndex = 0;
	if(PortToIndex(ComPortNum,iIndex) == FALSE)
	{
		return ;
	}
	
	/* Write one byte to the transmit data register */
  USART_SendData(g_USART_Info[iIndex].pUSART, c);	
}

void CPU_USART_TxBufferEmptyInterruptEnable( int ComPortNum, BOOL Enable )
{	
	int iIndex = 0;
	if(PortToIndex(ComPortNum,iIndex) == FALSE)
	{
		return ;
	}
	
	//Save the ENABLE flag
	g_USART_Info[iIndex].bTxBufferEmptyInterrupt = Enable;
  
  //Write to the registry
  if(Enable == FALSE)
  {
  	USART_ITConfig(g_USART_Info[iIndex].pUSART, USART_IT_TXE, DISABLE);
  }
  else
  {
  	USART_ITConfig(g_USART_Info[iIndex].pUSART, USART_IT_TXE, ENABLE);
  }
  
}

BOOL CPU_USART_TxBufferEmptyInterruptState( int ComPortNum )
{
  int iIndex = 0;
	if(PortToIndex(ComPortNum,iIndex) == FALSE)
	{
		return FALSE;
	}
	
	return g_USART_Info[iIndex].bTxBufferEmptyInterrupt;
}

void CPU_USART_RxBufferFullInterruptEnable( int ComPortNum, BOOL Enable )
{
	//Convert the port number to registry.
	USART_TypeDef *pUSART = ConvertPort(ComPortNum);
	if(pUSART == NULL)
	{
		return ;
	}	
	
	int iIndex = 0;
	if(PortToIndex(ComPortNum,iIndex) == FALSE)
	{
		return ;
	}
	
	//Save the ENABLE flag
	g_USART_Info[iIndex].bRxBufferFullInterrupt = Enable;
}

BOOL CPU_USART_RxBufferFullInterruptState( int ComPortNum )
{
	//Convert the port number to registry.
	int iIndex = 0;
	if(PortToIndex(ComPortNum,iIndex) == FALSE)
	{
		return FALSE;
	}	
	
  return g_USART_Info[iIndex].bRxBufferFullInterrupt;
}

void CPU_USART_ProtectPins( int ComPortNum, BOOL On )
{
}

UINT32 CPU_USART_PortsCount()
{
    return USART_COUNT;
}

void CPU_USART_GetPins( int ComPortNum, GPIO_PIN& rxPin, GPIO_PIN& txPin,GPIO_PIN& ctsPin, GPIO_PIN& rtsPin )
{   
    rxPin = GPIO_PIN_NONE; 
    txPin = GPIO_PIN_NONE; 
    ctsPin= GPIO_PIN_NONE; 
    rtsPin= GPIO_PIN_NONE; 

    return;
}

BOOL CPU_USART_SupportNonStandardBaudRate ( int ComPortNum )
{
    return FALSE;
}

void CPU_USART_GetBaudrateBoundary( int ComPortNum, UINT32& maxBaudrateHz, UINT32& minBaudrateHz )
{
    maxBaudrateHz = 115200;
    minBaudrateHz = 4800;
}

BOOL CPU_USART_IsBaudrateSupported( int ComPortNum, UINT32 & BaudrateHz )
{   
    return IS_USART_BAUDRATE(BaudrateHz);
}

BOOL CPU_USART_TxHandshakeEnabledState( int comPort )
{
    return TRUE;
}




