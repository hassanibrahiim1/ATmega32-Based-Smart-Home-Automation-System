#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*RS -> 0*/
	DIO_voidSetPinVal(CTRL_PORT,RS,PIN_VAL_LOW);
	/*RW ->0 */
	DIO_voidSetPinVal(CTRL_PORT,RW,PIN_VAL_LOW);
	/*SET COMMAND TO THE REQUIRED PORT*/
	DIO_voidSetPortVal(DATA_PORT,Copy_u8Command);
	/*SET ENABLE PULSE*/
	DIO_voidSetPinVal(CTRL_PORT,EN,PIN_VAL_HIGH);
	_delay_ms(1);
	DIO_voidSetPinVal(CTRL_PORT,EN,PIN_VAL_LOW);
}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*RS -> 1*/
	DIO_voidSetPinVal(CTRL_PORT,RS,PIN_VAL_HIGH);
	/*RW ->0 */
	DIO_voidSetPinVal(CTRL_PORT,RW,PIN_VAL_LOW);
	/*SET data TO THE REQUIRED PORT*/
	DIO_voidSetPortVal(DATA_PORT,Copy_u8Data);
	/*SET ENABLE PULSE*/
	DIO_voidSetPinVal(CTRL_PORT,EN,PIN_VAL_HIGH);
	_delay_ms(1);
	DIO_voidSetPinVal(CTRL_PORT,EN,PIN_VAL_LOW);

}

void CLCD_voidInit(void)
{
	//Set Data Port As Output
	DIO_voidSetPortDir(DATA_PORT,PORT_DIR_OUT);
	//Set The First Three Pins of CTRL_PORT As OutPut
	DIO_voidSetPinDir(CTRL_PORT,PIN0,PIN_DIR_OUT);
	DIO_voidSetPinDir(CTRL_PORT,PIN1,PIN_DIR_OUT);
	DIO_voidSetPinDir(CTRL_PORT,PIN2,PIN_DIR_OUT);

	_delay_ms(40);
	CLCD_voidSendCommand(0b00111000);
	_delay_ms(1);
	CLCD_voidSendCommand(0b00001100);
	_delay_ms(1);
	CLCD_voidSendCommand(1);
	_delay_ms(2);

}

void CLCD_voidSendString(const char *ptr)
{
	u8 Local_u8Iterator=0;
	while(ptr[Local_u8Iterator]!='\0')
	{
		CLCD_voidSendData(ptr[Local_u8Iterator]);
		Local_u8Iterator++;
	}
}

void CLCD_voidSendPosition(u8 Copy_u8X,u8 Copy_u8Y)
{
	u8 Local_u8Position;
	if(Copy_u8X==0)
	{
		Local_u8Position=Copy_u8Y;
	}
	else if(Copy_u8X==1)
	{
		Local_u8Position=Copy_u8Y+0X40;
	}
	CLCD_voidSendCommand(Local_u8Position+128);


}

void CLCD_voidSendNum(u16 Copy_u16Num)
{
	u8 Local_u8Arr[10];
	u8 Local_u8Iterator1=0,Local_u8Iterator2;
	if(Copy_u16Num==0)
	{
		CLCD_voidSendData('0');
	}
	else
	{
		while(Copy_u16Num)
		{
			Local_u8Arr[Local_u8Iterator1]=Copy_u16Num%10 + '0';
			Copy_u16Num/=10;
			Local_u8Iterator1++;
		}
	}
	for(Local_u8Iterator2=Local_u8Iterator1;Local_u8Iterator2>0;Local_u8Iterator2--)
	{
		CLCD_voidSendData(Local_u8Arr[Local_u8Iterator2-1]);
	}

}
void CLCD_voidSendSpecialCharecter(u8 *ptr,u8 BlockNum,u8 Copy_u8X,u8 Copy_u8Y)
{
	//calculate the address to be written in in CGRAM
	u8 Local_u8Address=BlockNum*8;
	//SET THE CGRAM ADDRESS
	CLCD_voidSendCommand(Local_u8Address+64);
	//DRAW THE CHARECTER TO REQUIRED POSITION IN CGRAM
	for(u8 i=0;i<8;i++)
	{
		CLCD_voidSendData(ptr[i]);
	}
	//back to DDRAM
	CLCD_voidSendPosition(Copy_u8X,Copy_u8Y);
	//SEND DATA TO BE DISPLAYED
	CLCD_voidSendData(BlockNum);
}
void CLCD_voidDrawMan(void)
{
	u8 face[8] ={
			0b00001110,
			0b00010101,
			0b00011111,
			0b00011011,
			0b00001110,
			0b00000100,
			0b00011111,
			0b00001110,

	};
	u8 Lower_Body[8]= {
			0b00001110,
			0b00001110,
			0b00001110,
			0b00001010,
			0b00001010,
			0b00001010,
			0b00001010,
			0b00011011,

	};
	u8 Left_Hand[8] = {	0,0,0,0,4,2,1,0	};
	u8 Right_Hand[8] = {0,0,0,0,4,8,16,0};
	CLCD_voidSendSpecialCharecter(face,1,0,7);
	CLCD_voidSendSpecialCharecter(Lower_Body,2,1,7);
	CLCD_voidSendSpecialCharecter(Left_Hand,3,0,6);
	CLCD_voidSendSpecialCharecter(Right_Hand,4,0,8);


}
