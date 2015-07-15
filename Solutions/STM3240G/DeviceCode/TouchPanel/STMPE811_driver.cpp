#include "STMPE811_driver.h"

TS_STATE TS_State;              /* The global structure holding the TS state */


void TOUCH_GPIO_init(void)
{
	RCC->AHB1ENR |= TOUCH_I2C_SCL_GPIO_RCC;
	GPIO_Set(TOUCH_I2C_SDA_GPIO,TOUCH_I2C_SDA_PIN,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	
	GPIO_AF_Set(TOUCH_I2C_SDA_GPIO,TOUCH_I2C_SCL_AF_SOURCE,TOUCH_I2C_SCL_AF_MODE);	
	GPIO_Set(TOUCH_I2C_SCL_GPIO,TOUCH_I2C_SCL_PIN,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	
	GPIO_AF_Set(TOUCH_I2C_SCL_GPIO,TOUCH_I2C_SDA_AF_SOURCE,TOUCH_I2C_SDA_AF_MODE);
	
	RCC->AHB1ENR |= TOUCH_I2C_INT_GPIO_RCC;	
	GPIO_Set(TOUCH_I2C_INT_GPIO,TOUCH_I2C_INT_PIN,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_NONE); 
}

void TOUCH_I2C_init(void)
{
		RCC->APB1ENR |= 1 << 21;//开I2C1时钟
		I2C1->CR1 |= 1<<15;             //I2C复位
		HAL_Time_Sleep_MicroSeconds(20);
		I2C1->CR1 &= ~(1<<15);             //I2C复位
		I2C1->CR1 |= 0 << 1;// 设置为I2C模式
		I2C1->CR2 |= 42; //设置APB1的时钟为42M              

		I2C1->CCR |= 0<<15;    //设置I2C主模式为Standard Mode
		I2C1->CCR |= 210<<0;            //分频系数 = PCLK1/2/f(PCLK1=42MHZ,f=100KHZ)

		I2C1->TRISE |= 43;    //最大允许SCL上升时间为1000ns,故TRISE[5:0]写入(1000ns/(1000/42)ns = 42+1)

		//I2C1->CR1 |= 1<<6;              //广播呼叫使能

		I2C1->OAR1 |= 0<<15;            //寻址模式 1响应10位地址  0响应7位地址
		I2C1->OAR1 |= 1<<14;            //必须始终由软件保持为1
		//I2C1->OAR1 |= 0x82 ;//设置接口地址的 7-1位

		//I2C1->CR2 |= 1<<9;              //事件中断使能
		//I2C1->CR2 |= 1<<8;              //出错中断使能
		I2C1->CR1 |= 1<<0;              //I2C1使能
		I2C1->CR1 |= 1<<10;             ////使能ACK	
}

void TOUCH_I2C_START(void)
{
  I2C1->CR1 |= 1 << 8;  //生成起始位
}

void TOUCH_I2C_STOP(void)
{
  I2C1->CR1 |= 1 << 9;  //生成停止位
}

void TOUCH_I2C_WRITE( u8 data)
{
  I2C1->DR = data;
}
void TOUCH_I2C_ENADLEACK(void)
{
	I2C1->CR1 |= 1<<10;             ////使能ACK	
}
void TOUCH_I2C_DISABLEACK(void)
{
I2C1->CR1 &= ~(1<<10); 
}

u8 TOUCH_I2C_READ(void)
{  
	  return I2C1->DR;
}

u8 TOUCH_I2C_READREG(u8 addr,u8 regaddr)
{

	 u8 res;
   TOUCH_I2C_START();           //start
	 //clear = I2C1->SR2;
	 while(!(I2C1->SR1 & 1<<0));  //wait start ok
 	 TOUCH_I2C_DISABLEACK();
	 TOUCH_I2C_WRITE(addr);       //write device address R/W=0
	 while(!(I2C1->SR1 & 1<<1));  //wait write address ok
	  I2C1->SR2;                  //clear REG SR2
   TOUCH_I2C_WRITE(regaddr);    //write reg address
 
	 while(!(I2C1->SR1 & 1<<2));  //wait write reg address ok
  
  	TOUCH_I2C_START();           //restart
	 while(!(I2C1->SR1 & 1<<0));  //wait restart ok
	 TOUCH_I2C_WRITE(addr|1);     //write device address  R/W=1
	 while(!(I2C1->SR1 & 1<<1));  //wait write address ok
	  I2C1->SR2;                  //clear REG SR2
	 while(!(I2C1->SR1 & 1<<6));
	 TOUCH_I2C_STOP();
	 res = TOUCH_I2C_READ();     //read regdata
   TOUCH_I2C_ENADLEACK();
	// printf("READ STMPE811 REG 0x%x is 0x%x\r\n",regaddr,res);
	 return res;
}

void TOUCH_I2C_WRITEREG(u8 addr,u8 regaddr,u8 regdata)
{
   TOUCH_I2C_START();           //start

	 while(!(I2C1->SR1 & 1<<0));  //wait start ok
 	 TOUCH_I2C_DISABLEACK();
	 TOUCH_I2C_WRITE(addr);       //write device address R/W=0
	 while(!(I2C1->SR1 & 1<<1));  //wait write address ok
	  I2C1->SR2;                  //clear REG SR2
   TOUCH_I2C_WRITE(regaddr);    //write reg address
	 while(!(I2C1->SR1 & 1<<2));  //wait write reg address ok
	
	 TOUCH_I2C_WRITE(regdata);
	 while(!(I2C1->SR1 & 1<<2));  //TX is Empty and wait write reg address ok
   TOUCH_I2C_STOP();
	// printf("WRITE STMPE811 REG 0x%x is 0x%x\r\n",regaddr,regdata);
}

u16 TOUCH_I2C_READBUFFER(u8 addr,u8 regaddr)
{

	 u16 res;
   TOUCH_I2C_START();           //start
	 //clear = I2C1->SR2;
	 while(!(I2C1->SR1 & 1<<0));  //wait start ok
 	 TOUCH_I2C_DISABLEACK();
	 TOUCH_I2C_WRITE(addr);       //write device address R/W=0
	 while(!(I2C1->SR1 & 1<<1));  //wait write address ok
	  I2C1->SR2;                  //clear REG SR2
   TOUCH_I2C_WRITE(regaddr);    //write reg address
	 while(!(I2C1->SR1 & 1<<2));  //wait write reg address ok
  
  	TOUCH_I2C_START();           //restart
	 while(!(I2C1->SR1 & 1<<0));  //wait restart ok
	 TOUCH_I2C_WRITE(addr|1);     //write device address  R/W=1
	 while(!(I2C1->SR1 & 1<<1));  //wait write address ok
	  I2C1->SR2;                  //clear REG SR2
	 while(!(I2C1->SR1 & 1<<6));
	 TOUCH_I2C_STOP();
	 res = TOUCH_I2C_READ();     //read regdata
	 res <<=8;
	 res |=  TOUCH_I2C_READ();
   TOUCH_I2C_ENADLEACK();
	// printf("READ STMPE811 REG 0x%x is 0x%x\r\n",regaddr,res);
	 return res;
}

void TOUCH_IOAFConfig(u8 DeviceAddr, u8 IO_Pin, u8 NewState)
{
  uint8_t tmp = 0;
  
  /* Get the current state of the GPIO_AF register */
  tmp = TOUCH_I2C_READREG(DeviceAddr, IOE_REG_GPIO_AF);
  
  if (NewState != 0)
  {
    /* Enable the selected pins alternate function */
    tmp |= (u8)IO_Pin;
  }
  else
  {
    /* Disable the selected pins alternate function */   
    tmp &= ~(u8)IO_Pin;   
  }
  
  /* Write back the new value in GPIO_AF register */  
  TOUCH_I2C_WRITEREG(DeviceAddr, IOE_REG_GPIO_AF, tmp);  
  TOUCH_I2C_READREG(DeviceAddr, IOE_REG_GPIO_AF);
}

void TOUCH_FnctCmd(u8 DeviceAddr, u8 Fct, u8 NewState)
{
  uint8_t tmp = 0;
  
  /* Get the register value */
  tmp = TOUCH_I2C_READREG(DeviceAddr, IOE_REG_SYS_CTRL2);
  
  if (NewState != 0)
  {
    /* Set the Functionalities to be Enabled */    
    tmp &= ~(uint8_t)Fct;
  }
  else
  {
    /* Set the Functionalities to be Disabled */    
    tmp |= (uint8_t)Fct;  
  }
  
  /* Set the register value */
  TOUCH_I2C_WRITEREG(DeviceAddr, IOE_REG_SYS_CTRL2, tmp);
  TOUCH_I2C_READREG(DeviceAddr, IOE_REG_SYS_CTRL2); 
}
/**
  * @brief  Configures the selected pin direction (to be an input or an output)
  * @param  DeviceAddr: The address of the IOExpander, could be : IOE_1_ADDR
  *         or IOE_2_ADDR.
  * @param  IO_Pin: IO_Pin_x: Where x can be from 0 to 7.   
  * @param  Direction: could be Direction_IN or Direction_OUT.      
  * @retval IOE_OK: if all initializations are OK. Other value if error.
  */
void TOUCH_IOPinConfig(uint8_t DeviceAddr, uint8_t IO_Pin, uint8_t Direction)
{
  uint8_t tmp = 0;   
  
  /* Get all the Pins direction */
  tmp = TOUCH_I2C_READREG(DeviceAddr, IOE_REG_GPIO_DIR);
  
  if (Direction != Direction_IN)
  {
    tmp |= (uint8_t)IO_Pin;
  }  
  else 
  {
    tmp &= ~(uint8_t)IO_Pin;
  }
  
  /* Write the register new value */
  TOUCH_I2C_WRITEREG(DeviceAddr, IOE_REG_GPIO_DIR, tmp);
      
}
/**
  * @brief  Configures the Edge for which a transition is detectable for the
  *         the selected pin.
  * @param  DeviceAddr: The address of the IOExpander, could be : IOE_1_ADDR
  *         or IOE_2_ADDR.
  * @param  IO_Pin: IO_Pin_x, Where x can be from 0 to 7.   
  * @param  Edge: The edge which will be detected. This parameter can be one or a
  *         a combination of following values: EDGE_FALLING and EDGE_RISING .
  * @retval IOE_OK: if all initializations are OK. Other value if error.
  */
void TOUCH_IOEdgeConfig(uint8_t DeviceAddr, uint8_t IO_Pin, uint8_t Edge)
{
  uint8_t tmp1 = 0, tmp2 = 0;   
  
  /* Get the registers values */
  tmp1 = TOUCH_I2C_READREG(DeviceAddr, IOE_REG_GPIO_FE);
  tmp2 = TOUCH_I2C_READREG(DeviceAddr, IOE_REG_GPIO_RE);

  /* Disable the Falling Edge */
  tmp1 &= ~(uint8_t)IO_Pin;
  /* Disable the Falling Edge */
  tmp2 &= ~(uint8_t)IO_Pin;

  /* Enable the Falling edge if selected */
  if (Edge & EDGE_FALLING)
  {
    tmp1 |= (uint8_t)IO_Pin;
  }

  /* Enable the Rising edge if selected */
  if (Edge & EDGE_RISING)
  {
    tmp2 |= (uint8_t)IO_Pin;
  }

  /* Write back the registers values */
  TOUCH_I2C_WRITEREG(DeviceAddr, IOE_REG_GPIO_FE, tmp1);
  TOUCH_I2C_WRITEREG(DeviceAddr, IOE_REG_GPIO_RE, tmp2);
  
}

/**
  * @brief  Writes a bit value to an output IO pin.
  * @param IO_Pin: The output pin to be set or reset. This parameter can be one 
  *        of the following values:
  *   @arg  AUDIO_RESET_PIN: Audio codec reset pin
  *   @arg  MII_INT_PIN: Ethernet Phy MII interrupt pin
  *   @arg  VBAT_DIV_PIN: Battery divider pin
  * @param BitVal: The value to be set. This parameter can be one of the
  *        following values: BitSet or BitReset. See IOE_BitVal_TypeDef.
  * @retval IOE_OK or PARAM_ERROR
  */
void TOUCH_WriteIOPin(uint8_t IO_Pin, IOE_BitValue_TypeDef BitVal)
{

  
  /* Apply the bit value to the selected pin */
  if (BitVal == BitReset)
  {
    /* Set the register */
    TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_GPIO_CLR_PIN, IO_Pin);
  }
  else
  {
    /* Set the register */
    TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_GPIO_SET_PIN, IO_Pin);
  }
  

}


