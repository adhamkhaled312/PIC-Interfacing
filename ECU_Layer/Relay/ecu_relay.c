/* 
 * File:   ecu_relay.c
 * Author: ADHAM KHALED
 *
 * Created on July 30, 2023, 2:23 AM
 */

#include "ecu_relay.h"

/**
 * @brief initialize the pin to OUTPUT and turn the relay ON or OFF   
 * @param relay refrence to relay configurations @ref relay_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType relay_initialize(const relay_t *relay){
    Std_ReturnType retVal=E_OK;
    if(NULL==relay){
        retVal=E_NOT_OK;
    }
    else{
        pin_config_t temp={
            .port=relay->port_name,
            .pin=relay->pin_no,
            .logic=relay->status,
            .direction=OUTPUT  
        };
        retVal=gpio_pin_initialize(&temp);
    }
    return retVal;
}
/**
 * @brief turn relay on
 * @param relay refrence to relay configurations @ref relay_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType relay_turn_on(const relay_t *relay){
    Std_ReturnType retVal=E_OK;
    if(NULL==relay){
        retVal=E_NOT_OK;
    }
    else{
        pin_config_t temp={
            .port=relay->port_name,
            .pin=relay->pin_no,
            .logic=relay->status,
            .direction=OUTPUT  
        };
        retVal=gpio_pin_write_logic(&temp,HIGH);
    }
    return retVal;
}
/**
 * @brief turn relay off
 * @param relay refrence to relay configurations @ref relay_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType relay_turn_off(const relay_t *relay){
    Std_ReturnType retVal=E_OK;
    if(NULL==relay){
        retVal=E_NOT_OK;
    }
    else{
        pin_config_t temp={
            .port=relay->port_name,
            .pin=relay->pin_no,
            .logic=relay->status,
            .direction=OUTPUT  
        };
        retVal=gpio_pin_write_logic(&temp,LOW);
    }
    return retVal;
}