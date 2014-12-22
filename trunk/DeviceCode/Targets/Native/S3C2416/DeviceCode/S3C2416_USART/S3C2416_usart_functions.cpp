////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cores\arm\include\cpu.h>
#include "S3C2416_USART.h"
static S3C2416_UART_TYPE* g_S3C2416_Uart[] = {UART0, UART1, UART2,UART3}; // IO addresses

BOOL CPU_USART_Initialize( int ComPortNum, int BaudRate, int Parity, int DataBits, int StopBits, int FlowValue )
{
	BOOL fRet = TRUE;
    if (ComPortNum >= TOTAL_USART_PORT) return FALSE;
    if (Parity >= USART_PARITY_MARK) return FALSE;
	GLOBAL_LOCK(irq);
	S3C2416_UART_TYPE* uart = g_S3C2416_Uart[ComPortNum];
    UINT32 clk;
	uart->UCON = 0x245;//按Uboot的设置
	clk = SYSTEM_PERIPHERAL_CLOCK_HZ;
	float div_val = (UINT32)((clk /(BaudRate *16))-1); //
	UINT16 UBRDIV = (UINT16) div_val;
	UINT16 UDIVSLOTID = (div_val - UBRDIV)*10;
	UINT16 UDIVSLOT;
	switch(UDIVSLOTID)
	{
		case 0: UDIVSLOT=0x0; break;
		case 1: UDIVSLOT=0x80; break;
		case 2: UDIVSLOT=0x808; break;		
		case 3: UDIVSLOT=0x0888; break;	
		case 4: UDIVSLOT=0x2222; break;	
		case 5: UDIVSLOT=0x4924; break;	
		case 6: UDIVSLOT=0x4a52; break;
		case 7: UDIVSLOT=0x54aa; break;
		case 8: UDIVSLOT=0x5555; break;
    	case 9: UDIVSLOT=0xd555; break;
		case 10: UDIVSLOT=0xd5d5; break;
		case 11: UDIVSLOT=0xd5d5; break;
		case 12: UDIVSLOT=0xdddd; break;
		case 13: UDIVSLOT=0xdfdd; break;
		case 14: UDIVSLOT=0xdfdf; break;
		case 15: UDIVSLOT=0xffdf; break;
        default:break;		
	}
   uart->UBRDIV = UBRDIV;
   uart->UDIVSLOT = UDIVSLOT;
	 switch(Parity)
    {
		case USART_PARITY_NONE:
		uart->ULCON &= ~(7 << 3);
		     break;		
        case USART_PARITY_ODD:
        uart->ULCON &= ~(7 << 3);
		uart->ULCON |=  4 << 3; 
            break;
        case USART_PARITY_EVEN:
        uart->ULCON &= ~(7 << 3);
		uart->ULCON |=  5 << 3; 
            break;
        case USART_PARITY_MARK:
        uart->ULCON &= ~(7 << 3);
		uart->ULCON |=  6 << 3; 
            break;
        case USART_PARITY_SPACE:
        uart->ULCON &= ~(7 << 3);
		uart->ULCON |=  7 << 3; 
          
        default: fRet = FALSE; // not supported
                          //fall through for default
    }
	
	switch(DataBits)
    {
        case 5:
           uart->ULCON &= ~(3<<0);
            break;
        case 6:
           uart->ULCON &= ~(3<<0);
		   uart->ULCON |=  1 << 0;
            break;
        case 7:
           uart->ULCON &= ~(3<<0);
		   uart->ULCON |=  2 << 0;
            break;
		case 8:
           uart->ULCON &= ~(3<<0);
		   uart->ULCON |=  3 << 0;
            break;	
        default:fRet = FALSE; // not supported
            //fall through for default
    }
	
    switch(StopBits)
    {
        case USART_STOP_BITS_ONE:
          uart->ULCON &= ~(1<<2);
            break;
        case USART_STOP_BITS_TWO:
          uart->ULCON |= 1<<2;
            break;
        // not supported
        case USART_STOP_BITS_NONE:
        default:
            fRet = FALSE;
            break;
    }
	 uart->UTXH = 0x4f4f4f4f;//按照Uboot设置
	 
	 return fRet;
}

BOOL CPU_USART_Uninitialize( int ComPortNum )
{
    return FALSE;
}

BOOL CPU_USART_TxBufferEmpty( int ComPortNum )
{
   if (g_S3C2416_Uart[ComPortNum]->UTRSTAT & (1<<2)) return TRUE;
    return FALSE;
}

BOOL CPU_USART_TxShiftRegisterEmpty( int ComPortNum )
{
   if (g_S3C2416_Uart[ComPortNum]->UTRSTAT & (1<<1)) return TRUE;
    return FALSE;
}

void CPU_USART_WriteCharToTxBuffer( int ComPortNum, UINT8 c )
{
 #ifdef DEBUG
    ASSERT(CPU_USART_TxBufferEmpty(ComPortNum));
#endif
    g_S3C2416_Uart[ComPortNum]->UTXH = c;
}

void CPU_USART_TxBufferEmptyInterruptEnable( int ComPortNum, BOOL Enable )
{
  
}

BOOL CPU_USART_TxBufferEmptyInterruptState( int ComPortNum )
{
 return FALSE;
}

void CPU_USART_RxBufferFullInterruptEnable( int ComPortNum, BOOL Enable )
{
  
}

BOOL CPU_USART_RxBufferFullInterruptState( int ComPortNum )
{
  return FALSE;
}

BOOL CPU_USART_TxHandshakeEnabledState( int comPort )
{
   return FALSE;
}

void CPU_USART_ProtectPins( int ComPortNum, BOOL On )
{

}

UINT32 CPU_USART_PortsCount()
{
     return TOTAL_USART_PORT;
}

void CPU_USART_GetPins( int ComPortNum, GPIO_PIN& rxPin, GPIO_PIN& txPin,GPIO_PIN& ctsPin, GPIO_PIN& rtsPin )
{   
   
}

BOOL CPU_USART_SupportNonStandardBaudRate (int ComPortNum )
{
    return FALSE;
}

void CPU_USART_GetBaudrateBoundary( int ComPortNum, UINT32& maxBaudrateHz, UINT32& minBaudrateHz )
{
   
}

BOOL CPU_USART_IsBaudrateSupported( int ComPortNum, UINT32& BaudrateHz )
{
   return FALSE;
}



