

#ifndef KEYPAD_PROGRAM_C_
#define KEYPAD_PROGRAM_C_

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "Keypad_Cfg.h"
#include "Keypad_interface.h"



void HAL_Keypad_voidInit(void)
{
  uint8_t Local_RowLoop , Local_ColLoop ;

  for(Local_RowLoop = KEYPAD_ROW_START  ; Local_RowLoop <= KEYPAD_ROW_END ; Local_RowLoop ++)
  {
	  MCAL_DIO_voidSetPinDirection(KEYPAD_ROW_PORT , Local_RowLoop , DIO_INPUT);
	  MCAL_DIO_voidSetPinInputType(KEYPAD_ROW_PORT , Local_RowLoop , DIO_INPUT_INTERNAL_PULL_UP);
  }

  for(Local_ColLoop = KEYPAD_COL_START  ; Local_ColLoop <= KEYPAD_COL_END ; Local_ColLoop ++)
   {
 	  MCAL_DIO_voidSetPinDirection(KEYPAD_COL_PORT , Local_ColLoop , DIO_OUTPUT);
 	  MCAL_DIO_voidSetPinValue(KEYPAD_COL_PORT , Local_ColLoop , DIO_HIGH);
   }

}

void HAL_Keypad_voidGetPressedKey(uint8_t *ptr_PressedValue)
{
	 uint8_t Local_RowLoop , Local_ColLoop  , Local_Value = 1;

	 for(Local_RowLoop = KEYPAD_ROW_START  ; Local_RowLoop <= KEYPAD_ROW_END ; Local_RowLoop ++)
	 {
		 for(Local_ColLoop = KEYPAD_COL_START  ; Local_ColLoop <= KEYPAD_COL_END ; Local_ColLoop ++)
		 {
			 MCAL_DIO_voidSetPinValue(KEYPAD_COL_PORT , Local_ColLoop , DIO_LOW);

			 MCAL_DIO_voidGetPinValue(KEYPAD_ROW_PORT , Local_RowLoop , &Local_Value);

			 if(Local_Value == 0)
			 {
				 *ptr_PressedValue = Key_Matrix [Local_RowLoop - KEYPAD_ROW_START][Local_ColLoop - KEYPAD_COL_START];

				 while(Local_Value == 0)
				 {
					 MCAL_DIO_voidGetPinValue(KEYPAD_ROW_PORT , Local_RowLoop , &Local_Value);
				 }
			 }
			 MCAL_DIO_voidSetPinValue(KEYPAD_COL_PORT , Local_ColLoop , DIO_HIGH);
		 }

	 }

}

#endif /* KEYPAD_PROGRAM_C_ */
