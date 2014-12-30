#include "intr.h"
#include <..\pal\com\usb\USB.h>
#include "usb_config.h"
#include "STM32F10x_usb.h"
#include "USB_Adapter.h"
#include "device.h"

//----------------------------------------------------------
//Global variable
UINT8 g_PreviousDeviceState = 0;
UINT8 g_ControlPacketBuffer[MAX_EP0_SIZE] = {0};
BOOL g_bFirstDescriptorPacket = FALSE;
DEVICE_INFO g_DeviceInfo = {0};
BOOL g_bTxRunning[MAX_ENDPOINT] = {0};
BOOL g_bTxNeedZLPS[MAX_ENDPOINT] = {0};
//----------------------------------------------------------

void USBInterruptHandler(void *pParam)
{	
	// ISTR register last read value 
	u16 wIstr = _GetISTR();
		
  if (wIstr & ISTR_RESET)
  {    
    ResetEvent();
  }

  if (wIstr & ISTR_WKUP)
  {
    ResumeEvent();
  }

  if (wIstr & ISTR_SUSP)
  {
    SuspendEvent();
  }


	if (wIstr & ISTR_CTR)
	{
	  // servicing of the endpoint correct transfer interrupt 
	  // clear of the CTR flag into the sub 
	  //CTR_LP();
	  EndpointHandler();	  
	}
	
	
}

void ResetEvent()
{

	_SetISTR((u16)CLR_RESET);
  Device_Reset();
  
  //clear all flags
  USB_ClearEvent( 0, USB_EVENT_ALL);
  
  //Reset the flag
  for(int i = 0; i < MAX_ENDPOINT; i ++)
  {
  	g_bTxRunning[i] = FALSE;
  	g_bTxNeedZLPS[i] = FALSE;
  }
    
  USB_CONTROLLER_STATE *pState = CPU_USB_GetState(DEFAULT_CONTROLLER);
  pState->DeviceState        = USB_DEVICE_STATE_DEFAULT;
  pState->Address            = 0;
  USB_StateCallback( pState );
}

void ResumeEvent()
{
	_SetISTR((u16)CLR_WKUP);
	
	USB_CONTROLLER_STATE *pState = CPU_USB_GetState(DEFAULT_CONTROLLER);
	
	//Restore the last value
	pState->DeviceState = g_PreviousDeviceState;
	USB_StateCallback( pState );
}

void SuspendEvent()
{   
	//clear of the ISTR bit must be done after setting of CNTR_FSUSP 
	_SetISTR((u16)CLR_SUSP);
	
	
	USB_CONTROLLER_STATE *pState = CPU_USB_GetState(DEFAULT_CONTROLLER);
	
	//Store the current state
	g_PreviousDeviceState = pState->DeviceState;
	
	pState->DeviceState = USB_DEVICE_STATE_SUSPENDED;
  USB_StateCallback( pState );
}

