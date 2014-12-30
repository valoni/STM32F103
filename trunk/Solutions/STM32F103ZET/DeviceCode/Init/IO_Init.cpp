////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Implementation for STM32Stamp board (STM32): Copyright (c) Oberon microsystems, Inc.
//
//  *** Board-specific IO Port Initialization ***
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "..\..\..\..\DeviceCode\Targets\Native\STM32\DeviceCode\stm32f10x.h"


/* Pin Configuration Register Values
    0x0  Analog Input
    0x1  Output 10Mhz
    0x2  Output  2Mhz
    0x3  Output 50Mhz
    0x4  Floating Input (default)
    0x5  Open-Drain 10Mhz
    0x6  Open-Drain  2Mhz
    0x7  Open-Drain 50Mhz
    0x8  Input with pull up/down
    0x9  Alternate Output 10Mhz
    0xA  Alternate Output  2Mhz
    0xB  Alternate Output 50Mhz
    0xC     -
    0xD  Alternate Open-Drain 10Mhz
    0xE  Alternate Open-Drain  2Mhz
    0xF  Alternate Open-Drain 50Mhz
*/
void __section(SectionForBootstrapOperations) STM3210E_InitSRam() {
		 			    
	RCC->AHBENR|=1<<8;       //ʹ��FSMCʱ��	  
	RCC->APB2ENR|=1<<5;      //ʹ��PORTDʱ��
	RCC->APB2ENR|=1<<6;      //ʹ��PORTEʱ��
 	RCC->APB2ENR|=1<<7;      //ʹ��PORTFʱ��
	RCC->APB2ENR|=1<<8;      //ʹ��PORTGʱ��	   

	//PORTD����������� 	
	GPIOD->CRH&=0X00000000;
	GPIOD->CRH|=0XBBBBBBBB; 
	GPIOD->CRL&=0XFF00FF00;
	GPIOD->CRL|=0X00BB00BB;   	 
	//PORTE����������� 	
	GPIOE->CRH&=0X00000000;
	GPIOE->CRH|=0XBBBBBBBB; 
	GPIOE->CRL&=0X0FFFFF00;
	GPIOE->CRL|=0XB00000BB; 
	//PORTF�����������
	GPIOF->CRH&=0X0000FFFF;
	GPIOF->CRH|=0XBBBB0000;  	    	 											 
	GPIOF->CRL&=0XFF000000;
	GPIOF->CRL|=0X00BBBBBB; 

	//PORTG����������� PG10->NE3     	 											 
	GPIOG->CRH&=0XFFFFF0FF;
	GPIOG->CRH|=0X00000B00;  
 	GPIOG->CRL&=0XFF000000;
	GPIOG->CRL|=0X00BBBBBB;  	 				  
  
	//�Ĵ�������
	//bank1��NE1~4,ÿһ����һ��BCR+TCR�������ܹ��˸��Ĵ�����
	//��������ʹ��NE3 ��Ҳ�Ͷ�ӦBTCR[4],[5]��				    
	FSMC_Bank1->BTCR[4]=0X00000000;
	FSMC_Bank1->BTCR[5]=0X00000000;
	FSMC_Bank1E->BWTR[4]=0X00000000;
	//����BCR�Ĵ���	ʹ���첽ģʽ,ģʽA(��д����һ��ʱ��Ĵ���)
	//BTCR[ż��]:BCR�Ĵ���;BTCR[����]:BTR�Ĵ���
	FSMC_Bank1->BTCR[4]|=1<<12;//�洢��дʹ��
	FSMC_Bank1->BTCR[4]|=1<<4; //�洢�����ݿ��Ϊ16bit 	    
	//����BTR�Ĵ���								    
	FSMC_Bank1->BTCR[5]|=3<<8; //���ݱ���ʱ�䣨DATAST��Ϊ3��HCLK 4/72M=55ns(��EM��SRAMоƬ)	 	 
	FSMC_Bank1->BTCR[5]|=0<<4; //��ַ����ʱ�䣨ADDHLD��δ�õ�	  	 
	FSMC_Bank1->BTCR[5]|=0<<0; //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/36M=27ns	 	 
	//����дʱ��Ĵ���  
	FSMC_Bank1E->BWTR[4]=0x0FFFFFFF;//Ĭ��ֵ
	//ʹ��BANK1����3
	FSMC_Bank1->BTCR[4]|=1<<0; 	
}


void __section(SectionForBootstrapOperations) BootstrapCode_GPIO() {

    /* Enable GPIOA, GPIOB, and GPIOC clocks */  
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN|RCC_APB2ENR_IOPDEN|RCC_APB2ENR_IOPEEN|RCC_APB2ENR_IOPFEN;

    // pins:      15------8                 7------0
    GPIOA->CRH = 0x44444444; GPIOA->CRL = 0x44444444;
    GPIOB->CRH = 0x44444444; GPIOB->CRL = 0x44444444;
    GPIOC->CRH = 0x44444444; GPIOC->CRL = 0x44444444;
    GPIOD->CRH = 0x44444444; GPIOD->CRL = 0x44444444;
    GPIOE->CRH = 0x44444444; GPIOE->CRL = 0x44444444;
    GPIOF->CRH = 0x44444444; GPIOF->CRL = 0x44444444;
	STM3210E_InitSRam(); // initialize FSMC & ports D-G
}
