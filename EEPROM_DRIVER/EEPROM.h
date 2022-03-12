/*
 * EEPROM.h
 *
 *  Created on: Jul 28, 2021
 *      Author: m7mdAG
 */

#ifndef EEPROM_H_
#define EEPROM_H_


typedef enum
{
	ERROR,
	NO_ERROR,
}FUNCTION_ERROR;

extern FUNCTION_ERROR MCAL_EEPROM_Write(uint16_t address, uint8_t data);	/*addresses must be between 0 to 1023*/

extern uint8_t MCAL_EEPROM_Read(uint16_t address);


#endif /* EEPROM_H_ */
