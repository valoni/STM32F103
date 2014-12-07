#include <tinyhal.h>
#include "stm32f10x_conf.h"


#define IRQ_StackTop			  0
#define IRQ_Reset     		  1
#define IRQ_NMI             2
#define IRQ_HardFault       3
#define IRQ_MemManage       4
#define IRQ_BusFault        5
#define IRQ_UsageFault      6
#define IRQ_SVC             11
#define IRQ_DebugMon        12
#define IRQ_PendSV          14
#define IRQ_SysTick         15
#define IRQ_WWDG            16
#define IRQ_PVD             17
#define IRQ_TAMPER          18
#define IRQ_RTC             19
#define IRQ_FLASH           20
#define IRQ_RCC             21
#define IRQ_EXTI0           22
#define IRQ_EXTI1           23
#define IRQ_EXTI2           24   
#define IRQ_EXTI3           25     
#define IRQ_EXTI4           26     
#define IRQ_DMAChannel1     27    
#define IRQ_DMAChannel3     29   
#define IRQ_DMAChannel4     30   
#define IRQ_DMAChannel5     31   
#define IRQ_DMAChannel6     32   
#define IRQ_DMAChannel7     33   
#define IRQ_ADC             34   
#define IRQ_USB_HP_CAN_TX   35 
#define IRQ_USB_LP_CAN_RX0  36
#define IRQ_CAN_RX1         37
#define IRQ_CAN_SCE         38
#define IRQ_EXTI9_5         39
#define IRQ_TIM1_BRK        40
#define IRQ_TIM1_UP         41
#define IRQ_TIM1_TRG_COM    42
#define IRQ_TIM1_CC         43
#define IRQ_TIM2            44
#define IRQ_TIM3            45
#define IRQ_TIM4            46
#define IRQ_I2C1_EV         47
#define IRQ_I2C1_ER         48
#define IRQ_I2C2_EV         49
#define IRQ_I2C2_ER         50
#define IRQ_SPI1            51
#define IRQ_SPI2            52
#define IRQ_USART1          53
#define IRQ_USART2          54
#define IRQ_USART3          55
#define IRQ_EXTI15_10       56
#define IRQ_RTCAlarm        57
#define IRQ_USBWakeUp       58

//---------------------------------------------------------------
//Description:
//	Initialize resource
//
//---------------------------------------------------------------
BOOL INTC_Initialize();

//---------------------------------------------------------------
//Description:
//	Connect the function to the vector table
//
//Parameters:
//	irq : [in] The IRQ index
//	ISR : [in] The handler function
//	ISR_Param : [in] The ISR function parameter.
//---------------------------------------------------------------
BOOL INTC_ActivateInterrupt(UINT32 Irq_Index, HAL_CALLBACK_FPN ISR, void* ISR_Param);

//---------------------------------------------------------------
//Description:
//	Disconnect the function to the vector table
//
//Parameters:
//	irq : [in] The IRQ index
//---------------------------------------------------------------
BOOL INTC_DeactivateInterrupt(UINT32 Irq_Index);

//---------------------------------------------------------------
//Description:
//	Get the interrupt enable status
//
//Parameters:
//	irq : [in] The IRQ index
//---------------------------------------------------------------
BOOL INTC_InterruptEnableState( UINT32 Irq_Index );

//---------------------------------------------------------------
//Description:
//	Conver the IRQ index to channel
//
//Parameters:
//	dwIrq : [in] The IRQ index
//	uChannel : [out] The channel index for stm32f10x
//---------------------------------------------------------------
BOOL IrqToChannel(UINT32 dwIrq,IRQn_Type &channel);

//-----------------------------------------------------------------------
//Description:
//	Conver the IRQ index to channel
//
//Parameters:
//	dwIrq : [in] The IRQ index
//	bEnable : [in] TRUE -- Enable interrupt. FALSE -- Disable interrupt.
//------------------------------------------------------------------------
BOOL EnableIrq(UINT32 dwIrq,BOOL bEnable);

//-----------------------------------------------------------------------
//Description:
//	Call the real handler funciton
//
//Parameters:
//	dwIrq : [in] The IRQ index
//------------------------------------------------------------------------
BOOL CallRealHandler(DWORD dwIrq);


//The handler funtion
extern "C" void NMI_Handler();               
extern "C" void HardFault_Handler();         
extern "C" void MemManage_Handler();         
extern "C" void BusFault_Handler();          
extern "C" void UsageFault_Handler();     
extern "C" void SVC_Handler();               
extern "C" void DebugMon_Handler();   
extern "C" void PendSV_Handler();            
extern "C" void SysTick_Handler();  
extern "C" void WWDG_IRQHandler();           
extern "C" void PVD_IRQHandler();            
extern "C" void TAMPER_IRQHandler();         
extern "C" void RTC_IRQHandler();            
extern "C" void FLASH_IRQHandler();          
extern "C" void RCC_IRQHandler();            
extern "C" void EXTI0_IRQHandler();          
extern "C" void EXTI1_IRQHandler();          
extern "C" void EXTI2_IRQHandler();          
extern "C" void EXTI3_IRQHandler();          
extern "C" void EXTI4_IRQHandler();          
extern "C" void DMAChannel1_IRQHandler();    
extern "C" void DMAChannel2_IRQHandler();    
extern "C" void DMAChannel3_IRQHandler();    
extern "C" void DMAChannel4_IRQHandler();    
extern "C" void DMAChannel5_IRQHandler();    
extern "C" void DMAChannel6_IRQHandler();    
extern "C" void DMAChannel7_IRQHandler();    
extern "C" void ADC_IRQHandler();            
extern "C" void USB_HP_CAN_TX_IRQHandler();  
extern "C" void USB_LP_CAN_RX0_IRQHandler(); 
extern "C" void CAN_RX1_IRQHandler();        
extern "C" void CAN_SCE_IRQHandler();        
extern "C" void EXTI9_5_IRQHandler();        
extern "C" void TIM1_BRK_IRQHandler();       
extern "C" void TIM1_UP_IRQHandler();        
extern "C" void TIM1_TRG_COM_IRQHandler();   
extern "C" void TIM1_CC_IRQHandler();        
extern "C" void TIM2_IRQHandler();           
extern "C" void TIM3_IRQHandler();           
extern "C" void TIM4_IRQHandler();           
extern "C" void I2C1_EV_IRQHandler();        
extern "C" void I2C1_ER_IRQHandler();        
extern "C" void I2C2_EV_IRQHandler();        
extern "C" void I2C2_ER_IRQHandler();        
extern "C" void SPI1_IRQHandler();           
extern "C" void SPI2_IRQHandler();           
extern "C" void USART1_IRQHandler();         
extern "C" void USART2_IRQHandler();         
extern "C" void USART3_IRQHandler();         
extern "C" void EXTI15_10_IRQHandler();      
extern "C" void RTCAlarm_IRQHandler();       
extern "C" void USBWakeUp_IRQHandler(); 
