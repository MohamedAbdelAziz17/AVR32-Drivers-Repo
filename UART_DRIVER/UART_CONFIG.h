


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#include "CPU_CONFIGURATION.h"
/*
#define UBRRL (*(volatile Uint8t*)(0x29))
#define UBRRH (*(volatile Uint8t*)(0x40))
#define UCSRA (*(volatile Uint8t*)(0x2B))
#define UCSRB (*(volatile Uint8t*)(0x29A)
#define UCSRC (*(volatile Uint8t*)(0x40))
#define UDR   (*(volatile Uint8t*)(0x2C))
*/
#define FRQ      160000

#define BAUDRATE 96
	
#define UART_polling 0

#define UART_interrupt 1

/*case of polling UART_init(null pointer)*/
/*case of interrupt UART_init(function address)*/
#define UART_running_mode	UART_polling

#endif /* UART_CONFIG_H_ */
