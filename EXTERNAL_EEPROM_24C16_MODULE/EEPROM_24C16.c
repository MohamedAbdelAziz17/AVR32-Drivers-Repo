/*
 * EEPROM_24C16.c
 *
 * Created: 3/5/2022 2:55:28 PM
 *  Author: m7mdAG
 */ 

#include "CPU_CONFIGURATION.h"
#include "TWI.h"
#include "EEPROM_24C16.h"

void HAL_EEPROM_WR (PAGE_ADDS u8DeviceAddress,uint8_t u8Address , uint8_t u8Data)
{
	MCAL_TWI_START_Condition();
	MCAL_TWI_Master_TRANSMIT_Address(u8DeviceAddress , WRITE);
	MCAL_TWI_Master_TRANSMIT_Data(u8Address);
	MCAL_TWI_Master_TRANSMIT_Data(u8Data);
	MCAL_TWI_STOP_Condition();
}

void HAL_EEPROM_RD (PAGE_ADDS u8DeviceAddress,uint8_t u8Address , uint8_t* u8Data)
{
	MCAL_TWI_START_Condition();
	MCAL_TWI_Master_TRANSMIT_Address(u8DeviceAddress , WRITE);
	MCAL_TWI_Master_TRANSMIT_Data(u8Address);
	
	MCAL_TWI_REPSTART_Condition();
	MCAL_TWI_Master_TRANSMIT_Address(u8DeviceAddress , READ);
	MCAL_TWI_Master_RECIEVE_Data(u8Data);
	MCAL_TWI_STOP_Condition();
}


