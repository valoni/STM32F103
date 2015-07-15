////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _PLATFORM_S3C2416_EK_SELECTOR_H_
#define _PLATFORM_S3C2416_EK_SELECTOR_H_ 1

/////////////////////////////////////////////////////////
//
// processor and features
//

#if defined(PLATFORM_ARM_S3C2416)
#define HAL_SYSTEM_NAME                 "SMART_S3C2416"
#define PLATFORM_ARM_S3C2416            1
    
//
// processor and features
//
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//
// constants, measured main clock = 18434048
//

#define PLATFORM_DEPENDENT__UPDATE_SIGNATURE_SIZE 256

// system cycle clock hz = main clock (18434048) * (MULA + 1) (1085) / DIVA (100)
#define SYSTME_CRYSTAL_CLOCK             12000000//晶振频率12M
#define SYSTEM_CYCLE_CLOCK_HZ           600000000//600M  
#define SYSTEM_PERIPHERAL_CLOCK_HZ       75000000//PLK为75M
#define SLOW_CLOCKS_SHIFT               6

#define SYSTEM_CLOCK_HZ                 3125147
#define CLOCK_COMMON_FACTOR             8000
#define SLOW_CLOCKS_PER_SECOND          32768
#define SLOW_CLOCKS_TEN_MHZ_GCD         128
#define SLOW_CLOCKS_MILLISECOND_GCD     8

#define SDRAM_MEMORY_Base               0x30000000
#define SDRAM_MEMORY_Size               (64*1024*1024)//64M 内存调试分两部分

#define SRAM_MEMORY_Base                0x00000000
#define SRAM_MEMORY_Size                (8*1024)

#define FLASH_MEMORY_Base   0x32000000
#define FLASH_MEMORY_Size   0x02000000
#define SRAM1_MEMORY_Base   0x30000000
#define SRAM1_MEMORY_Size   0x02000000

#define TXPROTECTRESISTOR               RESISTOR_DISABLED
#define RXPROTECTRESISTOR               RESISTOR_DISABLED
#define CTSPROTECTRESISTOR              RESISTOR_DISABLED
#define RTSPROTECTRESISTOR              RESISTOR_DISABLED

#define INSTRUMENTATION_H_GPIO_PIN      GPIO_PIN_NONE

#define DEBUG_TEXT_PORT    COM1
#define STDIO              COM1
#define DEBUGGER_PORT      COM1
#define MESSAGING_PORT     COM1

#define DRIVER_PAL_BUTTON_MAPPING                                           \
    { GPIO_PIN_NONE, BUTTON_NONE },  \
    { GPIO_PIN_NONE, BUTTON_NONE },  \
    { GPIO_PIN_NONE, BUTTON_NONE },  \
    { GPIO_PIN_NONE, BUTTON_NONE },  \
    { GPIO_PIN_NONE, BUTTON_NONE },  \
    { GPIO_PIN_NONE, BUTTON_NONE }, 


#define LCD_BIT_PIX 4
#define LCD_RGB_CONVERTION  1


//
// constants
/////////////////////////////////////////////////////////

// Max GPIO number 
#define S3C2416_MAX_GPIO       384

// Max GPIO PORT number 
#define S3C2416_MAX_PORT     12

/////////////////////////////////////////////////////////
//
// macros
//

#define GLOBAL_LOCK(x)             SmartPtr_IRQ x
#define DISABLE_INTERRUPTS()       SmartPtr_IRQ::ForceDisabled()
#define ENABLE_INTERRUPTS()        SmartPtr_IRQ::ForceEnabled()
#define INTERRUPTS_ENABLED_STATE() SmartPtr_IRQ::GetState()
#define GLOBAL_LOCK_SOCKETS(x)     SmartPtr_IRQ x

#if defined(_DEBUG)
#define ASSERT_IRQ_MUST_BE_OFF()   ASSERT(!SmartPtr_IRQ::GetState())
#define ASSERT_IRQ_MUST_BE_ON()    ASSERT( SmartPtr_IRQ::GetState())
#else
#define ASSERT_IRQ_MUST_BE_OFF()
#define ASSERT_IRQ_MUST_BE_ON()
#endif


//
// macros
//
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//
// global functions
//

//
// global functions
//
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// communicaiton facilities
//

// Port definitions
#define TOTAL_USART_PORT       4
#define TOTAL_USB_CONTROLLER   1
#define USB1                   ConvertCOM_UsbHandle(0)

#define TOTAL_SOCK_PORT        0

#define TOTAL_DEBUG_PORT       1
#define COM_DEBUG              ConvertCOM_DebugHandle(0)

#define COM_MESSAGING          ConvertCOM_MessagingHandle(0)

#define USART_TX_IRQ_INDEX(x)       ( (x) ? 0 : 0 )     /* TODO set right indexes */
#define USART_DEFAULT_PORT          COM1
#define USART_DEFAULT_BAUDRATE      115200

#define USB_IRQ_INDEX               0  // TODO set right index


#define PLATFORM_DEPENDENT_TX_USART_BUFFER_SIZE    2*1024  // there is one TX for each usart port
#define PLATFORM_DEPENDENT_RX_USART_BUFFER_SIZE    2*1024  // there is one RX for each usart port
#define PLATFORM_DEPENDENT_USB_QUEUE_PACKET_COUNT  32    // there is one queue for each pipe of each endpoint and the size of a single packet is sizeof(USB_PACKET64) == 68 bytes
//
// communicaiton facilities
/////////////////////////////////////////////////////////


// These are configuration for FATFS, uncomment if non-default values are needed
//#define PLATFORM_DEPENDENT_FATFS_SECTORCACHE_MAXSIZE  8
//#define PLATFORM_DEPENDENT_FATFS_SECTORCACHE_LINESIZE 2048
//#define PLATFORM_DEPENDENT_FATFS_MAX_OPEN_HANDLES     8
//#define PLATFORM_DEPENDENT_FATFS_MAX_VOLUMES          2

#include <processor_selector.h>

#endif // PLATFORM_ARM_S3C2416_EK

#endif // _PLATFORM_S3C2416_EK_SELECTOR_H_
