/*
 * DH11_SENSOR.h
 *
 * Created: 3/7/2022 1:03:53 PM
 *  Author: m7mdAG
 */ 


#ifndef DH11_SENSOR_H_
#define DH11_SENSOR_H_


#include "DIO_interface.h"

#define DH11_PORT_BIT	DIO_PORTC , 2

extern void HAL_DH11_START_SIGNAL();

extern void HAL_DH11_RESPONSE();

extern uint8_t HAL_DH11_RECEIVE_8BITS ();	/*DH11 will transmit 40 bits*/	
											

#endif /* DH11_SENSOR_H_ */