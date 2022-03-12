/*
 * RTC_DS1307.c
 *
 * Created: 3/6/2022 12:12:32 PM
 *  Author: m7mdAG
 */ 

#include "CPU_CONFIGURATION.h"
#include "TWI.h"
#include "RTC_DS1307.h"


uint8_t (*HAL_RTC_RD[7])(void) =
{
HAL_RTC_RD_Seconds,
HAL_RTC_RD_Minutes,
HAL_RTC_RD_Hours,
HAL_RTC_RD_Day,
HAL_RTC_RD_Date,
HAL_RTC_RD_Month,
HAL_RTC_RD_Year
};


void HAL_RTC_Init()
{
	MCAL_TWI_START_Condition();
	MCAL_TWI_Master_TRANSMIT_Address(RTC_Slave_ADDRESS , WRITE);
	MCAL_TWI_Master_TRANSMIT_Data(0x07);		/*move to this location*/
	MCAL_TWI_Master_TRANSMIT_Data(0x00);		/*set values to location 0x07 to 0*/
	MCAL_TWI_STOP_Condition();
}

static uint8_t HAL_RTC_RD_Seconds()
{
	uint8_t u8Data = 0;
	
	MCAL_TWI_START_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, WRITE); /*Device Address 0xD0*/
	
	MCAL_TWI_Master_TRANSMIT_Data(RTC_SECONDS_ADDRESS);		/*Seconds register*/
	
	MCAL_TWI_REPSTART_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, READ);
	
	MCAL_TWI_Master_RECIEVE_Data_NACK(&u8Data);
	
	MCAL_TWI_STOP_Condition();
	
	return u8Data;
}

static uint8_t HAL_RTC_RD_Minutes()
{
	uint8_t u8Data = 0;
	
	MCAL_TWI_START_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, WRITE); /*Device Address 0xD0*/
	
	MCAL_TWI_Master_TRANSMIT_Data(RTC_MINUTES_ADDRESS);		/*Minutes register*/
	
	MCAL_TWI_REPSTART_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, READ);
	
	MCAL_TWI_Master_RECIEVE_Data_NACK(&u8Data);
	
	MCAL_TWI_STOP_Condition();
	
	return u8Data;
}

static uint8_t HAL_RTC_RD_Hours()
{
	uint8_t u8Data = 0;
	
	MCAL_TWI_START_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, WRITE); /*Device Address 0xD0*/
	
	MCAL_TWI_Master_TRANSMIT_Data(RTC_Hours_ADDRESS);		/*Hour register*/
	
	MCAL_TWI_REPSTART_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, READ);
	
	MCAL_TWI_Master_RECIEVE_Data_NACK(&u8Data);
	
	MCAL_TWI_STOP_Condition();
	
	return (u8Data & 0x1F);
}

static uint8_t HAL_RTC_RD_Day()
{
	uint8_t u8Data = 0;
	
	MCAL_TWI_START_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, WRITE); /*Device Address 0xD0*/
	
	MCAL_TWI_Master_TRANSMIT_Data(RTC_Day_ADDRESS);		/*Day register*/
	
	MCAL_TWI_REPSTART_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, READ);
	
	MCAL_TWI_Master_RECIEVE_Data_NACK(&u8Data);
	
	MCAL_TWI_STOP_Condition();
	
	return u8Data;
}

static uint8_t HAL_RTC_RD_Date()
{
	uint8_t u8Data = 0;
	
	MCAL_TWI_START_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, WRITE); /*Device Address 0xD0*/
	
	MCAL_TWI_Master_TRANSMIT_Data(RTC_Date_ADDRESS);		/*Date register*/
	
	MCAL_TWI_REPSTART_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, READ);
	
	MCAL_TWI_Master_RECIEVE_Data_NACK(&u8Data);
	
	MCAL_TWI_STOP_Condition();
	
	return u8Data;
}

static uint8_t HAL_RTC_RD_Month()
{
	uint8_t u8Data = 0;
	
	MCAL_TWI_START_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, WRITE); /*Device Address 0xD0*/
	
	MCAL_TWI_Master_TRANSMIT_Data(RTC_Month_ADDRESS);		/*Month register*/
	
	MCAL_TWI_REPSTART_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, READ);
	
	MCAL_TWI_Master_RECIEVE_Data_NACK(&u8Data);
	
	MCAL_TWI_STOP_Condition();
	
	return u8Data;
}

static uint8_t HAL_RTC_RD_Year()
{
	uint8_t u8Data = 0;
	
	MCAL_TWI_START_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, WRITE); /*Device Address 0xD0*/
	
	MCAL_TWI_Master_TRANSMIT_Data(RTC_Year_ADDRESS);		/*Year register*/
	
	MCAL_TWI_REPSTART_Condition();
	
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, READ);
	
	MCAL_TWI_Master_RECIEVE_Data_NACK(&u8Data);
	
	MCAL_TWI_STOP_Condition();
	
	return u8Data;
}

void HAL_RTC_WR_CLOCK(uint8_t _hour, uint8_t _min, uint8_t _sec, uint8_t _AM_PM , uint8_t _12_24_hour)
{
	/*Values of parameters should be sent in hexadecimal*/
	
	_hour = _hour | (_AM_PM | _12_24_hour);
	
	MCAL_TWI_START_Condition();
	MCAL_TWI_Master_TRANSMIT_Address(RTC_Slave_ADDRESS , WRITE);
	MCAL_TWI_Master_TRANSMIT_Data(RTC_SECONDS_ADDRESS);		/*start at seconds register*/
	MCAL_TWI_Master_TRANSMIT_Data(_sec);					/*set seconds value*/
	MCAL_TWI_Master_TRANSMIT_Data(_min);					/*address increments, set min value*/
	MCAL_TWI_Master_TRANSMIT_Data(_hour);					/*address increments, set hour , am pm ,12 24 value*/
	MCAL_TWI_STOP_Condition();
}

uint8_t isPM()
{
	uint8_t u8Data = 0;
	
	MCAL_TWI_START_Condition();
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, WRITE); /*Device Address 0xD0*/
	MCAL_TWI_Master_TRANSMIT_Data(RTC_Hours_ADDRESS);		/*Hour register*/
	MCAL_TWI_REPSTART_Condition();
	MCAL_TWI_Master_TRANSMIT_Address(0xD0, READ);
	MCAL_TWI_Master_RECIEVE_Data_NACK(&u8Data);
	MCAL_TWI_STOP_Condition();
	return GET_BIT(u8Data , 5);
}

void HAL_RTC_WR_CALENDER(uint8_t _year ,uint8_t _month , uint8_t _day)
{
	MCAL_TWI_START_Condition();
	MCAL_TWI_Master_TRANSMIT_Address(RTC_Slave_ADDRESS , WRITE);
	MCAL_TWI_Master_TRANSMIT_Data(RTC_Date_ADDRESS);		/*start at seconds register*/
	MCAL_TWI_Master_TRANSMIT_Data(_day);					/*set seconds value*/
	MCAL_TWI_Master_TRANSMIT_Data(_month);					/*address increments, set min value*/
	MCAL_TWI_Master_TRANSMIT_Data(_year);					/*address increments, set hour , am pm ,12 24 value*/
	MCAL_TWI_STOP_Condition();
}

