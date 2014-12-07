///////////////////////////////////////////////////////////////////////////////////////////////////
//Description:
//	The file is copied from MCD Application Team,and I modified it.
//	The follows is the original copyright information:
//		/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
//		* File Name          : lcd.c
//		* Author             : MCD Application Team
//		* Version            : V1.1.2
//		* Date               : 09/22/2008
//		* Description        : This file includes the LCD driver for AM-240320L8TNQW00H 
//		*                     (LCD_ILI9320) Liquid Crystal Display Module of STM3210E-EVAL
//		*                      board.
//		********************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////



#include "ILI932x.h"

//------------------------------------------------------------------
//Macro

#define R0             0x00
#define R1             0x01
#define R2             0x02
#define R3             0x03
#define R4             0x04
#define R5             0x05
#define R6             0x06
#define R7             0x07
#define R8             0x08
#define R9             0x09
#define R10            0x0A
#define R12            0x0C
#define R13            0x0D
#define R14            0x0E
#define R15            0x0F
#define R16            0x10
#define R17            0x11
#define R18            0x12
#define R19            0x13
#define R20            0x14
#define R21            0x15
#define R22            0x16
#define R23            0x17
#define R24            0x18
#define R25            0x19
#define R26            0x1A
#define R27            0x1B
#define R28            0x1C
#define R29            0x1D
#define R30            0x1E
#define R31            0x1F
#define R32            0x20
#define R33            0x21
#define R34            0x22
#define R36            0x24
#define R37            0x25
#define R40            0x28
#define R41            0x29
#define R43            0x2B
#define R45            0x2D
#define R48            0x30
#define R49            0x31
#define R50            0x32
#define R51            0x33
#define R52            0x34
#define R53            0x35
#define R54            0x36
#define R55            0x37
#define R56            0x38
#define R57            0x39
#define R59            0x3B
#define R60            0x3C
#define R61            0x3D
#define R62            0x3E
#define R63            0x3F
#define R64            0x40
#define R65            0x41
#define R66            0x42
#define R67            0x43
#define R68            0x44
#define R69            0x45
#define R70            0x46
#define R71            0x47
#define R72            0x48
#define R73            0x49
#define R74            0x4A
#define R75            0x4B
#define R76            0x4C
#define R77            0x4D
#define R78            0x4E
#define R79            0x4F
#define R80            0x50
#define R81            0x51
#define R82            0x52
#define R83            0x53
#define R96            0x60
#define R97            0x61
#define R106           0x6A
#define R118           0x76
#define R128           0x80
#define R129           0x81
#define R130           0x82
#define R131           0x83
#define R132           0x84
#define R133           0x85
#define R134           0x86
#define R135           0x87
#define R136           0x88
#define R137           0x89
#define R139           0x8B
#define R140           0x8C
#define R141           0x8D
#define R143           0x8F
#define R144           0x90
#define R145           0x91
#define R146           0x92
#define R147           0x93
#define R148           0x94
#define R149           0x95
#define R150           0x96
#define R151           0x97
#define R152           0x98
#define R153           0x99
#define R154           0x9A
#define R157           0x9D
#define R192           0xC0
#define R193           0xC1
#define R229           0xE5

/* LCD Control pins */
#define CtrlPin_NCS    GPIO_Pin_2   /* PB.02 */
#define CtrlPin_RS     GPIO_Pin_7   /* PD.07 */
#define CtrlPin_NWR    GPIO_Pin_15  /* PD.15 */

/* LCD color */
//#define White          0xFFFF
//#define Black          0x0000
//#define Grey           0xF7DE
//#define Blue           0x001F
//#define Blue2          0x051F
//#define Red            0xF800
//#define Magenta        0xF81F
//#define Green          0x07E0
//#define Cyan           0x7FFF
//#define Yellow         0xFFE0

#define Line0          0
#define Line1          24
#define Line2          48
#define Line3          72
#define Line4          96
#define Line5          120
#define Line6          144
#define Line7          168
#define Line8          192
#define Line9          216

