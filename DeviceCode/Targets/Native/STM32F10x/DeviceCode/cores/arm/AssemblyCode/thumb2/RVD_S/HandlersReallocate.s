;*****************************************************************************

; Export the handle function

	EXPORT  Vectors_Handler_Function 
	EXPORT  Vectors_Handler_Parameter
	
	
;*****************************************************************************
Vectors_Size	EQU		512

	AREA |.text|, DATA, READWRITE
	
Vectors_Handler_Function
	SPACE Vectors_Size
	
Vectors_Handler_Parameter
	SPACE Vectors_Size
	
;*****************************************************************************

	END