void TOUCH_CONFIG(void)
{
/* Enable touch screen functionality */
  TOUCH_FnctCmd(STMPE811_ADDR, IOE_TS_FCT, ENABLE);
  
  /* Select Sample Time, bit number and ADC Reference */
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_ADC_CTRL1, 0x49);
  
  /* Wait for ~20 ms */
  HAL_Time_Sleep_MicroSeconds(20);  
  
  /* Select the ADC clock speed: 3.25 MHz */
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_ADC_CTRL2, 0x01);
  
  /* Select TSC pins in non default mode */  
  TOUCH_IOAFConfig(STMPE811_ADDR, (uint8_t)TOUCH_IO_ALL, DISABLE);
  
  /* Select 2 nF filter capacitor */
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_TSC_CFG, 0x9A);   
  
  /* Select single point reading  */
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_FIFO_TH, 0x01);
  
  /* Write 0x01 to clear the FIFO memory content. */
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_FIFO_STA, 0x01);
  
  /* Write 0x00 to put the FIFO back into operation mode  */
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_FIFO_STA, 0x00);
  
  /* set the data format for Z value: 7 fractional part and 1 whole part */
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_TSC_FRACT_XYZ, 0x01);
  
  /* set the driving capability of the device for TSC pins: 50mA */
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_TSC_I_DRIVE, 0x01);
  
  /* Use no tracking index, touch-screen controller operation mode (XYZ) and 
     enable the TSC */
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_TSC_CTRL, 0x03);
  
  /*  Clear all the status pending bits */
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_INT_STA, 0xFF); 
  
  /* Initialize the TS structure to their default values */ 
  TS_State.TouchDetected = TS_State.X = TS_State.Y = TS_State.Z = 0;
}


