/*
 * Watchdog_Timer.c
 *
 * Created: 3/4/2022 9:11:40 PM
 *  Author: m7mdAG
 */ 

#include "Watchdog_Timer.h"
#include "CPU_CONFIGURATION.h"

void MCAL_WDT_ON(WDT_TIMEOUT_PERIOD WDT_TM)
{
	SET_BIT(WDTCR , WDE);
	
	WDTCR = (WDTCR & 0x18) | WDT_TM ;
}

inline void MCAL_WDT_RESET()
{
	asm("WDR");	/*	Resets the timer	*/
}


void MCAL_WDT_OFF()
{
	WDTCR = (1 << WDE) | (1 << WDTOE);
	
	WDTCR = 0x00;
}