////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Implementation for the STM3240G board (STM32F4): Copyright (c) Oberon microsystems, Inc.
//
//  STM3240G specific definitions
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _PLATFORM_STM3240G_SELECTOR_H_
#define _PLATFORM_STM3240G_SELECTOR_H_ 1

/////////////////////////////////////////////////////////
//
// processor and features
//

#if defined(PLATFORM_ARM_STM3240G)
#define HAL_SYSTEM_NAME                     "STM3240G-EVAL"

#define PLATFORM_ARM_STM32F4 // STM32F407 cpu

#define USB_ALLOW_CONFIGURATION_OVERRIDE  1


//
// processor and features
//
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//
// constants
//

// legal SYSCLK: 24, 30, 32, 36, 40, 42, 48, 54, 56, 60, 64, 72, 84, 96, 108, 120, 144, 168MHz
#define SYSTEM_CLOCK_HZ                 168000000  // 168MHz
#define SYSTEM_CYCLE_CLOCK_HZ           168000000  // 168MHz
#define SYSTEM_APB1_CLOCK_HZ            42000000   // 42MHz
#define SYSTEM_APB2_CLOCK_HZ            84000000   // 84MHz
#define SYSTEM_CRYSTAL_CLOCK_HZ         25000000   // 25MHz external clock
#define SUPPLY_VOLTAGE_MV               3300       // 3.3V supply

#define CLOCK_COMMON_FACTOR             1000000    // GCD(SYSTEM_CLOCK_HZ, 1M)

#define SLOW_CLOCKS_PER_SECOND          1000000    // 1MHz
#define SLOW_CLOCKS_TEN_MHZ_GCD         1000000    // GCD(SLOW_CLOCKS_PER_SECOND, 10M)
#define SLOW_CLOCKS_MILLISECOND_GCD     1000       // GCD(SLOW_CLOCKS_PER_SECOND, 1k)

#define FLASH_MEMORY_Base               0x08000000
#define FLASH_MEMORY_Size               0x00100000
#define SRAM1_MEMORY_Base               0x20000000
#define SRAM1_MEMORY_Size               0x00020000

#define TXPROTECTRESISTOR               RESISTOR_DISABLED
#define RXPROTECTRESISTOR               RESISTOR_DISABLED
#define CTSPROTECTRESISTOR              RESISTOR_DISABLED
#define RTSPROTECTRESISTOR              RESISTOR_DISABLED

#define TOTAL_GPIO_PORT                 9 // PA - PI
#define INSTRUMENTATION_H_GPIO_PIN      GPIO_PIN_NONE

#define TOTAL_USART_PORT                3
#define USART_DEFAULT_PORT              COM3
#define USART_DEFAULT_BAUDRATE          115200

#define DEBUG_TEXT_PORT                 COM3
#define STDIO                           COM3
#define DEBUGGER_PORT                   USB1
#define MESSAGING_PORT                  COM3

#define TOTAL_USB_CONTROLLER            1
#define USB_MAX_QUEUES                  4  // 4 endpoints (EP0 + 3)

#define TOTAL_SOCK_PORT                 0


#define DRIVER_PAL_BUTTON_MAPPING              \
    { GPIO_PIN_NONE, BUTTON_B0 }, /* Up */    \
    { GPIO_PIN_NONE, BUTTON_B1 }, /* Down */  \
    { GPIO_PIN_NONE, BUTTON_B2 }, /* Left */               \
	{ GPIO_PIN_NONE, BUTTON_B3 }, /* Right */     \
    { GPIO_PIN_NONE, BUTTON_B4 }, /* Enter */     \


// System Timer Configuration
#define STM32F4_32B_TIMER 2
#define STM32F4_16B_TIMER 3


// Pin Configuration
#define STM32F4_ADC 3
#define STM32F4_AD_CHANNELS {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}

#define STM32F4_PWM_TIMER {4,4,4,4}
#define STM32F4_PWM_CHNL  {0,1,2,3}
#define STM32F4_PWM_PINS  {60,61,62,63} // PD12-PD15

#define STM32F4_SPI_SCLK_PINS {5, 29, 19} // PA5, PB13, PB3
#define STM32F4_SPI_MISO_PINS {6, 30, 20} // PA6, PB14, PB4
#define STM32F4_SPI_MOSI_PINS {7, 31, 21} // PA7, PB15, PB5

#define STM32F4_I2C_PORT     1
#define STM32F4_I2C_SCL_PIN  22 // PB6
#define STM32F4_I2C_SDA_PIN  25 // PB9

#define STM32F4_UART_RXD_PINS {10, 54, 43} // A10, D6, C11
#define STM32F4_UART_TXD_PINS { 9, 53, 42} //  A9, D5, C10
#define STM32F4_UART_CTS_PINS {11, 51, 59} // A11, D3, D11
#define STM32F4_UART_RTS_PINS {12, 52, 60} // A12, D4, D12

//
// constants
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//
// global functions
//

//
// global functions
//
/////////////////////////////////////////////////////////

#include <processor_selector.h>

#endif // PLATFORM_ARM_STM3240G
//
// drivers
/////////////////////////////////////////////////////////

#endif // _PLATFORM_STM3240G_SELECTOR_H_
