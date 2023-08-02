/* 
 * File:   ecu_dc_motor.h
 * Author: ADHAM KHALED
 *
 * Created on July 31, 2023, 2:13 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H
/* ----------------Includes----------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_dc_motor_cfg.h"

/* ----------------Macro Declarations---------------*/
#define DC_MOTOR_ON_STATUS 0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

#define DC_MOTOR_PIN0  0x00U
#define DC_MOTOR_PIN1  0x01U
/* ----------------Macro Functions Declarations----------------*/
/* ----------------Data Type Declarations----------------*/
typedef struct{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize the pins to be output
 * @param motor refrence to the dc motor configurations @ref dc_motor_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *motor);
/**
 * @brief move the motor right (forward)
 * @param motor refrence to the dc motor configurations @ref dc_motor_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *motor);
/**
 * @brief move the motor left (backward)
 * @param motor refrence to the dc motor configurations @ref dc_motor_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *motor);
/**
 * @brief stop the motor
 * @param motor refrence to the dc motor configurations @ref dc_motor_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType dc_motor_move_stop(const dc_motor_t *motor);



#endif	/* ECU_DC_MOTOR_H */

