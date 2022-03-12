
#include "CPU_CONFIGURATION.h"
#include "STD_TYPES.h"
#include "TWI.h"
#include "math.h"


void MCAL_TWI_MASTER_Init(void)
{
#if TWI_MASTER_PRESCALAR == TWI_PRESCALAR_1
	
	CLR_BIT(TWSR , TWPS1); CLR_BIT(TWSR , TWPS0);
	
#elif TWI_MASTER_PRESCALAR == TWI_PRESCALAR_4

	CLR_BIT(TWSR , TWPS1); SET_BIT(TWSR , TWPS0);
	
#elif TWI_MASTER_PRESCALAR == TWI_PRESCALAR_16

	SET_BIT(TWSR , TWPS1); CLR_BIT(TWSR , TWPS0);
	
#elif TWI_MASTER_PRESCALAR == TWI_PRESCALAR_64

	SET_BIT(TWSR , TWPS1); SET_BIT(TWSR , TWPS0);
	
#endif
	
	TWBR = ( (F_CPU/TWI_CLOCK_FREQ) - 16)  / 2 * pow( 4 , (TWSR & 0x03) ) ;	/* equation to calculate bit rate to generate the user defined SCL*/
	
 	SET_BIT(TWCR, TWEN);/*Enable Two wire Interface*/

	CLR_BIT(TWCR , TWINT);

}

void MCAL_TWI_START_Condition(void)
{
	/*Send start condition*/
	TWCR=(1<<TWEN)	|	(1<<TWINT)	|	(1<<TWSTA);

	while(GET_BIT(TWCR, TWINT) == 0);/*wait for TWINT flag set*/
	
	while((TWSR & 0xF8) != START_CONDITION);/*CHECK STATUS to insure the start is done*/
	
	CLR_BIT(TWCR , TWINT);
}

void MCAL_TWI_REPSTART_Condition(void)
{
	/*Send start condition*/
	TWCR=(1<<TWEN)	|	(1<<TWINT)	|	(1<<TWSTA);

	while(GET_BIT(TWCR, TWINT) == 0);/*wait for TWINT flag set*/
	
	while((TWSR & 0xF8) != REP_START_CONDITION);/*CHECK STATUS to insure the start is done*/
	
	CLR_BIT(TWCR , TWINT);	
}

void MCAL_TWI_Master_TRANSMIT_Address(Uint8t address, RW readORwrite)
{
	if(readORwrite == READ)
	{
		SET_BIT(address , 0);	/*logic 1 --> read*/
	}
	else if(readORwrite == WRITE)
	{
		CLR_BIT(address , 0);	/*logic 0 --> write*/
	}
	
	TWDR = address;	/*LSB Bit must be 1 or 0 according to READ or WRITE operation*/
	
	TWCR = (1 << TWINT) | (1 << TWEN); /*Clear flag and enable the TWI to transmit address*/
	
	while(GET_BIT(TWCR, TWINT) == 0);/*wait for flag to set , indicates address is transmitted*/
	
	if(readORwrite == READ)
	{
		while((TWSR & 0xF8) != MASTER_TRNSM_SLAVE_RD_ACK);		/*address + read transmitted*/
	}
	else if(readORwrite == WRITE)
	{
		while((TWSR & 0xF8) != MASTER_TRNSM_SLAVE_WR_ACK);		/*address + write transmitted*/
	}

	
	CLR_BIT(TWCR , TWINT);
}

void MCAL_TWI_Master_TRANSMIT_Data(Uint8t data)
{
	/*AFTER SLA+W TRANSMITTED*/
	TWDR = data;
	
	TWCR = (1 << TWINT) | (1 << TWEN); /*Clear flag and enable the TWI to transmit data*/
 	
 	while(GET_BIT(TWCR, TWINT) == 0);/*wait for flag set*/
 	
 	while((TWSR & 0xF8) != WR_BYTE_ACK );	/*byte is transmitted*/
	
	CLR_BIT(TWCR , TWINT);
}

void MCAL_TWI_STOP_Condition(void)
{
	
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);	/*Transmit STOP condition*/
	
	CLR_BIT(TWCR , TWINT);
}



void MCAL_TWI_SLAVE_Init(uint8_t slaveAddress)
{
	TWAR = slaveAddress;/*set slave address*/
	
	CLR_BIT(TWAR, TWGCE); /*Disable general call*/

	TWCR = (1<< TWINT) | (1<<TWEN) | (1<<TWEA);
	
}

uint8_t MCAL_TWI_SLAVE_Available(void)
{
	if(GET_BIT(TWCR, TWINT) == 1)
	{
		return SLAVE_ADDRESSED;
	}
	else
	{
		return SLAVE_NOT_ADDRESSED;
	}
	
}

void MCAL_TWI_Slave_Listen()
{
	/*Wait to be addressed*/
	while(GET_BIT(TWCR, TWINT) == 0);
	
	/*send ACK*/
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	
	while((TWSR & 0xF8) != SLAVE_RECEIVED_WR_REQ );
	
	CLR_BIT(TWCR , TWINT);
}

void MCAL_TWI_SLAVE_RECIEVE_Data(uint8_t *recievedData)
{

	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);	/* SEND ACK */
	
	while(GET_BIT(TWCR, TWINT) == 0);
	
	while((TWSR & 0xF8) != SLAVE_DATA_RECEIVED);
	
	*recievedData = TWDR;
	
	CLR_BIT(TWCR , TWINT);

}

void MCAL_TWI_Master_RECIEVE_Data_ACK(Uint8t *data)
{
	/*AFTER SLA+R TRANSMITTED*/

	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);	/* SEND ACK */
	
	while(GET_BIT(TWCR, TWINT) != 0);
	
	while((TWSR & 0xF8) != RD_BYTE_ACK);
	
	*data= TWDR;

}
void MCAL_TWI_Master_RECIEVE_Data_NACK(uint8_t *data)
{
	/*AFTER SLA+R TRANSMITTED*/

	TWCR = (1<<TWEN)|(1<<TWINT);	/* SEND ACK */
	
	while(GET_BIT(TWCR, TWINT) != 0);
	
	while((TWSR & 0xF8) != RD_BYTE_NACK);
	
	*data= TWDR;	
}


void MCAL_TWI_SLAVE_TRANSMIT_Data(Uint8t *data)
{
	//AFTER ADDRESSED BY MASTER
	
	TWCR = (1 << TWINT) | (1 <<TWEN)|(1 <<TWEA);
	
	while(GET_BIT(TWCR, TWINT) != 0);/*When start condition finished*/
	
	while((TWSR & 0xF8)!=SLAVE_BYTE_TRANSMITTED);
	
	TWDR = *data;
}







