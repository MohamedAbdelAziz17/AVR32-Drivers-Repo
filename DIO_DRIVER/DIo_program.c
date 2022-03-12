
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "AVR_DIO_REG.h"

#include "DIO_interface.h"

void MCAL_DIO_voidSetPortDirection(uint8_t Copy_u8PortNo  , uint8_t Copy_u8PortDirection)
{
	switch(Copy_u8PortNo)
		{
		case DIO_PORTA :
			DDRA = Copy_u8PortDirection ;
			break ;
		case DIO_PORTB :
			DDRB = Copy_u8PortDirection ;
				break ;
		case DIO_PORTC :
			DDRC = Copy_u8PortDirection ;
				break ;
		case DIO_PORTD :
			DDRD = Copy_u8PortDirection ;
				break ;

		}

}

void MCAL_DIO_voidSetPinDirection(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo , uint8_t Copy_u8PinDirection)
{
	switch(Copy_u8PortNo)
	{
	case DIO_PORTA :
		ASSIGN_BIT(DDRA , Copy_u8PinNo , Copy_u8PinDirection);
		break ;
	case DIO_PORTB :
		ASSIGN_BIT(DDRB , Copy_u8PinNo , Copy_u8PinDirection);
			break ;
	case DIO_PORTC :
		ASSIGN_BIT(DDRC , Copy_u8PinNo , Copy_u8PinDirection);
			break ;
	case DIO_PORTD :
		ASSIGN_BIT(DDRD , Copy_u8PinNo , Copy_u8PinDirection);
			break ;

	}
}

void MCAL_DIO_voidSetPortValue(uint8_t Copy_u8PortNo  , uint8_t Copy_u8PortValue)
{

	switch(Copy_u8PortNo)
	{
		case DIO_PORTA :
			PORTA = Copy_u8PortValue ;
		break ;
		case DIO_PORTB :
			PORTB = Copy_u8PortValue ;
		break ;
		case DIO_PORTC :
			PORTC = Copy_u8PortValue ;
		break ;
		case DIO_PORTD :
			PORTD = Copy_u8PortValue ;
		break ;

			}

}
void MCAL_DIO_voidSetPinValue(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo , uint8_t Copy_u8PinValue)
{
	switch(Copy_u8PortNo)
	{
		case DIO_PORTA :
			ASSIGN_BIT(PORTA , Copy_u8PinNo , Copy_u8PinValue);
		break ;
		case DIO_PORTB :
			ASSIGN_BIT(PORTB , Copy_u8PinNo , Copy_u8PinValue);
		break ;
		case DIO_PORTC :
			ASSIGN_BIT(PORTC , Copy_u8PinNo , Copy_u8PinValue);
		break ;
		case DIO_PORTD :
			ASSIGN_BIT(PORTD , Copy_u8PinNo , Copy_u8PinValue);
		break ;

			}


}

void MCAL_DIO_voidGetPortValue(uint8_t Copy_u8PortNo  , uint8_t *ptr_u8PortValue)
{
	switch(Copy_u8PortNo)
	{
		case DIO_PORTA :
			*ptr_u8PortValue = PINA ;
		break ;
		case DIO_PORTB :
			*ptr_u8PortValue = PINB ;
		break ;
		case DIO_PORTC :
			*ptr_u8PortValue = PINC ;
		break ;
		case DIO_PORTD :
			*ptr_u8PortValue = PIND ;
		break ;

	}

}
void MCAL_DIO_voidGetPinValue(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo , uint8_t *ptr_u8PortValue)
{
	switch(Copy_u8PortNo)
	{
		case DIO_PORTA :
			*ptr_u8PortValue = GET_BIT(PINA , Copy_u8PinNo);
		break ;
		case DIO_PORTB :
			*ptr_u8PortValue = GET_BIT(PINB , Copy_u8PinNo);
		break ;
		case DIO_PORTC :
			*ptr_u8PortValue = GET_BIT(PINC , Copy_u8PinNo);
		break ;
		case DIO_PORTD :
			*ptr_u8PortValue = GET_BIT(PIND , Copy_u8PinNo);
		break ;

	}

}

void MCAL_DIO_voidSetPortInputType(uint8_t Copy_u8PortNo  , uint8_t Copy_u8PortValue)
{

	switch(Copy_u8PortNo)
		{
			case DIO_PORTA :
				PORTA = Copy_u8PortValue ;
			break ;
			case DIO_PORTB :
				PORTB = Copy_u8PortValue ;
			break ;
			case DIO_PORTC :
				PORTC = Copy_u8PortValue ;
			break ;
			case DIO_PORTD :
				PORTD = Copy_u8PortValue ;
			break ;

				}

}
void MCAL_DIO_voidSetPinInputType(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo , uint8_t Copy_u8PinValue)
{
	switch(Copy_u8PortNo)
		{
			case DIO_PORTA :
				ASSIGN_BIT(PORTA , Copy_u8PinNo , Copy_u8PinValue);
			break ;
			case DIO_PORTB :
				ASSIGN_BIT(PORTB , Copy_u8PinNo , Copy_u8PinValue);
			break ;
			case DIO_PORTC :
				ASSIGN_BIT(PORTC , Copy_u8PinNo , Copy_u8PinValue);
			break ;
			case DIO_PORTD :
				ASSIGN_BIT(PORTD , Copy_u8PinNo , Copy_u8PinValue);
			break ;

				}
}


