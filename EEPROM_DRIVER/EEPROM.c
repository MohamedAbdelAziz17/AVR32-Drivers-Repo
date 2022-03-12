/*
 * EEPROM.c
 *
 *  Created on: Jul 28, 2021
 *      Author: m7mdAG
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "CPU_CONFIGURATION.h"
#include "EEPROM.h"

//void __vector_17(void)__attribute((signal,used));
uint16_t g_address = 0;
uint8_t  g_data     = 0;
uint8_t func_check_wr = 0;
uint8_t func_check_rd = 0;

FUNCTION_ERROR MCAL_EEPROM_Write(uint16_t address, uint8_t data){
	if( address > 1023 )
	{
		return ERROR;
	}
	while(GET_BIT(EECR,EEWE) != 0);

	EEAR = address;
	
	EEDR = data;

	SET_BIT(EECR,EEMWE); /*Start Master Write enable*/
	
	SET_BIT(EECR,EEWE); /*Start Write enable*/
	
	_delay_us(2);
	
	return NO_ERROR;
}

uint8_t MCAL_EEPROM_Read(uint16_t address){
	
	if(address > 1023)
	{
		return ERROR;
	}
	
	while(GET_BIT(EECR,EEWE) != 0);

	EEAR = address;
	
	g_address = address;
	
	SET_BIT(EECR,EERE); /*Start Read enable*/
	
	_delay_ms(4);

	return EEDR;
}





/*
void __vector_17(void){

	if(func_check_wr){
		EEAR = 0x00;
		EEAR = g_address;
		EEDR = g_data;
		SET_BIT(EECR,EEMWE); //Start Master Write enable
		_delay_us(4);
		SET_BIT(EECR,EEWE); //Start Write enable
		func_check_wr = 0;
	}
}
*/
/*
  	while(EECR & (1<<EEWE));

 */

/*
while(EECR & (1<<EEWE));
EEAR = address;
SET_BIT(EECR,EERE); //Start Read enable
_delay_us(4);
return EEDR;
*/