void EndpointHandler()
{

	USB_CONTROLLER_STATE *pState = CPU_USB_GetState(DEFAULT_CONTROLLER);
	
	__IO uint16_t wEPVal = 0;
	u16 wIstr = 0;
	
  //stay in loop while pending ints
  while (((wIstr = _GetISTR()) & ISTR_CTR) != 0)
  {
    //extract highest priority endpoint number
    uint8_t eptIndex = (uint8_t)(wIstr & ISTR_EP_ID);
        
    if (eptIndex == 0)
    {
    	//Decode and service control endpoint interrupt
    	
    	//Store the result for control packet
    	static UINT8 s_ControlResult = 0;
    	
    	//Set RX & TX status to NAK
	    _SetEPRxTxStatus(ENDP0,EP_RX_NAK,EP_TX_NAK);
	    
	    //DIR bit = origin of the interrupt
      if ((wIstr & ISTR_DIR) == 0)
      {	
      	//DIR = 0      => IN  int      
      		
      	//If DIR bit=0, CTR_TX bit is set in the USB_EPnR register related to the interrupting endpoint. 
				//The interrupting transaction is of IN type (data transmitted by the USB peripheral to the host PC).				
				
				//DIR = 0 implies that (EP_CTR_TX = 1) always,so clear it.
				_ClearEP_CTR_TX(ENDP0);
				
				if(s_ControlResult == USB_STATE_ADDRESS)
				{
					//Get the device information
					DEVICE_INFO &devInfo = GetDeviceInfo();
									
					//To check the USB request
					if(devInfo.USBbRequest == SET_ADDRESS)
					{										
						//Set the address
						SetDeviceAddress(devInfo.USBwValue0);
					}					
				}
				else if(s_ControlResult == USB_STATE_DATA)
				{
					//If you not set endpoint status here,the host is waiting for responding.
	      	_SetEPRxTxStatus(ENDP0,EP_RX_VALID,EP_TX_STALL);
      	}	
	
      }
      else
      {
      	//DIR = 1 & CTR_RX       => SETUP or OUT int
        //DIR = 1 & (CTR_TX | CTR_RX) => 2 int pending
        
      	//If DIR bit=1, CTR_RX bit or both CTR_TX/CTR_RX are set in the USB_EPnR register 
				//related to the interrupting endpoint. The interrupting transaction is of OUT type (data 
				//received by the USB peripheral from the host PC) or two pending transactions are waiting to be processed.
				
				
				//Get the endpoint value
				wEPVal = _GetENDPOINT(ENDP0);
        
        if ((wEPVal &EP_SETUP) != 0)
        {        	        	
        	//SETUP bit kept frozen while CTR_RX = 1
          _ClearEP_CTR_RX(ENDP0);          
             
          //Get the received packet data to buffer
          DWORD dwLen = USB_SIL_Read(EP0_OUT,g_ControlPacketBuffer);
          pState->Data = g_ControlPacketBuffer;
          pState->DataSize = dwLen;
          
         
          // special handling for the very first SETUP command - Getdescriptor[DeviceType], the host looks for 8 bytes data only
          USB_SETUP_PACKET* pSetup= (USB_SETUP_PACKET* )& g_ControlPacketBuffer[0];
          if((pSetup->bRequest == USB_GET_DESCRIPTOR) && (((pSetup->wValue & 0xFF00) >> 8) == USB_DEVICE_DESCRIPTOR_TYPE) && (pSetup->wLength != 0x12))
          {
          	g_bFirstDescriptorPacket = TRUE;
        	}
          else
          {
            g_bFirstDescriptorPacket = FALSE;
          }

					//Send it to the upper layer
          UINT8 result = USB_ControlCallback(pState);
          s_ControlResult = result;
          
          //lcd_printf("result:%d\r\n",result);
                               
          switch(result)
          {
              case USB_STATE_DATA:
              //setup packet was handled and the upper layer has data to send
                  break;

              case USB_STATE_ADDRESS:
              {              	
              		//Upper layer needs us to change the address and address stage handles in hardware           		
              		
                  break;                  
							}
              case USB_STATE_DONE:
                  pState->DataCallback = NULL;
                  break;

              case USB_STATE_STALL:
              // since the setup command all handled in the hardware, should not have this state
              //
              // setup packet failed to process successfully
              // set stall condition on the default control
              // endpoint
              //
                  break;

              case USB_STATE_STATUS:
              // handle by hardware
                  break;

              case USB_STATE_CONFIGURATION:
              {
									//USB spec 9.4.5 SET_CONFIGURATION resets halt conditions, resets toggle bits     		
                  break;
							}
              case USB_STATE_REMOTE_WAKEUP:
		              // It is not using currently as the device side won't go into SUSPEND mode unless
		              // the PC is purposely to select it to SUSPEND, as there is always SOF in the bus
		              // to keeping the device from SUSPEND.
                  break;

              default:
                  ASSERT(0);
                  break;
              		//the status change is only seen and taken care in hardware
          }
          
          if(result != USB_STATE_STALL)
          {
              SendControlData();

              // If port is now configured, output any queued data
              if( result == USB_STATE_CONFIGURATION )
              {
                  for( int ep = 1; ep < MAX_ENDPOINT; ep++ )
                  {                  	
                      if( pState->Queues[ep] && pState->IsTxQueue[ep] )
                      {
                          CPU_USB_StartOutput( pState, ep );
                      }
                  }                 
              }
          }
     
          return;
        }
        else if ((wEPVal & EP_CTR_RX) != 0)
        {
        	//Clear pending
          _ClearEP_CTR_RX(ENDP0);                
          return;
        }
      }
    }
    else
    {    	
    	// Decode and service non control endpoints interrupt
    	
    	//lcd_printf("The endpoint is %d !\r\n",eptIndex);

      //process related endpoint register
      wEPVal = _GetENDPOINT(eptIndex);
      
      // OUT packet received
      if ((wEPVal & EP_CTR_RX) != 0)
      {      	
        //clear int flag 
        _ClearEP_CTR_RX(eptIndex);

        //call OUT service function 
        
				BOOL          DisableRx = FALSE;
				USB_PACKET64* Packet64 = USB_RxEnqueue( pState, eptIndex, DisableRx );
				
				if(Packet64 != NULL)
				{
					uint8_t u8EptOutAddr = 0;
					if(ConvertToEndpointOutAddress(eptIndex,u8EptOutAddr) != FALSE)
					{
						//Get the received packet data to buffer
	        	Packet64->Size = USB_SIL_Read(u8EptOutAddr,Packet64->Buffer);						
					}
					
				}
				else
				{
				    //flow control should absolutely protect us from ever getting here, so if we do, it is a bug
				    ASSERT(0);
				}
							
      } 

			// IN packet sent
      if ((wEPVal & EP_CTR_TX) != 0)
      {
        // clear int flag
        _ClearEP_CTR_TX(eptIndex);

        //call IN service function 
        TxPacket( pState, eptIndex );
      }
    }
   
   }
}



