#pragma once

//----------------------------------------------------------------------------------------------------
//Micro

//The max endpoint number
#define MAX_ENDPOINT				3

//The max packet size
#define MAX_PACKET_SIZE			0x40

//The default client controller
#define DEFAULT_CONTROLLER		0



//mask defining which events has to be handled by the device application software 
#define IMR_MSK (CNTR_RESETM | CNTR_SUSPM | CNTR_WKUPM)

//Buffer table base address
#define BTABLE_ADDRESS      (0x00)

//EP0
//rx/tx buffer base address 
#define ENDP0_RXADDR        (0x40)
#define ENDP0_TXADDR        (0x80)


//EP1 
//rx/tx buffer base address 
#define ENDP1_RXADDR        (0xC0)
#define ENDP1_TXADDR        (0x100)

//EP2
//rx/tx buffer base address */
#define ENDP2_RXADDR        (0x140)
#define ENDP2_TXADDR        (0x180)
