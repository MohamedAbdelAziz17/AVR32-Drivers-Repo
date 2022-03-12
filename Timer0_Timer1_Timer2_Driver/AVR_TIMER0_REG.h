/*
 * TIMER0_CFG.h
 *
 *  Created on: Mar 29, 2021
 *      Author: m7mdAG
 */

#ifndef AVR_TIMER0_REG_H_
#define AVR_TIMER0_REG_H_

#define TCCR0 *((volatile uint8_t*)0x53)  // Timer counter control register
#define TCNT0 *((volatile uint8_t*)0x52)  // timer counter register
#define OCR0  *((volatile uint8_t*)0x5C)  // Output Compare Register
#define TIMSK *((volatile uint8_t*)0x59)  // Timer interrupt mask
#define TIFR  *((volatile uint8_t*)0x58)  // Timer interrupt flag register
#define SREG  *((volatile uint8_t*)0x5F)  // Status Register

// Bits of TCCR0 //
#define CS00  0U
#define CS01  1U
#define CS02  2U
#define WGM01 3U
#define COM00 4U
#define COM01 5U
#define WGM00 6U
#define FOC0  7U

// Bits of TIMSK //
#define TOIE0 0U
#define OCIE0 1U

// Bits of TIFR //
#define TOV0    0U
#define OCF0    1U


#endif /* AVR_TIMER0_REG_H_ */
