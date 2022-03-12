
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "AVR_DIO_REG.h"
#include "TIMER0.h"
#include "DIO_interface.h"
#include <avr/interrupt.h>
#include "Common.h"




uint32_t Num_OVF = 0;
uint32_t Num_CTC = 0;
uint32_t Initial_Value = 0;  // used in ISR function

void (*g_ptr_to_func)(void) = NULL_PTR;

/*Polling Mode*/
void MCAL_TIMER0_WITHOUT_INTERRUPT_Initialization(void)
{
	#if WAVE_GENERATION_MODE == NORMAL_MODE
	CLR_BIT(TCCR0, WGM01);CLR_BIT(TCCR0, WGM00);
	#elif WAVE_GENERATION_MODE == CTC_MODE
	SET_BIT(TCCR0, WGM01);CLR_BIT(TCCR0, WGM00);
	#endif
	SET_BIT(TCCR0, CS02);CLR_BIT(TCCR0, CS01);SET_BIT(TCCR0, CS00);
}
void MCAL_TIMER0_WITHOUT_INTERRUPT_Set_Delay(uint32_t Delay, uint8_t ocr)
{
	#if WAVE_GENERATION_MODE == NORMAL_MODE
	uint32_t counter = 0;
	uint8_t Tick = PRESCALER / F_OSC;
	uint32_t Count = (Delay * MISECOND) / Tick;
	uint32_t OVF = Count / BITS;
	OVF++;
	uint32_t InitialValue = BITS - (Count % BITS);
	TCNT0 = InitialValue;
	/*Polling Mode*/
	while (counter != OVF)
	{
		/*Waiting flag after overflow*/
		while (GET_BIT(TIFR, TOV0) != 1);
		/*Re-initialize flag, down flag*/
		SET_BIT(TIFR, TOV0); // set 1 to down flag manually in polling
		counter++;
	}
	#elif WAVE_GENERATION_MODE == CTC_MODE
	uint32_t counter = 0;
	uint8_t Tick = PRESCALER / F_OSC;
	uint32_t Count = (Delay * MISECOND) / Tick;
	OCR0 = ocr;
	uint32_t CTC = Count / OCR0;
	CTC++;
	/*Polling Mode*/
	while (counter != CTC)
	{
		while (GET_BIT(TIFR, OCF0) != 1);
		SET_BIT(TIFR, OCF0);
		counter++;
	}
	#endif
	return;
}
/*Interrupt Mode*/
void MCAL_TIMER0_WITH_INTERRUPT_Initialization(void)
{
	
	#if WAVE_GENERATION_MODE == NORMAL_MODE
	CLR_BIT(TCCR0, WGM01);CLR_BIT(TCCR0, WGM00);
	
	/*Local Enable Interrupt*/
	SET_BIT(TIMSK, TOIE0);
	
	#elif WAVE_GENERATION_MODE == CTC_MODE
	SET_BIT(TCCR0, WGM01);CLR_BIT(TCCR0, WGM00);
	/*Enable Interrupt*/
	SET_BIT(TIMSK, OCIE0);
	#endif
	
	/*Prescaler set to 1024*/
	SET_BIT(TCCR0, CS02);CLR_BIT(TCCR0, CS01);SET_BIT(TCCR0, CS00);
	/*Enable Global Interrupt*/
	SET_BIT(SREG,7);
}
void MCAL_TIMER0_WITH_INTERRUPT_Set_Delay(uint32_t Delay, uint8_t ocr , void (*ptr_to_func)(void))
{
	g_ptr_to_func = ptr_to_func;	//set user's function as ISR
	
	#if WAVE_GENERATION_MODE == NORMAL_MODE
	
	uint8_t Tick = PRESCALER / F_OSC;
	
	uint32_t Counts = (Delay * MISECOND) / Tick;		//	us / us
	
	Num_OVF = Counts / BITS;	
	//Num_OVF = (Delay * MISECOND) / (Tick*BITS);
	
	Initial_Value = BITS - (Counts % BITS); //compensate counting the decimal value by pre-loading
	//Initial_Value = BITS - ((fmod(Num_OVF, 10)*BITS));
	
	TCNT0 = Initial_Value; // set data register to initial value
	
	Num_OVF++; // must increased by one because the decimal value
	
	
	#elif WAVE_GENERATION_MODE == CTC_MODE
	
	uint8_t Tick = PRESCALER / F_OSC;
	
	uint32_t Counts = (Delay * MISECOND) / Tick;
	
	OCR0 = ocr;
	
	Num_CTC = Counts / OCR0;
	
	Num_CTC++;
	
	#endif
}

