/*
 * TIMER1.c
 *
 *  Created on: Jul 24, 2021
 *      Author: m7mdAG
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "AVR_DIO_REG.h"
#include "TIMER1.h"
#include "Common.h"

void (*g_TIMER1_ptrToFunction)(void)=NULL_PTR;
//void __vector_9(void)__attribute((signal,used)); //overflow interrupt
//void __vector_7(void)__attribute((signal,used)); //Compare match A
//void __vector_8(void)__attribute((signal,used)); //Compare match B
uint16_t g_NumOfOVF = 0;
uint16_t g_InitialValue=0;
uint8_t g_checkDesired=0;
void MCAL_TIMER1_Initialization(void){
	#if WAVE_GENERATION_MODE == NORMAL_MODE
		TCCR1A = (TCCR1A & 0xFC) | 0x00;
		TCCR1B = (TCCR1B & 0xE7) | 0x00;
		SET_BIT(TIMSK, TOIE1);
	#elif WAVE_GENERATION_MODE == CTC_MODE
		TCCR1A = (TCCR1A & 0xFC) | 0x00;
		TCCR1B = (TCCR1B & 0xE7) | 0x08;
		SET_BIT(TIMSK, OCIE1A);
		SET_BIT(TIMSK, OCIE1B);
	#endif

	// Prescaler
	#if TIMER1_PRESCALER == PRE_CLK1024
		TCCR1B = (TCCR1B & 0xF8) | 0x05;  // CS12 CS11 CS10
	#elif TIMER1_PRESCALER == PRE_CLK256
		TCCR1B = (TCCR1B & 0xF8) | 0x04;
	#elif TIMER1_PRESCALER == PRE_CLK64
		TCCR1B = (TCCR1B & 0xF8) | 0x03;
	#elif TIMER1_PRESCALER == PRE_CLK8
		TCCR1B = (TCCR1B & 0xF8) | 0x02;
	#elif TIMER1_PRESCALER == PRE_NOPRE
		TCCR1B = (TCCR1B & 0xF8) | 0x01;
	#endif
	/*Enable Global Interrupt*/
	SET_BIT(SREG,7);
}

void MCAL_TIMER1_Set_Delay(uint32_t Desired, uint8_t ocr,void (*ptrToFunction)(void)){
	g_TIMER1_ptrToFunction = ptrToFunction;

#if WAVE_GENERATION_MODE == NORMAL_MODE
	if(Desired <=4190){
		g_checkDesired=0;
		uint8_t  tick_time	= PRESCALER / F_OSC; //64 us .. 15625 Hz
		g_InitialValue 		= BITS-(Desired*MISECOND/tick_time);
		TCNT1 				= g_InitialValue;
	}
	else{
		g_checkDesired=1;
			uint8_t Tick = PRESCALER / F_OSC;
			uint32_t Counts =(Desired * MISECOND) / Tick;
			g_NumOfOVF = Counts / BITS;
			g_InitialValue = BITS - (Counts % BITS); //compensate counting the decimal value by pre-loading
			TCNT1 = g_InitialValue; // set data register to initial value
			g_NumOfOVF++; // must increased by one because the decimal value

	}
				 //NumOfOVF needed if we desired time exceeds 4.19s
				 // below 4.19s we should modify initial value each time
#elif WAVE_GENERATION_MODE == CTC_MODE
	uint8_t Tick = PRESCALER / F_OSC;
	g_InitialValue = (Desired*MISECOND)/Tick;
	OCR1A = g_InitialValue; // new TOP
#endif
}


