/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/




/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	Data_5Bit,
	Data_6Bit,
	Data_7Bit,
	Data_8Bit,
	Reserved_Do_Not_Use,
	Reserved_Do_Not_Use2,
	Reserved_Do_Not_Use3,
	Data_9Bit
}UART_BitData;


typedef enum{
	Disabled,
	Reserved,
	Even_Parity,
	Odd_Parity,
}UART_Parity;

typedef enum{
	St_1Bit,
	St_2Bit
}UART_StopBit;

typedef uint32 UART_BaudRate;

typedef enum{
	ASYNC,
	SYNC
}transmission_Mode;


typedef enum{
	SYNC_OR_ASYNC_Normal,
	ASYNC_Double
}transmission_speed;


typedef struct{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
	transmission_Mode trans_mod;
	transmission_speed trans_speed;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

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