#define Horizontal     0x00
#define Vertical       0x01

/* Note: LCD /CS is CE4 - Bank 4 of NOR/SRAM Bank 1~4 */
#define LCD_BASE        ((u32)(0x60000000 | 0x0C000000))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

//The width and height
#define LCD_WIDTH				240
#define LCD_HEIGHT			320

//For the formatted font begin position
#define DEFAULT_DRAW_BEGIN_X_POSITION		0
#define DEFAULT_DRAW_BEGIN_Y_POSITION		1
#define DEFAULT_DRAW_BACKGROUND_COLOR		ILI932x::Black
#define DEFAULT_DRAW_CHARACTER_COLOR		ILI932x::White
	
//If the character is not less than VISIBLE_CHARACTER_THRESHOLD_VALUE,it is visible
#define VISIBLE_CHARACTER_THRESHOLD_VALUE		32
//------------------------------------------------------------------
//The static member variable
u16 CILI932x::ms_CurXPos = DEFAULT_DRAW_BEGIN_X_POSITION;
u16 CILI932x::ms_CurYPos = DEFAULT_DRAW_BEGIN_Y_POSITION;
//------------------------------------------------------------------

CILI932x::CILI932x()
{}

CILI932x::~CILI932x()
{}



void CILI932x::LCD_Init(void)
{ 
/* Configure the LCD Control pins --------------------------------------------*/
  LCD_CtrlLinesConfig();

/* Configure the FSMC Parallel interface -------------------------------------*/
  LCD_FSMCConfig();

  Delay(5); /* delay 50 ms */
/* Start Initial Sequence ----------------------------------------------------*/
  LCD_WriteReg(R229,0x8000); /* Set the internal vcore voltage */
  LCD_WriteReg(R0,  0x0001); /* Start internal OSC. */
  LCD_WriteReg(R1,  0x0100); /* set SS and SM bit */
  LCD_WriteReg(R2,  0x0700); /* set 1 line inversion */
  LCD_WriteReg(R3,  0x1030); /* set GRAM write direction and BGR=1. */
  LCD_WriteReg(R4,  0x0000); /* Resize register */
  LCD_WriteReg(R8,  0x0202); /* set the back porch and front porch */
  LCD_WriteReg(R9,  0x0000); /* set non-display area refresh cycle ISC[3:0] */
  LCD_WriteReg(R10, 0x0000); /* FMARK function */
  LCD_WriteReg(R12, 0x0000); /* RGB interface setting */
  LCD_WriteReg(R13, 0x0000); /* Frame marker Position */
  LCD_WriteReg(R15, 0x0000); /* RGB interface polarity */

/* Power On sequence ---------------------------------------------------------*/
  LCD_WriteReg(R16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  LCD_WriteReg(R17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
  LCD_WriteReg(R18, 0x0000); /* VREG1OUT voltage */
  LCD_WriteReg(R19, 0x0000); /* VDV[4:0] for VCOM amplitude */
  Delay(20);                 /* Dis-charge capacitor power voltage (200ms) */
  LCD_WriteReg(R16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  LCD_WriteReg(R17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
  Delay(5);                  /* Delay 50 ms */
  LCD_WriteReg(R18, 0x0139); /* VREG1OUT voltage */
  Delay(5);                  /* Delay 50 ms */
  LCD_WriteReg(R19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
  LCD_WriteReg(R41, 0x0013); /* VCM[4:0] for VCOMH */
  Delay(5);                  /* Delay 50 ms */
  LCD_WriteReg(R32, 0x0000); /* GRAM horizontal Address */
  LCD_WriteReg(R33, 0x0000); /* GRAM Vertical Address */

/* Adjust the Gamma Curve ----------------------------------------------------*/
  LCD_WriteReg(R48, 0x0006);
  LCD_WriteReg(R49, 0x0101);
  LCD_WriteReg(R50, 0x0003);
  LCD_WriteReg(R53, 0x0106);
  LCD_WriteReg(R54, 0x0b02);
  LCD_WriteReg(R55, 0x0302);
  LCD_WriteReg(R56, 0x0707);
  LCD_WriteReg(R57, 0x0007);
  LCD_WriteReg(R60, 0x0600);
  LCD_WriteReg(R61, 0x020b);
  
/* Set GRAM area -------------------------------------------------------------*/
  LCD_WriteReg(R80, 0x0000); /* Horizontal GRAM Start Address */
  LCD_WriteReg(R81, 0x00EF); /* Horizontal GRAM End Address */
  LCD_WriteReg(R82, 0x0000); /* Vertical GRAM Start Address */
  LCD_WriteReg(R83, 0x013F); /* Vertical GRAM End Address */


  //LCD_WriteReg(R96,  0x2700); /* 2.8-->9325->0x2700 Gate Scan Line */
  LCD_WriteReg(R96,  0xA700); /* 3.2-->9320->0xA700 Gate Scan Line */


  LCD_WriteReg(R97,  0x0001); /* NDL,VLE, REV */
  LCD_WriteReg(R106, 0x0000); /* set scrolling line */

/* Partial Display Control ---------------------------------------------------*/
  LCD_WriteReg(R128, 0x0000);
  LCD_WriteReg(R129, 0x0000);
  LCD_WriteReg(R130, 0x0000);
  LCD_WriteReg(R131, 0x0000);
  LCD_WriteReg(R132, 0x0000);
  LCD_WriteReg(R133, 0x0000);

/* Panel Control -------------------------------------------------------------*/
  LCD_WriteReg(R144, 0x0010);
  LCD_WriteReg(R146, 0x0000);
  LCD_WriteReg(R147, 0x0003);
  LCD_WriteReg(R149, 0x0110);
  LCD_WriteReg(R151, 0x0000);
  LCD_WriteReg(R152, 0x0000);

  /* Set GRAM write direction and BGR = 1 */
  /* I/D=01 (Horizontal : increment, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  LCD_WriteReg(R3, 0x1018);

  LCD_WriteReg(R7, 0x0173); /* 262K color and display ON */  
}

void CILI932x::LCD_Clear(u16 Color)
{
  u32 index = 0;
  

  LCD_SetCursor(0x00, 0x00); 

  LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

  for(index = 0; index < 76800; index++)
  {
    LCD->LCD_RAM = Color;
  }  
  
  //Reset the current cursor position
  ms_CurXPos = DEFAULT_DRAW_BEGIN_X_POSITION;
  ms_CurYPos = DEFAULT_DRAW_BEGIN_Y_POSITION;
}


void CILI932x::LCD_SetCursor(u8 Xpos, u16 Ypos)
{
  LCD_WriteReg(R32, Xpos);
  
  //It's reversed in the y coordination to the actual screen,so I reversed it here.
  LCD_WriteReg(R33, LCD_HEIGHT - Ypos);

}


void CILI932x::LCD_SetDisplayWindow(u8 Xpos, u16 Ypos,  u8 Width, u16 Height)
{
  /* Horizontal GRAM Start Address */
  LCD_WriteReg(R80, Xpos);

  /* Horizontal GRAM End Address */
  LCD_WriteReg(R81, Xpos+Width);
 
  /* Vertical GRAM Start Address */
  LCD_WriteReg(R82, Ypos);

  /* Vertical GRAM End Address */
  LCD_WriteReg(R83, Ypos+Height);

  LCD_SetCursor(Xpos, Ypos);
}


void CILI932x::LCD_DrawBMP(u8 Xpos, u16 Ypos, u16 Width, u16 Height, const u8 *pBitmap)
{
  LCD_DrawBMP(Xpos, Ypos, Width, Height,(const u16 *)pBitmap,1);
}

void CILI932x::LCD_DrawBMP(u8 Xpos, u16 Ypos, u16 Width, u16 Height,const u16 *pBitmap)
{
	LCD_DrawBMP(Xpos, Ypos, Width, Height,pBitmap,1);
}

void CILI932x::LCD_DrawBMP(u8 Xpos, u16 Ypos, u16 Width, u16 Height,const u32 *pBitmap)
{
	LCD_DrawBMP(Xpos, Ypos, Width, Height,(const u16 *)pBitmap,2);
}

void CILI932x::LCD_DrawBMP(u8 Xpos, u16 Ypos, u16 Width, u16 Height,const u16 *pBitmap,u16 Step)
{
	vu32 index;
  vu32 size = Height * Width;
  const u16 *bitmap_ptr = pBitmap + (Step - 1); //Alignment the begin position.

  LCD_SetDisplayWindow(Xpos, Ypos, Width - 1, Height - 1);

  /* Set GRAM write direction and BGR = 1 */
  /* I/D=00 (Horizontal : decrement, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  LCD_WriteReg(R3, 0x1008);
 
  LCD_WriteRAM_Prepare();
 
  for(index = 0; index < size; index += Step)
  {
	LCD_WriteRAM(*bitmap_ptr++);
  }
 
  /* Set GRAM write direction and BGR = 1 */
  /* I/D = 01 (Horizontal : increment, Vertical : decrement) */
  /* AM = 1 (address is updated in vertical writing direction) */
  LCD_WriteReg(R3, 0x1018);
  LCD_SetDisplayWindow(00, 00, 239, 319);
}

void CILI932x::LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD->LCD_RAM = LCD_RegValue;
}


u16 CILI932x::LCD_ReadReg(u8 LCD_Reg)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = LCD_Reg;
  /* Read 16-bit Reg */
  return (LCD->LCD_RAM);
}


void CILI932x::LCD_WriteRAM_Prepare(void)
{
  LCD->LCD_REG = R34;
}


void CILI932x::LCD_WriteRAM(u16 RGB_Code)
{
  /* Write 16-bit GRAM Reg */
  LCD->LCD_RAM = RGB_Code;
}


u16 CILI932x::LCD_ReadRAM(void)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = R34; /* Select GRAM Reg */
  /* Read 16-bit Reg */
  return LCD->LCD_RAM;
}


void CILI932x::LCD_PowerOn(void)
{
/* Power On sequence ---------------------------------------------------------*/
  LCD_WriteReg(R16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  LCD_WriteReg(R17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
  LCD_WriteReg(R18, 0x0000); /* VREG1OUT voltage */
  LCD_WriteReg(R19, 0x0000); /* VDV[4:0] for VCOM amplitude*/
  Delay(20);             /* Dis-charge capacitor power voltage (200ms) */
  LCD_WriteReg(R16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  LCD_WriteReg(R17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
  Delay(5);              /* Delay 50 ms */
  LCD_WriteReg(R18, 0x0139); /* VREG1OUT voltage */
  Delay(5);              /* Delay 50 ms */
  LCD_WriteReg(R19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
  LCD_WriteReg(R41, 0x0013); /* VCM[4:0] for VCOMH */
  Delay(5);              /* Delay 50 ms */
  LCD_WriteReg(R7, 0x0173);  /* 262K color and display ON */
}


void CILI932x::LCD_DisplayOn(void)
{
  /* Display On */
  LCD_WriteReg(R7, 0x0173); /* 262K color and display ON */
}


void CILI932x::LCD_DisplayOff(void)
{
  /* Display Off */
  LCD_WriteReg(R7, 0x0); 
}


void CILI932x::LCD_CtrlLinesConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |
                         RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG |
                         RCC_APB2Periph_AFIO, ENABLE);

  /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
     PD.10(D15), PD.14(D0), PD.15(D1) as alternate 
     function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
     PE.14(D11), PE.15(D12) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_WriteBit(GPIOE, GPIO_Pin_6, Bit_SET);

  /* Set PF.00(A0 (RS)) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  /* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
}


void CILI932x::LCD_FSMCConfig(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;

/*-- FSMC Configuration ------------------------------------------------------*/
/*----------------------- SRAM Bank 4 ----------------------------------------*/
  /* FSMC_Bank1_NORSRAM4 configuration */
  p.FSMC_AddressSetupTime = 0;
  p.FSMC_AddressHoldTime = 0;
  p.FSMC_DataSetupTime = 2;
  p.FSMC_BusTurnAroundDuration = 0;
  p.FSMC_CLKDivision = 0;
  p.FSMC_DataLatency = 0;
  p.FSMC_AccessMode = FSMC_AccessMode_A;

  /* Color LCD configuration ------------------------------------
     LCD configured as follow:
        - Data/Address MUX = Disable
        - Memory Type = SRAM
        - Data Width = 16bit
        - Write Operation = Enable
        - Extended Mode = Enable
        - Asynchronous Wait = Disable */
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  

  /* BANK 4 (of NOR/SRAM Bank 1~4) is enabled */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
}

void CILI932x::Delay(UINT32 uSec)
{
	uSec *= 1000;
	HAL_Time_Sleep_MicroSeconds(uSec);
}

u16 CILI932x::LCD_GetWidth()
{
	return LCD_WIDTH;
}

u16 CILI932x::LCD_GetHeight()
{
	return LCD_HEIGHT;
}

void CILI932x::LCD_DrawChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{
	int width = Font_Width();
	int height = Font_Height();
  
  const UINT8* font = Font_GetGlyph( c );
	UINT8 tmp_char = 0;
	
  for (int i = 0; i < height; i++)
  {
  	//The fonts is two type:8x15 and 8x8, so the size of UINT8 is the same with one width. 
  	tmp_char = font[i];
  	
    for (int j = 0; j < width; j++)
    {
      if ( (tmp_char >> 7-j) & 0x01 == 0x01)      
      {
        LCD_DrawPoint(x + j, y + i, charColor); // The char color
      }
      else
      {
        LCD_DrawPoint(x + j, y + i, bkColor); // The background color
      }
    }
  }
}


void CILI932x::LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	if( x > LCD_WIDTH || y > LCD_HEIGHT) 
	{
		return;
	}

  LCD_SetCursor(x,y);

  LCD_WriteRAM_Prepare();
  LCD_WriteRAM(color);
}


void CILI932x::LCD_DrawString(u16 x,u16 y,const u8 *pString,u16 charColor,u16 bkColor)
{
	if(pString == NULL)
	{
		return ;
	}
	
	u16 DrawX = x;
	while(*pString != '\0')
	{
		LCD_DrawChar(DrawX,y,*pString,charColor,bkColor);
		
		DrawX += Font_Width();
		pString ++;
	}
	
	ms_CurXPos = DrawX;
	ms_CurYPos = y;
}

u8 CILI932x::LCD_GetBitsPerPixel()
{
	//The type is RGB565,so is 16bit
	return 16;
}

void CILI932x::LCD_DrawFormattedChar(u8 character)
{
	if(ms_CurXPos + Font_Width() > LCD_GetWidth() || character == '\n')
	{
		ms_CurXPos = DEFAULT_DRAW_BEGIN_X_POSITION;
		ms_CurYPos += Font_Height();
	}
	
	if(ms_CurYPos >= LCD_GetHeight())
	{
		//Clear the screen
		LCD_Clear(DEFAULT_DRAW_BACKGROUND_COLOR);
	}
	
	//Draw the character
	LCD_DrawChar(ms_CurXPos,ms_CurYPos,character,DEFAULT_DRAW_CHARACTER_COLOR,DEFAULT_DRAW_BACKGROUND_COLOR);
		
	if(character >= VISIBLE_CHARACTER_THRESHOLD_VALUE)
	{
		//If the character is more than VISIBLE_CHARACTER_THRESHOLD_VALUE, 
		//it's the visible character, and it should increase the position
		ms_CurXPos += Font_Width();
	}

}