void SendControlData()
{
	USB_CONTROLLER_STATE *pState = CPU_USB_GetState(DEFAULT_CONTROLLER);
	
	if(pState->DataCallback != NULL)
	{
	    // this call can't fail 
	    pState->DataCallback( pState );
	
	    if (pState->DataSize == 0)
	    {
	        // Send zero length packet from endpoint0
					SendEmptyPacket(0);
	        
	        //State->DataCallback = NULL;
	    }
	    else
	    {
	        // Ready to send	        
	        USB_SIL_Write(EP0_IN, pState->Data, pState->DataSize);  
					SetEPTxValid(ENDP0);

	        //Special handling the USB driver set address test, cannot use the first descriptor as the ADDRESS state is handle in the hardware
	        if(g_bFirstDescriptorPacket != FALSE)
	        {
	            pState->DataCallback = NULL;
	        }
	    }
	}

	
}


BOOL SendEmptyPacket(int endpoint)
{
	uint8_t reg = 0;
	if(ConvertToEndpointRegistry(endpoint,reg) != FALSE)
	{
		_SetEPTxCount(reg, 0); 
		SetEPTxValid(reg);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

DEVICE_INFO& GetDeviceInfo()
{
	union
  {
    uint8_t* b;
    uint16_t* w;
  } pBuf;
  
  pBuf.b = PMAAddr + (uint8_t *)(_GetEPRxAddr(ENDP0) * 2); // *2 for 32 bits addr 
	
	uint16_t offset = 1;  
  
	g_DeviceInfo.USBbmRequestType = *pBuf.b++; // bmRequestType 
	g_DeviceInfo.USBbRequest = *pBuf.b++; // bRequest 
	pBuf.w += offset;  // word not accessed because of 32 bits addressing 
	g_DeviceInfo.USBwValue = ByteSwap(*pBuf.w++); // wValue 
	pBuf.w += offset;  // word not accessed because of 32 bits addressing 
	g_DeviceInfo.USBwIndex  = ByteSwap(*pBuf.w++); // wIndex 
	pBuf.w += offset;  // word not accessed because of 32 bits addressing 
	g_DeviceInfo.USBwLength = *pBuf.w; // wLength 
	
	return g_DeviceInfo;

}

BOOL TxPacket( USB_CONTROLLER_STATE* State, int endpoint )
{
	GLOBAL_LOCK(irq);
	
	// transmit a packet on UsbPortNum, if there are no more packets to transmit, then die
	USB_PACKET64* Packet64;

	while(TRUE)
	{
		Packet64 = USB_TxDequeue( State, endpoint, TRUE );

		if(Packet64 == NULL || Packet64->Size > 0)
		{
			break;
		}
	}
	
	if(Packet64 != NULL)
	{
		//Convert to the library value used
		uint8_t u8EptInAddr = 0;
		if(ConvertToEndpointInAddress(endpoint,u8EptInAddr) == FALSE)
		{
			return FALSE;
		}
		
		uint8_t u8EptReg = 0;
		if(ConvertToEndpointRegistry(endpoint,u8EptReg) == FALSE)
		{
			return FALSE;
		}
		
		//Write the data through the endpoint  
		USB_SIL_Write(u8EptInAddr, Packet64->Buffer, Packet64->Size);  
		SetEPTxValid(u8EptReg);
		
		g_bTxNeedZLPS[endpoint] = (Packet64->Size == 64);

	}
	else
	{
		// send the zero leght packet since we landed on the FIFO boundary before
    // (and we queued a zero length packet to transmit)
		if(g_bTxNeedZLPS[endpoint] != FALSE)
		{
			SendEmptyPacket(endpoint);
			g_bTxNeedZLPS[endpoint] = FALSE;
		}
		
		// no more data
    g_bTxRunning[endpoint] = FALSE;   		
	}


	return TRUE;
}

void SetDeviceAddress(uint8_t Val)
{
  //Set address in every used endpoint
  for (int i = 0; i < MAX_ENDPOINT; i++)
  {
    _SetEPAddress((uint8_t)i, (uint8_t)i);
  }
  
  //Set device address and enable function
  _SetDADDR(Val | DADDR_EF); 

}