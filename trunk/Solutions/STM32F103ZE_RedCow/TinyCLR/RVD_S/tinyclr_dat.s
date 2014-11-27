;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Copyright (c) Microsoft Corporation.  All rights reserved.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    AREA |.text|, CODE, READONLY

    ; has to keep it as ARM code, otherwise the the label TinyClr_Dat_Start and TinyClr_Dat_End are 1 word shift.

    ; ARM directive is only valid for ARM/THUMB processor, but not CORTEX 
    IF :DEF:COMPILE_ARM :LOR: :DEF:COMPILE_THUMB
    ARM
    ENDIF
    
    EXPORT  TinyClr_Dat_Start
    EXPORT  TinyClr_Dat_End

		;If you don't have the source code line ,the address of TinyClr_Dat_Start would be "%Data_BaseAddress% + 1",
		;when you call memcpy function which would cause the hard fault.
		;If you have "SPACE 0",the address of TinyClr_Dat_Start is  "%Data_BaseAddress%" which is right.
		;Be careful: %Data_BaseAddress% is defined in the scatterfile_tools_xx.XML file, and it must be 4 byte align
		SPACE 0 
		
TinyClr_Dat_Start
    INCBIN tinyclr.dat
TinyClr_Dat_End

    END
