/*
 * DH11_SENSOR.c
 *
 * Created: 3/7/2022 1:07:18 PM
 *  Author: m7mdAG
 */ 

#include "CPU_CONFIGURATION.h"
#include "DH11_SENSOR.h"

void HAL_DH11_START_SIGNAL()
{
	MCAL_DIO_voidSetPinDirection(DH11_PORT_BIT , DIO_OUTPUT);
	
	MCAL_DIO_voidSetPinValue(DH11_PORT_BIT , DIO_LOW);	/*start signal --> low - high*/
	_delay_ms(20);
	MCAL_DIO_voidSetPinValue(DH11_PORT_BIT , DIO_HIGH);
}

void HAL_DH11_RESPONSE()
{
	/*Response signal must be low - high - low*/
	
	MCAL_DIO_voidSetPinDirection(DH11_PORT_BIT , DIO_INPUT);
	
	_delay_us(40);
	
	uint8_t read_pin = 0;
	
	do
	{
		MCAL_DIO_voidGetPinValue(DH11_PORT_BIT , &read_pin);
		
	} while ( read_pin != 0 ) ;
	
	do
	{
		MCAL_DIO_voidGetPinValue(DH11_PORT_BIT , &read_pin);
		
	} while ( read_pin != 1 ) ;
	
	do
	{
		MCAL_DIO_voidGetPinValue(DH11_PORT_BIT , &read_pin);
		
	} while ( read_pin != 0 ) ;
	
}

uint8_t HAL_DH11_RECEIVE_8BITS ()
{
	uint8_t received_bits = 0;
	
	/*Check for 0 indication of transmission start*/
	uint8_t read_pin = 0;
	
	
	for(uint8_t bit = 0 ; bit < 8 ; bit++)
	{
		do
		{
			MCAL_DIO_voidGetPinValue(DH11_PORT_BIT , &read_pin);
			
		} while (read_pin != 1);
		
		/*wait 30us then check if data pin is high or low*/
		_delay_us(30);
		
		MCAL_DIO_voidGetPinValue(DH11_PORT_BIT , &read_pin);
		
		if(read_pin == 1)
		received_bits = (received_bits << 1) | 0x01;	/*bit = 1*/
		else
		received_bits = (received_bits << 1) | 0x00;	/*bit = 0*/
		
		do
		{
			MCAL_DIO_voidGetPinValue(DH11_PORT_BIT , &read_pin);
			
		} while (read_pin != 0);
	}
	
	return received_bits;
}
