#pragma once

#include <tinyhal.h>
#include "stm32f10x.h"
#include ".\library\library.h"

//---------------------------------------
//Description:
//	Initialize the device
//---------------------------------------
void Device_Init();


//---------------------------------------
//Description:
//	Reset the device
//---------------------------------------
void Device_Reset();


//-----------------------------------------------------------
//Description:
//	Initialize USB Cable.
//-----------------------------------------------------------
void Device_Cable_Initialize ();

//-----------------------------------------------------------
//Description:
//	Software Connection/Disconnection of USB Cable.
//-----------------------------------------------------------
void Device_Cable_Config (FunctionalState NewState);