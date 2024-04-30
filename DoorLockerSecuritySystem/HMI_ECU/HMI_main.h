/******************************************************************************
 *
 * Project Name: DoorLockerSecuritySystem
 *
 * File Name: HMI_main.h
 *
 * Description: Header file for HMI_main Micro-controller
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/

#ifndef HMI_MAIN_H_
#define HMI_MAIN_H_

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * function to take the password
 * and handle LCD layout
 */
static uint32 Password_taking(uint8 sentence[]);

/*
 * Description:
 * function to display the main options
 * '+' to open the door
 * '-' to change password
 */
uint8 mainOptions(void);

/*
 * Description:
 * function to send the password to the Control_ECU
 */
void sendPassword(uint32 password);

/*
 * Description:
 * Callback function for the timer function
 * that is called when the timer interrupt occurs
 */
void passwordTimeOut(void);

#endif /* HMI_MAIN_H_ */
