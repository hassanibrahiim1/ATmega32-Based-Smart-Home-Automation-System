/*
 * UART_interface.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Hassan Ibrahim Hassan
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_VoidInit(void);
void UART_VoidTransmit(u8 Copy_u8Data);
u8 UART_U8Recieve(void);
void UART_VoidTransmitString(char * Copy_u8Ptr);
void UART_voidRecieveString(char*ReceivedString,u8 MAX_SIZE);
#endif /* UART_INTERFACE_H_ */
