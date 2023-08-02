/* 
 * File:   ecu_seven_seg.c
 * Author: ADHAM KHALED
 *
 * Created on August 1, 2023, 8:48 PM
 */
#include "ecu_seven_seg.h"
/**
 * @brief initialize the pins to be output
 * @param segment refrence to the seven segment configurations @ref segment_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType seven_segment_initialize(const segment_t *segment){
    Std_ReturnType retVal=E_OK;
    if(NULL==segment){
        retVal=E_NOT_OK;
    }  
    else{
        retVal=gpio_pin_initialize(&(segment->segment_pin[SEGMENT_PIN0]));
        retVal=gpio_pin_initialize(&(segment->segment_pin[SEGMENT_PIN1]));
        retVal=gpio_pin_initialize(&(segment->segment_pin[SEGMENT_PIN2]));
        retVal=gpio_pin_initialize(&(segment->segment_pin[SEGMENT_PIN3]));
    }
    return retVal;
}
/**
 * @brief write number on the seven segment
 * @param segment refrence to the seven segment configurations @ref segment_t
 * @param number the number to be written
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType seven_segment_write_number(const segment_t *segment,uint8 number){
    Std_ReturnType retVal=E_OK;
    if(NULL==segment || number>SEGMENT_MAX_NUMBER){
        retVal=E_NOT_OK;
    }  
    else{
        retVal=gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_PIN0]),number&0x01);
        retVal=gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_PIN1]),(number>>1)&0x01);
        retVal=gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_PIN2]),(number>>2)&0x01);
        retVal=gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_PIN3]),(number>>3)&0x01);


    }
    return retVal;
}