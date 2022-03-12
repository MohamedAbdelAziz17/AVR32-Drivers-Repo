
#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

#include "AVR_TIMER0_REG.h"

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

#define PRE_NOCLK    0
#define PRE_CLK8     1
#define PRE_CLK64    2
#define PRE_CLK256   3
#define PRE_CLK1024  4

// CHOOSE //
#define WAVE_GENERATION_MODE     PHASECORRECT_PWM_MODE

#define TIMER0_PRESCALER         PRE_CLK1024

#define PWM_MODE                 NON_INVERTING

#endif /* TIMER0_CONFIG_H_ */
