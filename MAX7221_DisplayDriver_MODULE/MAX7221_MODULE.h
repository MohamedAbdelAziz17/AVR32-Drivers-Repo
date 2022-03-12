/*
 * MAX7221_MODULE.h
 *
 * Created: 3/7/2022 5:54:40 PM
 *  Author: m7mdAG
 */ 


#ifndef MAX7221_MODULE_H_
#define MAX7221_MODULE_H_

typedef enum
{
	DIG0 = 0X01,
	DIG1 = 0X02,
	DIG2 = 0X03,
	DIG3 = 0X04,
	DIG4 = 0X05,
	DIG5 = 0X06,
	DIG6 = 0X07,
	DIG7 = 0X08,
	
}enumDigits;

void HAL_MAX7221_Init();

void HAL_MAX7221_DISPLAY(enumDigits _digit , uint8_t _number);




#endif /* MAX7221_MODULE_H_ */