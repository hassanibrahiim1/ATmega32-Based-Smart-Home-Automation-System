/*
 * Smart_Home_progarm.c
 *
 *  Created on: Dec 16, 2023
 *      Author: pc
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "CLCD_interface.h"
#include "DIO_interface.h"
#include "UART_interface.h"
#include "Smart_Home_interface.h"
#include <string.h>

#define MAX_STRINGLENGTH	10
#define NUMBER_OF_USERS	10


char Recieved_String[MAX_STRINGLENGTH];
u8 Recieved_Char;

typedef struct {
	char username[MAX_STRINGLENGTH];
	char password[MAX_STRINGLENGTH];
} User;
User users[] ={
				   {"Hassan","00000"},
				   {"Ibrahim","11111"},
				   {"Ahmed","22222"},
				   {"Mazen","33333"},
				   {"Ali","44444"},
				   {"Emad","55555"},
				   {"Youssef","66666"},
				   {"Salah","77777"},
				   {"Kareem","88888"},
				   {"Moataz","99999"},
				   {"Mohamed","12345"}
			  };
void main(void)
{
	//LED Control PINS
	DIO_voidSetPinDir(B,PIN0,PIN_DIR_OUT);
	DIO_voidSetPinVal(B,PIN0,PIN_VAL_HIGH);
	DIO_voidSetPinDir(B,PIN1,PIN_DIR_OUT);
	DIO_voidSetPinVal(B,PIN1,PIN_VAL_HIGH);
	DIO_voidSetPinDir(B,PIN2,PIN_DIR_OUT);
	DIO_voidSetPinVal(B,PIN2,PIN_VAL_HIGH);
	//BUZZER PIN
	DIO_voidSetPinDir(B,PIN3,PIN_DIR_OUT);
	DIO_voidSetPinVal(B,PIN3,PIN_VAL_LOW);

	//set TXD PIN as Output //set RXD PIN as Input
	DIO_voidSetPinDir(D,PIN0,PIN_DIR_IN);
	DIO_voidSetPinDir(D,PIN1,PIN_DIR_OUT);


	//Init LCD and UART
	UART_VoidInit();
	//start connection
	Login_System();
	//applications
	control_home();

	while(1)
	{




	}
}
/*void Start_message(void)
{
	u8 Start_connection ='s';
	//Wait for connection
	while(Start_connection != UART_U8Recieve() );
	//Start
	UART_VoidTransmitString("Hello to my SMART HOME\r");
	UART_VoidTransmitString("PLEASE ENTER USERNAME :\r");
	(void)UART_U8Recieve();

}
//return 1 when thief
//return 0 when password is correct*/
void Login_System(void)
{
	u8 Start_connection ='s';
	//Wait for connection
	while(Start_connection != UART_U8Recieve() );
	//Start
	UART_VoidTransmitString("Hello to my SMART HOME\r");
	UART_VoidTransmitString("PLEASE ENTER USERNAME :\r");
	(void)UART_U8Recieve();

	u8 THIEF_FLAG=0; //set when thief
	u8 try=0;
	//USERNAME

	while(try < 3)
	{
		try++;

		UART_voidRecieveString(Recieved_String,MAX_STRINGLENGTH);
		for(u8 i =0 ; i < NUMBER_OF_USERS; i++)
		{
			if (strcmp(users[i].username,Recieved_String) == 0)
			{
				//User is Found
				try=100;
				break;
			}
			else
			{
				//user not found
				UART_VoidTransmit("User not found\r");
			}
		}
	}
	if(try==3){
		/******************THIEF*********************/
		DIO_voidSetPinVal(B,PIN3,PIN_VAL_HIGH);
		UART_VoidTransmitString("Thief Detected\r");
		//RED LED
		DIO_voidSetPinVal(B,PIN0,PIN_VAL_LOW);
		DIO_voidSetPinVal(B,PIN1,PIN_VAL_HIGH);
		DIO_voidSetPinVal(B,PIN2,PIN_VAL_HIGH);
		THIEF_FLAG=1;
	}
	//Password
	try = 0;
	while(try < 3)
	{
		try++;
		UART_voidRecieveString(Recieved_String,MAX_STRINGLENGTH);
		if(strcmp(users[i].password,Recieved_String) == 0 )
		{
			//correct password
			UART_VoidTransmitString("HELLO ");
			UART_VoidTransmitString(users[i].username);

			break;
		}
		else
		{
			//incorrect password
			UART_VoidTransmit("incorrect password\r");
		}
	}
	if(try == 3)
	{
		DIO_voidSetPinVal(B,PIN3,PIN_VAL_HIGH);
		UART_VoidTransmitString("Thief Detected\r");
		//RED LED
		DIO_voidSetPinVal(B,PIN0,PIN_VAL_LOW);
		DIO_voidSetPinVal(B,PIN1,PIN_VAL_HIGH);
		DIO_voidSetPinVal(B,PIN2,PIN_VAL_HIGH);
		THIEF_FLAG=1;
	}
	while(THIEF_FLAG);

}
void control_home(void)
{
	UART_VoidTransmitString("Choose Subsystem Number to Control:\r");
	UART_VoidTransmitString("1)Door\r2)LCD\r3)LCD\r4)Servo Motor\r5)Back to User Login\r");
	Recieved_Char = UART_U8Recieve();
	switch (Recieved_Char) {
	case '1'://Door


		break;
	case '2'://LED
		UART_VoidTransmitString("a)Turn ON RED LED\rb)TURN ON BLUE\rc)TURN ON GREEN LED\rd)TURN OFF LED\re)Back to Subsytems Control\r");
		Recieved_Char = UART_U8Recieve();
		switch (Recieved_Char) {
		case 'a':
			//RED LED
			DIO_voidSetPinVal(B,PIN0,PIN_VAL_LOW);
			DIO_voidSetPinVal(B,PIN1,PIN_VAL_HIGH);
			DIO_voidSetPinVal(B,PIN2,PIN_VAL_HIGH);
			//SEND MESSAGE TO PHONE
			UART_VoidTransmitString("RED LED ON\r");
			//Buzzer
			DIO_voidSetPinVal(B,PIN3,PIN_VAL_HIGH);
			_delay_ms(10);
			DIO_voidSetPinVal(B,PIN3,PIN_VAL_LOW);
			break;
		case 'b':
			//BlUE LED
			DIO_voidSetPinVal(B,PIN2,PIN_VAL_LOW);
			DIO_voidSetPinVal(B,PIN1,PIN_VAL_HIGH);
			DIO_voidSetPinVal(B,PIN0,PIN_VAL_HIGH);
			//SEND MESSAGE TO PHONE
			UART_VoidTransmitString("BLUE LED ON\r");
			//Buzzer
			DIO_voidSetPinVal(B,PIN3,PIN_VAL_HIGH);
			_delay_ms(10);
			DIO_voidSetPinVal(B,PIN3,PIN_VAL_LOW);
			break;
		case 'c':

			//GREEN LED
			DIO_voidSetPinVal(B,PIN1,PIN_VAL_LOW);
			DIO_voidSetPinVal(B,PIN0,PIN_VAL_HIGH);
			DIO_voidSetPinVal(B,PIN2,PIN_VAL_HIGH);
			//SEND MESSAGE TO PHONE
			UART_VoidTransmitString("GREEN LED ON\r");
			//Buzzer
			DIO_voidSetPinVal(B,PIN3,PIN_VAL_HIGH);
			_delay_ms(10);
			DIO_voidSetPinVal(B,PIN3,PIN_VAL_LOW);
			break;
		case 'd':
			//turn off
			DIO_voidSetPinVal(B,PIN1,PIN_VAL_HIGH);
			DIO_voidSetPinVal(B,PIN0,PIN_VAL_HIGH);
			DIO_voidSetPinVal(B,PIN2,PIN_VAL_HIGH);
			UART_VoidTransmitString("LED OFF\r");
			break;
		case 'e':
			//back
			control_home();
			break;
		default:
			UART_VoidTransmitString("WRONG CHOICE\r");
			break;
		}
		break;
		case '3'://LCD

			break;
		case '4'://Servo

			break;
		case '5'://Back


			break;
		default:
			UART_VoidTransmitString("WRONG CHOICE !\r");
			break;
	}

}


