
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Common.h"
#include "DIO_interface.h"
#include "LCD_Cfg.h"
#include "LCD_interface.h"
#include "CPU_CONFIGURATION.h"


#include "avr/delay.h"


static void HAL_LCD_voidWriteData(uint8_t Copy_u8Data);


void HAL_LCD_voidReadData(uint8_t *Copy_u8value){

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); /*Enable is low */

	MCAL_DIO_voidSetPinValue(LCD_RS_PIN , DIO_HIGH); /*0 write Command */

	MCAL_DIO_voidSetPinValue(LCD_RW_PIN , DIO_HIGH); /*0 read */
	_delay_ms(20);

    MCAL_DIO_voidGetPortValue(LCD_DATA_PORT,Copy_u8value);
    _delay_ms(20);
	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_HIGH); /*Enable is high */

	_delay_ms(20);

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); /*Enable is low */

}
void HAL_LCD_voidWriteCommand(uint8_t Copy_u8Command)
{
#if(LCD_BIT_MODE == MODE_8_BIT)


	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); //Enable is low

	MCAL_DIO_voidSetPinValue(LCD_RS_PIN , DIO_LOW); //0 write Command

	MCAL_DIO_voidSetPinValue(LCD_RW_PIN , DIO_LOW); //0 write

	MCAL_DIO_voidSetPortValue(LCD_DATA_PORT , Copy_u8Command);

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_HIGH); //Enable is high

	_delay_ms(2);

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); //Enable is low
	_delay_ms(2);

/* MAZIDI
	PORTD=Copy_u8Command;
	PORTC &= ~(1<<0);
	PORTC &= ~(1<<1);
	PORTC |= (1<<2);
	_delay_us(1);
	PORTC &= ~(1<<2);
	_delay_us(100);
	*/
#elif(LCD_BIT_MODE == MODE_4_BIT)

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); /*Enable is low */

	MCAL_DIO_voidSetPinValue(LCD_RS_PIN , DIO_LOW); /*0 write Command */

	MCAL_DIO_voidSetPinValue(LCD_RW_PIN , DIO_LOW); /*0 write */

	LCD_DATA_PORT_REG = (Copy_u8Command & 0xF0) | (LCD_DATA_PORT_REG & 0x0F) ;

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_HIGH); /*Enable is high */

	_delay_ms(2);

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); /*Enable is low */

	_delay_ms(2);

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); /*Enable is low */

	MCAL_DIO_voidSetPinValue(LCD_RS_PIN , DIO_LOW); /*0 write Command */

	MCAL_DIO_voidSetPinValue(LCD_RW_PIN , DIO_LOW); /*0 write */

	LCD_DATA_PORT_REG = (Copy_u8Command << 4) | (LCD_DATA_PORT_REG & 0x0F) ;

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_HIGH); /*Enable is high */

	_delay_ms(2);

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); /*Enable is low */

	_delay_ms(2);

#endif

}

void HAL_LCD_voidWriteData(uint8_t Copy_u8Data)
{
#if(LCD_BIT_MODE == MODE_8_BIT)

	MCAL_DIO_voidSetPortValue(LCD_DATA_PORT , Copy_u8Data);

	MCAL_DIO_voidSetPinValue(LCD_RS_PIN , DIO_HIGH); //1 for Data 0 for command

	MCAL_DIO_voidSetPinValue(LCD_RW_PIN , DIO_LOW); //0 to write


	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_HIGH); //Enable is high

	_delay_us(1);

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); //Enable is low
	_delay_us(100);

/*	Mazidi
	PORTD=Copy_u8Data;
	PORTC |= (1<<DIO_PIN_0);
	PORTC &= ~(1<<DIO_PIN_1);
	PORTC |= (1<<DIO_PIN_2);
	_delay_ms(2);
	PORTC &= ~(1<<DIO_PIN_2);
	_delay_us(100);
	*/
