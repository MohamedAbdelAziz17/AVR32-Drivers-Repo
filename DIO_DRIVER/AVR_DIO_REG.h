
#ifndef AVR_DIO_REG_H_
#define AVR_DIO_REG_H_

/*__________________________________________________
 *                   PORTA :-
 * Create Pointer to write in Address of Registers
 *__________________________________________________
 ****************************************************/
#define DDRA *((volatile uint8_t*)0x3A)     //Data Direction Register (INPUT or OUTPUT)
#define PORTA *((volatile uint8_t*)0x3B)    //Write Value to OUTPU (HIGH or Low), in case INPUT(PULL UP or FLOATING)
#define PINA *((volatile uint8_t*)0x39)     //Read INPUT value Register


/*__________________________________________________
 *                   PORTB :-
 * Create Pointer to write in Address of Registers
 *__________________________________________________
 ****************************************************/
#define DDRB *((volatile uint8_t*)0x37)      //Data Direction Register (INPUT or OUTPUT)
#define PORTB *((volatile uint8_t*)0x38)     //Write Value to OUTPU (HIGH or Low), in case INPUT(PULL UP or FLOATING)
#define PINB *((volatile uint8_t*)0x36)      //Read INPUT value Register


/*__________________________________________________
 *                   PORTC :-
 * Create Pointer to write in Address of Registers
 *__________________________________________________
 ****************************************************/
#define DDRC *((volatile uint8_t*)0x34)      //Data Direction Register (INPUT or OUTPUT)
#define PORTC *((volatile uint8_t*)0x35)     //Write Value to OUTPU (HIGH or Low), in case INPUT(PULL UP or FLOATING)
#define PINC *((volatile uint8_t*)0x33)      //Read INPUT value Register


/*__________________________________________________
 *                   PORTD :-
 * Create Pointer to write in Address of Registers
 *__________________________________________________
 ****************************************************/
#define DDRD *((volatile uint8_t*)0x31)      //Data Direction Register (INPUT or OUTPUT)
#define PORTD *((volatile uint8_t*)0x32)     //Write Value to OUTPU (HIGH or Low), in case INPUT(PULL UP or FLOATING)
#define PIND *((volatile uint8_t*)0x30)      //Read INPUT value Register




#endif /* AVR_DIO_REG_H_ */
