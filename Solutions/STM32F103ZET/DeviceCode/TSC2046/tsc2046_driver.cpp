////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tsc2046_driver.h>
#include "..\..\..\..\DeviceCode\Targets\Native\STM32\DeviceCode\stm32f10x.h"

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入
/////////////////////////////////////////////////////////////////
//与触摸屏芯片连接引脚	   
//#define PEN  	PFin(10)  	//PF10 INT
#define DOUT 	PFin(8)   	//PF8  MISO
#define TDIN 	PFout(9)  	//PF9  MOSI
#define TCLK 	PBout(1)  	//PB1  SCLK
#define TCS  	PBout(2)  	//PB2  CS  
extern TOUCH_SPI_CONFIGURATION g_TSC2046_Config;
extern TOUCH_PANEL_SamplingSettings g_TouchPanel_Sampling_Settings;
/*
void HAL_Time_Sleep_MicroSeconds(u32 uSec)
{
	HAL_Time_Sleep_MicroSeconds(uSec);
}
*/
u8 CMD_RDX=0XD0;
u8 CMD_RDY=0X90;
BOOL TSC2046_Driver::Enable( GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc )
{   
/*  
    if (!::CPU_GPIO_ReservePin( g_TSC2046_Config.SpiConfiguration.DeviceCS, TRUE ))
    {
        return FALSE;
    }    

    ::CPU_GPIO_EnableOutputPin( g_TSC2046_Config.SpiConfiguration.DeviceCS, TRUE );    

    CPU_GPIO_SetDebounce(3);

    if (!::CPU_GPIO_EnableInputPin2(    
            g_TSC2046_Config.InterruptPin,
            TRUE,
            touchIsrProc,
            NULL,
            GPIO_INT_EDGE_BOTH,
            RESISTOR_PULLUP))
    {        
        return FALSE;
    }    

    ::CPU_SPI_Initialize();
	*/
//注意,时钟使能之后,对GPIO的操作才有效
	//所以上拉之前,必须使能时钟.才能实现真正的上拉输出
	RCC->APB2ENR|=1<<3;    //PB时钟使能	   
	RCC->APB2ENR|=1<<7;    //PF时钟使能	   
 	
	GPIOB->CRL&=0XFFFFF00F;//PB1  2   T_CLK   T_CS
	GPIOB->CRL|=0X00000330; 
	GPIOB->ODR|=3<<1;      //PB1 2 推挽输出 	 
	GPIOF->CRH&=0XFFFFFF00;
	GPIOF->CRH|=0X00000038;
	GPIOF->ODR|=3<<8;      //PF8,9全部上拉	  T_MISO T_MOSI  
	
    if (!::CPU_GPIO_EnableInputPin2(    
            90,//PF10 T_PEN
            TRUE,
            touchIsrProc,
            NULL,
            GPIO_INT_EDGE_BOTH,
            RESISTOR_PULLUP))
    {        
        return FALSE;
    }
	
    return TRUE;
}

BOOL TSC2046_Driver::Disable()
{
    CPU_GPIO_DisablePin(   90,//PF10 T_PEN
	                       RESISTOR_DISABLED,
						   0, 
						   GPIO_ALT_PRIMARY);
    
    return true;
}