#elif(LCD_BIT_MODE == MODE_4_BIT)

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); /*Enable is low */

	MCAL_DIO_voidSetPinValue(LCD_RS_PIN , DIO_HIGH); /*0 write Command */

	MCAL_DIO_voidSetPinValue(LCD_RW_PIN , DIO_LOW); /*0 write */

	LCD_DATA_PORT_REG = (Copy_u8Data & 0xF0) | (LCD_DATA_PORT_REG & 0x0F) ;

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_HIGH); /*Enable is high */

	_delay_ms(2);

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); /*Enable is low */

	_delay_ms(2);

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); /*Enable is low */

	MCAL_DIO_voidSetPinValue(LCD_RS_PIN , DIO_HIGH); /*0 write Command */

	MCAL_DIO_voidSetPinValue(LCD_RW_PIN , DIO_LOW); /*0 write */

	LCD_DATA_PORT_REG = (Copy_u8Data << 4) | (LCD_DATA_PORT_REG & 0x0F) ;

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_HIGH); /*Enable is high */

	_delay_ms(2);

	MCAL_DIO_voidSetPinValue(LCD_E_PIN , DIO_LOW); /*Enable is low */

	_delay_ms(2);
#endif

}


void HAL_LCD_Init(void)
{
#if(LCD_BIT_MODE == MODE_8_BIT)

	MCAL_DIO_voidSetPinDirection(LCD_E_PIN , DIO_OUTPUT);
	MCAL_DIO_voidSetPinDirection(LCD_RS_PIN , DIO_OUTPUT);
	MCAL_DIO_voidSetPinDirection(LCD_RW_PIN , DIO_OUTPUT);

	MCAL_DIO_voidSetPortDirection(LCD_DATA_PORT , DIO_PORT_OUTPUT);


	HAL_LCD_voidWriteCommand(0x38); // 00(8bits or 4bits)(1 line or 2 lines)(font)00
	HAL_LCD_voidWriteCommand(0x0E); //0b00001DCB

	_delay_ms(2);

	HAL_LCD_voidWriteCommand(0b00000001);

	_delay_ms(2);

	HAL_LCD_voidWriteCommand(0x06);


	/* mazidi
	DDRD 	=0xFF;
	DDRC	=0xFF;

	PORTC &= ~(1<<DIO_PIN_2);
	_delay_ms(2);
	HAL_LCD_voidWriteCommand(0x38);
	HAL_LCD_voidWriteCommand(0x0E);
	HAL_LCD_voidWriteCommand(0x01);
	_delay_ms(2);
	HAL_LCD_voidWriteCommand(0x06);
*/
#elif(LCD_BIT_MODE == MODE_4_BIT)

	MCAL_DIO_voidSetPinDirection(LCD_E_PIN , DIO_OUTPUT);
	MCAL_DIO_voidSetPinDirection(LCD_RS_PIN , DIO_OUTPUT);
	MCAL_DIO_voidSetPinDirection(LCD_RW_PIN , DIO_OUTPUT);

	LCD_DATA_DIR_REG = (LCD_DATA_DIR_REG & 0x0F) | 0xF0 ;

	HAL_LCD_voidWriteCommand(0x33); //0b00(1100)00

	_delay_ms(2);

	HAL_LCD_voidWriteCommand(0x32);

	_delay_ms(2);

	HAL_LCD_voidWriteCommand(0b00101100);

	_delay_ms(2);

	HAL_LCD_voidWriteCommand(0b00001111);

	_delay_ms(2);

	HAL_LCD_voidWriteCommand(0b00000001);

	_delay_ms(2);


#endif

}

void HAL_LCD_voidClr(uint8_t Copy_u8Rowc , uint8_t Copy_u8Colc,uint8_t Copy_u8BacktoRow , uint8_t Copy_u8BacktoCol){
	HAL_LCD_voidMoveCursor(Copy_u8Rowc,Copy_u8Colc);
	HAL_LCD_voidWriteCharacter(7);
    HAL_LCD_voidMoveCursor(Copy_u8BacktoRow ,Copy_u8BacktoCol);

}
void HAL_LCD_voidWriteCharacter(uint8_t Copy_u8Character)
{
	HAL_LCD_voidWriteData(Copy_u8Character);
}

