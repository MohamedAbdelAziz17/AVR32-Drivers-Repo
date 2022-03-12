/*
 * ADC_Program.c
 *
 *  Created on: Mar 25, 2021
 *      Author: m7mdAG
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Common.h"
#include "DIO_interface.h"
#include "AVR_ADC_REG.h"
#include "ADC_Interface.h"




void (*ADC_CallBack)(uint16_t Copy_u16Result)=NULL_PTR;
static uint8_t g_u8Resolution;
	   uint8_t g_u8ADC_Channel;
void __vector_16(void)__attribute((signal,used));

uint8_t MCAL_ADC_Init(ADC_ConfigStr_t *ADC_ConfigSt){
uint8_t Local_Error = NO_ERROR;

	switch (ADC_ConfigSt->u8REF_Select)
	{
		case ADC_AREF_INTERNAL_VREF_OFF:
			CLR_BIT(ADC_ADMUX,ADMUX_REFS0);
			CLR_BIT(ADC_ADMUX,ADMUX_REFS1);
			break;
		case ADC_AVCC_WITH_EXTERNAL_CAPACITORS_AT_VREF:
			SET_BIT(ADC_ADMUX,ADMUX_REFS0);
			CLR_BIT(ADC_ADMUX,ADMUX_REFS1);
			break;
		case ADC_INTERNAL_2_56_VREF:
			SET_BIT(ADC_ADMUX,ADMUX_REFS0);
			SET_BIT(ADC_ADMUX,ADMUX_REFS1);
			break;
		default:
			Local_Error= ERROR;
			break;
	}

	if(Local_Error==NO_ERROR){
	switch (ADC_ConfigSt->u8InterruptOrPolling) {
		case ADC_INTERRUPT:
			SET_BIT(ADC_ADCSRA,ADCSRA_ADIE); // set interrupt enable
			SET_BIT(ADC_SREG,7); // set global interrupt
			break;
		case ADC_POLLING:
			CLR_BIT(ADC_ADCSRA,ADCSRA_ADIE); // clear interrupt Enable
			break;

		default:
			Local_Error=ERROR;
			break;
	}
 }
	if(Local_Error==NO_ERROR){
		// auto trigger
	switch(ADC_ConfigSt->u8AutoTriggerSource){
		case ADC_NO_AUTO_TRIGGER:
			CLR_BIT(ADC_ADCSRA,ADCSRA_ADATE);
			break;
		case ADC_FREE_RUNNING_MODE:
			CLR_BIT(ADC_SFIOR,SFIOR_ADTS2);CLR_BIT(ADC_SFIOR,SFIOR_ADTS1);CLR_BIT(ADC_SFIOR,SFIOR_ADTS0);SET_BIT(ADC_ADCSRA,ADCSRA_ADATE);
			break;
		case ADC_EXTERNAL_INT0_REQUEST:
			CLR_BIT(ADC_SFIOR,SFIOR_ADTS2);SET_BIT(ADC_SFIOR,SFIOR_ADTS1);CLR_BIT(ADC_SFIOR,SFIOR_ADTS0);SET_BIT(ADC_ADCSRA,ADCSRA_ADATE);
			break;
		case ADC_TIMER0_OVERFLOW:
			SET_BIT(ADC_SFIOR,SFIOR_ADTS2);CLR_BIT(ADC_SFIOR,SFIOR_ADTS1);CLR_BIT(ADC_SFIOR,SFIOR_ADTS0);SET_BIT(ADC_ADCSRA,ADCSRA_ADATE);
			break;

		default:
			Local_Error=ERROR;
			break;
		}
	}

	if(Local_Error==NO_ERROR)
	{
		SET_BIT(ADC_ADCSRA,ADCSRA_ADEN); // enable the ADC
		SET_BIT(ADC_ADMUX,ADMUX_ADLAR); // work with left adjustment
		ADC_ADCSRA = (ADC_ADCSRA & 0xF8) | (ADC_ConfigSt->u8Prescalar); // choose prescalar
		g_u8Resolution=ADC_ConfigSt->u8Resolution; // choose resolution
		SET_BIT(ADC_ADCSRA,ADCSRA_ADIE); // enable
	}

	return Local_Error;
}

// start conversion with polling //
uint8_t MCAL_ADC_StartConversionBusyWait(uint8_t u8ADC_Channel , uint16_t* ptr_result){

	g_u8ADC_Channel=u8ADC_Channel;
	MCAL_DIO_voidSetPinDirection(ADC_DIO_PORT,u8ADC_Channel,DIO_INPUT);
	uint8_t Local_Error=NO_ERROR;

	ADC_ADMUX = ((ADC_ADMUX & 0xE0) | u8ADC_Channel); // choose channel

	SET_BIT(ADC_ADCSRA,ADCSRA_ADSC); // start conversion

	while((GET_BIT(ADC_ADCSRA, ADCSRA_ADIF))!=1); // keep in this loop until the flag equal 1 (polling)

	if(g_u8Resolution==ADC_RESOLUTION8){
		*ptr_result= ADC_ADCH;
	}

	else if(g_u8Resolution==ADC_RESOLUTION10){
		*ptr_result= ADC_ADCL>>6; // adhl read first

		*ptr_result |= ((uint16_t)ADC_ADCH<<2);
	}

	else{
		Local_Error= ERROR;
	}

return Local_Error;
}
// start conversion with interrupt //
uint8_t MCAL_ADC_StartConversionSetCallBackISR(uint8_t u8ADC_Channel , void (*ptr_FunctionADC)(uint16_t Copy_u16Result)){
	g_u8ADC_Channel=u8ADC_Channel;

	uint8_t Local_Error=NO_ERROR;
	MCAL_DIO_voidSetPinDirection(ADC_DIO_PORT,u8ADC_Channel,DIO_INPUT);

		ADC_ADMUX = ((ADC_ADMUX & 0xE0) | u8ADC_Channel); // choose channel
		SET_BIT(ADC_ADCSRA,ADCSRA_ADSC); // start conversion

		if(ptr_FunctionADC!=NULL_PTR){
		ADC_CallBack=ptr_FunctionADC;
		}
		else{
		Local_Error=ERROR;
		}

		return Local_Error;
}

void __vector_16(void)
{
	uint16_t local_result;

	if(g_u8Resolution==ADC_RESOLUTION8){
		local_result= ADC_ADCH;
	}
	else if(g_u8Resolution==ADC_RESOLUTION10){
		local_result= ADC_ADCL>>6 | (uint16_t)ADC_ADCH<<2;
	}

	if(ADC_CallBack!=NULL_PTR){
		ADC_CallBack(local_result);
	}
}

