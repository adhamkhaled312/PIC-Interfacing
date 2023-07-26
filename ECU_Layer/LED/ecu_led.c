/* 
 * File:   ecu_led.c
 * Author: ADHAM KHALED
 *
 * Created on July 26, 2023, 4:21 PM
 */
#include "ecu_led.h"
/**
 * @brief initialize the pin to OUTPUT and turn the led ON or OFF
 * @param led refrence to the led configurations @red led_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType retVal=E_OK;
    if(NULL==led){
        retVal=E_NOT_OK;
    }
    else{
        pin_config_t temp={
            .direction=OUTPUT,
            .logic=led->status,
            .pin=led->pin_no,
            .port=led->port_name
        };
        retVal=gpio_pin_initialize(&temp);
    }
    return retVal;
}
/**
 * @brief turn led on
 * @param led refrence to the led configurations @red led_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType retVal=E_OK;
    if(NULL==led){
        retVal=E_NOT_OK;
    }
    else{
        pin_config_t temp={
            .direction=OUTPUT,
            .logic=led->status,
            .pin=led->pin_no,
            .port=led->port_name
        };
        retVal=gpio_pin_write_logic(&temp,HIGH);
    }
    return retVal;
}
/**
 * @brief turn led off
 * @param led refrence to the led configurations @red led_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType retVal=E_OK;
    if(NULL==led){
        retVal=E_NOT_OK;
    }
    else{
        pin_config_t temp={
            .direction=OUTPUT,
            .logic=led->status,
            .pin=led->pin_no,
            .port=led->port_name
        };
        retVal=gpio_pin_write_logic(&temp,LOW);
    }
    return retVal;
}
/**
 * @brief toggle the led
 * @param led refrence to the led configurations @red led_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType led_turn_toggle(const led_t *led){
    Std_ReturnType retVal=E_OK;
    if(NULL==led){
        retVal=E_NOT_OK;
    }
    else{
        pin_config_t temp={
            .direction=OUTPUT,
            .logic=led->status,
            .pin=led->pin_no,
            .port=led->port_name
        };
        retVal=gpio_pin_toggle_logic(&temp);
    }
    return retVal;
}