/* 
 * File:   ecu_dc_motor.c
 * Author: ADHAM KHALED
 *
 * Created on July 31, 2023, 2:13 AM
 */
#include "ecu_dc_motor.h"
/**
 * @brief initialize the pins to be output
 * @param motor refrence to the dc motor configurations @ref dc_motor_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *motor){
    Std_ReturnType retVal=E_OK;
    if(NULL==motor){
        retVal=E_NOT_OK;
    }
    else{
        retVal=gpio_pin_initialize(&(motor->dc_motor_pin[DC_MOTOR_PIN0]));
        retVal=gpio_pin_initialize(&(motor->dc_motor_pin[DC_MOTOR_PIN1]));
    }
    return retVal; 
}
/**
 * @brief move the motor right (forward)
 * @param motor refrence to the dc motor configurations @ref dc_motor_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *motor){
    Std_ReturnType retVal=E_OK;
    if(NULL==motor){
        retVal=E_NOT_OK;
    }
    else{
        retVal=gpio_pin_write_logic(&(motor->dc_motor_pin[DC_MOTOR_PIN0]),HIGH);
        retVal=gpio_pin_write_logic(&(motor->dc_motor_pin[DC_MOTOR_PIN1]),LOW);
    }
    return retVal; 
}
/**
 * @brief move the motor left (backward)
 * @param motor refrence to the dc motor configurations @ref dc_motor_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *motor){
    Std_ReturnType retVal=E_OK;
    if(NULL==motor){
        retVal=E_NOT_OK;
    }
    else{
        retVal=gpio_pin_write_logic(&(motor->dc_motor_pin[DC_MOTOR_PIN0]),LOW);
        retVal=gpio_pin_write_logic(&(motor->dc_motor_pin[DC_MOTOR_PIN1]),HIGH);
    }
    return retVal; 
}
/**
 * @brief stop the motor
 * @param motor refrence to the dc motor configurations @ref dc_motor_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType dc_motor_move_stop(const dc_motor_t *motor){
    Std_ReturnType retVal=E_OK;
    if(NULL==motor){
        retVal=E_NOT_OK;
    }
    else{
        retVal=gpio_pin_write_logic(&(motor->dc_motor_pin[DC_MOTOR_PIN0]),LOW);
        retVal=gpio_pin_write_logic(&(motor->dc_motor_pin[DC_MOTOR_PIN1]),LOW);
    }
    return retVal; 
}