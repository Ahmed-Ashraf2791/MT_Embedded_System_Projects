 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: motor.c
 *
 * Description: source file for the DC-Motor driver
 *
 * Author: Ahmed Ashraf El-Sayed Bekheet
 *
 *******************************************************************************/

#include "motor.h"
#include "gpio.h"
#include "pwm.h"
#include "timer1.h"

void set_motor(void){
	tick++;
}

void DcMotor_Init(void){
	/*configure three pins as output*/
	GPIO_setupPinDirection(PORT_INPUT1_ID, PIN_INPUT1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_INPUT2_ID,PIN_INPUT2_ID,PIN_OUTPUT);
	/*STOP DC motor*/
	GPIO_writePin(PORT_INPUT1_ID,  PIN_INPUT1_ID, LOGIC_LOW);
	GPIO_writePin(PORT_INPUT2_ID,  PIN_INPUT2_ID, LOGIC_LOW);

	/*set timmer one*/
	tick=0;
	Timer1_ConfigType  Config_Ptr_timer;
	Config_Ptr_timer.prescaler = PRE_8;
	Config_Ptr_timer.compare_value = 0;
	Config_Ptr_timer.initial_value = 0;
	Config_Ptr_timer.mode = OVF;
	Timer1_setCallBack(&set_motor);
	Timer1_init(&Config_Ptr_timer);

}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	switch(state){
		case STOP:  // IN1 = 0  , IN2 = 0
				GPIO_writePin(PORT_INPUT1_ID,  PIN_INPUT1_ID, LOGIC_LOW);
				GPIO_writePin(PORT_INPUT2_ID,  PIN_INPUT2_ID, LOGIC_LOW);
				break;
		case CW:  // IN1 = 0  , IN2 = 1
				GPIO_writePin(PORT_INPUT1_ID,  PIN_INPUT1_ID, LOGIC_LOW);
				GPIO_writePin(PORT_INPUT2_ID,  PIN_INPUT2_ID, LOGIC_HIGH);
				break;
		case ACW:  // IN1 = 1  , IN2 = 0
				GPIO_writePin(PORT_INPUT1_ID,  PIN_INPUT1_ID, LOGIC_HIGH);
				GPIO_writePin(PORT_INPUT2_ID,  PIN_INPUT2_ID, LOGIC_LOW);
				break;
	}
	PWM_Timer0_Start(speed);
}



