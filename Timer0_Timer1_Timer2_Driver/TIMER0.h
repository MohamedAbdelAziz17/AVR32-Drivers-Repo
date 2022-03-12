
#ifndef TIMER0_H_
#define TIMER0_H_

#include "TIMER0_CONFIG.h"
/*Polling Mode*/
extern void MCAL_TIMER0_WITHOUT_INTERRUPT_Initialization(void);
extern void MCAL_TIMER0_WITHOUT_INTERRUPT_Set_Delay(uint32_t Delay, uint8_t ocr );
/*Interrupt Mode*/
extern void MCAL_TIMER0_WITH_INTERRUPT_Initialization(void);
extern void MCAL_TIMER0_WITH_INTERRUPT_Set_Delay(uint32_t Delay, uint8_t ocr , void (*ptr_to_func)(void));
/* Fast PWM */
extern void MCAL_TIMER0_FastPWM_Initialization(void);
extern void MCAL_TIMER0_FastPWM_Set_Duty(uint8_t desired_Duty);
/* PhasePWM PWM */
extern void MCAL_TIMER0_PhasePWM_Initialization(void);
extern void MCAL_TIMER0_PhasePWM_Set_Duty(uint8_t desired_Duty);
#endif /* TIMER0_H_ */
