/*
 * motor.h
 *
 *  Created on: Oct 6, 2022
 *      Author: Ahmed Ashraf El-Sayed Bekheet
 */

#ifndef MOTOR_H_
#define MOTOR_H_
#include "std_types.h"

typedef enum
{
	STOP,CW,ACW
}DcMotor_State;


void DcMotor_Init(void);
void DcMotor_Rotate(const DcMotor_State state,uint8 speed);

#endif /* MOTOR_H_ */
