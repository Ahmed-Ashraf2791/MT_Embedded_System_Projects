/*
 ============================================================================
 Name        : main.c
 Author      : Ahmed Ashraf El-Sayed Bekheet
 Description : Ultrasonic Sensor using ICU to calculate the distance to object
 Date        : 13/10/2022
 ============================================================================
 */

#include "ultrasonic_sensor.h"
#include "lcd.h"
#include "avr/io.h" /* To use the SREG Register */

int main(void)
{
	uint16 distance = 0;

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Initialize the LCD driver */
	LCD_init();

	/* Initialize the Ultrasonic driver */
	Ultrasonic_init();

	/* Display the distance on LCD screen */
	LCD_displayString("Distance=  ");
	LCD_moveCursor(0,13);
	LCD_displayString("cm");


	while(1)
	{
		/* Read the distance from the Ultrasonic sensor continously */
		distance = Ultrasonic_readDistance();
		LCD_moveCursor(0,10);
		LCD_intgerToString(distance);
	}
}
