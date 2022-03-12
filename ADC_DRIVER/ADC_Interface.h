/*
 * ADC_Interface.h
 *
 *  Created on: Mar 25, 2021
 *      Author: m7mdAG
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_DIO_PORT   DIO_PORTA

#define ADC_CHANNEL0   0U
#define ADC_CHANNEL1   1U
#define ADC_CHANNEL2   2U
#define ADC_CHANNEL3   3U
#define ADC_CHANNEL4   4U
#define ADC_CHANNEL5   5U
#define ADC_CHANNEL6   6U
#define ADC_CHANNEL7   7U


#define ADC_AREF_INTERNAL_VREF_OFF                  0U
#define ADC_AVCC_WITH_EXTERNAL_CAPACITORS_AT_VREF   1U
#define ADC_INTERNAL_2_56_VREF                      2U


#define ADC_INTERRUPT   1U
#define ADC_POLLING     2U

#define ADC_NO_AUTO_TRIGGER        8U  //CLEAR THIS IF DON'T WANT THESE FEATURES OR SET TO USE THE FEATURES
#define ADC_TURN_AUTO_TRIGGER	   3U
#define ADC_FREE_RUNNING_MODE      0U
#define ADC_ANALOG_COMPARATOR      1U
#define ADC_EXTERNAL_INT0_REQUEST  2U
#define ADC_TIMER0_OVERFLOW		   4U



#define ADC_PRESCALAR_2		1U
#define ADC_PRESCALAR_4		2U
#define ADC_PRESCALAR_8		3U
#define ADC_PRESCALAR_16	4U
#define ADC_PRESCALAR_32	5U
#define ADC_PRESCALAR_64	6U
#define ADC_PRESCALAR_128	7U

#define ADC_RESOLUTION8   0U
#define ADC_RESOLUTION10  1U
typedef struct{
	uint8_t u8REF_Select;
	uint8_t u8InterruptOrPolling;
	uint8_t u8AutoTriggerSource;
	uint8_t u8Prescalar;
	uint8_t u8Resolution;
}ADC_ConfigStr_t;


extern uint8_t MCAL_ADC_Init(ADC_ConfigStr_t *ADC_ConfigSt);

extern uint8_t MCAL_ADC_StartConversionBusyWait(uint8_t u8ADC_Channel , uint16_t* ptr_result);
extern uint8_t MCAL_ADC_StartConversionSetCallBackISR(uint8_t u8ADC_Channel , void (*ptr_FunctionADC)(uint16_t Copy_u16Result));




#endif /* ADC_INTERFACE_H_ */
