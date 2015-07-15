#pragma once

#include <tinyhal.h>
#include "stm32f10x.h"

namespace ILI932x
{
	enum Color
	{
		White =    0xFFFF,
		Black =    0x0000,
		Grey =     0xF7DE,
		Blue =     0x001F,
		Blue2 =    0x051F,
		Red =      0xF800,
		Magenta =  0xF81F,
		Green =    0x07E0,
		Cyan =     0x7FFF,
		Yellow =   0xFFE0,
	};
};

class CILI932x
{
public:
	/*******************************************************************************
	* Function Name  : STM3210E_LCD_Init
	* Description    : Initializes the LCD.
	* Input          : None
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_Init(void);

	/*******************************************************************************
	* Function Name  : LCD_Clear
	* Description    : Clears the hole LCD.
	* Input          : Color: the color of the background.
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_Clear(u16 Color);
	
	/*******************************************************************************
	* Function Name  : LCD_SetCursor
	* Description    : Sets the cursor position.
	* Input          : - Xpos: specifies the X position.
	*                  - Ypos: specifies the Y position. 
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_SetCursor(u8 Xpos, u16 Ypos);
	
	/*******************************************************************************
	* Function Name  : LCD_SetDisplayWindow
	* Description    : Sets a display window
	* Input          : - Xpos: specifies the X buttom left position.
	*                  - Ypos: specifies the Y buttom left position.
	*                  - Width: display window width.
	*                  - Height: display window height.
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_SetDisplayWindow(u8 Xpos, u16 Ypos,u8 Width, u16 Height);
	
	/*******************************************************************************
	* Function Name  : LCD_DrawBMP
	* Description    : Displays a bitmap picture loaded in the internal Flash.
	* Input          : - BmpAddress: Bmp picture address in the internal Flash.
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_DrawBMP(u8 Xpos, u16 Ypos, u16 Width, u16 Height,const u8 *pBitmap);
	
	//----------------------------------------------------------------------------
	//Description:
	//	Display the bitmap data
	//----------------------------------------------------------------------------
	static void LCD_DrawBMP(u8 Xpos, u16 Ypos, u16 Width, u16 Height,const u16 *pBitmap);
	
	//----------------------------------------------------------------------------
	//Description:
	//	Display the bitmap data
	//----------------------------------------------------------------------------
	static void LCD_DrawBMP(u8 Xpos, u16 Ypos, u16 Width, u16 Height,const u32 *pBitmap);
	
	//----------------------------------------------------------------------------
	//Description:
	//	Get the lcd width
	//----------------------------------------------------------------------------
	static u16 LCD_GetWidth();
	
	//----------------------------------------------------------------------------
	//Description:
	//	Get the lcd height
	//----------------------------------------------------------------------------
	static u16 LCD_GetHeight();	

	//----------------------------------------------------------------------------
	//Description:
	//	Display the char data
	//
	//Parameters:
	//	x : [in] x position
	//	y : [in] y position
	//	c : [in] The char to draw
	//	charColor : [in] The char color
	//	bkColor : [in] The back color
	//----------------------------------------------------------------------------
	static void LCD_DrawChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor);
	
	//----------------------------------------------------------------------------
	//Description:
	//	Writes a specified formatted character to the LCD screen at the current cursor position
	//
	//Parameters:
	//	character : [in] The char to draw
	//----------------------------------------------------------------------------
	static void LCD_DrawFormattedChar(u8 character);
	
	//----------------------------------------------------------------------------
	//Description:
	//	Draw the point
	//
	//Parameters:
	//	x : [in] The x position
	//	y : [in] The y position
	//	color : [in] The color of point
	//----------------------------------------------------------------------------
	static void LCD_DrawPoint(u16 x,u16 y,u16 color);
	
	//----------------------------------------------------------------------------
	//Description:
	//	Display the string data
	//
	//Parameters:
	//	x : [in] x position
	//	y : [in] y position
	//	pString : [in] The string to display
	//	charColor : [in] The char color
	//	bkColor : [in] The back color
	//----------------------------------------------------------------------------
	static void LCD_DrawString(u16 x,u16 y,const u8 *pString,u16 charColor,u16 bkColor);

	/*******************************************************************************
	* Function Name  : LCD_PowerOn
	* Description    : Power on the LCD.
	* Input          : None
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_PowerOn(void);
	
	/*******************************************************************************
	* Function Name  : LCD_DisplayOn
	* Description    : Enables the Display.
	* Input          : None
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_DisplayOn(void);
	
	/*******************************************************************************
	* Function Name  : LCD_DisplayOff
	* Description    : Disables the Display.
	* Input          : None
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_DisplayOff(void);
	
	//----------------------------------------------------------------------------
	//Description:
	//	Retrieves the number of bits per pixel on the LCD screen. 
	//----------------------------------------------------------------------------
	static u8 LCD_GetBitsPerPixel();
	

	
	
public:
	CILI932x();
	virtual ~CILI932x();				
	
protected:
	/*******************************************************************************
	* Function Name  : LCD_WriteReg
	* Description    : Writes to the selected LCD register.
	* Input          : - LCD_Reg: address of the selected register.
	*                  - LCD_RegValue: value to write to the selected register.
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
	
	/*******************************************************************************
	* Function Name  : LCD_ReadReg
	* Description    : Reads the selected LCD Register.
	* Input          : None
	* Output         : None
	* Return         : LCD Register Value.
	*******************************************************************************/
	static u16 LCD_ReadReg(u8 LCD_Reg);
	
