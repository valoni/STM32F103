#include "device.h"
#include "usb_config.h"
#include "intr.h"
#include "STM32F10x_usb.h"


void Device_Init()
{	
  // CNTR_PWDN = 0 
  _SetCNTR(CNTR_FRES);

  // CNTR_FRES = 0 
  _SetCNTR(0);
    
  //USB interrupts initialization
  
  //clear pending interrupts
  _SetISTR(0);           
    
  //set interrupts mask
  _SetCNTR(IMR_MSK);  

}


void Device_Reset()
{
	//Set device as not configured 
  SetBTABLE(BTABLE_ADDRESS);

  //Initialize Endpoint 0 
  Clear_Status_Out(ENDP0);
  SetEPType(ENDP0, EP_CONTROL);
  SetEPTxStatus(ENDP0, EP_TX_STALL);
  SetEPTxAddr(ENDP0, ENDP0_TXADDR);  
  SetEPRxAddr(ENDP0, ENDP0_RXADDR);
  SetEPRxCount(ENDP0, MAX_PACKET_SIZE);
  SetEPRxValid(ENDP0);
 
   //Initialize Endpoint 1   
  Clear_Status_Out(ENDP1);
  SetEPType(ENDP1, EP_BULK);
  SetEPTxStatus(ENDP1, EP_TX_NAK);
  SetEPTxAddr(ENDP1, ENDP1_TXADDR);
  SetEPRxStatus(ENDP1, EP_RX_DIS);
  //SetEPRxAddr(ENDP1, ENDP1_RXADDR);
  //SetEPRxCount(ENDP1, MAX_PACKET_SIZE);
  //SetEPRxValid(ENDP1);
  
  //Initialize Endpoint 2   
  Clear_Status_Out(ENDP2);
  SetEPType(ENDP2, EP_BULK);
  SetEPTxStatus(ENDP2, EP_TX_DIS);
  //SetEPTxAddr(ENDP2, ENDP2_TXADDR);
  SetEPRxStatus(ENDP2, EP_RX_VALID);
  SetEPRxAddr(ENDP2, ENDP2_RXADDR);
  SetEPRxCount(ENDP2, MAX_PACKET_SIZE);
  SetEPRxValid(ENDP2);
  
  //Set this device to response on default address 
  SetDeviceAddress(0);
}



void Device_Cable_Config (FunctionalState NewState)
{ 
  if (NewState != DISABLE)
  {
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
  }
  else
  {
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
  }
}


void Device_Cable_Initialize ()
{
	//Set the GPIO registry value before the GPIO function begin to work,
	//or it would be detected by host after intializing GPIO,
	//and it may take wrong while something wouldn't finish intializing,
	//and then you could remove the comment to try again
	//Device_Cable_Config(DISABLE);
	
	// PB.05 used as USB pull-up in D+
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
}