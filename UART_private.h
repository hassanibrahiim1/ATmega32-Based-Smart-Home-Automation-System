/*
 * UART_private.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Hassan Ibrahim Hassan
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_
/***************************************************/
//DATA REGISTER
#define	UDR	*((volatile u8*)0X2C)
/***************************************************/
//CONTROL AND STATUS REGISTERS
#define UCSRA	*((volatile u8*)0X2B)
#define UCSRA_RXC	7	//receive complete
#define UCSRA_UDRE	5	//UART DATA REGISTER EMPTY FLAG

#define UCSRB	*((volatile u8*)0X2A)
//SET THESE TWO BITS TO USE D0 & D1 as RX & TX
#define UCSRB_RXEN	4
#define UCSRB_TXEN	3
//CHARACTER SIZE THIRD BIT
#define UCSRB_UCSZ2	2

#define UCSRC	*((volatile u8*)0X40)
//REGISTER SELECET BIT (1 -> UCSRC) (0 -> UBRRH)
#define URSEL	7
//USART MODE SELECT [0 FOR ASYNCHRONOUS][1 FOR SYNCHRONOUS]
#define UCSRC_UMSEL	6
//STOP SECLECT BIT [0 -> 1 BIT] [1 -> 2 BIT]
#define UCSRC_USBS	3
//CHARACTER SIZE FIRST AND SECOND BIT
#define UCSRC_UCSZ1	2
#define UCSRC_UCSZ0	1
/***************************************************/
//BAUD RATE REGISTERS
#define UBRRL	*((volatile u8*)0X29)
#define UBRRH	*((volatile u8*)0X40)

#endif /* UART_PRIVATE_H_ */
