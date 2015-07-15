/*
 * S3C2440_USART.h
 *
 *  Created on: 24.4.2011
 *      Author: Matti Eerola
 */

#ifndef S3C2440_USART_H_
#define S3C2440_USART_H_

//////////////////////////////////////////////////////////////////////////////
// S3C2440_USART_Driver
//
struct S3C2440_USART_Driver
{
    static const UINT32 c_RefFlagRx = 0x01;
    static const UINT32 c_RefFlagTx = 0x02;

    //--//
    INT8 m_RefFlags[TOTAL_USART_PORT];

    //--//
    static BOOL Initialize( int comPort, int baudRate, int Parity, int DataBits, int StopBits, int flowValue );
    static BOOL Uninitialize( int comPort );
    static BOOL TxBufferEmpty( int comPort );
    static BOOL TxShiftRegisterEmpty( int comPort );
    static void WriteCharToTxBuffer( int comPort,  UINT8 c );
    static void TxBufferEmptyInterruptEnable( int comPort, BOOL enable );
    static BOOL TxBufferEmptyInterruptState( int comPort );
    static void RxBufferFullInterruptEnable( int comPort, BOOL enable );
    static BOOL RxBufferFullInterruptState( int comPort );
    static BOOL TxHandshakeEnabledState( int comPort );
    static void ProtectPins( int comPort, BOOL on );
    static void USART_ISR( void* Param );
    static void GetPins( int comPort,  GPIO_PIN& rxPin, GPIO_PIN& txPin,GPIO_PIN& ctsPin, GPIO_PIN& rtsPin );
    static void BaudrateBoundary( int ComPortNum, UINT32& maxBaudrateHz, UINT32& minBaudrateHz );
    static BOOL IsBaudrateSupported( int ComPortNum, UINT32 & BaudrateHz );

private:
    static void RefFlags( int ComPortNum, INT8 RefFlags, BOOL Add );
};
//
// S3C2440_USART_Driver
//////////////////////////////////////////////////////////////////////////////

#endif /* S3C2440_USART_H_ */
