 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: motor.h
 *
 * Description: header file for the DC-Motor driver
 *
 * Author:  Ahmed Ashraf El-Sayed Bekheet
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* The Ports and Pins IDs for the DC-Motor three pins */
#define PORT_ENABLE      PORTB_ID
#define PIN_ENABLE       PIN3_ID
#define PORT_INPUT1_ID   PORTB_ID
#define PORT_INPUT2_ID   PORTB_ID
#define PIN_INPUT1_ID    PIN1_ID
#define PIN_INPUT2_ID    PIN2_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum{
	STOP,CW,ACW
}DcMotor_State;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
void set_motor(void);

#endif /* MOTOR_H_ */
