////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _S3C2416_H_1
#define _S3C2416_H_1 1
    
//
//  PERIPHERAL ID DEFINITIONS FOR S3C2416
//
#define S3C2416_ID_FIQ    ((unsigned int)  0) // Advanced Interrupt Controller (FIQ)
#define S3C2416_ID_SYS    ((unsigned int)  1) // System Interrupt
#define S3C2416_ID_PIOA   ((unsigned int)  2) // Parallel IO Controller A
#define S3C2416_ID_PIOB   ((unsigned int)  3) // Parallel IO Controller B
#define S3C2416_ID_PIOC   ((unsigned int)  4) // Parallel IO Controller C
#define S3C2416_ID_US0    ((unsigned int)  6) // USART 0
#define S3C2416_ID_US1    ((unsigned int)  7) // USART 1
#define S3C2416_ID_US2    ((unsigned int)  8) // USART 2
#define S3C2416_ID_MCI    ((unsigned int)  9) // Multimedia Card Interface
#define S3C2416_ID_UDP    ((unsigned int) 10) // USB Device Port
#define S3C2416_ID_TWI    ((unsigned int) 11) // Two-Wire Interface
#define S3C2416_ID_SPI0   ((unsigned int) 12) // Serial Peripheral Interface 0
#define S3C2416_ID_SPI1   ((unsigned int) 13) // Serial Peripheral Interface 1
#define S3C2416_ID_SSC0   ((unsigned int) 14) // Serial Synchronous Controller 0
#define S3C2416_ID_SSC1   ((unsigned int) 15) // Serial Synchronous Controller 1
#define S3C2416_ID_SSC2   ((unsigned int) 16) // Serial Synchronous Controller 2
#define S3C2416_ID_TC0    ((unsigned int) 17) // Timer Counter 0
#define S3C2416_ID_TC1    ((unsigned int) 18) // Timer Counter 1
#define S3C2416_ID_TC2    ((unsigned int) 19) // Timer Counter 2
#define S3C2416_ID_UHP    ((unsigned int) 20) // USB Host Port
#define S3C2416_ID_LCDC   ((unsigned int) 21) // LCD Controller
#define S3C2416_ID_IRQ0   ((unsigned int) 29) // Advanced Interrupt Controller (IRQ0)
#define S3C2416_ID_IRQ1   ((unsigned int) 30) // Advanced Interrupt Controller (IRQ1)
#define S3C2416_ID_IRQ2   ((unsigned int) 31) // Advanced Interrupt Controller (IRQ2)
#define S3C2416_ALL_INT   ((unsigned int) 0xE03FFFDF) // ALL VALID INTERRUPTS

//
// BASE ADDRESS DEFINITIONS FOR S3C2416
//
#define S3C2416_BASE_SYS          0xFFFFEA00 // (SYS) Base Address
#define S3C2416_BASE_SDRAMC       0xFFFFEA00 // (SDRAMC) Base Address
#define S3C2416_BASE_SMC          0xFFFFEC00 // (SMCTRL) Base Address
#define S3C2416_BASE_MATRIX       0xFFFFEE00 // (MATRIX) Base Address
#define S3C2416_BASE_AIC          0xFFFFF000 // (AIC) Base Address
#define S3C2416_BASE_PDC_DBGU     0xFFFFF300 // (PDC_DBGU) Base Address
#define S3C2416_BASE_DBGU         0xFFFFF200 // (DBGU) Base Address
#define S3C2416_BASE_PIOA         0xFFFFF400 // (PIOA) Base Address
#define S3C2416_BASE_PIOB         0xFFFFF600 // (PIOB) Base Address
#define S3C2416_BASE_PIOC         0xFFFFF800 // (PIOC) Base Address
#define S3C2416_BASE_CKGR         0xFFFFFC20 // (CKGR) Base Address
#define S3C2416_BASE_PMC          0xFFFFFC00 // (PMC) Base Address
#define S3C2416_BASE_RSTC         0xFFFFFD00 // (RSTC) Base Address
    #define S3C2416_RTSC__PROCRST     0x01         // processor reset bit
    #define S3C2416_RTSC__PERRST      0x04         // Peripheral reset bit
    #define S3C2416_RTSC__EXTRST      0x08         // asserts NRST pin
    #define S3C2416_RSTC__RESET_KEY   0xA5000000   // reset key
