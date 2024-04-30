/******************************************************************************
 *
 * Project Name: DoorLockerSecuritySystem
 *
 * File Name: control_main.h
 *
 * Description: Source file for Control_main Micro-controller
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/

#include "MCAL/std_types.h"
#include "MCAL/external_eeprom.h"
#include "MCAL/buzzer.h"
#include "MCAL/dcMotor.h"
#include "HAL/uart.h"
#include "HAL/timer1.h"
#include "HAL/twi.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "control_main.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define SAME_PASS 2
#define DIFF_PASS 0
#define EEPROM_ADD 0x0311

#define PASSWORD_TIME_OUT 60
#define DOOR_OPEN_TIME 15
#define DOOR_HOLD_TIME 3
#define DOOR_CLOSE_TIME 15

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static uint32 password1 = 0;
static uint32 password2 = 0;
static uint32 option_password = 0;
static uint32 reStored_password = 0;
static uint8 timerValue = 0;
static uint8 count_timer = 0;
static uint8 ack_set = 0;
static uint8 countWrngPass = 0;

/*******************************************************************************
 *                           Main Function                                     *
 *******************************************************************************/

int main(void)
{

	// Configure the UART specifications
	UART_ConfigType uart_configuration;
	uart_configuration.baud_rate = 9600;
	uart_configuration.bit_data = Data_8Bit;
	uart_configuration.parity = Disabled;
	uart_configuration.stop_bit = St_1Bit;
	uart_configuration.trans_mod = ASYNC;
	uart_configuration.trans_speed = ASYNC_Double;

	// Start the UART
	UART_init(&uart_configuration);

	// Configure the TWI interface specifications
	TWI_ConfigType twi_configuration;
	twi_configuration.bit_rate = TWI_CPU_1;
	twi_configuration.address = 0x01;

	/* Start the TWI/I2C Driver */
	TWI_init(&twi_configuration);

	/* *************************************
	 * Configure the TIMER1 specifications
	 * Timer interrupt every 1sec
	 * In compare modes:
	 * 		Fcpu = 8Mhz;
	 * 		initial_value = 0;
	 * 		compare_value = 31250;
	 * 		prescaler = 256;
	 * In Normal Mode:
	 * 		prescaler = 1024;
	 */
	static Timer1_ConfigType timer_config;
	timer_config.mode = TIMER1_COMPARE_MODE;
	timer_config.prescaler = TIMER1_PRESCALER_256;
	timer_config.initial_value = 0;
	timer_config.compare_value = 31250;
	//	timer_config.compare_value = 6000;

	// Set CallBack function for timer1
	//	Timer1_setCallBack(TimeOut);

	/* Start the Buzzer Driver */
	Buzzer_init();
	/* Start the DC-Motor Driver */
	DcMotor_Init();

	SREG |= (1 << 7); /* Enable Global Interrupts */

	/*
	 * 	--------------------------------- 1# receive 2$ passwords and compare ----------------------------------------
	 */
	// ___________________________________________________________________________________________________________________
	while (1)
	{
		do
		{

			// receive password1 from the HMI_ECU
			receivePassword(&password1);

			// receive password2 to the HMI_ECU
			receivePassword(&password2);

			if (password1 == password2)
			{
				ack_set = SAME_PASS;
				UART_sendByte(ack_set);

				storePassword(EEPROM_ADD, password1);
			}
			else
			{
				ack_set = DIFF_PASS;
				UART_sendByte(ack_set);
			}
		} while (ack_set == DIFF_PASS);

		/*
		 * 	--------------------------------- 2# receive 1$ password and compare ----------------------------------------
		 */
		// receive option from HMI_MC
		uint8 option;
		while (1)
		{
			option = UART_recieveByte();

			// receive optionPassword from the HMI_ECU

			countWrngPass = 0;
			do
			{
				option_password = 0;
				reStored_password = 0;
				receivePassword(&option_password);

				reStorePassword(EEPROM_ADD, &reStored_password);

				if (option_password == reStored_password)
				{
					UART_sendByte(5);
					break;
				}
				else
				{
					countWrngPass++;
					UART_sendByte(countWrngPass);
				}

			} while (countWrngPass < 3);

			if (countWrngPass == 3)
			{
				// Activate Buzzer for 1-minute.
				Buzzer_on();
				timerValue = PASSWORD_TIME_OUT;
				count_timer = 0;
				Timer1_setCallBack(TimeOut);
				Timer1_init(&timer_config);
				while (count_timer < timerValue)
					; //// <<--------------------
				Buzzer_off();
				continue;
			}

			if (option == '+')
			{
				// rotates motor for 15-seconds CW
				timerValue = DOOR_OPEN_TIME;
				count_timer = 0;
				Timer1_setCallBack(TimeOut);
				Timer1_init(&timer_config);
				DcMotor_Rotate(CW, 200);
				while (count_timer < timerValue)
					; //// <<--------------------

				// hold the motor for 3-seconds
				timerValue = DOOR_HOLD_TIME;
				count_timer = 0;
				Timer1_setCallBack(TimeOut);
				Timer1_init(&timer_config);
				DcMotor_Rotate(CW, 0);
				while (count_timer < timerValue)
					; //// <<--------------------

				// rotates motor for 15-seconds A_CW
				timerValue = DOOR_CLOSE_TIME;
				count_timer = 0;
				Timer1_setCallBack(TimeOut);
				Timer1_init(&timer_config);
				DcMotor_Rotate(A_CW, 200);
				while (count_timer < timerValue)
					; //// <<--------------------

				// stop motor
				DcMotor_Rotate(stop, 0);
			}
			else if (option == '-')
			{
				break;
			}
			// end of main while(1) loop
		}
		// end of main while(1) loop
	}
	// end of main
}

//___________________________________________________________________________________________________________________

/*
 * Description:
 * function to Store the current password in the EEPROM
 */
void storePassword(uint16 address, uint32 password)
{
	uint8 i;
	for (i = 0; i < 4; i++)
	{
		EEPROM_writeByte(address + i, (password >> (i * 8)) & 0x000000FF);
		_delay_ms(10);
	}
}

/*
 * Description:
 * function to Retrieve the password from the EEPROM
 */
void reStorePassword(uint16 address, uint32 *password)
{
	*password = 0;
	uint8 i;
	uint8 byte = 0;
	for (i = 0; i < 4; i++)
	{
		EEPROM_readByte((address + i), &byte);
		_delay_ms(50);
		*password |= ((uint32)byte) << (i * 8);
	}

	_delay_ms(20);
}

/*
 * Description:
 * function to receive the password from the HMI_ECU
 */
void receivePassword(uint32 *password)
{
	uint8 recived_byte = 0;
	*password = 0;
	// receive password from the HMI_ECU
	for (uint8 i = 0; i < 5; i++)
	{
		recived_byte = UART_recieveByte();
		*password = ((*password) * 10) + recived_byte;
	}
}

/*
 * Description:
 * Callback function for the timer function
 * that is called when the timer interrupt occurs
 */
void TimeOut(void)
{
	if (count_timer >= timerValue)
	{
		Timer1_deInit();
		return;
	}
	count_timer++;
}