/**
  * @brief  Return Touch Screen X position value
  * @param  None
  * @retval X position.
  */
static uint16_t IOE_TS_Read_Y(void)
{
  int32_t x, xr;
 
  x = TOUCH_I2C_READBUFFER(STMPE811_ADDR, IOE_REG_TSC_DATA_Y);
  
  /* first correction */
  xr =  (x * 320) >> 12;
  /* second correction */
  xr = ((xr * 32)/29) - 17;
  
  if(xr <= 0)
    xr = 0;
  
  return (uint16_t)(xr); 
}

/**
  * @brief  Return Touch Screen Y position value
  * @param  None
  * @retval Y position.
  */
static uint16_t IOE_TS_Read_X(void)
{
  int32_t y, yr;
  y= TOUCH_I2C_READBUFFER(STMPE811_ADDR, IOE_REG_TSC_DATA_X);
  
  yr= (y * 240) >> 12;
  yr = ((yr * 240) / 217) - 12;
  
  if(yr <= 0)
    yr = 0;
  
  return (uint16_t)(yr); 
}

/**
  * @brief  Return Touch Screen Z position value
  * @param  None
  * @retval Z position.
  */
static uint16_t IOE_TS_Read_Z(void)
{
  uint32_t z;
  z = TOUCH_I2C_READREG(STMPE811_ADDR, IOE_REG_TSC_DATA_Z);
  
  
  if(z <= 0)
    z = 0;
  
  return (uint16_t)(z); 
}