void MCAL_TIMER1_FASTPWM_Init(void){
	SET_BIT(DDRD,5);SET_BIT(DDRD,4); // OCR1A OCR1B output
	TCCR1A = (TCCR1A & 0xFC) | 0x02; // choose PWM top OCR1A 0x03 top ICR1 0x02
	TCCR1B = (TCCR1B & 0xE7) | 0x18;

#if PWM_MODE == NON_INVERTING
	TCCR1A = (TCCR1A & 0x0F) | 0xA0;
#elif PWM_MODE == INVERTING
	TCCR1A = (TCCR1A & 0x0C) | 0xF0;
#endif

#if TIMER1_PRESCALER == PRE_CLK1024
	TCCR1B = (TCCR1B & 0xF8) | 0x05;  // CS12 CS11 CS10
#elif TIMER1_PRESCALER == PRE_CLK256
	TCCR1B = (TCCR1B & 0xF8) | 0x04;
#elif TIMER1_PRESCALER == PRE_CLK64
	TCCR1B = (TCCR1B & 0xF8) | 0x03;
#elif TIMER1_PRESCALER == PRE_CLK8
	TCCR1B = (TCCR1B & 0xF8) | 0x02;
#elif TIMER1_PRESCALER == PRE_NOPRE
	TCCR1B = (TCCR1B & 0xF8) | 0x01;
#endif

}
extern void MCAL_TIMER1_PhaseCorrect_Init(void){
	SET_BIT(DDRD,5);SET_BIT(DDRD,4); // OCR1A OCR1B output
	TCCR1A = (TCCR1A & 0xFC) | 0x00; // choose PhaseCorrect top ICR1
	TCCR1B = (TCCR1B & 0xE7) | 0x10;

#if PWM_MODE == NON_INVERTING
	TCCR1A = (TCCR1A & 0x0F) | 0xA0;
#elif PWM_MODE == INVERTING
	TCCR1A = (TCCR1A & 0x0C) | 0xF0;
#endif

#if TIMER1_PRESCALER == PRE_CLK1024
	TCCR1B = (TCCR1B & 0xF8) | 0x05;  // CS12 CS11 CS10
#elif TIMER1_PRESCALER == PRE_CLK256
	TCCR1B = (TCCR1B & 0xF8) | 0x04;
#elif TIMER1_PRESCALER == PRE_CLK64
	TCCR1B = (TCCR1B & 0xF8) | 0x03;
#elif TIMER1_PRESCALER == PRE_CLK8
	TCCR1B = (TCCR1B & 0xF8) | 0x02;
#elif TIMER1_PRESCALER == PRE_NOPRE
	TCCR1B = (TCCR1B & 0xF8) | 0x01;
#endif
}
void MCAL_TIMER1_Set_Duty(uint8_t desired_Duty,uint16_t desired_freq){
#if WAVE_GENERATION_MODE == FAST_PWM_MODE
	ICR1 = (((uint32_t)F_OSC*1000000)/((uint32_t)PRESCALER*desired_freq))-1; //equation from data sheet

	OCR1A = ((desired_Duty * ICR1) / 100) - 1; // ICR1 is top
//	OCR1B = ((desired_Duty * ICR1) / 100) - 1; // if wanted remove the //

#elif WAVE_GENERATION_MODE == PHASECORRECT_PWM_MODE
	ICR1 = (((uint32_t)F_OSC*1000000)/((uint32_t)PRESCALER*desired_freq*2))-1; //equation from data sheet

	OCR1A = ((desired_Duty * ICR1) / 100) - 1; // ICR1 is top
//	OCR1B = ((desired_Duty * ICR1) / 100) - 1; // if wanted remove the //
#endif
}


/*
//ISR happen each OverFlow
void __vector_9(void){
	static uint32_t ExecutionCounter1=0;

	if(g_checkDesired==0){
	g_TIMER1_ptrToFunction();
	TCNT1=g_InitialValue;
	}
	else{
		if(ExecutionCounter1 ==(g_NumOfOVF)){
			g_TIMER1_ptrToFunction();
			ExecutionCounter1= 0;
		}
		ExecutionCounter1++;
	}
}

//Compare match A

void __vector_7(void){

	g_TIMER1_ptrToFunction();
	OCR1A = g_InitialValue;

}
//Compare match B
void __vector_8(void){

}


*/





