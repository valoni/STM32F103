#pragma once

#include <tinyhal.h>
#include "stm32f10x.h"

//-----------------------------------------------------------------------------------------
//Description:
//	Convert the input value to the endpoint in address
//
//Parameters:
//	iInput : [in] The input value for converting
//	u8Convert : [out] The converted value
//-----------------------------------------------------------------------------------------
BOOL ConvertToEndpointInAddress(int iInput,uint8_t &u8Convert);

//-----------------------------------------------------------------------------------------
//Description:
//	Convert the input value to the endpoint out address
//
//Parameters:
//	iInput : [in] The input value for converting
//	u8Convert : [out] The converted value
//-----------------------------------------------------------------------------------------
BOOL ConvertToEndpointOutAddress(int iInput,uint8_t &u8Convert);

//-----------------------------------------------------------------------------------------
//Description:
//	Convert the input value to the endpoint registry
//
//Parameters:
//	iInput : [in] The input value for converting
//	u8Convert : [out] The converted value
//-----------------------------------------------------------------------------------------
BOOL ConvertToEndpointRegistry(int iInput,uint8_t &u8Convert);


//-----------------------------------------------------------------------------------------
//Description:
//	Get the transmit buffer address in the input ST libarry value
//
//Parameters:
//	iInput : [in] The input enpoint registry value for getting. For example ENDP2.
//	u16Val : [out] Store the value
//-----------------------------------------------------------------------------------------
BOOL GetTxBufAddr(int iInput,uint16_t &u16Val);

//-----------------------------------------------------------------------------------------
//Description:
//	Get the Receive buffer address in the input ST libarry value
//
//Parameters:
//	iInput : [in] The input enpoint registry value for getting. For example ENDP2.
//	u16Val : [out] Store the value
//-----------------------------------------------------------------------------------------
BOOL GetRxBufAddr(int iInput,uint16_t &u16Val);