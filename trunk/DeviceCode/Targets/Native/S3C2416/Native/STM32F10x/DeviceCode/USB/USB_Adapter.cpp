#include "USB_Adapter.h"
#include "STM32F10x_usb.h"
#include ".\library\library.h"



BOOL ConvertToEndpointInAddress(int iInput,uint8_t &u8Convert)
{
	switch(iInput)
	{
		case 0:
			u8Convert = EP0_IN;
			break;
		case 1:
			u8Convert = EP1_IN;
			break;
		case 2:
			u8Convert = EP2_IN;
			break;
		case 3:
			u8Convert = EP3_IN;
			break;
		default:
			return FALSE;
	}
	
	return TRUE;
	
}

BOOL ConvertToEndpointOutAddress(int iInput,uint8_t &u8Convert)
{
	switch(iInput)
	{
		case 0:
			u8Convert = EP0_OUT;
			break;
		case 1:
			u8Convert = EP1_OUT;
			break;
		case 2:
			u8Convert = EP2_OUT;
			break;
		case 3:
			u8Convert = EP3_OUT;
			break;
		default:
			return FALSE;
	}
	
	return TRUE;
}

BOOL ConvertToEndpointRegistry(int iInput,uint8_t &u8Convert)
{
	switch(iInput)
		{
			case 0:
				u8Convert = ENDP0;
				break;
			case 1:
				u8Convert = ENDP1;
				break;
			case 2:
				u8Convert = ENDP2;
				break;
			case 3:
				u8Convert = ENDP3;
				break;
			case 4:
				u8Convert = ENDP4;
				break;
			case 5:
				u8Convert = ENDP5;
				break;
			case 6:
				u8Convert = ENDP6;
				break;
			case 7:
				u8Convert = ENDP7;
				break;
			default:
				return FALSE;
		}
		
		return TRUE;
}


BOOL GetTxBufAddr(int iInput,uint16_t &u16Val)
{
	switch(iInput)
	{
		case ENDP0:
			u16Val = ENDP0_TXADDR;
			break;
		case ENDP1:
			u16Val = ENDP1_TXADDR;
			break;
		case ENDP2:
			u16Val = ENDP2_TXADDR;
			break;
		default:
			return FALSE;
	}
	
	return TRUE;
}

BOOL GetRxBufAddr(int iInput,uint16_t &u16Val)
{
	switch(iInput)
	{
		case ENDP0:
			u16Val = ENDP0_RXADDR;
			break;
		case ENDP1:
			u16Val = ENDP1_RXADDR;
			break;
		case ENDP2:
			u16Val = ENDP2_RXADDR;
			break;
		default:
			return FALSE;
	}
	
	return TRUE;
}