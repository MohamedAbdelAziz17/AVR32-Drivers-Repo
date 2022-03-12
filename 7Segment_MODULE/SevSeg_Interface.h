/*
 * SevSeg_Interface.h
 *
 *  Created on: Mar 11, 2021
 *      Author: m7mdAG
 */

#ifndef SEVSEG_INTERFACE_H_
#define SEVSEG_INTERFACE_H_


void HAL_SevSegInit(uint8_t portnum, uint8_t bitnum);
void HAL_SevSegEnable(uint8_t portnum, uint8_t bitnum);
void HAL_SevSegDisable(uint8_t portnum, uint8_t bitnum);
void HAL_SevSegWrite(uint8_t DecoderStatment,uint8_t num,uint8_t port);

#endif /* SEVSEG_INTERFACE_H_ */
