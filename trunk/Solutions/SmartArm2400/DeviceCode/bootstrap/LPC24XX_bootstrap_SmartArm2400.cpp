//-----------------------------------------------------------------------------
// Software that is described herein is for illustrative purposes only  
// which provides customers with programming information regarding the  
// products. This software is supplied "AS IS" without any warranties.  
// NXP Semiconductors assumes no responsibility or liability for the 
// use of the software, conveys no license or title under any patent, 
// copyright, or mask work right to the product. NXP Semiconductors 
// reserves the right to make changes in the software without 
// notification. NXP Semiconductors also make no representation or 
// warranty that such application will be suitable for the specified 
// use without further testing or modification. 
//-----------------------------------------------------------------------------

#include <tinyhal.h>
#include <DeviceCode\LPC24XX.h>
	
#pragma arm section code = "SectionForBootstrapOperations"

#if defined(COMPILE_ARM) || defined(COMPILE_THUMB)
FORCEINLINE void __section(SectionForBootstrapOperations) Bootstrap_Delay( INT32 count )
{
#ifdef __GNUC__
    asm("1: subs %0, %0, #4\nbgt 1b" :: "r" (count));
#else
    __asm
    {
Loop:
        subs    count, count, #4
        bgt     Loop
    }
#endif
}
#elif defined(COMPILE_THUMB2)
FORCEINLINE void __section(SectionForBootstrapOperations) Bootstrap_Delay( INT32 count )
{
    // TODO: WRITE THUMB2 code
}
#endif


void __section(SectionForBootstrapOperations) delayMs(UINT32 timer_num, UINT32 delayInMs)
{

  LPC24XX_TIMER& TIMER = LPC24XX::TIMER( timer_num );

	TIMER.TCR = 0x02;		/* reset timer */
	TIMER.PR  = 0x00;		/* set prescaler to zero */
	TIMER.MR0 = delayInMs * (SYSTEM_CLOCK_HZ / 1000-1);
	TIMER.IR  = 0xff;		/* reset all interrrupts */
	TIMER.MCR = 0x04;		/* stop timer on match */
	TIMER.TCR = LPC24XX_TIMER::TCR_TEN;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (TIMER.TCR & LPC24XX_TIMER::TCR_TEN)
  {
  }
	TIMER.TCR = 0x02;		/* reset timer */
	TIMER.MCR = 0x00;		/* Clear MCR */
  return;
}

void __section(SectionForBootstrapOperations) BootstrapCode_Clocks()
{
    
    // Disconnect the PLL if already connected
    if ((LPC24XX::SYSCON().PLLSTAT & LPC24XX_SYSCON::CNCTD ))
    {
        LPC24XX::SYSCON().PLLCON  = LPC24XX_SYSCON::PLLE;
        LPC24XX::SYSCON().PLLFEED = 0xAA;
        LPC24XX::SYSCON().PLLFEED = 0x55;
    }
    
    // Disable the PLL
    LPC24XX::SYSCON().PLLCON  = 0x0;
    LPC24XX::SYSCON().PLLFEED = 0xAA;
    LPC24XX::SYSCON().PLLFEED = 0x55;
    
    // Enable the Oscillator and wait for it to be stable
    LPC24XX::SYSCON().SCS = (LPC24XX::SYSCON().SCS | LPC24XX_SYSCON::OSCEN);
    while ( ((LPC24XX::SYSCON().SCS & LPC24XX_SYSCON::READY) == 0) )
    {
    }
    
    // Select Main Oscillator as the PLL clock source
    LPC24XX::SYSCON().CLKSRCSEL = LPC24XX_SYSCON::OSC;
    
    // See platform_SmartArm2400_selector.h
    LPC24XX::SYSCON().PLLCFG  = (((PLL_NVAL-1) << 16) | (PLL_MVAL-1));

	LPC24XX::SYSCON().PLLCON  = LPC24XX_SYSCON::PLLE;
    LPC24XX::SYSCON().PLLFEED = 0xAA;
    LPC24XX::SYSCON().PLLFEED = 0x55;
   
    // Wait while PLL locks
    while ( (LPC24XX::SYSCON().PLLSTAT & LPC24XX_SYSCON::LOCKD) == 0x0 )
    {
    }
    
    // Enable MAM
    LPC24XX::SYSCON().MAMTIM = 7;
    LPC24XX::SYSCON().MAMCR = 2;

    // Set CCLK and USB clock divider
    LPC24XX::SYSCON().CCLKCFG = (CCLK_DIVIDER-1);
    LPC24XX::SYSCON().USBCLKCFG = (USB_DIVIDER-1);
    
    // PLL locked now connect it
    LPC24XX::SYSCON().PLLCON = (LPC24XX_SYSCON::PLLC | LPC24XX_SYSCON::PLLE);
    LPC24XX::SYSCON().PLLFEED = 0xAA;
    LPC24XX::SYSCON().PLLFEED = 0x55;
    
    // Enable UART2
    LPC24XX::SYSCON().PCONP |= ((1<<24)|(1<<3));
}

//should be unused in the LPC24XX, I'm leaving it here as a possible reference
void __section(SectionForBootstrapOperations) BootstrapCode_Ext_SRAM()
{

// BCFG1 Register Configuration Value:  0x20000C21
// IDCY   :  1  ->  2 idle cycles
// WST1   :  1  ->  4 CCLK cycles
// RBLE   :  1  ->  Memory Bank composed of two 16 bit devices
// WST2   :  1  ->  4 CCLK cycles
// BUSERR :  0  ->  not relevant
// WPERR  :  0  ->  no write protection error
// WP     :  0  ->  bank not write protected
// BM     :  0  ->  no burst rom bank
// MW     :  2  ->  32-bit wide bus
// AT     :  0  ->  always write 0 to this field

//THIS WAS THE ONLY UNCOMMENTED LINE IN LPC22XX function:   LPC22XX::EMC().BCFG1=0x20000C21;   

}

