/* 
 * File:   ecu_keypad.h
 * Author: ADHAM KHALED
 *
 * Created on August 2, 2023, 2:47 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* ----------------Includes----------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_keypad_cfg.h"
/* ----------------Macro Declarations---------------*/
#define KEYPAD_ROWS    4
#define KEYPAD_COLUMNS 4 
/* ----------------Macro Functions Declarations----------------*/
/* ----------------Data Type Declarations----------------*/
typedef struct{
    pin_config_t keypad_row_pins[KEYPAD_ROWS];
    pin_config_t keypad_column_pins[KEYPAD_COLUMNS];
}keypad_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize the keypad pins
 * @param keypad refrence to the keypad configurations @ref keypad_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType keypad_initialize(const keypad_t *keypad);
/**
 * @brief get the value of the keypad button pressed
 * @param keypad refrence to the keypad configurations @ref keypad_t
 * @param value refrence to store the value of the pressed keypad button in
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType keypad_get_value(const keypad_t *keypad,uint8 *value);
#endif	/* ECU_KEYPAD_H */
