/* 
 * File:   ecu_button.h
 * Author: ADHAM KHALED
 *
 * Created on July 28, 2023, 4:47 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H
/* ----------------Includes----------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"
/* ----------------Macro Declarations---------------*/
/* ----------------Macro Functions Declarations----------------*/
/* ----------------Data Type Declarations----------------*/
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_state_t;
typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;
typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize the led to be input
 * @param btn refrence to the button configurations @ref button_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType button_initialize(const button_t *btn);
/**
 * @brief read the status of the button (pressed or not)
 * @param btn refrence to the button configurations @ref button_t
 * @param btn_state button state @ref button_state_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType button_read_state(const button_t *btn,button_state_t *btn_state );
#endif	/* ECU_BUTTON_H */