#define S3C2416_BASE_RSTC_SR      0xFFFFFD04 
    #define S3C2416_RTSC_SR__SRCMP    (1ul < 17)   // Software Reset Command in progress
    #define S3C2416_RTSC_SR__NRSTL    (1ul < 16)   // Registers the NRST Pin Level at Master Clock (MCK)
    #define S3C2416_RTSC_SR__RSTTYP   (7ul <  8)   // Reset Type mask
    #define S3C2416_RTSC_SR__BODSTS   (1ul <  1)   // Brownout Detection Status
    #define S3C2416_RTSC_SR__URSTS    (1ul <  0)   // User Reset Status
#define S3C2416_BASE_RSTC_MR      0xFFFFFD08 
#define S3C2416_BASE_SHDWC        0xFFFFFD10 // (SHDWC) Base Address
#define S3C2416_BASE_RTTC         0xFFFFFD20 // (RTTC) Base Address
#define S3C2416_BASE_PITC         0xFFFFFD30 // (PITC) Base Address
#define S3C2416_BASE_WDTC         0xFFFFFD40 // (WDTC) Base Address
#define S3C2416_BASE_TC0          0xFFFA0000 // (TC0) Base Address
#define S3C2416_BASE_TC1          0xFFFA0040 // (TC1) Base Address
#define S3C2416_BASE_TC2          0xFFFA0080 // (TC2) Base Address
#define S3C2416_BASE_TCB0         0xFFFA0000 // (TCB0) Base Address
#define S3C2416_BASE_UDP          0xFFFA4000 // (UDP) Base Address
#define S3C2416_BASE_PDC_MCI      0xFFFA8100 // (PDC_MCI) Base Address
#define S3C2416_BASE_MCI          0xFFFA8000 // (MCI) Base Address
#define S3C2416_BASE_TWI          0xFFFAC000 // (TWI) Base Address
#define S3C2416_BASE_PDC_US0      0xFFFB0100 // (PDC_US0) Base Address
#define S3C2416_BASE_US0          0xFFFB0000 // (US0) Base Address
#define S3C2416_BASE_PDC_US1      0xFFFB4100 // (PDC_US1) Base Address
#define S3C2416_BASE_US1          0xFFFB4000 // (US1) Base Address
#define S3C2416_BASE_PDC_US2      0xFFFB8100 // (PDC_US2) Base Address
#define S3C2416_BASE_US2          0xFFFB8000 // (US2) Base Address
#define S3C2416_BASE_PDC_SSC0     0xFFFBC100 // (PDC_SSC0) Base Address
#define S3C2416_BASE_SSC0         0xFFFBC000 // (SSC0) Base Address
#define S3C2416_BASE_PDC_SSC1     0xFFFC0100 // (PDC_SSC1) Base Address
#define S3C2416_BASE_SSC1         0xFFFC0000 // (SSC1) Base Address
#define S3C2416_BASE_PDC_SSC2     0xFFFC4100 // (PDC_SSC2) Base Address
#define S3C2416_BASE_SSC2         0xFFFC4000 // (SSC2) Base Address
#define S3C2416_BASE_PDC_SPI0     0xFFFC8100 // (PDC_SPI0) Base Address
#define S3C2416_BASE_SPI0         0xFFFC8000 // (SPI0) Base Address
#define S3C2416_BASE_PDC_SPI1     0xFFFCC100 // (PDC_SPI1) Base Address
#define S3C2416_BASE_SPI1         0xFFFCC000 // (SPI1) Base Address
#define S3C2416_BASE_SHDWC        0xFFFFFD10 // (SHDWC) shutdown controller
#define S3C2416_SHDWC__SHUTDOWN_KEY   0xA5000000   // reset key
#define S3C2416_SHDWC__SHDW           0x01         // processor reset bit