ISR(TIMER0_OVF_vect)
{
#if WAVE_GENERATION_MODE == NORMAL_MODE
	static uint32_t desired_counts = 0;
	
	desired_counts++;
	
	if(desired_counts == Num_OVF && g_ptr_to_func != NULL_PTR)
	{
		(*g_ptr_to_func)();
		desired_counts = 0;
		TCNT0 = Initial_Value;
	}
	
#endif
}

ISR(TIMER0_COMP_vect)
{
#if WAVE_GENERATION_MODE == CTC_MODE

	static uint32_t desired_counts = 0;

	desired_counts++;

	
	if(desired_counts == Num_CTC && g_ptr_to_func != NULL_PTR)
	{
		(*g_ptr_to_func)();
		desired_counts = 0;
		TCNT0 = Initial_Value;
	}

#endif
}

void MCAL_TIMER0_FastPWM_Initialization(void)
{
	SET_BIT(DDRB,3);      // OC0 PIN output
	/*
	#if WAVE_GENERATION_MODE == FAST_PWM_MODE
	SET_BIT(TCCR0, WGM01);SET_BIT(TCCR0, WGM00);
	#if PWM_MODE == NON_INVERTING
	SET_BIT(TCCR0, COM01);CLR_BIT(TCCR0, COM00);
	#elif PWM_MODE == INVERTING
	SET_BIT(TCCR0, COM01);SET_BIT(TCCR0, COM00);
	#endif
	#elif WAVE_GENERATION_MODE == PHASECORRECT_PWM_MODE
	SET_BIT(TCCR0, WGM01);CLR_BIT(TCCR0, WGM00);
	#if PWM_MODE == NON_INVERTING
	SET_BIT(TCCR0, COM01);CLR_BIT(TCCR0, COM00);
	#elif PWM_MODE == INVERTING
	SET_BIT(TCCR0, COM01);SET_BIT(TCCR0, COM00);
	#endif
	#endif
	*/
	SET_BIT(TCCR0, WGM01);SET_BIT(TCCR0, WGM00);/*Choose Fast PWM*/
#if PWM_MODE == NON_INVERTING
	SET_BIT(TCCR0, COM01);CLR_BIT(TCCR0, COM00);/*Non- Inverting Mode*/
#elif PWM_MODE == INVERTING
	SET_BIT(TCCR0, COM01);SET_BIT(TCCR0, COM00);
#endif
	SET_BIT(TCCR0, CS02);CLR_BIT(TCCR0, CS01);CLR_BIT(TCCR0, CS00); /*Prescalar 1024*/
}

void MCAL_TIMER0_FastPWM_Set_Duty(uint8_t desired_Duty)
{
	
	if(desired_Duty > 100)
	{
		return;
	}
	
	#if PWM_MODE == NON_INVERTING
	
	OCR0 = ((BITS * desired_Duty) / 100) - 1;
	
	#elif PWM_MODE == INVERTING
	
	OCR0 = (BITS - 1) - (((BITS * desired_Duty) / 100) - 1);
	
	#endif
}

void MCAL_TIMER0_PhasePWM_Initialization(void){
	
		CLR_BIT(TCCR0, WGM01);SET_BIT(TCCR0, WGM00); // choose PhaseCorrectPWM
		
		#if PWM_MODE == NON_INVERTING
		SET_BIT(TCCR0, COM01);CLR_BIT(TCCR0, COM00);
		
		#elif PWM_MODE == INVERTING
		SET_BIT(TCCR0, COM01);SET_BIT(TCCR0, COM00);
		
		#endif
		
		#if TIMER0_PRESCALER == PRE_CLK1024       // choose prescalar
		TCCR0 = (TCCR0 & 0xF8) | 0x05;				// CS12 CS11 CS10
		#elif TIMER0_PRESCALER == PRE_CLK256
		TCCR0 = (TCCR0 & 0xF8) | 0x04;
		#elif TIMER0_PRESCALER == PRE_CLK64
		TCCR0 = (TCCR0 & 0xF8) | 0x03;
		#elif TIMER0_PRESCALER == PRE_CLK8
		TCCR0 = (TCCR0 & 0xF8) | 0x02;
		#elif TIMER0_PRESCALER == PRE_NOPRE
		TCCR0 = (TCCR0 & 0xF8) | 0x01;
		#endif
		
	
		MCAL_DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN_3,DIO_OUTPUT); // OC0 pin as output
		
}
void MCAL_TIMER0_PhasePWM_Set_Duty(uint8_t desired_Duty){
	
	if(desired_Duty > 100)
	{
		return;
	}
	
	
	
#if WAVE_GENERATION_MODE == NON_INVERTING
	
	OCR0 = ((desired_Duty * BITS) / 100) - 1;
	
#elif WAVE_GENERATION_MODE == INVERTING
	OCR0 = BITS - ((desired_Duty*BITS)/100) - 1;
	
#endif
	
}