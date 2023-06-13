/*
 * Mini_Project2.c
 *
 *  Created on: Sep 12, 2022
 *      Author: Ahmed Ashraf El-Sayed Bekheet
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char sec = 0;      // seconds counter
unsigned char min = 0;      // minutes counter
unsigned char hour = 0;     // hours counter


ISR(TIMER1_COMPA_vect)
{
	sec++;
	if(sec == 60){   //seconds counter reaches 60 increment minutes counter by 1 (1 minute passed) (3rd digit = 1)
		sec = 0;
		min++;
	}
	if(min == 60){   //minutes counter reaches 60 increment hours counter by 1 (1 hour passed)  (5th digit = 1)
		min = 0;
		hour++;
	}
	if(hour == 24){  //hours counter reaches 24 (1 day passed) reset hours counter and start again from beginning
		hour = 0;
	}
}


ISR(INT0_vect)
{

// all counters = 0 to display 0 (coming from 4 pins of port C that go to decoder the 7 segment)
	sec=0;
	min=0;
	hour=0;
	TCNT1 = 0; // Reset the timer counter
	TCCR1B |= (1<<CS12) | (1<<CS10);  // Resume the clock
}


void INT0_Init(void)
{
	DDRD  &= (~(1<<PD2));     // Configure INT0/PD2 as input pin
	// Trigger INT1 with the falling edge
	MCUCR |= (1<<ISC11);
	MCUCR &= ~(1<<ISC10);
	GICR  |= (1<<INT0);       // Enable external interrupt pin INT0
}


ISR(INT1_vect)
{
	//Stop the clock
	TCCR1B &= ~(1<<CS12);
	TCCR1B &= ~(1<<CS10);
}


void INT1_Init(void)
{
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	// Trigger INT1 with the falling edge
	//MCUCR |= (1<<ISC11);
	//MCUCR &= ~(1<<ISC10);
	MCUCR |= (1<<ISC00) | (1<<ISC01);   // Trigger INT0 with the raising edge
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
}


ISR(INT2_vect)
{
	// Resume the clock
	TCCR1B |= (1<<CS12);
	TCCR1B |= (1<<CS10);
}


void INT2_Init(void)
{
	DDRB  &= (~(1<<PB2));               // Configure INT0/PD2 as input pin
	// Trigger INT1 with the falling edge
	MCUCR |= (1<<ISC11);
	MCUCR &= ~(1<<ISC10);
	GICR  |= (1<<INT2);                 // Enable external interrupt pin INT2
}


void Timer1_Init_Compare_Mode(void)
{
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);	// Compare Mode not PWM
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10); 	// Set the mode to CTC and the prescaler to 8
	TCNT1 = 0;							// Start from 0
	OCR1A = 977;						// value that timer compare with (number of el3dat)
	TIMSK = (1<<OCIE1A);				// Enable timer interrupt
}


int main(void)
{
	SREG  |= (1<<7);   // Enable global interrupts in MC.
	INT0_Init();    // Enable and configure external INT0
	INT1_Init();    // Enable and configure external INT1
	INT2_Init();    // Enable and configure external INT2
	Timer1_Init_Compare_Mode();    // Start the timer.
	DDRA  |= 0x3F;     // Configure pins as output from PA0 --> PA5
	DDRC  |= 0x0F;     // Configure pins as output from PC0 --> PC3
	PORTC = (PORTC & 0xF0)| 0x00; 	// At first display 0

	while(1)
	{
		PORTA = (PORTA & 0xC0) | 0x01;      //(PORTA & 0xC0) to keep pin PA6,PA7 SAFE from any changes
		// first digit in 7 segment comes from 4 pins from decoder (without % 10 so there is number that will be wrong if we try number like 25 = 9 [first 4 bits])
		//if we try all numbers from 1 to 9 (%10) gives the same number when it 10%10 =0 that is right because that is the first digit ,, 11%10 = 1 ,, 21%10 =1
		PORTC = (PORTC & 0xF0) | sec%10;
		_delay_ms(2);
		PORTA = (PORTA & 0xC0) | 0x02;
        //second digit of 7 segment division by 10 (11/10 = 1.1 =1 skip 0.1) if (%10  the first 2 digits will increment with each other 2 2 , 3 3 , .......)
		PORTC = (PORTC & 0xF0) | sec/10;
		_delay_ms(2);
		PORTA = (PORTA & 0xC0) | 0x04;
		PORTC = (PORTC & 0xF0) | min%10;
		_delay_ms(2);
		PORTA = (PORTA & 0xC0) | 0x08;
		PORTC = (PORTC & 0xF0) | min/10;
		_delay_ms(2);
		PORTA = (PORTA & 0xC0) | 0x10;
		PORTC = (PORTC & 0xF0) | hour%10;
		_delay_ms(2);
		PORTA = (PORTA & 0xC0) | 0x20;
		PORTC = (PORTC & 0xF0) | hour/10;
		_delay_ms(2);

	}
}



