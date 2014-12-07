////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "STM32F10x_usb.h"
#include <tinyhal.h>
#include "INTC_Adapter.h"
#include "stm32f10x.h"
#include "intr.h"
#include "..\..\..\..\..\..\DeviceCode\pal\COM\usb\usb.h"
#include "USB_Adapter.h"
#include "device.h"
#include ".\library\library.h"

//----------------------------------------------------------------------------------------------------
//Global variable
USB_CONTROLLER_STATE g_UsbControllerState[1]; // Only 1 USB Client Controller for this device
Hal_Queue_KnownSize<USB_PACKET64,USB_QUEUE_PACKET_COUNT> g_QueueBuffers[MAX_ENDPOINT - 1];
UINT16 g_EndpointStatus[MAX_ENDPOINT];

//----------------------------------------------------------------------------------------------------
//External variable
extern BOOL g_bTxRunning[MAX_ENDPOINT]; //Define in intr.cpp


//----------------------------------------------------------------------------------------------------
//Function front declare
HRESULT InitializeEndpoint(int Controller);
BOOL InitializeInterrupt();
//----------------------------------------------------------

USB_CONTROLLER_STATE *CPU_USB_GetState( int Controller )
{
	if(Controller != DEFAULT_CONTROLLER)
	{
		return NULL;
	}
	else
	{
		return &g_UsbControllerState[0];
	}
}

HRESULT CPU_USB_Initialize( int Controller )
{  
	GLOBAL_LOCK(irq);
	
	//Initialize the USB cable
	Device_Cable_Initialize();
	
	// Enable the interrupt
  CPU_INTC_ActivateInterrupt( IRQ_USB_LP_CAN_RX0, USBInterruptHandler, NULL);
    
  
  //Select USBCLK source
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

  //Enable USB clock 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
  
  //Initialize the endpoint
  InitializeEndpoint(Controller);
  
  //The function would initialize the pointer variable in the USB driver library
  //and call device initialize.
  Device_Init();
  
  //Initialize the interrupt
  InitializeInterrupt();
  
  //Enable the host to detect the device inserted
  //CPU_USB_ProtectPins(DEFAULT_CONTROLLER,FALSE);
  
	return S_OK;
}

HRESULT CPU_USB_Uninitialize( int Controller )
{
	GLOBAL_LOCK(irq);
	return S_OK;
}

BOOL CPU_USB_StartOutput( USB_CONTROLLER_STATE* State, int endpoint )
{	
	GLOBAL_LOCK(irq);
		
	// If endpoint is not an output
	if( State->Queues[endpoint] == NULL || !State->IsTxQueue[endpoint] )
	{
	    return FALSE;
	}
	
	//if the halt feature for this endpoint is set, then just clear all the characters
	USB_CONTROLLER_STATE *pState = CPU_USB_GetState(DEFAULT_CONTROLLER);
	if(pState != NULL && pState->EndpointStatus[endpoint] & USB_STATUS_ENDPOINT_HALT)
	{
			//Clear Tx queue
			//it is much faster to just re-initialize the queue and it does the same thing
	    State->Queues[endpoint]->Initialize();
	    
	    return TRUE;
	}
	
	
	//If TxRunning, interrupts will drain the queue
	if(g_bTxRunning[endpoint] == FALSE)
	{
	    g_bTxRunning[endpoint] = TRUE;
	
	    TxPacket( State, endpoint );
	}
	else if(irq.WasDisabled()) // We should not call EP_TxISR after calling TxPacket becuase it can cause a TX FIFO overflow error.
	{
	    EndpointHandler();
	}
	
	return TRUE;
}

BOOL CPU_USB_RxEnable( USB_CONTROLLER_STATE* State, int endpoint )
{
  GLOBAL_LOCK(irq);
  
  uint8_t eptReg = 0;
	if(ConvertToEndpointRegistry(endpoint,eptReg) == FALSE)
	{
		//Go to the next loop
		return FALSE;
	}
	
  SetEPRxValid(eptReg);
  
  //If you delete the loop,sometimes the MFDeploy tools would crash by ping operate.But I don't know why.
	for(int i = 100000; i > 0; i --);
  
	return TRUE;
}

BOOL CPU_USB_GetInterruptState()
{
	GLOBAL_LOCK(irq);
	return (_GetISTR() != 0);
}

BOOL CPU_USB_ProtectPins( int Controller, BOOL On )
{	
	GLOBAL_LOCK(irq);
	
	if(On == FALSE)
	{
		//Setting On to false enables the pins, thus enabling the host to detect the USB client.
		//As soon as the USB client is detected, the enumeration process begins.
		Device_Cable_Config(ENABLE);
	}
	else
	{
		//Setting the On parameter to true detaches the USB module from the host. 
		//This protects the USB pins by stopping all USB communications
		Device_Cable_Config(DISABLE);
	}
	
	return TRUE;
}


