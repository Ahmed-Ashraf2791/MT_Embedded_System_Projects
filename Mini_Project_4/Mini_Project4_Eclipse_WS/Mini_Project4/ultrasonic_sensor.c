/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic_sensor.c
 *
 * Description: Source file for the HC-SR04 Ultrasonic driver
 *
 * Author: Ahmed Ashraf El-Sayed Bekheet
 *
 *******************************************************************************/

#include "ultrasonic_sensor.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h> /* For the delay functions */

uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint8 g_distance = 0;

/*
 * Description :
 * Call-Back Function used to calculate g_timeHigh for the ECHO signal
 * call from ICU to ultrasonic sensor in software layers
 * Get high time of ECHO PIN (time between rising edge & falling edge of ECHO signal)
 * ICU in PD6 just waiting for ECHO PIN to be risen (rising edge) once it happened
 * ICU begin to count edges (what we need rising edge followed by falling edge) and to record this
   time in g_timeHigh (high time of ECHO signal).
 */

void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
	}
}

/*
 * Description :
 * initialize ICU as (prescaler 8 & detect rising edge)
 * pass address of function (Ultrasonic_edgeProcessing) that calculate high time of ECHO signal
   to call back function
 * Configure PB5 as o/p (Trig Pin).
 */
void Ultrasonic_init(void){
	/* Initialize the ICU driver as F_CPU_8 & RISING */
	Icu_ConfigType Sensor_Config = {F_CPU_8,RISING};
	Icu_init(&Sensor_Config);
	/* Setup the ICU call back function */
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	/* Configure PB5 as o/p PIN */
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
}

/*
 * Description :
* Send signal with LOGIC_HIGH (5V) then delay 10us then LOGIC_LOW (0V)
* check Trig Pin signal in PDF
*/

void Ultrasonic_Trigger(void){
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_LOW);
}

/*
 * Description :
* Calculate distance as shown in MT ultrasonic_sensor PDF.
* First send trigger signal
* wait for sensor to transmit for ICU i/p pin PD6 (once the ECHO signal be logic 1 the ICU
  starts calculations  g_edgeCount = 1 and waiting for next falling edge once once the ECHO signal
  be logic 0 g_edgeCount = 2 from all of that we calculated g_timeHigh and get out from
  while(g_edgeCount != 2) [this step happened in call_back (Ultrasonic_edgeProcessing) function]
*/

uint16 Ultrasonic_readDistance(void){
	/* Clear all variables as they may have values from previous read operation */
	g_distance = 0;
	g_edgeCount = 0;
	g_timeHigh = 0;

	/* Clear the timer counter register to start measurements once trigger is sent */
	Icu_clearTimerValue();

	/* Send the trigger to activate the Ultra-sonic sensor (Start measurements) */
	Ultrasonic_Trigger();

	/* Wait until the ICU measures the pulse in the ECHO pin */
	while(g_edgeCount != 2);

	/* Calculate the distance in Centimeter value */
	/* +1 to regulate the error happened in accuracy of sensor */
	g_distance = (g_timeHigh / 58) + 1 ;

	return g_distance;
}

