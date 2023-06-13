/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic_sensor.h
 *
 * Description: Header file for the HC-SR04 Ultrasonic driver
 *
 * Author: Ahmed Ashraf El-Sayed Bekheet
 *
 *******************************************************************************/
#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include "std_types.h"

void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_SENSOR_H_ */
