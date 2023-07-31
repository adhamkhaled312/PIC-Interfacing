/* 
 * File:   ecu_dc_motor.c
 * Author: ADHAM KHALED
 *
 * Created on July 31, 2023, 2:13 AM
 */
#include "ecu_dc_motor.h"

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