//--------------------------------------------------------------
//Description:
//	Initialize the endpoint
//--------------------------------------------------------------
HRESULT InitializeEndpoint(int Controller)
{
	UINT8 endpointNum = 0;
	USB_CONTROLLER_STATE     &State = g_UsbControllerState[Controller];
	const USB_ENDPOINT_DESCRIPTOR  *ep    = NULL;
	const USB_INTERFACE_DESCRIPTOR *itfc  = NULL;
	
	// For all endpoints in the USB Configuration list
	//logicalEndpoint = 1;
  while( USB_NextEndpoint( &State, ep, itfc) ) // && logicalEndpoint < 11 )
  {
  		//Becareful:You must write the dumy code here,or the "endpointNum = ep->bEndpointAddress & 0x7F;" source code
  		//would get the wrong result! It may be the MDK's bug.
  		//You could see the description in the article in norains's blog:
  		//http://blog.csdn.net/norains/archive/2011/04/15/6325662.aspx
  		int iDumy = 0;

      // Figure out which endpoint we are initializing
      endpointNum = ep->bEndpointAddress & 0x7F;
      
      // Check interface and endpoint numbers against hardware capability
      if( endpointNum >= MAX_ENDPOINT || itfc->bInterfaceNumber > 3 )
          return S_FALSE;
			
			/*        
      EndpointInit[logicalEndpoint].bits.EPNUM      = endpointNum;
      EndpointInit[logicalEndpoint].bits.FIFONUM    = endpointNum;
      EndpointInit[logicalEndpoint].bits.DIR        = (ep->bEndpointAddress & 0x80) ? 1 : 0;
      EndpointInit[logicalEndpoint].bits.INTERFACE  = itfc->bInterfaceNumber;
      EndpointInit[logicalEndpoint].bits.TYPE       = ep->bmAttributes & 0x03;
      EndpointInit[logicalEndpoint].bits.TRXTYP     = 3;      // Always 3 for non-control endpoints
      EndpointInit[logicalEndpoint].bits.CONFIG     = 1;      // Always only 1 configuration: #1
			*/
			
      // Set the maximum size of the endpoint hardware FIFO
      if( (ep->bmAttributes & 0x03) == USB_ENDPOINT_ATTRIBUTE_BULK )
      {
          int endpointSize = ep->wMaxPacketSize;

          // If the endpoint maximum size in the configuration list is bogus
          if( endpointSize != 8 && endpointSize != 16 && endpointSize != 32 && endpointSize != 64 )
              return S_FALSE;
              
          // If too large an endpoint size was requested
          //if( endpointSize > s_EpAttr[endpointNum].Payload )
          //    return S_FALSE;
					
					//EndpointInit[logicalEndpoint].bits.MAXPKTSIZE = endpointSize;
					
          State.MaxPacketSize[endpointNum] = endpointSize;
      }
      else
      {
          // If Isochronous or Interupt type endpoint, always use the maximum size
					//EndpointInit[logicalEndpoint].bits.MAXPKTSIZE = s_EpAttr[endpointNum].Payload;
          //State.MaxPacketSize[endpointNum] = s_EpAttr[endpointNum].Payload;
      }

      // Since endpoint 0 is only used for control, there is never a need to allocate a buffer for it
      // In fact State.Queues[0] is always NULL - it is a cheap placeholder to make the queueIndex = endpointIndex
      g_QueueBuffers[endpointNum-1].Initialize();                       // Clear queue before use
      State.Queues[endpointNum] = &g_QueueBuffers[endpointNum-1];       // Attach queue to endpoint
      
      // Enable an interrupt for the endpoint & set its direction
      if( (ep->bEndpointAddress & 0x80) ? 1 : 0 )        // If transmit endpoint
      {
          State.IsTxQueue[endpointNum] = TRUE;         
      }
      else        
      {
      		// Receive endpoint
          State.IsTxQueue[endpointNum] = FALSE;         
      }

      //udp.UDP_IER |= (AT91_UDP::UDP_EPINT0 << endpointNum);

      // Move onto the next logical endpoint
      //logicalEndpoint++;
  }


  State.EndpointStatus = &g_EndpointStatus[0];
  State.EndpointCount  = MAX_ENDPOINT;
  State.PacketSize     = MAX_PACKET_SIZE;
  State.FirstGetDescriptor = TRUE;
}

//--------------------------------------------------------------
//Description:
//	Initialize the interrupt
//--------------------------------------------------------------
BOOL InitializeInterrupt()
{
	//Enable the receive interrupts
	NVIC_InitTypeDef NVIC_InitStructure;	
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  return TRUE;
}