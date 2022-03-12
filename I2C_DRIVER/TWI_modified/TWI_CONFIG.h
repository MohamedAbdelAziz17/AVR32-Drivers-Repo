


#ifndef TWI_CONFIG_H_
#define TWI_CONFIG_H_

#include "CPU_CONFIGURATION.h"

/*Register for two wire interface*/
/*
#define TWCR (*((volatile uint8*)0x56))
#define TWDR (*((volatile uint8*)0x23))
#define TWAR (*((volatile uint8*)0x22))
#define TWBR (*((volatile uint8*)0x20))
#define TWSR (*((volatile uint8*)0x21))
*/

/*	MASTER status codes	*/

#define START_CONDITION				0x08 // start has been sent

#define REP_START_CONDITION		    0x10 // repeated start

#define MASTER_TRNSM_SLAVE_WR_ACK	0x18 // "Slave address + WRITE" has been transmitted , ACK received

#define MASTER_TRNSM_SLAVE_WR_NACK  0x20

#define MASTER_TRNSM_SLAVE_RD_ACK	0x40 // "Slave address + READ" has been transmitted  , ACK received

#define MASTER_TRNSM_SLAVE_RD_NACK  0x20

#define WR_BYTE_ACK					0x28 // Master transmit data , ACK received

#define WR_BYTE_NACK				0x30

#define RD_BYTE_ACK				    0x50 // Master received data with ACK

#define RD_BYTE_NACK				0x58


/*	SLAVE status codes	*/

#define SLAVE_RECEIVED_WR_REQ    0x60 // SLAVE received "Slave address + WRITE" , ACK returned

#define SLAVE_RECEIVED_RD_REQ    0xA8 // SLAVE received "Slave address + READ"  , ACK returned

#define SLAVE_DATA_RECEIVED      0x80 // SLAVE received data	, ACK returned

#define SLAVE_BYTE_TRANSMITTED   0xB8 // SLAVE transmitted data	, ACK returned



#define SLAVE_ADDRESSED		0
#define SLAVE_NOT_ADDRESSED	1


typedef enum
{
	READ ,
	WRITE,
}RW;

#define TWI_PRESCALAR_1		 0
#define TWI_PRESCALAR_4		 1
#define TWI_PRESCALAR_16	 2
#define TWI_PRESCALAR_64	 3

#define TWI_MASTER_PRESCALAR	TWI_PRESCALAR_1	/*define TWPS*/

#define TWI_CLOCK_FREQ 100000		/*50khz*/	/*define SCL frequency*/


#endif /* TWI_CONFIG_H_ */

