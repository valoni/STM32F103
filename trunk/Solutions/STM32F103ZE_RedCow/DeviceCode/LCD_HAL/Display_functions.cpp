////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tinyhal.h"
#include "ILI932x.h"
//--//


BOOL LCD_Initialize()
{
	DISPLAY_CONTROLLER_CONFIG config;
	config.Width = CILI932x::LCD_GetWidth();
	config.Height = CILI932x::LCD_GetHeight();
  LCD_Controller_Initialize(config);
  
  return TRUE;
}

BOOL LCD_Uninitialize()
{
	LCD_Controller_Uninitialize();
	return TRUE;
}

void LCD_Clear()
{
	CILI932x::LCD_Clear(ILI932x::Black);
}

void LCD_BitBltEx( int x, int y, int width, int height, UINT32 data[] )
{
	CILI932x::LCD_DrawBMP(x,y,width,height,reinterpret_cast<const u32 *>(data));
}

void LCD_BitBlt( int width, int height, int widthInWords, UINT32 data[], BOOL fUseDelta )
{
	NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
}

void LCD_WriteChar( unsigned char c, int row, int col )
{
	CILI932x::LCD_DrawChar(row,col,c,ILI932x::White,ILI932x::Black);
}

void LCD_WriteFormattedChar( unsigned char c )
{
	CILI932x::LCD_DrawFormattedChar(c);
}

INT32 LCD_GetWidth()
{
	return CILI932x::LCD_GetWidth();
}

INT32 LCD_GetHeight()
{
	return CILI932x::LCD_GetHeight();
}

INT32 LCD_GetBitsPerPixel()
{
	return CILI932x::LCD_GetBitsPerPixel();
}

UINT32 LCD_GetPixelClockDivider()
{
	NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
	return 0;
}
INT32 LCD_GetOrientation()
{
	//The orientation of the screen, 0 means that the screen is not rotated. 
	return 0;
}
void LCD_PowerSave( BOOL On )
{
	//Nothing to do
}

UINT32* LCD_GetFrameBuffer()
{
	NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
	return NULL;
}

UINT32 LCD_ConvertColor(UINT32 color)
{
	NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
	return color;
}


//--//


