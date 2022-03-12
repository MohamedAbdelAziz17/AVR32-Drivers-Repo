

#ifndef UART_H_
#define UART_H_

#include "UART_CONFIG.h"

void MCAL_UART_Init(void (*local_ptr)(uint8_t) );

void MCAL_UART_Transmit(uint8_t u8Data);

void MCAL_UART_Transmit_String(uint8_t* u8arr_ptr);

uint8_t MCAL_UART_Receive_Char(void);		/*return method*/
	
uint8_t Serial_available(void);

#endif /* UART_H_ */
