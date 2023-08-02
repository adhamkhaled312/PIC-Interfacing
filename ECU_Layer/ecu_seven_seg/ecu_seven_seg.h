/* 
 * File:   ecu_seven_seg.h
 * Author: ADHAM_KHALED
 *
 * Created on August 1, 2023, 8:48 PM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/* ----------------Includes----------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_seven_seg_cfg.h"
/* ----------------Macro Declarations---------------*/
#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3

#define SEGMENT_MAX_NUMBER 9
/* ----------------Macro Functions Declarations----------------*/
/* ----------------Data Type Declarations----------------*/
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;
typedef struct{
    pin_config_t segment_pin[4];
    segment_type_t segment_type;
}segment_t;
/* ----------------Functions Declarations----------------*/
Std_ReturnType seven_segment_initialize(const segment_t *segment);
Std_ReturnType seven_segment_write_number(const segment_t *segment,uint8 number);

#endif	/* ECU_SEVEN_SEG_H */

