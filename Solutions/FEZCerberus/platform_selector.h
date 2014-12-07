////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Implementation for FEZCerberus board (STM32F4): Copyright (c) Oberon microsystems, Inc.
//
//  FEZCerberus specific definitions
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//代码和项目进行了调整，可以直接在NetDIY上运行
//NetDIY订购链接：http://item.taobao.com/item.htm?spm=a1z10.1.w4004-7514950083.3.Q1zDlx&id=39046877395

#ifndef _PLATFORM_FEZCerberus_SELECTOR_H_
#define _PLATFORM_FEZCerberus_SELECTOR_H_ 1

/////////////////////////////////////////////////////////
//
// processor and features
//

#if defined(PLATFORM_ARM_FEZCerberus)
#define HAL_SYSTEM_NAME                     "NetDIY"
#define PLATFORM_ARM_STM32F4  // STM32F405 cpu
//#define USB_ALLOW_CONFIGURATION_OVERRIDE  1
#define RUNTIME_MEMORY_PROFILE__extrasmall 1

//
// processor and features
//
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//
// Platform Select for shared OSHW drivers
//

#define FEZ_CERBERUS	1
    
//
// Platform Select for shared OSHW drivers
//
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//
// Solution info
//

#define GHI_VERSION_MAJOR  1      //4
#define GHI_VERSION_MINOR  0      //2
#define GHI_VERSION_BUILD  0      //5
#define GHI_VERSION_REVISION 0
#define GHIOEMSTRING "Copyright (C) GHI Electronics, LLC"

//
// Solution info
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
//#define SYSTEM_CRYSTAL_CLOCK_HZ       12000000   // 12MHz external clock
#define SYSTEM_CRYSTAL_CLOCK_HZ         25000000   // 25MHz external clock yefan
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

#define TOTAL_GPIO_PORT                 (4+1) // PA - PD 
#define INSTRUMENTATION_H_GPIO_PIN      GPIO_PIN_NONE

#define TOTAL_USART_PORT                3
#define USART_DEFAULT_PORT              COM1
#define USART_DEFAULT_BAUDRATE          115200

#define DEBUG_TEXT_PORT                 USB1
#define STDIO                           USB1
#define DEBUGGER_PORT                   USB1
#define MESSAGING_PORT                  USB1

#define TOTAL_USB_CONTROLLER            1
#define USB_MAX_QUEUES                  4  // 4 endpoints (EP0 + 3)

#define TOTAL_SOCK_PORT                 0


// System Timer Configuration
#define STM32F4_32B_TIMER 5
#define STM32F4_16B_TIMER 12

// Pin Configuration
#define STM32F4_ADC 1       //PA7 PA6 PA5 PA3 PB0 PB1
#define STM32F4_AD_CHANNELS {7, 6, 5, 3, 8, 9} 

//                        PC9 PA8 PB9 PB8 PC8 PC7 PC6                    
#define STM32F4_PWM_TIMER {   8,   1,   4,   4,   8,   8,   8}
#define STM32F4_PWM_CHNL  {   4,   1,   4,   3,   3,   2,   1}
#define STM32F4_PWM_PINS  {0x29,0x08,0x19,0x18,0x28,0x27,0x26}

#define STM32F4_SPI_SCLK_PINS {0x13} // PB3
#define STM32F4_SPI_MISO_PINS {0x14} // PB4
#define STM32F4_SPI_MOSI_PINS {0x15} // PB5

#define STM32F4_I2C_PORT     1
#define STM32F4_I2C_SCL_PIN  0x16 // PB6
#define STM32F4_I2C_SDA_PIN  0x17 // PB7

#define STM32F4_UART_RXD_PINS {0x0A} 
#define STM32F4_UART_TXD_PINS {0x09}
#define STM32F4_UART_CTS_PINS {}
#define STM32F4_UART_RTS_PINS {}

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

#endif // PLATFORM_ARM_FEZCerberus
//
// drivers
/////////////////////////////////////////////////////////

#endif // _PLATFORM_FEZCerberus_SELECTOR_H_
