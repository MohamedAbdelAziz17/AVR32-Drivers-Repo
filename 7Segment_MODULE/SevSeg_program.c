/*
 * SevSeg_program.c

 *
 *  Created on: Mar 11, 2021
 *      Author: m7mdAG
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "AVR_DIO_REG.h"
#include "SevSeg_Interface.h"
#include "DIO_interface.h"
		//******* Pins of 7Segment *******//
void HAL_SevSegInit(uint8_t portnum, uint8_t bitnum){
	switch(portnum){
	case DIO_PORTA :
			SET_BIT(DDRA,bitnum);
			break ;
		case DIO_PORTB :
			SET_BIT(DDRB,bitnum);
				break ;
		case DIO_PORTC :
			SET_BIT(DDRC,bitnum);
			break ;
		case DIO_PORTD :
			SET_BIT(DDRD,bitnum);
			break ;
	}
}
//******* Enable Pins of 7Segment *******//
void HAL_SevSegEnable(uint8_t portnum, uint8_t bitnum){
		switch(portnum){
		case DIO_PORTA :
				SET_BIT(DDRA,bitnum); //bit is "output"
				SET_BIT(PORTA,bitnum); // bit is "logic 1" (enabled)
				break ;
			case DIO_PORTB :
				SET_BIT(DDRB,bitnum);
				SET_BIT(PORTB,bitnum);
					break ;
			case DIO_PORTC :
				SET_BIT(DDRC,bitnum);
				SET_BIT(PORTC,bitnum);
				break ;
			case DIO_PORTD :
				SET_BIT(DDRD,bitnum);
				SET_BIT(PORTD,bitnum);
				break ;
		}
	}
//******* Disable Pins of 7Segment *******//
void HAL_SevSegDisable(uint8_t portnum, uint8_t bitnum){
		switch(portnum){
		case DIO_PORTA :
				CLR_BIT(PORTA,bitnum); // bit is logic 0 (disabled)
				break ;
			case DIO_PORTB :
				CLR_BIT(PORTB,bitnum);
					break ;
			case DIO_PORTC :
				CLR_BIT(PORTC,bitnum);
				break ;
			case DIO_PORTD :
				CLR_BIT(PORTD,bitnum);
				break ;
		}
	}
//******* Write Numbers on 7Segment *******//
void HAL_SevSegWrite(uint8_t DecoderStatment,uint8_t num,uint8_t port){
	if(DecoderStatment==1){
		// if you use BCD Decoder
		// code
		if(num<10 && num>=0){
		uint8_t arr[10]={0,1,2,3,4,5,6,7,8,9};
		MCAL_DIO_voidSetPortValue(port,(arr[num])<<4);
		}
	}
	else{
		// if you use regular 7 Segment
		//code
		if(num<10 && num>=0){
		uint8_t arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
		MCAL_DIO_voidSetPortValue(port,(arr[num])<<4);
		}
	}

}



