#ifndef  __TOUCH_H
#define  __TOUCH_H
#include <tinyhal.h>
#include "..\..\..\..\DeviceCode\Targets\Native\STM32F4\DeviceCode\stm32f4xx.h"
#include "..\..\..\..\DeviceCode\Targets\Native\STM32F4\DeviceCode\sys.h"

#define TOUCH_I2C_SCL_GPIO_RCC         1<<1
#define TOUCH_I2C_SCL_GPIO             GPIOB
#define TOUCH_I2C_SCL_PIN              1<<6
#define TOUCH_I2C_SCL_AF_SOURCE        ((uint8_t)0x06)
#define TOUCH_I2C_SCL_AF_MODE          ((uint8_t)0x04) //I2C1

#define TOUCH_I2C_SDA_GPIO_RCC          1<<1
#define TOUCH_I2C_SDA_GPIO              GPIOB
#define TOUCH_I2C_SDA_PIN               1<<9
#define TOUCH_I2C_SDA_AF_SOURCE         ((uint8_t)0x09)
#define TOUCH_I2C_SDA_AF_MODE           ((uint8_t)0x04) //I2C1

#define TOUCH_I2C_INT_GPIO_RCC   1<<8
#define TOUCH_I2C_INT_GPIO       GPIOI
#define TOUCH_I2C_INT_PIN        1<<12

#define STMPE811_ADDR               0x82    
//#define IOE_2_ADDR                 0x88    
#define STMPE811_ID                0x0811
/*------------------------------------------------------------------------------
    STMPE811 device register definition
------------------------------------------------------------------------------*/
/** 
  * @brief  Identification registers  
  */ 
#define IOE_REG_CHP_ID             0x00
#define IOE_REG_ID_VER             0x02

/** 
  * @brief  General Control Registers  
  */ 
#define IOE_REG_SYS_CTRL1          0x03
#define IOE_REG_SYS_CTRL2          0x04
#define IOE_REG_SPI_CFG            0x08 

/** 
  * @brief  Interrupt Control register  
  */ 
#define IOE_REG_INT_CTRL           0x09
#define IOE_REG_INT_EN             0x0A
#define IOE_REG_INT_STA            0x0B
#define IOE_REG_GPIO_INT_EN        0x0C
#define IOE_REG_GPIO_INT_STA       0x0D

/** 
  * @brief  GPIO Registers  
  */ 
#define IOE_REG_GPIO_SET_PIN       0x10
#define IOE_REG_GPIO_CLR_PIN       0x11
#define IOE_REG_GPIO_MP_STA        0x12
#define IOE_REG_GPIO_DIR           0x13
#define IOE_REG_GPIO_ED            0x14
#define IOE_REG_GPIO_RE            0x15
#define IOE_REG_GPIO_FE            0x16
#define IOE_REG_GPIO_AF            0x17

/** 
  * @brief  ADC Registers  
  */ 
#define IOE_REG_ADC_INT_EN         0x0E
#define IOE_REG_ADC_INT_STA        0x0F
#define IOE_REG_ADC_CTRL1          0x20
#define IOE_REG_ADC_CTRL2          0x21
#define IOE_REG_ADC_CAPT           0x22
#define IOE_REG_ADC_DATA_CH0       0x30 /* 16-Bit register */
#define IOE_REG_ADC_DATA_CH1       0x32 /* 16-Bit register */
#define IOE_REG_ADC_DATA_CH2       0x34 /* 16-Bit register */
#define IOE_REG_ADC_DATA_CH3       0x36 /* 16-Bit register */
#define IOE_REG_ADC_DATA_CH4       0x38 /* 16-Bit register */
#define IOE_REG_ADC_DATA_CH5       0x3A /* 16-Bit register */
#define IOE_REG_ADC_DATA_CH6       0x3B /* 16-Bit register */
#define IOE_REG_ADC_DATA_CH7       0x3C /* 16-Bit register */ 

/** 
  * @brief  TouchScreen Registers  
  */ 
#define IOE_REG_TSC_CTRL           0x40
#define IOE_REG_TSC_CFG            0x41
#define IOE_REG_WDM_TR_X           0x42 
#define IOE_REG_WDM_TR_Y           0x44
#define IOE_REG_WDM_BL_X           0x46
#define IOE_REG_WDM_BL_Y           0x48
#define IOE_REG_FIFO_TH            0x4A
#define IOE_REG_FIFO_STA           0x4B
#define IOE_REG_FIFO_SIZE          0x4C
#define IOE_REG_TSC_DATA_X         0x4D 
#define IOE_REG_TSC_DATA_Y         0x4F
#define IOE_REG_TSC_DATA_Z         0x51
#define IOE_REG_TSC_DATA_XYZ       0x52 
#define IOE_REG_TSC_FRACT_XYZ      0x56
#define IOE_REG_TSC_DATA           0x57
#define IOE_REG_TSC_I_DRIVE        0x58
#define IOE_REG_TSC_SHIELD         0x59

