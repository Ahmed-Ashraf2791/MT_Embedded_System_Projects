 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the AVR UART driver
 *
 * Author: Ahmed Ashraf El-Sayed Bekheet
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
//typedef	uint32  UART_BaudRate;

typedef enum
{
	FIVE_DATA_BITS,SIX_DATA_BITS,SEVEN_DATA_BITS,EIGHT_DATA_BIT,RESRVED1,RESRVED2,RESRVED3,NINE_DATA_BIT
}UART_BitData;

typedef enum
{
	DISABLED,RESRVED,EVEN_PARITY,ODD_PARITY
}UART_Parity;

typedef enum
{
	ONE_STOP_BIT,TWO_STOP_BITS
}UART_StopBit;

typedef enum
{
	BUAD_RATE_2400_bps = 2400,
	BUAD_RATE_4800_bps = 4800,
	BUAD_RATE_9600_bps = 9600,
	BUAD_RATE_14400_bps = 14400,
	BUAD_RATE_19200_bps = 19200,
	BUAD_RATE_28800_bps = 28800,
	BUAD_RATE_38400_bps = 38400,
	BUAD_RATE_57600_bps = 57600,
	BUAD_RATE_76800_bps = 76800,
	BUAD_RATE_115200_bps = 115200,
	BUAD_RATE_230400_bps = 230400,
	BUAD_RATE_250000_bps = 250000,
	BUAD_RATE_1M_bps = 1000000,
}UART_BaudRate;

typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 UART_BaudRate baud_rate;
}UART_ConfigType;
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
