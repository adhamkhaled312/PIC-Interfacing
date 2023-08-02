/* 
 * File:   ecu_keypad.s
 * Author: ADHAM KHALED
 *
 * Created on August 2, 2023, 2:47 PM
 */
#include "ecu_keypad.h"

static const uint8 btns_values[KEYPAD_ROWS][KEYPAD_COLUMNS]={
                                                        {'7','8','9','/'},
                                                        {'4','5','6','*'},
                                                        {'1','2','3','-'},
                                                        {'#','0','=','+'},

};
/**
 * @brief initialize the keypad pins
 * @param keypad refrence to the keypad configurations @ref keypad_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType keypad_initialize(const keypad_t *keypad){
    Std_ReturnType retVal=E_OK;
    uint8 rows_counter=0;
    uint8 columns_counter=0;
    if(NULL==keypad){
        retVal=E_NOT_OK;
    }
    else{
        for(rows_counter=0;rows_counter<KEYPAD_ROWS;rows_counter++){
            retVal=gpio_pin_initialize(&(keypad->keypad_row_pins[rows_counter]));
        }
        for(columns_counter=0;columns_counter<KEYPAD_COLUMNS;columns_counter++){
            retVal=gpio_pin_initialize(&(keypad->keypad_column_pins[columns_counter]));    
        }
    }
    return retVal;
}
/**
 * @brief get the value of the keypad button pressed
 * @param keypad refrence to the keypad configurations @ref keypad_t
 * @param value refrence to store the value of the pressed keypad button in
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType keypad_get_value(const keypad_t *keypad,uint8 *value){
    Std_ReturnType retVal=E_OK;
    uint8 rows_counter=0;
    uint8 columns_counter=0;
    uint8 temp_counter=0;
    logic_t status=LOW;
    if(NULL==keypad){
        retVal=E_NOT_OK;
    }
    else{
        for(rows_counter=0;rows_counter<KEYPAD_ROWS;rows_counter++){
            for(temp_counter=0;temp_counter<KEYPAD_ROWS;temp_counter++){
                retVal=gpio_pin_write_logic(&(keypad->keypad_row_pins[temp_counter]),LOW);
            }
            retVal=gpio_pin_write_logic(&(keypad->keypad_row_pins[rows_counter]),HIGH);
            for(columns_counter=0;columns_counter<KEYPAD_COLUMNS;columns_counter++){
                retVal=gpio_pin_read_logic(&(keypad->keypad_column_pins[columns_counter]),&status);
                if(status==HIGH){
                    *value=btns_values[rows_counter][columns_counter];
                }
        }
        }

    }
    return retVal;
}