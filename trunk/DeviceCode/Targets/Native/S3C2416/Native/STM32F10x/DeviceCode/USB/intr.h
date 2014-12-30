#pragma once

#include <tinyhal.h>
#include "stm32f10x.h"
#include ".\library\library.h"

//--------------------------------------------------------
//Description:
//	The function for USB interrupt handling
//--------------------------------------------------------
void USBInterruptHandler(void *pParam);

//--------------------------------------------------------
//Description:
//	Reset
//--------------------------------------------------------
void ResetEvent();

//--------------------------------------------------------
//Description:
//	Resume
//--------------------------------------------------------
void ResumeEvent();

//--------------------------------------------------------
//Description:
//	Suspend
//--------------------------------------------------------
void SuspendEvent();

//--------------------------------------------------------
//Description:
//	The ISR is for endpoint
//--------------------------------------------------------
void EndpointHandler();

//--------------------------------------------------------
//Description:
//	Send the control data
//--------------------------------------------------------
void SendControlData();

//--------------------------------------------------------
//Description:
//	Send the empty packet from the endpoint
//--------------------------------------------------------
BOOL SendEmptyPacket(int endpoint);

//--------------------------------------------------------
//Description:
//	Get the device information from the registry
//--------------------------------------------------------
DEVICE_INFO& GetDeviceInfo();

//--------------------------------------------------------
//Description:
//	Transmit the packet
//--------------------------------------------------------
BOOL TxPacket( USB_CONTROLLER_STATE* State, int endpoint );

//--------------------------------------------------------
//Description:
//	Set the device and all the used Endpoints addresses
//--------------------------------------------------------
void SetDeviceAddress(uint8_t);