/**
  * @brief  Returns Status and positions of the Touch screen.
  * @param  None
  * @retval Pointer to TS_STATE structure holding Touch Screen information.
  */
TS_STATE* IOE_TS_GetState(void)
{
  uint32_t xDiff, yDiff , x , y;
  static uint32_t _x = 0, _y = 0;
  
  /* Check if the Touch detect event happened */
  TS_State.TouchDetected = (TOUCH_I2C_READREG(STMPE811_ADDR, IOE_REG_TSC_CTRL) & 0x80);
  if(TS_State.TouchDetected) 
  {
    x = IOE_TS_Read_X();
    y = IOE_TS_Read_Y();
    xDiff = x > _x? (x - _x): (_x - x);
    yDiff = y > _y? (y - _y): (_y - y);       
    if (xDiff + yDiff > 5)
    {
      _x = x;
      _y = y;       
    }
  }  
  /* Update the X position */
  TS_State.X = _x;
    
  /* Update the Y position */  
  TS_State.Y = _y;
  /* Update the Z Pression index */  
  TS_State.Z = IOE_TS_Read_Z();  
  
  /* Clear the interrupt pending bit and enable the FIFO again */
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_FIFO_STA, 0x01);
  TOUCH_I2C_WRITEREG(STMPE811_ADDR, IOE_REG_FIFO_STA, 0x00);
  
  /* Return pointer to the updated structure */
  return &TS_State; 
}

