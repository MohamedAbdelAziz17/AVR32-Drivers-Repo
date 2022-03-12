/*
 * Watchdog_Timer.h
 *
 * Created: 3/4/2022 9:10:01 PM
 *  Author: m7mdAG
 */ 


#ifndef WATCHDOG_TIMER_H_
#define WATCHDOG_TIMER_H_

typedef enum
{
	WDT_TIMEOUT_16_3ms,
	WDT_TIMEOUT_32_5ms,
	WDT_TIMEOUT_65ms,
	WDT_TIMEOUT_0_13s,
	WDT_TIMEOUT_0_26s,
	WDT_TIMEOUT_0_52s,
	WDT_TIMEOUT_1_0s,
	WDT_TIMEOUT_2_1s,
	
}WDT_TIMEOUT_PERIOD;


extern void MCAL_WDT_ON(WDT_TIMEOUT_PERIOD WDT_TM);

extern inline void MCAL_WDT_RESET();

extern void MCAL_WDT_OFF();




#endif /* WATCHDOG_TIMER_H_ */