

#ifndef CPU_CONFIGURATION_H_
#define CPU_CONFIGURATION_H_

#undef F_CPU /*Remove previous definition*/
#define F_CPU 16000000/*16 MegaHz(16 Million)*/
#include <avr/io.h> /*All registers are Pre-Defined here*/
#include <util/delay.h>
#include <avr/interrupt.h>
#include "BIT_MATH.h"
#endif /* CPU_CONFIGURATION_H_ */
