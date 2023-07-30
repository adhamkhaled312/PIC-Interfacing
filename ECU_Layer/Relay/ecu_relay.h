/* 
 * File:   ecu_relay.h
 * Author: ADHAM KHALED
 *
 * Created on July 30, 2023, 2:23 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H
/* ----------------Includes----------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_relay_cfg.h"
/* ----------------Macro Declarations---------------*/
#define RELAY_ON_STATUS 0x01U
#define RELAY_OFF_STATUS 0x00U
/* ----------------Macro Functions Declarations----------------*/
/* ----------------Data Type Declarations----------------*/
typedef struct
{
    uint8 port_name:4;
    uint8 pin_no:3;
    uint8 status:1;
}relay_t;

/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize the pin to OUTPUT and turn the relay ON or OFF   
 * @param relay refrence to relay configurations @ref relay_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType relay_initialize(const relay_t *relay);
/**
 * @brief turn relay on
 * @param relay refrence to relay configurations @ref relay_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType relay_turn_on(const relay_t *relay);
/**
 * @brief turn relay off
 * @param relay refrence to relay configurations @ref relay_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType relay_turn_off(const relay_t *relay);

#endif	/* ECU_RELAY_H */

