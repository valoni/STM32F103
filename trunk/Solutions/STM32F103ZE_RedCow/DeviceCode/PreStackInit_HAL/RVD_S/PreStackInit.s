;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Copyright (c) Microsoft Corporation.  All rights reserved.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    EXPORT  PreStackInit

    IMPORT  PreStackInit_Exit_Pointer
    IMPORT  ARM_Vectors

    PRESERVE8

    AREA SectionForBootstrapOperations, CODE, READONLY

    ENTRY

    ; ARM directive is only valid for ARM/THUMB processor, but not CORTEX 
    IF :DEF:COMPILE_ARM :LOR: :DEF:COMPILE_THUMB  
    ARM
    ENDIF    

PreStackInit


    ;*************************************************************************
    ;
    ; TODO: Enter your pre stack initialization code here (if needed)
    ;       e.g. SDRAM initialization if you don't have/use SRAM for the stack
    ;
    
    ;Initialize the SRAM
		; Enable FSMC clock
		LDR R0,= 0x00000114
		LDR R1,= 0x40021014
		STR R0,[R1]                  
                 
		; Enable GPIOD, GPIOE, GPIOF and GPIOG clocks
		LDR R0,= 0x000001E0
		LDR R1,= 0x40021018
		STR R0,[R1]      
 
		; SRAM Data lines, NOE and NWE configuration
		; SRAM Address lines configuration
		; NOE and NWE configuration  
		; NE3 configuration
		; NBL0, NBL1 configuration
 
		LDR R0,= 0x44BB44BB
		LDR R1,= 0x40011400
		STR R0,[R1]            
									
		LDR R0,= 0xBBBBBBBB
		LDR R1,= 0x40011404
		STR R0,[R1]            
									
		LDR R0,= 0xB44444BB
		LDR R1,= 0x40011800
		STR R0,[R1]            
 
		LDR R0,= 0xBBBBBBBB
		LDR R1,= 0x40011804
		STR R0,[R1]            
 
		LDR R0,= 0x44BBBBBB
		LDR R1,= 0x40011C00
		STR R0,[R1]       
 
		LDR R0,= 0xBBBB4444
		LDR R1,= 0x40011C04
		STR R0,[R1]       
 
		LDR R0,= 0x44BBBBBB
		LDR R1,= 0x40012000
		STR R0,[R1]            
 
		LDR R0,= 0x44444B44
		LDR R1,= 0x40012004
		STR R0,[R1]     
                                             
		; FSMC Configuration  
		; Enable FSMC Bank1_SRAM Bank
                  
		LDR R0,= 0x00001000
		LDR R1,= 0xA0000010
		STR R0,[R1]     
 
		LDR R0,= 0x00000200
		LDR R1,= 0xA0000014
		STR R0,[R1]     
				
		LDR R0,= 0x0FFFFFFF
		LDR R1,= 0xA0000114
		STR R0,[R1]     
				
		LDR R0,= 0x00001001
		LDR R1,= 0xA0000010
		STR R0,[R1]     
 					
     


    ;*************************************************************************
    ; DO NOT CHANGE THE FOLLOWING CODE! we can not use pop to return because we 
    ; loaded the PC register to get here (since the stack has not been initialized).  
    ; Make sure the PreStackInit_Exit_Pointer is within range and 
    ; in the SectionForBootstrapOperations
    ; go back to the firstentry(_loader) code 
    ;
    ;
PreStackEnd
    B     PreStackInit_Exit_Pointer

    ;
    ;**************************************************************************
    IF :DEF:COMPILE_THUMB  
    THUMB
    ENDIF   


    END


