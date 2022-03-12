

#ifndef INT_INTERFACE_H_
#define INT_INTERFACE_H_

#define EXTINT_0   0
#define EXTINT_1   1
#define EXTINT_2   2

#define EXTINT_LOW_LEVEL 0
#define EXTINT_ON_CHANGE 1
#define EXTINT_FALLING_EDGE 2
#define EXTINT_RISING_EDGE 3



uint8_t   MCAL_EXTINT_u8Init(uint8_t Copy_EXTINT_No , uint8_t Copy_EXINT_LevelDetection);

uint8_t MCAL_EXTINT_u8SetCallBack(uint8_t Copy_EXTINT_No  , void (*Ptr_PointerToFunction)(void));


#endif /* INT_INTERFACE_H_ */
