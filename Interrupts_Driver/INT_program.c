
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Common.h"
#include "DIO_interface.h"
#include "AVR_INT_REG.h"
#include "INT_interface.h"


static void (*CallBack_INT0)(void ) = NULL_PTR ;
static void (*CallBack_INT1)(void ) = NULL_PTR ;
static void (*CallBack_INT2)(void ) = NULL_PTR ;

void __vector_1(void)__attribute((signal,used));
void __vector_2(void)__attribute((signal,used));
void __vector_3(void)__attribute((signal,used));

uint8_t  MCAL_EXTINT_u8Init(uint8_t Copy_EXTINT_No , uint8_t Copy_EXINT_LevelDetection)
{
	uint8_t Local_ErrorStatus = NO_ERROR ;

	switch(Copy_EXTINT_No)
	{
	case EXTINT_0 :
			switch(Copy_EXINT_LevelDetection)
			{
			case EXTINT_LOW_LEVEL :
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC00);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC01);
				break;
			case EXTINT_ON_CHANGE :
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC00);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC01);
				break;
			case EXTINT_FALLING_EDGE :
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC00);
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC01);
				break;
			case EXTINT_RISING_EDGE :
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC00);
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC01);
				break;
			default :
				Local_ErrorStatus = ERROR ;
				break;
			}

			if(Local_ErrorStatus == NO_ERROR)
			{
				SET_BIT(EXTINT_SREG , SREG_GLOBAL_ENABLE);
				SET_BIT(EXTINT_GICR , GICR_INT_0);
			}
		break ;
	case EXTINT_1 :
		    switch(Copy_EXINT_LevelDetection)
		    {
		    case EXTINT_LOW_LEVEL :
		    	CLR_BIT(EXTINT_MCUCR , MCUCR_ISC10);
		    	CLR_BIT(EXTINT_MCUCR , MCUCR_ISC11);
		    	break;
		    case EXTINT_ON_CHANGE :
		    	SET_BIT(EXTINT_MCUCR , MCUCR_ISC10);
		    	CLR_BIT(EXTINT_MCUCR , MCUCR_ISC11);
		    	break;
		    case EXTINT_FALLING_EDGE :
		    	CLR_BIT(EXTINT_MCUCR , MCUCR_ISC10);
		    	SET_BIT(EXTINT_MCUCR , MCUCR_ISC11);
		    	break;
		    case EXTINT_RISING_EDGE :
		    	SET_BIT(EXTINT_MCUCR , MCUCR_ISC10);
		    	SET_BIT(EXTINT_MCUCR , MCUCR_ISC11);
		    	break;
	        default :
		    	Local_ErrorStatus = ERROR ;
		    	break;
		    }

		    if(Local_ErrorStatus == NO_ERROR)
		    {
		    	SET_BIT(EXTINT_SREG , SREG_GLOBAL_ENABLE);
		    	SET_BIT(EXTINT_GICR , GICR_INT_1);
		    }
		break ;
	case EXTINT_2 :

		 switch(Copy_EXINT_LevelDetection)
		  {
		 	 case EXTINT_FALLING_EDGE :
				 CLR_BIT(EXTINT_MCUSCR , MCUSCR_ISC2);
				   break;
			case EXTINT_RISING_EDGE :
				 SET_BIT(EXTINT_MCUCR , MCUSCR_ISC2);
				    break;

		  }
		 if(Local_ErrorStatus == NO_ERROR)
		 {
			 SET_BIT(EXTINT_SREG , SREG_GLOBAL_ENABLE);
			 SET_BIT(EXTINT_GICR , GICR_INT_2);
		 }
		break ;
	default :
		Local_ErrorStatus = ERROR ;
		break;

	}

	return Local_ErrorStatus;
}

uint8_t MCAL_EXTINT_u8SetCallBack(uint8_t Copy_EXTINT_No  , void (*Ptr_PointerToFunction)(void))
{
	uint8_t Local_u8ErrorStatus = NO_ERROR;


	switch (Copy_EXTINT_No) {
		case EXTINT_0:

			CallBack_INT0 = Ptr_PointerToFunction ;
			break;
		case EXTINT_1:
			CallBack_INT1 = Ptr_PointerToFunction ;
			break;
		case EXTINT_2:
			CallBack_INT2 = Ptr_PointerToFunction ;
			break;
		default:
			break;
	}

	return Local_u8ErrorStatus;

}

void __vector_1(void)
{
	if(CallBack_INT0 != NULL_PTR)
	{
		CallBack_INT0();
	}
}

void __vector_2(void)
{
	if(CallBack_INT1 != NULL_PTR)
	{
		CallBack_INT1();
	}
}

void __vector_3(void)
{
	if(CallBack_INT2 != NULL_PTR)
	{
		CallBack_INT2();
	}
}

