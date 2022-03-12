
#include "UART.h"
#include "Common.h"


uint8_t g_recieved_data = 0;

void (*ptr_to_func)(uint8_t) = NULL_PTR ;

void MCAL_UART_Init( void (*local_ptr)(uint8_t) )
{
	
	/*Baud rate value variable*/
	uint16_t UBRR_Val = 0;
	
	/*Enable Transmitter and Receiver bits*/
	UCSRB = (1 << RXEN) | (1 << TXEN);
	
	/*Full configuration for UART*/
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	
	/*Baud Rate Calculations*/
	UBRR_Val = (((FRQ) / (16 * BAUDRATE)) - 1);
	
	UBRRL = UBRR_Val;
	
	UBRRH = UBRR_Val >> 8;
	
#if UART_running_mode == UART_interrupt

	/*enable global*/
	sei();
	
	/*local interrupt*/
	UCSRB |= (1 << RXCIE);
	
	/*set address of user function to global variable to use in ISR*/
	ptr_to_func = local_ptr;
	
#endif

}

void MCAL_UART_Transmit(uint8_t u8Data)
{
	while (! (UCSRA & (1<<UDRE)));  /* Wait for empty transmit buffer */
	
	UDR = u8Data;
	
	while (GET_BIT(UCSRA, TXC) != 1);
	
}

void MCAL_UART_Transmit_String(uint8_t* u8arr_ptr)
{
	uint8_t loop = 0;
	
	while(u8arr_ptr[loop] != NULL_CHAR)
	{
		MCAL_UART_Transmit(u8arr_ptr[loop]);
		loop++;
	}
}



uint8_t MCAL_UART_Receive_Char(void)
{
	while (GET_BIT(UCSRA, RXC) != 1);	/*wait till data recieved*/
	
	return UDR;
}

ISR(USART_RXC_vect)
{
	g_recieved_data = UDR;
	
	(*ptr_to_func)(g_recieved_data);
	
}

uint8_t Serial_available()
{
	return GET_BIT(UCSRA , RXC);
}

