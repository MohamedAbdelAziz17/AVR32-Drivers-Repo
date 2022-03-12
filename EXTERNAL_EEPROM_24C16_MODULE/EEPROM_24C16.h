/*
 * EEPROM_24C16.h
 *
 * Created: 3/5/2022 2:54:34 PM
 *  Author: m7mdAG
 */ 


#ifndef EEPROM_24C16_H_
#define EEPROM_24C16_H_


/************************************************************************/
/*       Each Page has 8 bit address (2048 bytes of data)               */
/************************************************************************/

typedef enum
{
	EEPROM_PAGE1_ADDRESS = 0xA0,
	EEPROM_PAGE2_ADDRESS = 0xA2,
	EEPROM_PAGE3_ADDRESS = 0xA4,
	EEPROM_PAGE4_ADDRESS = 0xA6,
	EEPROM_PAGE5_ADDRESS = 0xA8,
	EEPROM_PAGE6_ADDRESS = 0xAA,
	EEPROM_PAGE7_ADDRESS = 0xAC,
	EEPROM_PAGE8_ADDRESS = 0xAE,
	
}PAGE_ADDS;


void HAL_EEPROM_WR (PAGE_ADDS u8DeviceAddress,uint8_t u8Address , uint8_t u8Data);

void HAL_EEPROM_RD (PAGE_ADDS u8DeviceAddress,uint8_t u8Address , uint8_t* u8Data);



#endif /* EEPROM_24C16_H_ */