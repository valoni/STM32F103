
;*****************************************************************************

; Export the handle function

	EXPORT  ARM_Vectors
	EXPORT  ARM_Vectors_End

	
 
	IMPORT     StackTop
	IMPORT     EntryPoint
	IMPORT     NMI_Handler              
	IMPORT     HardFault_Handler        
	IMPORT     MemManage_Handler        
	IMPORT     BusFault_Handler         
	IMPORT     UsageFault_Handler       
	IMPORT     SVC_Handler              
	IMPORT     DebugMon_Handler         
	IMPORT     PendSV_Handler           
	IMPORT     SysTick_Handler          
	IMPORT     WWDG_IRQHandler          
	IMPORT     PVD_IRQHandler           
	IMPORT     TAMPER_IRQHandler        
	IMPORT     RTC_IRQHandler           
	IMPORT     FLASH_IRQHandler         
	IMPORT     RCC_IRQHandler           
	IMPORT     EXTI0_IRQHandler         
	IMPORT     EXTI1_IRQHandler         
	IMPORT     EXTI2_IRQHandler         
	IMPORT     EXTI3_IRQHandler         
	IMPORT     EXTI4_IRQHandler         
	IMPORT     DMAChannel1_IRQHandler   
	IMPORT     DMAChannel2_IRQHandler   
	IMPORT     DMAChannel3_IRQHandler   
	IMPORT     DMAChannel4_IRQHandler   
	IMPORT     DMAChannel5_IRQHandler   
	IMPORT     DMAChannel6_IRQHandler   
	IMPORT     DMAChannel7_IRQHandler   
	IMPORT     ADC_IRQHandler           
	IMPORT     USB_HP_CAN_TX_IRQHandler 
	IMPORT     USB_LP_CAN_RX0_IRQHandler
	IMPORT     CAN_RX1_IRQHandler       
	IMPORT     CAN_SCE_IRQHandler       
	IMPORT     EXTI9_5_IRQHandler       
	IMPORT     TIM1_BRK_IRQHandler      
	IMPORT     TIM1_UP_IRQHandler       
	IMPORT     TIM1_TRG_COM_IRQHandler  
	IMPORT     TIM1_CC_IRQHandler       
	IMPORT     TIM2_IRQHandler          
	IMPORT     TIM3_IRQHandler          
	IMPORT     TIM4_IRQHandler          
	IMPORT     I2C1_EV_IRQHandler       
	IMPORT     I2C1_ER_IRQHandler       
	IMPORT     I2C2_EV_IRQHandler       
	IMPORT     I2C2_ER_IRQHandler       
	IMPORT     SPI1_IRQHandler          
	IMPORT     SPI2_IRQHandler          
	IMPORT     USART1_IRQHandler        
	IMPORT     USART2_IRQHandler        
	IMPORT     USART3_IRQHandler        
	IMPORT     EXTI15_10_IRQHandler     
	IMPORT     RTCAlarm_IRQHandler      
	IMPORT     USBWakeUp_IRQHandler     
;*****************************************************************************
 
	AREA |.text|, CODE, READONLY
 
;Vector list

ARM_Vectors
					      DCD     StackTop              ; Top of Stack
                DCD     EntryPoint             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler           ; Window Watchdog
                DCD     PVD_IRQHandler            ; PVD through EXTI Line detect
                DCD     TAMPER_IRQHandler         ; Tamper
                DCD     RTC_IRQHandler            ; RTC
                DCD     FLASH_IRQHandler          ; Flash
                DCD     RCC_IRQHandler            ; RCC
                DCD     EXTI0_IRQHandler          ; EXTI Line 0
                DCD     EXTI1_IRQHandler          ; EXTI Line 1
                DCD     EXTI2_IRQHandler          ; EXTI Line 2
                DCD     EXTI3_IRQHandler          ; EXTI Line 3
                DCD     EXTI4_IRQHandler          ; EXTI Line 4
                DCD     DMAChannel1_IRQHandler    ; DMA Channel 1
                DCD     DMAChannel2_IRQHandler    ; DMA Channel 2
                DCD     DMAChannel3_IRQHandler    ; DMA Channel 3
                DCD     DMAChannel4_IRQHandler    ; DMA Channel 4
                DCD     DMAChannel5_IRQHandler    ; DMA Channel 5
                DCD     DMAChannel6_IRQHandler    ; DMA Channel 6
                DCD     DMAChannel7_IRQHandler    ; DMA Channel 7
                DCD     ADC_IRQHandler            ; ADC
                DCD     USB_HP_CAN_TX_IRQHandler  ; USB High Priority or CAN TX
                DCD     USB_LP_CAN_RX0_IRQHandler ; USB Low  Priority or CAN RX0
                DCD     CAN_RX1_IRQHandler        ; CAN RX1
                DCD     CAN_SCE_IRQHandler        ; CAN SCE
                DCD     EXTI9_5_IRQHandler        ; EXTI Line 9..5
                DCD     TIM1_BRK_IRQHandler       ; TIM1 Break
                DCD     TIM1_UP_IRQHandler        ; TIM1 Update
                DCD     TIM1_TRG_COM_IRQHandler   ; TIM1 Trigger and Commutation
                DCD     TIM1_CC_IRQHandler        ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler           ; TIM2
                DCD     TIM3_IRQHandler           ; TIM3
                DCD     TIM4_IRQHandler           ; TIM4
                DCD     I2C1_EV_IRQHandler        ; I2C1 Event
                DCD     I2C1_ER_IRQHandler        ; I2C1 Error
                DCD     I2C2_EV_IRQHandler        ; I2C2 Event
                DCD     I2C2_ER_IRQHandler        ; I2C2 Error
                DCD     SPI1_IRQHandler           ; SPI1
                DCD     SPI2_IRQHandler           ; SPI2
                DCD     USART1_IRQHandler         ; USART1
                DCD     USART2_IRQHandler         ; USART2
                DCD     USART3_IRQHandler         ; USART3
                DCD     EXTI15_10_IRQHandler      ; EXTI Line 15..10
                DCD     RTCAlarm_IRQHandler       ; RTC Alarm through EXTI Line
                DCD     USBWakeUp_IRQHandler      ; USB Wakeup from suspend
ARM_Vectors_End


;*****************************************************************************



	END