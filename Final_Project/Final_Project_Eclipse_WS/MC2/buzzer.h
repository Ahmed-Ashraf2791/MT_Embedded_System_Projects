/*
 * buzzer.h
 *
 *  Created on: Nov 1, 2022
 *      Author: Ahmed Ashraf El-Sayed Bekheet
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#define BUZZER_PIN  PIN0_ID
#define BUZZER_PORT PORTB_ID

void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);


#endif /* BUZZER_H_ */
