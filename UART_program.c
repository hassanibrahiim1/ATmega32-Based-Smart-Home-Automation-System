/*
 * UART_program.c
 *
 *  Created on: Dec 3, 2023
 *      Author: pc
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"


void UART_VoidInit(void)
{
	//ASYNCHRONOUS MODE
	//8 BIT CHARACTER SIZE
	UCSRC = 0b10000110;
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	//BAUD RATE 9600
	UBRRL = 51;
	//ENABLE PIN D0 & D1 AS RX & TX
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);

}
void UART_VoidTransmit(u8 Copy_u8Data)
{
	//POLLING ON UDRE (UART DATA REGISTER EMPTY)
	while(0 == (GET_BIT(UCSRA,UCSRA_UDRE)));
	UDR = Copy_u8Data;
}
u8 UART_U8Recieve(void)
{
	while(0 == (GET_BIT(UCSRA,UCSRA_RXC)));
	return UDR;
}
void UART_VoidTransmitString(char * Copy_u8Ptr)
{
	u8 i =0;
	while(Copy_u8Ptr[i] != '\0')
	{
		//POLLING ON UDRE (UART DATA REGISTER EMPTY)
		while(0 == (GET_BIT(UCSRA,UCSRA_UDRE)));
		UDR = Copy_u8Ptr[i];
		i++;

	}
}

void UART_voidRecieveString(char*ReceivedString,u8 MAX_SIZE)
{
	u8 i = 0;
	for(i=0 ; i<MAX_SIZE;i++)
	{
		ReceivedString[i] = UART_U8Recieve();
		if (ReceivedString[i] == '\r' || ReceivedString[i] == '\n') {
			// Terminate the string
			break;
		}
	}
	ReceivedString[i] = '\0';

}

