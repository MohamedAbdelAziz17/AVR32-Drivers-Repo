/*
 * N5110_LCD.h
 *
 * Created: 3/6/2022 8:57:20 PM
 *  Author: m7mdAG
 */ 


#ifndef N5110_LCD_H_
#define N5110_LCD_H_

/*	NOTE:	ADJUST PRESCALAR of SPI to be SPR0 = 1 , SPR1 = 1  */


typedef enum
{
	/*0 <= y <= 5*/
	_y_0 = 0x40,
	_y_1 = 0x41,
	_y_2 = 0x42,
	_y_3 = 0x43,
	_y_5 = 0x45,
	
}N5110_x_coordination;

typedef enum
{
	/*0 <= x <= 83*/
	_x_0 = 0x80,
	_x_1 = 0x90,
	_x_2 = 0xA0,
	_x_3 = 0xB0,
	_x_5 = 0xC0,
	_x_6 = 0xD0,
	
}N5110_y_coordination;


/*ADJUSTABLE*/
#define N5110_RST_BIT	0
#define N5110_DC_BIT	1
#define N5110_PORT		DIO_PORTB

extern void HAL_N5110_Init();

extern void HAL_N5110_RESET();

extern void HAL_N5110_CMND(uint8_t u8Command);

extern void HAL_N5110_DATA(uint8_t* u8Data);

extern void HAL_N5110_SET_XY(N5110_x_coordination _x , N5110_y_coordination _y);

extern void HAL_N5110_CLEAR();




#endif /* N5110_LCD_H_ */