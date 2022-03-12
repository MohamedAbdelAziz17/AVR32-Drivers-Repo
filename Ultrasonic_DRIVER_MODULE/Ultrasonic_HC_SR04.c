/*
 * Ultrasonic_HC_SR04.c
 *
 * Created: 10/27/2021 4:58:42 PM
 *  Author: m7mdAG
 */ 

#include "STD_TYPES.h"
#include "AVR_DIO_REG.h"
#include "DIO_interface.h"
#include "Ultrasonic_HC_SR04.h"
#include "CPU_CONFIGURATION.h"
#include "LCD_interface.h"
#include <avr/interrupt.h>

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	// Increment Timer Overflow count
}

void HAL_Ultrasonic_Init(void){
	switch (trigger_port)
	{
		case DIO_PORTA:
			MCAL_DIO_voidSetPinDirection(DIO_PORTA,trigger_pin,DIO_OUTPUT);
			break;
		case DIO_PORTB:
			MCAL_DIO_voidSetPinDirection(DIO_PORTB,trigger_pin,DIO_OUTPUT);
			break;
		case DIO_PORTC:
		    MCAL_DIO_voidSetPinDirection(DIO_PORTC,trigger_pin,DIO_OUTPUT);
			break;
		case DIO_PORTD:
			MCAL_DIO_voidSetPinDirection(DIO_PORTD,trigger_pin,DIO_OUTPUT);
			break;
			default:break;
	}
	
	switch (echo_port)
	{
		case DIO_PORTA:
		MCAL_DIO_voidSetPinDirection(DIO_PORTA,echo_pin,DIO_INPUT);
		break;
		case DIO_PORTB:
		MCAL_DIO_voidSetPinDirection(DIO_PORTB,echo_pin,DIO_INPUT);
		break;
		case DIO_PORTC:
		MCAL_DIO_voidSetPinDirection(DIO_PORTC,echo_pin,DIO_INPUT);
		break;
		case DIO_PORTD:
		MCAL_DIO_voidSetPinDirection(DIO_PORTD,echo_pin,DIO_INPUT);
		break;
		default:break;
	}
	
	MCAL_DIO_voidSetPinValue(echo_port,echo_pin,DIO_HIGH);
	
	sei();			// Enable global interrupt
	TIMSK = (1 << TOIE1);	// Enable Timer1 overflow interrupts
	TCCR1A = 0;		// Set all bit to zero Normal operation

}

uint16_t HAL_Ultrasonic_ReadDistance(){
	
		MCAL_DIO_voidSetPinValue(trigger_port,trigger_pin,DIO_LOW);
		_delay_us(5);
	
		MCAL_DIO_voidSetPinValue(trigger_port,trigger_pin,DIO_HIGH);
		_delay_us(10);
		MCAL_DIO_voidSetPinValue(trigger_port,trigger_pin,DIO_LOW);
		/*
			TCCR1A = 0;
			
			TCNT1 = 0;
			TCCR1B = 0x41;			// capture on rise edge
			TIFR = (1<<ICF1);   	//clear flag
		
			HAL_LCD_printNumber(1);
			
			while((TIFR&(1<<ICF1))==0); // waiting first edge
			uint16_t firstEdge = ICR1;
			
			uint16_t TimerOverflow = 0;// Clear Timer overflow count 
				
			TCNT1 = 0;
			TCCR1B = 0x01;			// capture on fall edge
			TIFR = (1<<ICF1);   	//clear flag
			
			HAL_LCD_printNumber(2);
			
			while ((TIFR&(1<<ICF1))== 0); // waiting second edge
			
			long count = ICR1 + (65535 * TimerOverflow);
			uint16_t seconedEdge = ICR1;
			
			HAL_LCD_printNumber(3);
			
			uint16_t period = seconedEdge - firstEdge; // ticks
			Uint32t duration =  (count / 932.8);
			return duration;
			*/
			

			TCNT1 = 0;	 //Clear Timer counter 
			TCCR1B = 0x41;	// Capture on rising edge, No prescaler
			TIFR = 1<<ICF1;	// Clear ICP flag (Input Capture flag) 
			TIFR = 1<<TOV1;	// Clear Timer Overflow flag 

			//Calculate width of Echo by Input Capture (ICP) 

			while ((TIFR & (1 << ICF1)) == 0);// Wait for rising edge 
			TCNT1 = 0;	// Clear Timer counter 
			TCCR1B = 0x01;	// Capture on falling edge, No prescaler 
			TIFR = 1<<ICF1;	// Clear ICP flag (Input Capture flag) 
			TIFR = 1<<TOV1;	// Clear Timer Overflow flag 
			Uint16t TimerOverflow = 0;// Clear Timer overflow count 
			
			while ((TIFR & (1 << ICF1)) == 0);// Wait for falling edge 
			long count = ICR1 + (65535 * TimerOverflow);	// Take count 
			// 16MHz Timer freq, sound speed =343 m/s 
			long distance = (double)count / 932.8;
						return distance;
			
			
}