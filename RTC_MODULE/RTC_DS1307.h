/*
 * RTC_DS1307.h
 *
 * Created: 3/6/2022 12:08:41 PM
 *  Author: m7mdAG
 */ 


#ifndef RTC_DS1307_H_
#define RTC_DS1307_H_

typedef enum
{
	SECONDS,
	MINUTES,
	HOURS,
	DAY,
	DATE,
	MONTH,
	YEAR
}enumRTC_INFO;

#define RTC_Slave_ADDRESS	0xD0

#define RTC_SECONDS_ADDRESS 0x00
#define RTC_MINUTES_ADDRESS 0x01
#define RTC_Hours_ADDRESS	0x02
#define RTC_Day_ADDRESS		0x03
#define RTC_Date_ADDRESS	0x04
#define RTC_Month_ADDRESS	0x05
#define RTC_Year_ADDRESS	0x06


#define RTC_AM_				0x00
#define RTC_PM_				0x20

#define RTC_12_hour_MODE	0x40
#define RTC_24_hour_MODE	0x00

extern void HAL_RTC_Init();

static uint8_t HAL_RTC_RD_Seconds(void);
static uint8_t HAL_RTC_RD_Minutes(void);
static uint8_t HAL_RTC_RD_Hours(void);
static uint8_t HAL_RTC_RD_Day(void);
static uint8_t HAL_RTC_RD_Date(void);
static uint8_t HAL_RTC_RD_Month(void);
static uint8_t HAL_RTC_RD_Year(void);


extern uint8_t (*HAL_RTC_RD[7])(void);

extern void HAL_RTC_WR_CLOCK(uint8_t _hour, uint8_t _min, uint8_t _sec, uint8_t _AM_PM , uint8_t _12_24_hour);

extern uint8_t isPM();

extern void HAL_RTC_WR_CALENDER(uint8_t _year ,uint8_t _month , uint8_t _day);




#endif /* RTC_DS1307_H_ */