void HAL_LCD_voidWriteString(uint8_t arr[])
{
	uint8_t Loop = 0 ;

	while(arr[Loop] != NULL_CHAR)
	{
		HAL_LCD_voidWriteData(arr[Loop]);
		Loop++ ;
	}
}

void HAL_LCD_voidMoveCursor(uint8_t Copy_u8Row , uint8_t Copy_u8Col)
{
	/*if(Copy_u8Row == 0)
	{
		HAL_LCD_voidWriteCommand( 128 + Copy_u8Col);
	}
	else if(Copy_u8Row == 1)
	{
		HAL_LCD_voidWriteCommand( 128 + 0x40 + Copy_u8Col); //128 = 0x80 = 0b10000000
	}*/

	HAL_LCD_voidWriteCommand( 128 + (0x40 * Copy_u8Row) + Copy_u8Col);
}
void HAL_LCD_SpecialChar(uint8_t arr[] , uint8_t Copy_BlockNum ,  uint8_t Copy_Row , uint8_t Copy_Col)
{
	uint8_t Loop;

	HAL_LCD_voidWriteCommand(0x40+(0x08*Copy_BlockNum));
	for(Loop = 0 ; Loop < 8 ; Loop++)
	{
	HAL_LCD_voidWriteData(arr[Loop]);
	}


	HAL_LCD_voidMoveCursor(Copy_Row , Copy_Col);
}

void HAL_LCD_voidShiftCursorRight(uint8_t numofTimes,uint8_t Copy_u8Row){
	HAL_LCD_voidWriteCommand(0x80+(0x01*numofTimes)+(0x40 * Copy_u8Row));
}
void HAL_LCD_voidShiftCursorLeft(uint8_t numofTimes,uint8_t Copy_u8Row){
	HAL_LCD_voidWriteCommand(0x80-(0x01*numofTimes)+(0x40 * Copy_u8Row));
}


void HAL_LCD_voidWriteNumber(uint16_t number){
	uint8_t arr[10];
	uint8_t i=0;

	while(number!=0){
		arr[i+1]=number%10;
		i++;
		number/=10;
	}
	for(;i>0;i--){
		HAL_LCD_voidWriteCharacter(arr[i]+48);
	}

}
void HAL_LCD_DecimalNumber(float32_t number){
	// true part
	uint16_t temporaryNumber=(uint16_t)number;
	uint8_t arr[10];
	uint8_t i=0;
	if(temporaryNumber == 0)  //exception
		HAL_LCD_voidWriteCharacter('0');

	while(temporaryNumber!=0){
		arr[i+1]=temporaryNumber%10;
		i++;
		temporaryNumber/=10;
	}
	for(;i>0;i--){
		HAL_LCD_voidWriteCharacter(arr[i]+48);
	}

	// decimal part
	uint8_t tempNum;
	if(((uint16_t)((number-(uint16_t) number)*10)) == 0){ // exception for ex: 0.05

		HAL_LCD_voidWriteCharacter('.');
		HAL_LCD_voidWriteCharacter('0');

		tempNum = (number-(uint16_t) number)*100;

		uint8_t tempArray[3];
		uint8_t j=0;
		while(tempNum !=0)
			{
			tempArray[j+1]=tempNum%10;
			j++;
			tempNum/=10;
				}
		for(;j>0;j--)
			HAL_LCD_voidWriteCharacter(tempArray[j]+48);
	}
	else{
		HAL_LCD_voidWriteCharacter('.');
		tempNum = (number-(uint16_t) number)*100;
	uint8_t tempArray[3];
	uint8_t j=0;
	while(tempNum !=0)
		{
		tempArray[j+1]=tempNum%10;
		j++;
		tempNum/=10;
			}
	for(;j>0;j--)
		HAL_LCD_voidWriteCharacter(tempArray[j]+48);

	}

}

void HAL_LCD_printNumber(Uint32t number){
	Uint8t temp_array[10];
	ltoa(number, (Uint8t*)temp_array,10);
	HAL_LCD_voidWriteString(temp_array);
}
void HAL_LCD_clear(void){
	_delay_ms(1);
	HAL_LCD_voidWriteCommand(0x01);
}





