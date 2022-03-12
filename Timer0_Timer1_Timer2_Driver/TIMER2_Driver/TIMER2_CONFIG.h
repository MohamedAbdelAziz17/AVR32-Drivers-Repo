/*
 * TIMER2_CONFIG.h
 *
 * Created: 11/3/2021 6:26:20 PM
 *  Author: m7mdAG
 */ 


#ifndef TIMER2_CONFIG_H_
#define TIMER2_CONFIG_H_



#include "CPU_CONFIGURATION.h"

#define F_OSC     16     // if 16000000 uint8_t would read it as zero
#define BITS      256
#define MISECOND  1000
#define PRESCALER 1024

#define NORMAL_MODE              0
#define PHASECORRECT_PWM_MODE    1
#define CTC_MODE                 2
#define FAST_PWM_MODE            3

#define INVERTING     0
#define NON_INVERTING 1

#define PRE_NOPRE    0
#define PRE_CLK8     1
#define PRE_CLK64    2
#define PRE_CLK256   3
#define PRE_CLK1024  4

// CHOOSE //
#define WAVE_GENERATION_MODE     FAST_PWM_MODE
#define TIMER1_PRESCALER         PRE_CLK1024
#define PWM_MODE                 NON_INVERTING




#endif /* TIMER2_CONFIG_H_ */