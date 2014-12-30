/*
 * S3C2440__USART.cpp
 *
 *  Created on: 9.4.2011
 *      Author: Matti Eerola
 */

#include <tinyhal.h>
#include "S3C2440_USART.h"
#include "..\S3C2440_TIME\S3C2440_TIME.h"
#include "..\S3C2440.h"

BOOL S3C2440_USART_Driver::Initialize( int comPort, int BaudRate, int Parity, int DataBits, int StopBits, int FlowValue )
{
	S3C2440::Debug_printf("S3C2440_USART_Driver::Initialize COM%d\r\n", comPort);
	S3C2440_USART &usart = S3C2440::USART(comPort);

	usart.UFCON = 0x07;
	usart.UMCON = 0x0;

	// Parity, etc..
	UINT8 hwParity;
	if (Parity == USART_PARITY_NONE)
		hwParity = 0;
	else if (Parity == USART_PARITY_ODD)
		hwParity = 4;
	else if (Parity == USART_PARITY_EVEN)
		hwParity = 5;
	else
		return FALSE;

	if (DataBits < 5 || DataBits > 8)
		return FALSE;
	UINT8 hwDataBits = DataBits - 5;

	if (StopBits != USART_STOP_BITS_ONE && StopBits != USART_STOP_BITS_TWO)
		return FALSE;
	INT8 hwStopBits = 0;
	if (StopBits == USART_STOP_BITS_TWO)
		hwStopBits = 1;

	usart.ULCON = (hwParity << 3) | (hwParity << 2) | hwDataBits;

	usart.UCON = (1<<9)|(1<<8)|(0<<7)|(1<<6)|(0<<5)|(0<<4)|(1<<2)|(1);

	//Baud rate
	UINT32 clockRate = S3C2440_TIME_Driver::PeripheralBusClock();
	UINT32 div = ( (int)(clockRate/16/BaudRate+0.5) -1 );
	usart.UBRDIV = div;

	// Interrupts
	UINT32 interrupt = 28;
	if (comPort == 1)
		interrupt = 23;
	else if (comPort == 2)
		interrupt = 15;

	S3C2440_AIC &aic = S3C2440::AIC();
	UINT32 rxSubInterrupt = comPort*3;
	UINT32 txSubInterrupt = comPort*3 + 1;
	//enable rx interrupts
	aic.SubInterruptEnable(rxSubInterrupt);
	//todo: implement writing with interrupts and then enable tx interrupts

	if (!CPU_INTC_ActivateInterrupt( interrupt, USART_ISR, (void*)(size_t)comPort ))
	{
		return FALSE;
	}

    return TRUE;
}


BOOL S3C2440_USART_Driver::Uninitialize( int comPort )
{
    return TRUE;
}

void S3C2440_USART_Driver::RefFlags( int comPort, INT8 RefFlags, BOOL Add )
{
    ASSERT_IRQ_MUST_BE_OFF();

    S3C2440_USART &usart = S3C2440::USART(comPort);

}

BOOL S3C2440_USART_Driver::TxBufferEmpty( int comPort )
{
    S3C2440_USART &usart = S3C2440::USART(comPort);
    return (usart.UTRSTAT & 0x2) != 0;
}

BOOL S3C2440_USART_Driver::TxShiftRegisterEmpty( int comPort )
{
    S3C2440_USART &usart = S3C2440::USART(comPort);

    return TRUE;
}

void S3C2440_USART_Driver::WriteCharToTxBuffer( int comPort, UINT8 c )
{
    S3C2440_USART &usart = S3C2440::USART(comPort);
    usart.UTXH = c;
}

void S3C2440_USART_Driver::TxBufferEmptyInterruptEnable( int comPort, BOOL enable )
{
	char c;

	if (enable)
	{
		USART_Flush(comPort);
	}
}

BOOL S3C2440_USART_Driver::TxBufferEmptyInterruptState( int comPort )
{
    S3C2440_USART &usart = S3C2440::USART(comPort);


    return TRUE;
}

void S3C2440_USART_Driver::RxBufferFullInterruptEnable( int comPort, BOOL Enable )
{

}

BOOL S3C2440_USART_Driver::RxBufferFullInterruptState( int comPort )
{
    S3C2440_USART &usart = S3C2440::USART(comPort);


    return FALSE;
}

void S3C2440_USART_Driver::USART_ISR( void* param )
{
    GLOBAL_LOCK(irq);

    UINT32  comPort = (UINT32)param;

    S3C2440_USART &usart = S3C2440::USART(comPort);

    if (usart.UTRSTAT & 0x01) // Receive buffer data ready? (0 = Empty)
    {
    	unsigned char c = (unsigned char)usart.URXH;
    	//S3C2440::Debug_SendByte(c); //send byte back to COM1

        USART_AddCharToRxBuffer( comPort, c );

        Events_Set( SYSTEM_EVENT_FLAG_COM_IN );
    }
}

BOOL S3C2440_USART_Driver::TxHandshakeEnabledState( int comPort )
{
    return TRUE;
}

void S3C2440_USART_Driver::ProtectPins( int comPort, BOOL on )
{

}

void S3C2440_USART_Driver::GetPins(int comPort, GPIO_PIN& rxPin, GPIO_PIN& txPin, GPIO_PIN& ctsPin, GPIO_PIN& rtsPin)
{
    rxPin = GPIO_PIN_NONE;
    txPin = GPIO_PIN_NONE;
    ctsPin= GPIO_PIN_NONE;
    rtsPin= GPIO_PIN_NONE;

    return;
}
void  S3C2440_USART_Driver::BaudrateBoundary(int ComPortNum, UINT32& maxBaudrateHz, UINT32& minBaudrateHz)
{
    maxBaudrateHz = 115200;
    minBaudrateHz = 115200;

}

BOOL S3C2440_USART_Driver::IsBaudrateSupported(int ComPortNum, UINT32 & BaudrateHz)
{
	return TRUE;
}
