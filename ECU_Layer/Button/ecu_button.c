/* 
 * File:   ecu_button.c
 * Author: ADHAM KHALED
 *
 * Created on July 28, 2023, 4:47 PM
 */
#include "ecu_button.h"
/**
 * @brief initialize the led to be input
 * @param btn refrence to the button configurations @ref button_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType button_initialize(const button_t *btn){
    Std_ReturnType retVal=E_OK;
    if(NULL==btn){
        retVal=E_NOT_OK;
    }
    else{
        gpio_pin_direction_initialize(&(btn->button_pin));
    }
    return retVal;
}
/**
 * @brief read the status of the button (pressed or not)
 * @param btn refrence to the button configurations @ref button_t
 * @param btn_state button state @ref button_state_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType button_read_state(const button_t *btn,button_state_t *btn_state ){
    Std_ReturnType retVal=E_OK;
    logic_t status=LOW;
    if(NULL==btn ||NULL==btn_state){
        retVal=E_NOT_OK;
    }
    else{
        gpio_pin_read_logic(&(btn->button_pin),&status);
        switch (btn->button_connection)
        {
        case BUTTON_ACTIVE_HIGH:
            if(status==HIGH){
                *btn_state=BUTTON_PRESSED;
            }
            else if(status==LOW){
                *btn_state=BUTTON_RELEASED;
            }
            break;
        case BUTTON_ACTIVE_LOW:
            if(status==HIGH){
                *btn_state=BUTTON_RELEASED;
            }
            else if(status==LOW){
                *btn_state=BUTTON_PRESSED;
            }
            break;
        default:
            retVal=E_NOT_OK;
            break;
        }
    }
    return retVal;
}