/*
 * N5110_LCD.c
 *
 * Created: 3/6/2022 8:59:06 PM
 *  Author: m7mdAG
 */ 

#include "CPU_CONFIGURATION.h"
#include "DIO_interface.h"
#include "SPI.h"
#include "N5110_LCD.h"
#include "Font.h"


void HAL_N5110_RESET()
{
	MCAL_DIO_voidSetPinValue(N5110_PORT , N5110_RST_BIT , DIO_LOW);
	
	_delay_ms(50);
	
	MCAL_DIO_voidSetPinValue(N5110_PORT , N5110_RST_BIT , DIO_HIGH);
}

void HAL_N5110_CMND(uint8_t u8Command)
{
	MCAL_DIO_voidSetPinValue(N5110_PORT , N5110_DC_BIT , DIO_LOW); /*DC pin 0 to send command*/
	
	MCAL_SPI_SS_ENABLE(0);
	
	MCAL_SPI_Transmit(u8Command);
	
	MCAL_DIO_voidSetPinValue(N5110_PORT , N5110_DC_BIT , DIO_HIGH); /*DC pin 1 to send data*/
	
	MCAL_SPI_SS_DISABLE(0);
}

void HAL_N5110_Init()
{
	MCAL_DIO_voidSetPinDirection(N5110_PORT , N5110_RST_BIT , DIO_OUTPUT);
	MCAL_DIO_voidSetPinDirection(N5110_PORT , N5110_DC_BIT  , DIO_OUTPUT);
	
	HAL_N5110_RESET();					/*Reset*/
	HAL_N5110_CMND(0x21);			/* command set in addition mode */
	HAL_N5110_CMND(0xC0);			/* set the voltage by sending C0 means VOP = 5V */
	HAL_N5110_CMND(0x07);			/* set the temp. coefficient to 3 */
	HAL_N5110_CMND(0x13);			/* set value of Voltage Bias System */
	HAL_N5110_CMND(0x20);			/* command set in basic mode */
	HAL_N5110_CMND(0x0C);			/* display result in normal mode */
}

void HAL_N5110_DATA(uint8_t* u8Data)
{
	MCAL_DIO_voidSetPinValue(N5110_PORT , N5110_DC_BIT , DIO_HIGH); /*DC pin 1 to send data*/
	
	MCAL_SPI_SS_ENABLE(0);
	
	uint8_t data_size = strlen(u8Data);
	
	for(uint8_t i = 0 ; i < data_size ; i++ )
	{
		
		for ( uint8_t j = 0 ; j < 5 ; j++ )
		{
			MCAL_SPI_Transmit(ASCII[u8Data[i] - 0x20][j]);  /* send the data on data register */
		}
		
		MCAL_SPI_Transmit(0x00);
	}
	
	MCAL_SPI_SS_DISABLE(0);
}


void HAL_N5110_SET_XY(N5110_x_coordination _x , N5110_y_coordination _y)
{
	HAL_N5110_CMND(_x);
	HAL_N5110_CMND(_y);
}

void HAL_N5110_CLEAR()
{
	MCAL_SPI_SS_ENABLE(0);
	MCAL_DIO_voidSetPinValue(N5110_PORT , N5110_DC_BIT , DIO_HIGH);
	
	for (uint8_t i = 0 ; i <= 503 ; i++)
	{
		MCAL_SPI_Transmit(0x00);
	}
	
	MCAL_DIO_voidSetPinValue(N5110_PORT , N5110_DC_BIT , DIO_LOW);
	
	MCAL_SPI_SS_DISABLE(0);
}