#define S3C2416_BASE_UHP          0x00500000 // (UHP) Base Address
#define S3C2416_BASE_LCDC         0x00600000 // (LCDC) Base Address
#define S3C2416_BASE_LCDC_16B_TFT 0x00600000 // (LCDC_16B_TFT) Base Address

// Timer number - See S3C2416.H
#define S3C2416_MAX_TIMER      5

// Max GPIO number 
#define S3C2416_MAX_GPIO       384

// Max GPIO PORT number 
#define S3C2416_MAX_PORT     12

// Max USART Number
#define S3C2416_MAX_USART   4 

// Define the multiplexing pins USART
#define S3C2416_DRXD   S3C2416_GPIO_Driver::PA9
#define S3C2416_DTXD   S3C2416_GPIO_Driver::PA10
#define S3C2416_TXD0   S3C2416_GPIO_Driver::PC8
#define S3C2416_RXD0   S3C2416_GPIO_Driver::PC9
#define S3C2416_RTS0   S3C2416_GPIO_Driver::PC10
#define S3C2416_CTS0   S3C2416_GPIO_Driver::PC11    
#define S3C2416_TXD1   S3C2416_GPIO_Driver::PC12
#define S3C2416_RXD1   S3C2416_GPIO_Driver::PC13
#define S3C2416_TXD2   S3C2416_GPIO_Driver::PC14
#define S3C2416_RXD2   S3C2416_GPIO_Driver::PC15

// Define the multiplexing pins LCD
#define S3C2416_LCDVSYNC  S3C2416_GPIO_Driver::PB0
#define S3C2416_LCDHSYNC  S3C2416_GPIO_Driver::PB1
#define S3C2416_LCDDOTCK  S3C2416_GPIO_Driver::PB2       
#define S3C2416_LCDDEN    S3C2416_GPIO_Driver::PB3
#define S3C2416_LCDCC     S3C2416_GPIO_Driver::PB4
#define S3C2416_LCDD0     S3C2416_GPIO_Driver::PB5
#define S3C2416_LCDD1     S3C2416_GPIO_Driver::PB6
#define S3C2416_LCDD2     S3C2416_GPIO_Driver::PB7
#define S3C2416_LCDD3     S3C2416_GPIO_Driver::PB8
#define S3C2416_LCDD4     S3C2416_GPIO_Driver::PB9
#define S3C2416_LCDD5     S3C2416_GPIO_Driver::PB10
#define S3C2416_LCDD6     S3C2416_GPIO_Driver::PB11
#define S3C2416_LCDD7     S3C2416_GPIO_Driver::PB12
#define S3C2416_LCDD8     S3C2416_GPIO_Driver::PB13
#define S3C2416_LCDD9     S3C2416_GPIO_Driver::PB14
#define S3C2416_LCDD10    S3C2416_GPIO_Driver::PB15
#define S3C2416_LCDD11    S3C2416_GPIO_Driver::PB16
#define S3C2416_LCDD12    S3C2416_GPIO_Driver::PB17
#define S3C2416_LCDD13    S3C2416_GPIO_Driver::PB18
#define S3C2416_LCDD14    S3C2416_GPIO_Driver::PB19
#define S3C2416_LCDD15    S3C2416_GPIO_Driver::PB20
#define S3C2416_LCDD16    S3C2416_GPIO_Driver::PB21
#define S3C2416_LCDD17    S3C2416_GPIO_Driver::PB22
#define S3C2416_LCDD18    S3C2416_GPIO_Driver::PB23
#define S3C2416_LCDD19    S3C2416_GPIO_Driver::PB24
#define S3C2416_LCDD20    S3C2416_GPIO_Driver::PB25
#define S3C2416_LCDD21    S3C2416_GPIO_Driver::PB26
#define S3C2416_LCDD22    S3C2416_GPIO_Driver::PB27
#define S3C2416_LCDD23    S3C2416_GPIO_Driver::PB28       

