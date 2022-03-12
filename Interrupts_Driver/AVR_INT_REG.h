

#ifndef AVR_INT_REG_H_
#define AVR_INT_REG_H_

#define EXTINT_SREG *((volatile uint8_t *) 0x5F)

#define EXTINT_MCUCR *((volatile uint8_t *) 0x55)

#define EXTINT_MCUSCR *((volatile uint8_t *) 0x54)

#define EXTINT_GICR *((volatile uint8_t *) 0x5B)

#define EXTINT_GIFR *((volatile uint8_t *) 0x5A)

/*Edge Detection INT0*/
#define MCUCR_ISC00 0
#define MCUCR_ISC01 1

/*Edge Detection INT1*/
#define MCUCR_ISC10 2
#define MCUCR_ISC11 3

/*Edge Detection INT2*/
#define MCUSCR_ISC2  6

/*Enable Interrupts*/
#define GICR_INT_0 6
#define GICR_INT_1 7
#define GICR_INT_2 5


/*Flag Interrupts*/
#define GIFR_INTF_0 6
#define GIFR_INTF_1 7
#define GIFR_INTF_2 5

#define SREG_GLOBAL_ENABLE 7

#endif /* AVR_INT_REG_H_ */
