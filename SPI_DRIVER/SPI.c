#include "SPI.h"
#include "CPU_CONFIGURATION.h"
#include "STD_TYPES.h"
#include "Common.h"
#include "DIO_interface.h"


static volatile uint8_t g_data_recieve;

void (*g_ptr)(uint8_t data ) = NULL_PTR;



void MCAL_SPI_Init(void(*local_ptr)(uint8_t))
{
	
#if SPI_MODE == MASTER
	
	SET_BIT(SPI_PORT, MOSI);/*Define direction as output*/
	CLR_BIT(SPI_PORT, MISO);/*Define direction as input*/
	SET_BIT(SPI_PORT, CLK);/*Define direction as output*/
	SET_BIT(SPI_PORT, SS); /*Define direction as output*/
	
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR1) | (1<<SPR0);
	
#elif SPI_MODE == SLAVE
	
	MCAL_DIO_voidSetPinDirection(DIO_PORTB , MOSI , DIO_INPUT);
	
	MCAL_DIO_voidSetPinDirection(DIO_PORTB , MISO , DIO_OUTPUT);
	
	MCAL_DIO_voidSetPinDirection(DIO_PORTB , CLK , DIO_INPUT);

	MCAL_DIO_voidSetPinDirection(DIO_PORTB , SS , DIO_INPUT);
	
	SPCR = (1<<SPE);
	
	
#endif

#if SPI_run_mode == SPI_interrupt
		
	SET_BIT(SPCR , SPIE);
	
	sei();
	
	g_ptr = local_ptr;
	

#elif SPI_run_mode == SPI_polling

	g_ptr = NULL_PTR;
	
#endif
}



void MCAL_SPI_SS_ENABLE(uint8_t u8SlaveNumber)
{
	/*** Choose Slave ***/
	switch (u8SlaveNumber)
	{
		case 0:
		MCAL_DIO_voidSetPinValue(DIO_PORTB , SS , DIO_LOW);
		break;
		
		default: break;
	}
}

void	MCAL_SPI_SS_DISABLE(uint8_t u8SlaveNumber)
{
	/*** Choose Slave ***/
	switch (u8SlaveNumber)
	{
		case 0:
		MCAL_DIO_voidSetPinValue(DIO_PORTB , SS , DIO_HIGH);
		break;
		
		default: break;
	}
}

void MCAL_SPI_Transmit(Uint8t u8Data){
	
	/*** transmit data ***/
	#if SPI_run_mode == SPI_polling

	SPDR = u8Data;
	
	while(GET_BIT(SPSR , SPIF) != 1);
	
	#elif SPI_run_mode == SPI_interrupt
	
	SPDR = u8Data;
	
	#endif
}

Uint8t MCAL_SPI_Receive(void)
{
	/*Receive Data*/
	while(GET_BIT(SPSR,SPIF) != 1);
	
	g_data_recieve = SPDR;
	
	return g_data_recieve;
}



ISR(SPI_STC_vect){
	
#if SPI_MODE == MASTER

	MCAL_DIO_voidSetPinValue(DIO_PORTB , SS , DIO_HIGH);
	
	g_data_recieve = SPDR;
	

#elif SPI_MODE == SLAVE

	g_data_recieve = SPDR;

	(*g_ptr)(g_data_recieve);

#endif
}
