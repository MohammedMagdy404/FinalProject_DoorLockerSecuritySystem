/*/*
 ================================================================================================
 Name        : buzzer.h
 Author      : Mohamed magdy
 Description : Header file for BUZZER Driver
 Date        : 21/10/2023
 ================================================================================================
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "common_macros.h"
#include "std_types.h"
#include "../HAL/gpio.h"

#define BUZZER_PORT PORTB_ID
#define BUZZER_PIN PIN6_ID

/**********************************************************************************************
 *                                function declarations                                       *
 **********************************************************************************************/

/*
 * Description:
 * Setup the direction for the buzzer pin as output pin through the
 * GPIO driver.
 * Turn off the buzzer through the GPIO.
 */
void Buzzer_init(void);

/*
 * Description:
 * Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void);

/*
 * Description:
 * Function to disable the Buzzer through the GPIO.
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
