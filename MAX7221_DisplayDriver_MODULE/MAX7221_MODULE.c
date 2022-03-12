/*
 * MAX7221_MODULE.c
 *
 * Created: 3/7/2022 5:55:14 PM
 *  Author: m7mdAG
 */ 

#include "CPU_CONFIGURATION.h"
#include "MAX7221_MODULE.h"

void HAL_MAX7221_Init()
{
	/*Normal Operation (TURN ON)*/
	MCAL_SPI_SS_ENABLE(0);
	MCAL_SPI_Transmit(0x0C);	/*ADDRESS*/
	MCAL_SPI_Transmit(0x01);	/*DATA*/
	MCAL_SPI_SS_DISABLE(0);
	
	/*Scan Limit*/
	MCAL_SPI_SS_ENABLE(0);
	MCAL_SPI_Transmit(0x0B);
	MCAL_SPI_Transmit(0x07);
	MCAL_SPI_SS_DISABLE(0);
	
	/*Decode Mode For Digits*/
	MCAL_SPI_SS_ENABLE(0);
	MCAL_SPI_Transmit(0x09);
	MCAL_SPI_Transmit(0xFF);
	MCAL_SPI_SS_DISABLE(0);
	
	/*Intensity*/
	MCAL_SPI_SS_ENABLE(0);
	MCAL_SPI_Transmit(0x0A);
	MCAL_SPI_Transmit(0x0C);
	MCAL_SPI_SS_DISABLE(0);
}



void HAL_MAX7221_DISPLAY(enumDigits _digit , uint8_t _number)
{
	MCAL_SPI_SS_ENABLE(0);
	MCAL_SPI_Transmit(_digit);	/*Digit1*/
	MCAL_SPI_Transmit(_number);	/*number  = 1*/
	MCAL_SPI_SS_DISABLE(0);
}