void __section(SectionForBootstrapOperations) BootstrapCode_Ext_Flash()
{
	    // NAND Flash
    LPC24XX::EMC().SWAITWEN0 = 0x2;
    LPC24XX::EMC().SWAITOEN0 = 0x2;
    LPC24XX::EMC().SWAITRD0 = 0x8;
    LPC24XX::EMC().SWAITPAGE0 = 0x1f;
    LPC24XX::EMC().SWAITWR0 = 0x8;
    LPC24XX::EMC().SWAITTURN0 = 0xf;
    LPC24XX::EMC().SCONFIG0 = 0x00000080;

	// NOR Flash
    LPC24XX::EMC().SWAITWEN1 = 0x0; // 0x2
    LPC24XX::EMC().SWAITOEN1 = 0x3; // 0x2
    LPC24XX::EMC().SWAITRD1 = 0x4;  // 0x1f
    LPC24XX::EMC().SWAITPAGE1 = 0x1f;
    LPC24XX::EMC().SWAITWR1 = 0x2; //0x1f
    LPC24XX::EMC().SWAITTURN1 = 0x0;//0xf
    LPC24XX::EMC().SCONFIG1 = 0x00000081;
}

void __section(SectionForBootstrapOperations) BootstrapCode_Pins()
{
    // Connect SDRAM and Flash memory pins
    // !!! These settings are for EA-LPC2468-16-OEM-V2 board
    // To be updated for the EA-LPC2478 board
    // CS3 and CS4 
    LPC24XX::PCB().Regs[4].PINSEL = 0x50000000;
    
    // CAS, RAS, CLKOUT0, DYCS0. CKEOUT0 and DQMOUT0/1/2/3
    LPC24XX::PCB().Regs[5].PINSEL = 0x55010115;
    
    // D0 - D15
    LPC24XX::PCB().Regs[6].PINSEL = 0x55555555;
    
    // D16 - D31
    LPC24XX::PCB().Regs[7].PINSEL = 0x55555555;    
    
    // A0 - A15
    LPC24XX::PCB().Regs[8].PINSEL = 0x55555555;
    
    // A16 - A23, OE, WE, BLS1/2 and CS0/1
    LPC24XX::PCB().Regs[9].PINSEL = 0x50555555;
}

void __section(SectionForBootstrapOperations) BootstrapCode_Ext_SDRAM()
{
    volatile UINT32 dummy;
    UINT32 i;
    
    LPC24XX::EMC().CONTROL = 0x00000001;
    // Enable EMC Clock
    LPC24XX::SYSCON().PCONP |= 0x00000800;

	// 32 Bit SDRAM Init
    LPC24XX::EMC().DRP = 1;
    LPC24XX::EMC().DRAS = 2;
    LPC24XX::EMC().DSREX = 1;
    LPC24XX::EMC().DAPR = 1;
    LPC24XX::EMC().DDAL = 5;
    LPC24XX::EMC().DWR = 2;
    LPC24XX::EMC().DRC = 3;
    LPC24XX::EMC().DRFC = 3;
    LPC24XX::EMC().DXSR = 5;
    LPC24XX::EMC().DRRD = 1;
    LPC24XX::EMC().DMRD = 2;
    LPC24XX::EMC().DREADCONFIG = 1;
    LPC24XX::EMC().DRASCAS0 = 0x00000303;
    LPC24XX::EMC().DCONFIG0 = 0x00000280;	
	
	for (i = 0; i < 0xF0; i++) {
    }
    
    //NOP command
    LPC24XX::EMC().DCONTROL = 0x00000183;
	
	for (i = 0; i < 0xF0; i++) {
    }

    //PRECHARGE-ALL command
    LPC24XX::EMC().DCONTROL = 0x00000103;

	for (i = 0; i < 0xF0; i++) {
    }

    LPC24XX::EMC().DREFRESH = 0x0000004;
    
    //wait for precharge
    for(i = 0; i < 0xF0; i++)	// wait 128 AHB clock cycles
    {
    }
    
    //Set refresh period
    LPC24XX::EMC().DREFRESH = 45;
     
    //Set Mode
    LPC24XX::EMC().DCONTROL = 0x00000083;

    dummy = *((volatile unsigned int*)(SRAM1_MEMORY_Base | (0x33 << 11)));
	//dummy = *((volatile unsigned int*)(0xa0019800));
    
	//Set NORMAL mode
    LPC24XX::EMC().DCONTROL = 0x00000000;

    //Enable buffer
    LPC24XX::EMC().DCONFIG0 = 0x00080280;

	for (i = 0; i < 0xF0; i++) {
    }
}

// map the InternalRAM  to address 0
void __section(SectionForBootstrapOperations) Initialize_SyncOn()
{
    LPC24XX::SYSCON().MEMMAP=0x2;
}

extern "C"
{
void __section(SectionForBootstrapOperations) platform_prestackinit()
{
    BootstrapCode_Clocks();
    BootstrapCode_Pins();

#if !defined(TARGETLOCATION_RAM)
    BootstrapCode_Ext_SDRAM();
	//Initialize_SyncOn();
#endif

    BootstrapCode_Ext_SRAM();
    BootstrapCode_Ext_Flash();
}
}

#pragma arm section code
