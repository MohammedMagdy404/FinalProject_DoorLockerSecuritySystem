/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.h
 *
 * Description: Header file for the AVR TIMER1 driver
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/

#ifndef HAL_TIMER1_H_
#define HAL_TIMER1_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ocr_num 1

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	TIMER1_NORMAL_MODE,
	TIMER1_PWM_8BIT,
	TIMER1_PWM_9BIT,
	TIMER1_PWM_10BIT,
	TIMER1_COMPARE_MODE
} Timer1_Mode;

typedef enum
{
	TIMER1_PRESCALER_0,
	TIMER1_PRESCALER_1,
	TIMER1_PRESCALER_8,
	TIMER1_PRESCALER_64,
	TIMER1_PRESCALER_256,
	TIMER1_PRESCALER_1024,
	TIMER1_External_clk_falling_edg,
	TIMER1_External_clk_rising_edg
} Timer1_Prescaler;

typedef struct
{
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the Timer driver.
 */
void Timer1_init(const Timer1_ConfigType *Config_Ptr);

/*
 * Description:
 *  Function to disable the Timer1.
 */
void Timer1_deInit(void);

/*
 * Description:
 *  Function to set the Call Back function address.
 */
void Timer1_setCallBack(void (*a_ptr)(void));

#endif /* HAL_TIMER1_H_ */
