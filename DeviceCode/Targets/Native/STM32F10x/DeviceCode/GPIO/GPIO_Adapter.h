#include <tinyhal.h>
#include "stm32f10x_conf.h"

//--------------------------------------------------------------
//Micro defined

//The count of pin for each port area.
#define PIN_COUNT_EACH_PORT	16

#define ALL_PIN_COUNT				112 //7 * 16
//--------------------------------------------------------------

//--------------------------------------------------------
//Description:
//	Convert the input pin to GPIO_TypeDef value.
//Parameters:
//	pin : [in] The input GPIO pin value
//--------------------------------------------------------
GPIO_TypeDef* PinToPort(GPIO_PIN pin);

//--------------------------------------------------------
//Description:
//	Convert the input pin to stm32f10x port bit value.
//Parameters:
//	pin : [in] The input GPIO pin value
//	wBit : [out] The converted value
//--------------------------------------------------------
BOOL PinToBit(GPIO_PIN pin,uint16_t &wBit);

//--------------------------------------------------------
//Description:
//	To check the input GPIO_PIN is valid or not
//Parameters:
//	pin : [in] The input GPIO pin value
//--------------------------------------------------------
BOOL IsValidPin(GPIO_PIN pin);


//--------------------------------------------------------
//Description:
//	Convert the input pin to stm32f10x port source value.
//Parameters:
//	pin : [in] The input GPIO pin value
//	wPortSource : [out] The converted value
//--------------------------------------------------------
BOOL PinToPortSource(GPIO_PIN pin,uint8_t &wPortSource);

//--------------------------------------------------------
//Description:
//	Convert the input pin to stm32f10x pin source value.
//Parameters:
//	pin : [in] The input GPIO pin value
//	wPinSource : [out] The converted value
//--------------------------------------------------------
BOOL PinToPinSource(GPIO_PIN pin,uint8_t &wPinSource);

//--------------------------------------------------------
//Description:
//	Convert the input pin to stm32f10x EXTI line value.
//Parameters:
//	pin : [in] The input GPIO pin value
//	wLine : [out] The converted value
//--------------------------------------------------------
BOOL PinToLine(GPIO_PIN pin,uint32_t &dwLine);

//--------------------------------------------------------
//Description:
//	Convert the input pin to IRQ table index
//Parameters:
//	pin : [in] The input GPIO pin value
//	dwIrq : [out] The converted value
//--------------------------------------------------------
BOOL PinToIRQ(GPIO_PIN pin,DWORD &dwIrq);

