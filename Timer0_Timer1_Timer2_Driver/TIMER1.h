/*
 * TIMER1.h
 *
 *  Created on: Jul 24, 2021
 *      Author: m7mdAG
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "TIMER1_CONFIG.h"

extern void MCAL_TIMER1_Initialization(void);
extern void MCAL_TIMER1_Set_Delay(uint32_t Desired, uint8_t ocr,void (*ptrToFunction)(void));

extern void MCAL_TIMER1_FASTPWM_Init(void);
extern void MCAL_TIMER1_PhaseCorrect_Init(void);
extern void MCAL_TIMER1_Set_Duty(uint8_t desired_Duty,uint16_t desired_freq);


#endif /* TIMER1_H_ */
