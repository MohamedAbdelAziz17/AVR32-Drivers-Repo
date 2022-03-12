/*
 * Ultrasonic_HC_SR04.h
 *
 * Created: 10/27/2021 4:55:20 PM
 *  Author: m7mdAG
 */ 


#ifndef ULTRASONIC_HC_SR04_H_
#define ULTRASONIC_HC_SR04_H_

#define trigger_port DIO_PORTA
#define trigger_pin	 0
#define echo_port	 DIO_PORTA
#define echo_pin	 1

void HAL_Ultrasonic_Init(void);

uint16_t HAL_Ultrasonic_ReadDistance(void);

#endif /* ULTRASONIC_HC-SR04_H_ */