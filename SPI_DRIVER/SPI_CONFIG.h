#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include "CPU_CONFIGURATION.h"
/*
#define SPCR (*(volatile Uint8t*)(0x2D))
#define SPSR (*(volatile Uint8t*)(0x2E))
#define SPDR (*(volatile Uint8t*)(0x2F))
*/



#define SS   4
#define MOSI 5
#define MISO 6
#define CLK  7


#define SPI_PORT DDRB

#define MASTER 1
#define SLAVE  0

#define SPI_MODE MASTER

#define SPI_interrupt 0 
#define SPI_polling 1 

#define SPI_run_mode	SPI_polling

#endif /* SPI_CONFIG_H_ */