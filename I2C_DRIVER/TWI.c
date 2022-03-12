
#include "CPU_CONFIGURATION.h"
#include "TWI.h"

void TWI_MASTER_Init(void)
{
	TWSR=0x00; /*bits:0 0 dec(0) prescalar = 1*/
	TWBR = 152;/*Bit Rate of the clock to generate 50Khz*/
	SET_BIT(TWCR, TWEN);/*Enable Two wire Interface*/


}
void TWI_START_Condition(void)
{
	/*Enable Two wire Interface again*//*Hard set for flag waiting for dominant bit (0)clear flag*//*Start condition*/
	TWCR=(1<<TWEN)	|	(1<<TWINT)	|	(1<<TWSTA);

	while(GET_BIT(TWCR, TWINT) != 0);/*When start condition finished*/
	while((TWSR & 0x08) != 0x08);/*CHECK STATUS to insure the start is done*/
}
void TWI_Master_TRANSMIT_Address(Uint8t address,uint8_t readORwrite){
	TWDR = address;
	TWCR = (1 << TWINT) | (1 << TWEN); /*Clear flag and enable the TWI*/
	while(GET_BIT(TWCR, TWINT) != 0);/*When start condition finished*/
	if(readORwrite)
	while((TWSR & 0x40) != SLAVE_ADD_AND_RD_ACK);
	else
	while((TWSR & 0x18) != SLAVE_ADD_AND_WR_ACK);


}
void TWI_Master_TRANSMIT_Data(Uint8t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN); /*Clear flag and enable the TWI*/
	while(GET_BIT(TWCR, TWINT) != 0);/*When start condition finished*/
	while((TWSR & 0x28) != WR_BYTE_ACK);
}
void TWI_STOP_Condition(void)
{
	_delay_ms(5);
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

}
void TWI_SLAVE_Init(uint8_t slaveAddress)
{
	TWAR=slaveAddress;/*set slave address*/
	CLR_BIT(TWAR,TWGCE); /*Disable general call*/

	SET_BIT(TWCR, TWEN);/*Enable Two wire Interface*/
	SET_BIT(TWCR,TWEA); /*send ack*/
}

void TWI_Slave_wait(){
	/*Wait to be addressed*/
	while(GET_BIT(TWCR, TWINT) != 0);

}
uint8_t counter=0;
void TWI_SLAVE_RECIEVE_Data(uint8_t *recievedData){

if(TWAR == TWDR){
	counter^=1;
}

	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);

	while(GET_BIT(TWCR, TWINT) != 0);

	if(counter){
	*recievedData=TWDR;
	}
	else{
	}

}
void TWI_Master_RECIEVE_Data(Uint8t *data){
	//AFTER SEND SLA+R

	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	while(GET_BIT(TWCR, TWINT) != 0);
	while((TWSR & 0x50)!=0x50);
	*data= TWDR;

}
void TWI_SLAVE_TRANSMIT_Data(Uint8t *data)
{
	//AFTER ADDRESSED BY MASTER
	TWCR = (1 << TWINT) | (1 <<TWEN)|(1 <<TWEA);
	while(GET_BIT(TWCR, TWINT) != 0);/*When start condition finished*/
	while((TWSR & 0xA8)!=0xA8);
	TWDR = *data;
}