//PMC
#define S3C2416_PMC_PCK         (0x1 << 0 ) /**< (PMC) Processor Clock */
#define S3C2416_PMC_UHP         (0x1 << 6 ) /**< (PMC) USB Host Port Clock */
#define S3C2416_PMC_UDP         (0x1 << 7 ) /**< (PMC) USB Device Port Clock */
#define S3C2416_PMC_PCK0        (0x1 << 8 ) /**< (PMC) Programmable Clock Output */
#define S3C2416_PMC_PCK1        (0x1 << 9 ) /**< (PMC) Programmable Clock Output */
#define S3C2416_PMC_HCK0        (0x1 << 16) /**< (PMC) AHB UHP Clock Output */
#define S3C2416_PMC_HCK1        (0x1 << 17) /**< (PMC) AHB LCDC Clock Output */

#include "../S3C2416_GPIO/S3C2416_GPIO.h"
#include "../S3C2416_SAM/S3C2416_SAM.h"
#include "../S3C2416_TIME/S3C2416_TIME.h"
#include "../S3C2416_USART/S3C2416_USART.h"
#include "../S3C2416_USB/S3C2416_USB.h"


static const UINT8 c_LCD_1[] =
{
    S3C2416_LCDHSYNC,
    S3C2416_LCDDOTCK,
    S3C2416_LCDDEN,
    S3C2416_LCDCC,
    S3C2416_LCDD2,
    S3C2416_LCDD3,
    S3C2416_LCDD4,
    S3C2416_LCDD5,
    S3C2416_LCDD6,
    S3C2416_LCDD7,
    S3C2416_LCDD10,
    S3C2416_LCDD11,
    S3C2416_LCDD12,
    S3C2416_LCDD13,
    S3C2416_LCDD14,
    S3C2416_LCDD15,
};

static const UINT8 c_LCD_2[] =
{  
    S3C2416_LCDD18,
    S3C2416_LCDD19,
    S3C2416_LCDD20,
    S3C2416_LCDD21,
    S3C2416_LCDD22,
    S3C2416_LCDD23,
};

// Define the multiplexing pins NAND Flash
#define S3C2416_NAND_RE    S3C2416_GPIO_Driver::PC0
#define S3C2416_NAND_WE    S3C2416_GPIO_Driver::PC1

#define S3C2416_MAX_SPI   2
#define S3C2416_SPI_CS    4

// Define the multiplexing pins SPI0
#define S3C2416_SPI0_MISO  S3C2416_GPIO_Driver::PA0
#define S3C2416_SPI0_MOSI  S3C2416_GPIO_Driver::PA1
#define S3C2416_SPI0_SCLK  S3C2416_GPIO_Driver::PA2
#define S3C2416_SPI0_NSS   S3C2416_GPIO_Driver::PA3

// Define the multiplexing pins SPI1
#define S3C2416_SPI1_MISO  S3C2416_GPIO_Driver::PB30
#define S3C2416_SPI1_MOSI  S3C2416_GPIO_Driver::PB31
#define S3C2416_SPI1_SCLK  S3C2416_GPIO_Driver::PB29
#define S3C2416_SPI1_NSS   S3C2416_GPIO_Driver::PB28


//the selecting of CS pins could vary according to different hardware designs
#define S3C2416_SPI0_NCPS0      S3C2416_GPIO_Driver::PA3
#define S3C2416_SPI0_NCPS1      S3C2416_GPIO_Driver::PA4
#define S3C2416_SPI0_NCPS2      S3C2416_GPIO_Driver::PA5
#define S3C2416_SPI0_NCPS3      S3C2416_GPIO_Driver::PA6

// this has to at Altern B
#define S3C2416_SPI1_NCPS0      S3C2416_GPIO_Driver::PB27
#define S3C2416_SPI1_NCPS1      S3C2416_GPIO_Driver::PA24
#define S3C2416_SPI1_NCPS2      S3C2416_GPIO_Driver::PA25
#define S3C2416_SPI1_NCPS3      S3C2416_GPIO_Driver::PA26


// define the TWI (i2C) pins
#define S3C2416_TWI_SDA    S3C2416_GPIO_Driver::PA7
#define S3C2416_TWI_SCL    S3C2416_GPIO_Driver::PA8

#endif // _S3C2416_H_1

