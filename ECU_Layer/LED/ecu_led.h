/* 
 * File:   ecu_led.h
 * Author: ADHAM KHALED
 *
 * Created on July 26, 2023, 4:21 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/* ----------------Includes----------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"
/* ----------------Macro Declarations---------------*/
/* ----------------Macro Functions Declarations----------------*/
/* ----------------Data Type Declarations----------------*/
typedef enum{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port_name:4;
    uint8 pin_no:3;
    uint8 status:1;
}led_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize the pin to OUTPUT and turn the led ON or OFF
 * @param led refrence to the led configurations @red led_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType led_initialize(const led_t *led);
/**
 * @brief turn led on
 * @param led refrence to the led configurations @red led_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType led_turn_on(const led_t *led);
/**
 * @brief turn led off
 * @param led refrence to the led configurations @red led_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType led_turn_off(const led_t *led);
/**
 * @brief toggle the led
 * @param led refrence to the led configurations @red led_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType led_turn_toggle(const led_t *led);
#endif	/* ECU_LED_H */

