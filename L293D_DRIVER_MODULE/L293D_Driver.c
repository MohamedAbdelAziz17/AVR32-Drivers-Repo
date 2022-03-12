/*
 * L293D_Driver.c
 *
 * Created: 9/14/2021 2:40:38 PM
 *  Author: m7mdAG
 */ 
#include "CPU_CONFIGURATION.h"
#include "STD_TYPES.h"
#include "L293D_Driver.h"


void HAL_L293D_Init(){
	motorDDR	|= (1<<motor1_IN1) | (1<<motor1_IN2) | (1<<motor2_IN3) | (1<<motor2_IN4);  //IN1,2,3,4 output
	enable_DDR	|= (1<<enable1_pin) | (1<<enable2_pin); // en1,en2 output
}

void HAL_L293D(uint8_t motornumb,uint8_t direction){
	switch(motornumb){
		case motor1:
		switch(direction){
			case ccw:
			enable_Port |= (1<<enable1_pin);
			//motorPort = (motorPort&0xFC)| (1<<motor1_IN1); // bitmask
			motorPort |= (1<<motor1_IN1);
			break;
			case cw:
			enable_Port |= (1<<enable1_pin);
			//motorPort = (motorPort&0xFC)| (1<<motor1_IN2);
			motorPort |= (1<<motor1_IN2);
			break;
			case stop:
			enable_Port &= ~(1<<enable1_pin);
			break;
		}
		break;

		case motor2:
		switch(direction){
			case ccw:
			enable_Port |= (1<<enable2_pin);
			//motorPort = (motorPort&0xF3)|(1<<motor2_IN3);
			motorPort |= (1<<motor2_IN3);
			break;
			case cw:
			enable_Port |= (1<<enable2_pin);
			//motorPort = (motorPort&0xF3)|(1<<motor2_IN4);
			motorPort |= (1<<motor2_IN4);
			break;
			case stop:
			enable_Port &= ~(1<<enable2_pin);
			break;
		}
		break;

		default:	break;
	}
}
/************************************************************************/
/*	If a robot made of 2 motors exists so use this function             */
/************************************************************************/
void MotorDrive(uint8_t robotDir){
	switch(robotDir){
		case forward:
		HAL_L293D(motor1,cw);		HAL_L293D(motor2,cw);
		break;
		
		case backward:
		HAL_L293D(motor1,ccw);		HAL_L293D(motor2,ccw);
		break;
		
		case STOP:
		HAL_L293D(motor1,stop);		HAL_L293D(motor2,stop);
		break;
		
		case right:
		HAL_L293D(motor1,cw);		HAL_L293D(motor2,stop);
		break;
		
		case left:
		HAL_L293D(motor1,stop);		HAL_L293D(motor2,cw);
		break;

		default:	break;
	}
}










		/*case motor3:
		switch(direction){
			case ccw:
			motorPort = (motorPort&0xCF)| (1<<4);
			break;
			case cw:
			motorPort = (motorPort&0xCF)| (1<<5);
			break;
			case stop:
			motorPort = (motorPort&0xCF)| 0;
			break;
		}
		break;*/
		/*case motor4:
		switch(direction){
			case ccw:
			motorPort = (motorPort&0x3F)| (1<<6);
			break;
			case cw:
			motorPort = (motorPort&0x3F)| (1<<7);
			break;
			case stop:
			motorPort = (motorPort&0x3F)| 0;
			break;
		}*/