//SPI写数据
//向触摸屏IC写入1byte数据    
//num:要写入的数据
void TP_Write_Byte(u8 num)    
{  
	u8 count=0;   
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80)TDIN=1;  
		else TDIN=0;   
		num<<=1;    
		TCLK=0; 	 
		TCLK=1;		//上升沿有效	        
	}		 			    
} 		 
//SPI读数据 
//从触摸屏IC读取adc值
//CMD:指令
//返回值:读到的数据	   
u16 TP_Read_AD(u8 CMD)	  
{ 	 
	u8 count=0; 	  
	u16 Num=0; 
	TCLK=0;		//先拉低时钟 	 
	TDIN=0; 	//拉低数据线
	TCS=0; 		//选中触摸屏IC
	TP_Write_Byte(CMD);//发送命令字
	HAL_Time_Sleep_MicroSeconds(6);//ADS7846的转换时间最长为6us
	TCLK=0; 	     	    
	HAL_Time_Sleep_MicroSeconds(1);    	   
	TCLK=1;		//给1个时钟，清除BUSY	    	    
	TCLK=0; 	     	    
	for(count=0;count<16;count++)//读出16位数据,只有高12位有效 
	{ 				  
		Num<<=1; 	 
		TCLK=0;	//下降沿有效  	    	   
		TCLK=1;
		if(DOUT)Num++; 		 
	}  	
	Num>>=4;   	//只有高12位有效.
	TCS=1;		//释放片选	 
	return(Num);   
}
//读取一个坐标值(x或者y)
//连续读取READ_TIMES次数据,对这些数据升序排列,
//然后去掉最低和最高LOST_VAL个数,取平均值 
//xy:指令（CMD_RDX/CMD_RDY）
//返回值:读到的数据
#define READ_TIMES 5 	//读取次数
#define LOST_VAL 1	  	//丢弃值
u16 TP_Read_XOY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);		 		    
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 
//读取x,y坐标
//最小值不能少于100.
//x,y:读取到的坐标值
//返回值:0,失败;1,成功。
u8 TP_Read_XY(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=TP_Read_XOY(CMD_RDX);
	ytemp=TP_Read_XOY(CMD_RDY);	  												   
	//if(xtemp<100||ytemp<100)return 0;//读数失败
	*x=xtemp;
	*y=ytemp;
	return 1;//读数成功
}
//连续2次读取触摸屏IC,且这两次的偏差不能超过
//ERR_RANGE,满足条件,则认为读数正确,否则读数错误.	   
//该函数能大大提高准确度
//x,y:读取到的坐标值
//返回值:0,失败;1,成功。
#define ERR_RANGE 50 //误差范围 
u8 TP_Read_XY2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=TP_Read_XY(&x1,&y1);   
    if(flag==0)return(0);
    flag=TP_Read_XY(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-50内
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;	  
}  
//////////////////////////////////////////////////////////////////////////////////		  
//与LCD部分有关的函数  
//画一个触摸点
//用来校准用的
//x,y:坐标
//color:颜色

void TSC2046_Driver::GetPoint( TOUCH_PANEL_SAMPLE_FLAGS* pTipState, int* pSource, int* pUnCalX, int* pUnCalY )
{
    *pTipState = 0;
    *pUnCalX = 0;
    *pUnCalY = 0;
    *pSource = 0;

    static bool  stylusDown = false;

    /// Apparently there's a lot of noise from the touch hardware. We will take several
    /// independent measures to compensate for them:
    /// 1. Settle down time (instead of reading right away, wait few moments) --> ReadsToIgnore
    /// 2. Read multiple samples (read a number of them, and then take average) --> ReadsPerSample.
    ///

    UINT16 i = 0;
    UINT16 totalReads = g_TouchPanel_Sampling_Settings.ReadsToIgnore + g_TouchPanel_Sampling_Settings.ReadsPerSample;

    int x = -1;
    int y = -1;

    INT32 validReadCount = 0;

    UINT32 d1 = 0xFFFF;
    UINT32 d2 = 0;

    for(i = 0; i < totalReads; i++)
    {    
       // static unsigned char writeBufferX[4] = {0x90, 0, 0, 0};
       // static unsigned char readBuffer[3] =  {0, 0, 0};

        d2 = d1;
       // ::CPU_SPI_nWrite8_nRead8(g_TSC2046_Config.SpiConfiguration, writeBufferX, 4, readBuffer, 3, 1);
    
       // d1 = readBuffer[0];                
       // d1 <<= 8;
       // d1 |=  readBuffer[1];
      //  d1 >>= 3;  
       d1 = TP_Read_AD(CMD_RDY);	  

        if (d1 == d2)
            break;
    }

    y = d1;

    d1 = 0xFFFF;
    d2 = 0;
    for(i = 0; i < g_TouchPanel_Sampling_Settings.ReadsPerSample; i++)
    {
      //  static unsigned char writeBufferY[4] = {0xD0, 0, 0, 0};
      //  static unsigned char readBuffer[3] =  {0, 0, 0};

        d2 = d1;
       // ::CPU_SPI_nWrite8_nRead8(g_TSC2046_Config.SpiConfiguration, writeBufferY, 4, readBuffer, 3, 1);
    
       // d1 = readBuffer[0];                
       // d1 <<= 8;
       // d1 |=  readBuffer[1];
      //  d1 >>= 3;                 
         d1 = TP_Read_AD(CMD_RDX);	
        if (d1 == d2)
            break;
    }

    x = d1;

    if (x >= 3700)
    {
        validReadCount = 0;
    }
    else
    {
        validReadCount = 1;
    }

    
    if (stylusDown)
    {
        *pTipState |= TouchSamplePreviousDownFlag;
    }

    if (validReadCount > 0)
    {
        *pTipState |= TouchSampleValidFlag;
        *pUnCalX = x;
        *pUnCalY = y;
        *pTipState |= TouchSampleDownFlag;
        stylusDown = true;
    }
    else
    {
        *pUnCalX = -1;
        *pUnCalY = -1;
        stylusDown = false;       
    }    
}

