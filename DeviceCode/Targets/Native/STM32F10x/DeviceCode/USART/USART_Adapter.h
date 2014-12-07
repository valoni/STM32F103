#include <tinyhal.h>
#include "stm32f10x_conf.h"

//----------------------------------------------------------------------
//Macro
#define COM_PORT_BASE_NUMBER		0


//----------------------------------------------------------------------
//Type

typedef void (*PeriphClockCmdFunc)(uint32_t RCC_APB1Periph, FunctionalState NewState);
struct PeripheralInfo
{
	uint32_t PeriphVal;
	PeriphClockCmdFunc PeriphFunc;
};


//----------------------------------------------------------------------
//Description:
//	Convert the input pin to stm32f10x flow control value.
//If return value is FALSE,the default value is set to output buffer which
//is not suitable for the input value
//Parameters:
//	iInput: [in] The input value to converted
//	wConverted: [out] The output value converted
//-----------------------------------------------------------------------
BOOL ConvertFlowControl(int iInput,uint16_t &wConverted);

//---------------------------------------------------------------------
//Description:
//	Convert the input pin to stm32f10x parity value.
//If return value is FALSE,the default value is set to output buffer which
//is not suitable for the input value
//Parameters:
//	iInput: [in] The input value to converted
//	wConverted: [out] The output value converted
//---------------------------------------------------------------------
BOOL ConvertParity(int iInput,uint16_t &wConverted);

//-----------------------------------------------------------------------
//Description:
//	Convert the input pin to stm32f10x Stop bits value.
//If return value is FALSE,the default value is set to output buffer which
//is not suitable for the input value
//Parameters:
//	iInput: [in] The input value to converted
//	wConverted: [out] The output value converted
//-----------------------------------------------------------------------
BOOL ConvertStopBits(int iInput,uint16_t &wConverted);

//-----------------------------------------------------------------------
//Description:
//	Convert the input pin to stm32f10x USART port value.NULL means failed.
//Parameters:
//	iInput: [in] The input value to converted
//-----------------------------------------------------------------------
USART_TypeDef* ConvertPort(int iInput);

//-----------------------------------------------------------------------
//Description:
//	Get the input port initialize information of pin for transmiting.
//Parameters:
//	USART_TypeDef: [in] The USART port index
//	initInfo : [out] Stored the initialize information for the current port.
//-----------------------------------------------------------------------
BOOL GetTxInitInfo(USART_TypeDef* pPort,GPIO_InitTypeDef &initInfo);

//-----------------------------------------------------------------------
//Description:
//	Get the input port initialize information of pin for receiving.
//Parameters:
//	USART_TypeDef: [in] The USART port index
//	initInfo : [out] Stored the initialize information for the current port.
//-----------------------------------------------------------------------
BOOL GetRxInitInfo(USART_TypeDef* pPort,GPIO_InitTypeDef &initInfo);

//-----------------------------------------------------------------------
//Description:
//	Get the input port initialize information for NVIC
//Parameters:
//	USART_TypeDef: [in] The USART port index
//	initInfo : [out] Stored the initialize information for the current port.
//-----------------------------------------------------------------------
BOOL GetNVICInitInfo(USART_TypeDef* pPort,NVIC_InitTypeDef &initInfo);

//-----------------------------------------------------------------------
//Description:
//	Get the input port initialize information for peripheral clock
//Parameters:
//	USART_TypeDef: [in] The USART port index
//	PeriphInfo : [out] Stored the initialize information for the current port.
//-----------------------------------------------------------------------
BOOL GetPeripheralInfo(USART_TypeDef* pPort,PeripheralInfo &PeriphInfo);

//-----------------------------------------------------------------------
//Description:
//	Get the GPIO port for the input USART value.
//Parameters:
//	USART_TypeDef: [in] The USART port index
//-----------------------------------------------------------------------
GPIO_TypeDef* GetPort(USART_TypeDef* pPort);

//-----------------------------------------------------------------------
//Description:
//	Convert the input databit to stm32f10x word length bits value.
//If return value is FALSE,the default value is set to output buffer which
//is not suitable for the input value
//Parameters:
//	iInput: [in] The input value to converted
//	wConverted: [out] The output value converted
//-----------------------------------------------------------------------
BOOL ConvertWordLength(int iInput,uint16_t &wConverted);

//--------------------------------------------------------
//Description:
//	Convert the input prt to IRQ table index
//Parameters:
//	ComPortNum : [in] The input com port number
//	dwIrq : [out] The converted value
//--------------------------------------------------------
BOOL PortToIRQ(int ComPortNum,DWORD &dwIrq);