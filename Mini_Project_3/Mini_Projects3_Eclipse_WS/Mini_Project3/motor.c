/*
 * motor.c
 *
 *  Created on: Oct 6, 2022
 *      Author: Ahmed Ashraf El-Sayed Bekheet
 */

/*
 * Description :
 *Implement DC Motor Driver
 */

#include "gpio.h"
#include "pwm.h"
#include "motor.h"

void DcMotor_Init(void){

	/* PIN 0,1,3 in PORTB is output pins*/
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID ,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID ,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID ,PIN_OUTPUT);

	/* STOP DC Motor at the beginning*/
	GPIO_writePort(PORTB_ID,0xFC);

}



void DcMotor_Rotate(const DcMotor_State state , uint8 speed){

	uint8 temporary;
	/* write state (STOP/CW/ACW) ON PORTB */
	GPIO_writePort(PORTB_ID,state);
	/* Just temporary value to hold the EQN  (speed*255)/100 */
	/* if by mistake instead of (speed*255)/100 is [(speed*256)/100 (which is wrong)] if Temp >=120..max speed = 100.. the eqn will equal 256*/
	/* it means that duty_cycle = 256 and it max value is 255 (char) it will result in overflow and become duty_cycle = 0 and motor stop*/
	/* which was my error */
	temporary = (uint8) ((uint16)(speed*255)/(100));
	/* send speed to PWM Timer0 module (with some calculations to get duty cucle) */
	/* NUMBER OF COUNTS IN PWM TIMER 256 ......  SPEED/100 is precentage of (256 counts) (or max duty_cycle value is 255 (from 0 to 255))*/
	/* IF speed = 50 then the motor will rotate with the value of 50% of its max speed (max speed = 100) */
	/* duty cycle = (25*255)/100 = (63.75) 64 = 25% of its max speed*/
	PWM_Timer0_Start(temporary);

}
