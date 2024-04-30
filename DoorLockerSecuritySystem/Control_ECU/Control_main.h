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

#ifndef CONTROL_MAIN_H_
#define CONTROL_MAIN_H_

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * function to Store the current password in the EEPROM
 */
void storePassword(uint16 address, uint32 password);

/*
 * Description:
 * function to receive the password from the HMI_ECU
 */
void receivePassword(uint32 *password);

/*
 * Description:
 * function to Retrieve the password from the EEPROM
 */
void reStorePassword(uint16 address, uint32 *password);

/*
 * Description:
 * Callback function for the timer function
 * that is called when the timer interrupt occurs
 */
void TimeOut(void);

#endif /* CONTROL_MAIN_H_ */
