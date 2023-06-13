/*
 * main.c
 *
 *  Created on: Oct 7, 2022
 *      Author: Ahmed Ashraf El-Sayed Bekheet
 */


#include "motor.h"
#include "lm35_sensor.h"
#include "lcd.h"
#include "common_macros.h" /* For CLEAR/SET/GET_BIT Macro */
#include "avr/io.h" /* for registers like SREG*/
#include "std_types.h"
#include "adc.h" // to define INTERNAL & PRE_8



int main(void){
	uint8 Temp;

	SET_BIT(SREG,7);	/* enable I-bit (for PWM TIMERO MODULE )*/
	ADC_ConfigType ADC_Config = {INTERNAL,PRE_8};  // ref_volt first according to declaration of structure of ADC_config type
	LCD_init(); 	/* initialize LCD driver */
	ADC_init(&ADC_Config);		/* initialize ADC driver */
	DcMotor_Init(); /* initialize DC Motor driver */

	LCD_displayStringRowColumn(1,2,"Temp =    C");  // T in string is index 2 (start from coulmn 2) .... e is index 3 and so on
	while(1)
	{
		Temp = LM35_getTemperature(); /* in while(1) because Temp always changes  and  Call read channel function of ADC*/

		if(Temp < 30){
			/*Diplay on LCD*/
			LCD_displayStringRowColumn(0,2,"FAN IS OFF");
			LCD_moveCursor(1,9);  //ROW 1 ..... COULMN (7+2)
			LCD_intgerToString(Temp);
			/*STOP THE MOTOR*/
			DcMotor_Rotate(STOP,0);
		}

		else if((Temp >= 30) && (Temp < 60)){
			/*Diplay on LCD*/
			LCD_displayStringRowColumn(0,2,"FAN IS ON");
			LCD_displayStringRowColumn(0,11," ");  // overwrite last F from OF(F) which is written if we are going from 0(less than 30-) to 150
			LCD_moveCursor(1,9);  //ROW 1 ..... COULMN (7+2)
			LCD_intgerToString(Temp);
			/*MOVE THE MOTOR AT 25% OF ITS MAX SPEED AND CW*/
			DcMotor_Rotate(CW,25);
		}

		else if((Temp >= 60) && (Temp < 90)){
			LCD_displayStringRowColumn(0,2,"FAN IS ON");
			LCD_displayStringRowColumn(0,11," ");   // overwrite last F from OF(F)
			LCD_moveCursor(1,9);  //ROW 1 ..... COULMN (7+2)
			LCD_intgerToString(Temp);
			/*MOVE THE MOTOR AT 50% OF ITS MAX SPEED AND CW*/
			DcMotor_Rotate(CW,50);
		}

		else if((Temp >= 90) && (Temp < 120)){
			LCD_displayStringRowColumn(0,2,"FAN IS ON");
			LCD_displayStringRowColumn(0,11," ");       // overwrite last F from OF(F)
			LCD_moveCursor(1,9);  //ROW 1 ..... COULMN (7+2)
			LCD_intgerToString(Temp);
			/*MOVE THE MOTOR AT 75% OF HIS MAX SPEED AND CW*/
			DcMotor_Rotate(CW,75);
		}

		else if(Temp >= 120){
			LCD_displayStringRowColumn(0,2,"FAN IS ON");
			LCD_displayStringRowColumn(0,11," ");  // overwrite last F from OF(F)
			LCD_moveCursor(1,9);  //ROW 1 ..... COULMN (7+2)
			LCD_intgerToString(Temp);
			/*MOVE THE MOTOR AT ITS MAX SPEED AND CW*/
			DcMotor_Rotate(CW,100);


		}

	}

}
