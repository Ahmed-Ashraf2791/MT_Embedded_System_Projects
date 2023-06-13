/*
 * pwm.c
 *
 *  Created on: Oct 6, 2022
 *      Author: Ahmed Ashraf El-Sayed Bekheet
 */

#include "avr/io.h"
#include"pwm.h"
/*
 * Description:
 * Generate a PWM signal with frequency 500Hz
 */


void PWM_Timer0_Start(uint8 duty_cycle)
{

	TCNT0 = 0; //Set Timer Initial value
    /*The timer0 counts from 0 to 255 that is 256 counts then interrupt the CPU*/
	OCR0  = duty_cycle; // Set Compare Value  (max value of duty_cycle = 255 fit in char(uint8) datatype)

	DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