/**
  * @brief  Resets the IO Expander by Software (SYS_CTRL1, RESET bit).
  * @param  DeviceAddr: The address of the IOExpander, could be : IOE_1_ADDR
  *         or IOE_2_ADDR.
  * @retval IOE_OK: if all initializations are OK. Other value if error.
  */
void TOUCH_Reset(u8 DeviceAddr)
{
  /* Power Down the IO_Expander */
  TOUCH_I2C_WRITEREG(DeviceAddr, IOE_REG_SYS_CTRL1, 0x02);

  /* wait for a delay to insure registers erasing */
  HAL_Time_Sleep_MicroSeconds(2); 
  
  /* Power On the Codec after the power off => all registers are reinitialized*/
  TOUCH_I2C_WRITEREG(DeviceAddr, IOE_REG_SYS_CTRL1, 0x00);
  
}


u8 TOUCH_init(void)
{
	u8 res;
	u16 CHIP_ID;
//	TOUCH_GPIO_init();
//  TOUCH_I2C_init();
//	I2C_Internal_Initialize();
	CHIP_ID = TOUCH_I2C_READREG(STMPE811_ADDR,0x00);
	CHIP_ID <<= 8;
	CHIP_ID |=  TOUCH_I2C_READREG(STMPE811_ADDR,0x01);
	if (CHIP_ID == 0x0811) res = 0;
	else res = 1;
		
	TOUCH_Reset(STMPE811_ADDR);
	
  TOUCH_FnctCmd(STMPE811_ADDR, IOE_IO_FCT | IOE_ADC_FCT, ENABLE);
	
	TOUCH_CONFIG();

	return res;
}

BOOL STMPE811_Driver::Enable( GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc )
{
	TOUCH_init();
	return true;
	
}

BOOL STMPE811_Driver::Disable()
{
	return true;
}

void STMPE811_Driver::GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, int* pSource, int* pUnCalX, int* pUnCalY )
{
	
	static bool stylusDown = 0;
    *pTipState = 0;
    *pUnCalX = 0;
    *pUnCalY = 0;
    *pSource = 0;
    TS_STATE  *ts;
	ts = IOE_TS_GetState();	
	 if (stylusDown)
    {
        *pTipState |= TouchSamplePreviousDownFlag;
    }

    if (ts->TouchDetected)
    {
        *pTipState |= TouchSampleValidFlag;
        *pUnCalX = ts->X;
        *pUnCalY = ts->Y;
        *pTipState |= TouchSampleDownFlag;
        stylusDown = 1;
    }
    else
    {
        *pUnCalX = -1;
        *pUnCalY = -1;
        stylusDown = 0;               
    }    
}

HRESULT STMPE811_Driver::GetDeviceCaps(unsigned int iIndex, void* lpOutput)
{
	return false;
}