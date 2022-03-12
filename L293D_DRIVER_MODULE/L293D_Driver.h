/*
 * L293D_Driver.h
 *
 * Created: 9/14/2021 2:39:34 PM
 *  Author: m7mdAG
 */ 


#ifndef L293D_DRIVER_H_
#define L293D_DRIVER_H_

/************************************************************************/
/*                          USER DEFINED                                */
/************************************************************************/
#define motorDDR  DDRB
#define motorPort PORTB
#define motor1_IN1 0
#define motor1_IN2 1
#define motor2_IN3 2
#define motor2_IN4 3

#define enable_DDR	DDRB
#define enable_Port PORTB
#define enable1_pin	 4
#define enable2_pin  5

enum{
	motor1,
	motor2,
};
enum{
	cw,
	ccw,
	stop,
};
enum{
	right,
	left,
	backward,
	forward,
	STOP,
};
void HAL_L293D_Init(void);

void HAL_L293D(uint8_t motornumb,uint8_t direction);

void MotorDrive(uint8_t robotDir);


#endif /* L293D_DRIVER_H_ */