	/*******************************************************************************
	* Function Name  : LCD_WriteRAM_Prepare
	* Description    : Prepare to write to the LCD RAM.
	* Input          : None
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_WriteRAM_Prepare(void);
	
	/*******************************************************************************
	* Function Name  : LCD_WriteRAM
	* Description    : Writes to the LCD RAM.
	* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_WriteRAM(u16 RGB_Code);
	
	/*******************************************************************************
	* Function Name  : LCD_ReadRAM
	* Description    : Reads the LCD RAM.
	* Input          : None
	* Output         : None
	* Return         : LCD RAM Value.
	*******************************************************************************/
	static u16 LCD_ReadRAM(void);	
	
private:
	/*******************************************************************************
	* Function Name  : LCD_CtrlLinesConfig
	* Description    : Configures LCD Control lines (FSMC Pins) in alternate function
	                   Push-Pull mode.
	* Input          : None
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_CtrlLinesConfig(void);
	
	/*******************************************************************************
	* Function Name  : LCD_FSMCConfig
	* Description    : Configures the Parallel interface (FSMC) for LCD(Parallel mode)
	* Input          : None
	* Output         : None
	* Return         : None
	*******************************************************************************/
	static void LCD_FSMCConfig(void);
	
	//----------------------------------------------------------------------------
	//Description:
	//	Delay for a moment
	//
	//Parameters:
	//	uSec : [in] The millisecond time
	//----------------------------------------------------------------------------
	static void Delay(UINT32 uSec);
	
	//------------------------------------------------------------------------------------------------------------
	//Description:
	//	Display the bitmap data
	//
	//Parameters:
	//	Xpos : [in]Begin x position
	//	Ypos : [in]Begin y position
	//	Width : [in] The width
	//	Height : [in] The height
	//	pBitmap : [in] The pointer to the buffer storing the bitmap data.
	//	Step : [in] The step for increasing pointer.For example,if the pBitmap is u32 type original,
	//							but you convert the buffer to u16, and you should set the Step as 2 to correctly increase.
	//-----------------------------------------------------------------------------------------------------------
	static void LCD_DrawBMP(u8 Xpos, u16 Ypos, u16 Width, u16 Height,const u16 *pBitmap,u16 Step);
	
private:
	typedef struct
	{
	  vu16 LCD_REG;
	  vu16 LCD_RAM;
	} LCD_TypeDef;
	
private:
	static u16 ms_CurXPos;
	static u16 ms_CurYPos;
};