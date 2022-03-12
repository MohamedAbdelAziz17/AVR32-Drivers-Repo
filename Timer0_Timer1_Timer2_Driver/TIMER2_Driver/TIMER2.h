/*
 * TIMER2.h
 *
 * Created: 11/3/2021 6:26:59 PM
 *  Author: m7mdAG
 */ 


#ifndef TIMER2_H_
#define TIMER2_H_



#include "TIMER2_CONFIG.h"
/*Polling Mode*/
extern void MCAL_TIMER2_WITHOUT_INTERRUPT_Initialization(void);
extern void MCAL_TIMER2_WITHOUT_INTERRUPT_Set_Delay(uint32_t Delay, uint8_t ocr);
/*Interrupt Mode*/
extern void MCAL_TIMER2_WITH_INTERRUPT_Initialization(void);
extern void MCAL_TIMER2_WITH_INTERRUPT_Set_Delay(uint32_t Delay, uint8_t ocr);
/* Fast PWM */
extern void MCAL_TIMER2_FastPWM_Initialization(void);
extern void MCAL_TIMER2_FastPWM_Set_Duty(uint8_t Duty);
/* PhasePWM PWM */
extern void MCAL_TIMER2_PhasePWM_Initialization(void);
extern void MCAL_TIMER2_PhasePWM_Set_Duty(uint8_t desired_Duty);


#endif /* TIMER2_H_ */