////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _S3C2416__USART_H_1
#define _S3C2416__USART_H_1   1

typedef struct 
{
  volatile unsigned int ULCON ;//There are four UART line control registers 
  volatile unsigned int UCON ;//There are four UART control registers
  volatile unsigned int UFCON ;//There are four UART FIFO control registers
  volatile unsigned int UMCON ;//There are three UART MODEM control registers
  volatile unsigned int UTRSTAT;//There are four UART Tx/Rx status register
  volatile unsigned int UERSTAT;//There are four UART Rx error status registers 
  volatile unsigned int UFSTAT;//There are four UART FIFO status registers 
  volatile unsigned int UMSTAT;//There are three UART modem status registers
  volatile unsigned int UTXH;//There are four UART transmit buffer registers
  volatile unsigned int URXH;//There are four UART receive buffer registe
  volatile unsigned int UBRDIV;//There are four UART baud rate divisor registers 
  volatile unsigned int UDIVSLOT;//
}S3C2416_UART_TYPE;

#define ELFIN_UART_BASE	0x50000000

#define S3C2416_UART0_BASE   ELFIN_UART_BASE
#define S3C2416_UART1_BASE  (ELFIN_UART_BASE + 0x4000)
#define S3C2416_UART2_BASE  (ELFIN_UART_BASE + 0x8000)
#define S3C2416_UART3_BASE  (ELFIN_UART_BASE + 0xc000)

#define UART0  ((S3C2416_UART_TYPE *) S3C2416_UART0_BASE)
#define UART1  ((S3C2416_UART_TYPE *) S3C2416_UART1_BASE)
#define UART2  ((S3C2416_UART_TYPE *) S3C2416_UART2_BASE)
#define UART3  ((S3C2416_UART_TYPE *) S3C2416_UART3_BASE)
//////////////////////////////////////////////////////////////////////////////
// S3C2416_USART_Driver
//

//
// S3C2416_USART_Driver
//////////////////////////////////////////////////////////////////////////////

#endif //_S3C2416__USART_H_1