BOOL TSC2046_Driver::CalibrationPointGet(TOUCH_PANEL_CALIBRATION_POINT *pTCP)
{

    INT32   cDisplayWidth  = pTCP->cDisplayWidth;
    INT32   cDisplayHeight = pTCP->cDisplayHeight;

    int CalibrationRadiusX = cDisplayWidth  / 20;
    int CalibrationRadiusY = cDisplayHeight / 20;

    switch (pTCP -> PointNumber)
    {
    case    0:
        pTCP->CalibrationX = cDisplayWidth  / 2;
        pTCP->CalibrationY = cDisplayHeight / 2;
        break;

    case    1:
        pTCP->CalibrationX = CalibrationRadiusX * 2;
        pTCP->CalibrationY = CalibrationRadiusY * 2;
        break;

    case    2:
        pTCP->CalibrationX = CalibrationRadiusX * 2;
        pTCP->CalibrationY = cDisplayHeight - CalibrationRadiusY * 2;
        break;

    case    3:
        pTCP->CalibrationX = cDisplayWidth  - CalibrationRadiusX * 2;
        pTCP->CalibrationY = cDisplayHeight - CalibrationRadiusY * 2;
        break;

    case    4:
        pTCP->CalibrationX = cDisplayWidth - CalibrationRadiusX * 2;
        pTCP->CalibrationY = CalibrationRadiusY * 2;
        break;

    default:
        pTCP->CalibrationX = cDisplayWidth  / 2;
        pTCP->CalibrationY = cDisplayHeight / 2;
        
        return FALSE;
    }
    
    return TRUE;
}


HRESULT TSC2046_Driver::GetDeviceCaps(unsigned int iIndex, void* lpOutput)
{
    if ( lpOutput == NULL )
    {
        return FALSE;
    }

    switch ( iIndex )
    {
    case TOUCH_PANEL_SAMPLE_RATE_ID:
        {
            TOUCH_PANEL_SAMPLE_RATE  *pTSR  = (TOUCH_PANEL_SAMPLE_RATE*)lpOutput;    

            pTSR->SamplesPerSecondLow       = g_TouchPanel_Sampling_Settings.SampleRate.SamplesPerSecondLow;
            pTSR->SamplesPerSecondHigh      = g_TouchPanel_Sampling_Settings.SampleRate.SamplesPerSecondHigh;
            pTSR->CurrentSampleRateSetting  = g_TouchPanel_Sampling_Settings.SampleRate.CurrentSampleRateSetting;
            pTSR->MaxTimeForMoveEvent_ticks = g_TouchPanel_Sampling_Settings.SampleRate.MaxTimeForMoveEvent_ticks;
        }
        break; 

    case TOUCH_PANEL_CALIBRATION_POINT_COUNT_ID:
        {
            TOUCH_PANEL_CALIBRATION_POINT_COUNT *pTCPC = (TOUCH_PANEL_CALIBRATION_POINT_COUNT*)lpOutput;            

            pTCPC->flags              = 0;
            pTCPC->cCalibrationPoints = 5;
        }
        break;

    case TOUCH_PANEL_CALIBRATION_POINT_ID:        
        return(CalibrationPointGet((TOUCH_PANEL_CALIBRATION_POINT*)lpOutput));

    default:        
        return FALSE;
    }

    return TRUE;
}

