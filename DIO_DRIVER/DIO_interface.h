

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3


#define DIO_PIN_0 0
#define DIO_PIN_1 1
#define DIO_PIN_2 2
#define DIO_PIN_3 3
#define DIO_PIN_4 4
#define DIO_PIN_5 5
#define DIO_PIN_6 6
#define DIO_PIN_7 7

#define DIO_INPUT 	0
#define DIO_OUTPUT  1

#define DIO_LOW 	0
#define DIO_HIGH  1

#define DIO_PORT_LOW 	0
#define DIO_PORT_HIGH  255

#define DIO_PORT_OUTPUT 255
#define DIO_PORT_INPUT 0

#define DIO_INPUT_FLOATING  0
#define DIO_INPUT_INTERNAL_PULL_UP  1

extern void MCAL_DIO_voidSetPortDirection(uint8_t Copy_u8PortNo  , uint8_t Copy_u8PortDirection);
extern void MCAL_DIO_voidSetPinDirection(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo , uint8_t Copy_u8PinDirection);

void MCAL_DIO_voidSetPortValue(uint8_t Copy_u8PortNo  , uint8_t Copy_u8PortValue);
void MCAL_DIO_voidSetPinValue(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo , uint8_t Copy_u8PinValue);

void MCAL_DIO_voidGetPortValue(uint8_t Copy_u8PortNo  , uint8_t *ptr_u8PortValue);
void MCAL_DIO_voidGetPinValue(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo , uint8_t *ptr_u8PortValue);

void MCAL_DIO_voidSetPortInputType(uint8_t Copy_u8PortNo  , uint8_t Copy_u8PortValue);
void MCAL_DIO_voidSetPinInputType(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo , uint8_t Copy_u8PinValue);


#endif /* DIO_INTERFACE_H_ */
