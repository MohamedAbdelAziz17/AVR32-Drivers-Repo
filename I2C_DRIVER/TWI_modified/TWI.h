


#ifndef TWI_H_
#define TWI_H_

#include "TWI_CONFIG.h"

/*	MASTER	*/
void MCAL_TWI_MASTER_Init(void);

void MCAL_TWI_START_Condition(void);

void MCAL_TWI_REPSTART_Condition(void);

void MCAL_TWI_Master_TRANSMIT_Address(uint8_t address,RW readORwrite);

void MCAL_TWI_Master_TRANSMIT_Data(uint8_t data);
	
void MCAL_TWI_Master_RECIEVE_Data_ACK(uint8_t *data);
void MCAL_TWI_Master_RECIEVE_Data_NACK(uint8_t *data);

void MCAL_TWI_STOP_Condition(void);


/*	 SLAVE	 */
void MCAL_TWI_SLAVE_Init(uint8_t slaveAddress);

uint8_t MCAL_TWI_SLAVE_Available(void);

void MCAL_TWI_Slave_Listen(void);

void MCAL_TWI_SLAVE_RECIEVE_Data(uint8_t* recievedData);

void MCAL_TWI_SLAVE_TRANSMIT_Data(uint8_t *data);





/*
 slave transmit or receive operations always inside while loop */
/*
 master transmit can be inside while loop but receive not */





#endif /* TWI_H_ */