/** 
  * @brief  Temperature Sensor registers  
  */ 
#define IOE_REG_TEMP_CTRL          0x60
#define IOE_REG_TEMP_DATA          0x61
#define IOE_REG_TEMP_TH            0x62

#define IO_Pin_0                 0x01
#define IO_Pin_1                 0x02
#define IO_Pin_2                 0x04
#define IO_Pin_3                 0x08
#define IO_Pin_4                 0x10
#define IO_Pin_5                 0x20
#define IO_Pin_6                 0x40
#define IO_Pin_7                 0x80
#define IO_Pin_ALL               0xFF

#define TOUCH_YD                    IO_Pin_1 /* IO_Exapnader_1 */ /* Input */
#define TOUCH_XD                    IO_Pin_2 /* IO_Exapnader_1 */ /* Input */
#define TOUCH_YU                    IO_Pin_3 /* IO_Exapnader_1 */ /* Input */
#define TOUCH_XU                    IO_Pin_4 /* IO_Exapnader_1 */ /* Input */
#define TOUCH_IO_ALL                (uint32_t)(IO_Pin_1 | IO_Pin_2 | IO_Pin_3 | IO_Pin_4)

/*
  * @brief  IO Expander Functionalities definitions  
  */ 
#define IOE_ADC_FCT              0x01
#define IOE_TS_FCT               0x02
#define IOE_IO_FCT               0x04
#define IOE_TEMPSENS_FCT         0x08

/**
  * @brief Eval Board both IO Exapanders Pins definition 
  */ 
#define IO1_IN_ALL_PINS          (uint32_t)(MEMS_INT1_PIN | MEMS_INT2_PIN)
#define IO2_IN_ALL_PINS          (uint32_t)(JOY_IO_PINS)
#define IO1_OUT_ALL_PINS         (uint32_t)(VBAT_DIV_PIN)
#define IO2_OUT_ALL_PINS         (uint32_t)(AUDIO_RESET_PIN | MII_INT_PIN)


/** 
  * @brief  IO Pin directions  
  */ 
#define Direction_IN             0x00
#define Direction_OUT            0x01
/** 
  * @brief IO Interrupts  
  */ 
#define IO_IT_0                  0x01
#define IO_IT_1                  0x02
#define IO_IT_2                  0x04
#define IO_IT_3                  0x08
#define IO_IT_4                  0x10
#define IO_IT_5                  0x20
#define IO_IT_6                  0x40
#define IO_IT_7                  0x80
#define ALL_IT                   0xFF
#define IOE_JOY_IT               (uint8_t)(IO_IT_3 | IO_IT_4 | IO_IT_5 | IO_IT_6 | IO_IT_7)
#define IOE_TS_IT                (uint8_t)(IO_IT_0 | IO_IT_1 | IO_IT_2)
#define IOE_INMEMS_IT            (uint8_t)(IO_IT_2 | IO_IT_3)
/**
  * @brief Eval Board IO Pins definition 
  */ 
#define AUDIO_RESET_PIN             IO_Pin_2 /* IO_Exapnader_2 */ /* Output */
#define MII_INT_PIN                 IO_Pin_0 /* IO_Exapnader_2 */ /* Output */
#define VBAT_DIV_PIN                IO_Pin_0 /* IO_Exapnader_1 */ /* Output */
#define MEMS_INT1_PIN               IO_Pin_3 /* IO_Exapnader_1 */ /* Input */
#define MEMS_INT2_PIN               IO_Pin_2 /* IO_Exapnader_1 */ /* Input */
/** 
  * @brief  Edge detection value  
  */ 
#define EDGE_FALLING              0x01
#define EDGE_RISING               0x02
/** 
  * @brief  IO bit values  
  */ 
typedef enum
{
  BitReset = 0,
  BitSet = 1
}IOE_BitValue_TypeDef;


/** 
  * @brief  Touch Screen Information structure  
  */ 
typedef struct
{
  uint16_t TouchDetected;
  uint16_t X;
  uint16_t Y;
  uint16_t Z;
}TS_STATE; 
  

u8 TOUCH_init(void);
u8 TOUCH_I2C_READREG(u8 addr,u8 regaddr);
void TOUCH_I2C_WRITEREG(u8 addr,u8 regaddr,u8 regdata);
TS_STATE* IOE_TS_GetState(void);

struct STMPE811_Driver
{
    static BOOL Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc);
    static BOOL Disable();
    static void GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, int* pSource, int* pUnCalX, int* pUnCalY );
    static HRESULT GetDeviceCaps(unsigned int iIndex, void* lpOutput);

private:
    static BOOL CalibrationPointGet(TOUCH_PANEL_CALIBRATION_POINT *pTCP);

};

#endif