


#ifndef TWI_H_
#define TWI_H_

#include "TWI_CONFIG.h"


void TWI_MASTER_Init(void);
void TWI_START_Condition(void);
void TWI_Master_TRANSMIT_Address(Uint8t address,uint8_t readORwrite);
void TWI_Master_TRANSMIT_Data(Uint8t data);
void TWI_STOP_Condition(void);




void TWI_SLAVE_Init(uint8_t slaveAddress);
void TWI_Slave_wait(void);
void TWI_SLAVE_RECIEVE_Data(uint8_t* recievedData);


void TWI_Master_RECIEVE_Data(Uint8t *data);
void TWI_SLAVE_TRANSMIT_Data(Uint8t *data);

/*
 slave transmit or receive operations always inside while loop */
/*
 master transmit can be inside while loop but receive not */





#endif /* TWI_H_ */
