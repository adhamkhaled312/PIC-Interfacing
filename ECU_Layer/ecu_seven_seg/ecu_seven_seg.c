/* 
 * File:   ecu_seven_seg.c
 * Author: ADHAM KHALED
 *
 * Created on August 1, 2023, 8:48 PM
 */
#include "ecu_seven_seg.h"
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