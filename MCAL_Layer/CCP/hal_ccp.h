/* 
 * File:   hal_ccp1.h
 * Author: ADHAM_KHALED
 *
 * Created on September 17, 2023, 1:55 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* ----------------Includes----------------*/
#include "../mcal_std_types.h"
#include "C:\Program Files (x86)\Microchip\MPLABX\v5.35\packs\Microchip\PIC18Fxxxx_DFP\1.2.26\xc8\pic\include\proc\pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "ccp_cfg.h"
/* ----------------Macro Declarations---------------*/
#define CCP_MODULE_DISABLE                 ((uint8)0x00)

#define CCP_COMPARE_MODE_TOGGLE            ((uint8)0x02)
#define CCP_COMPARE_MODE_SET_PIN_LOW       ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((uint8)0x09)
#define CCP_COMPARE_MODE_GEN_INTERRUPT     ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT         ((uint8)0x0B)

#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((uint8)0x07)

#define CCP_PMW_MODE                       ((uint8)0x0C)

#define CCP_CAPTURE_NOT_READY              ((uint8)0x00)
#define CCP_CAPTURE_READY                  ((uint8)0x01)

#define CCP_COMPARE_NOT_READY              ((uint8)0x00)
#define CCP_COMPARE_READY                  ((uint8)0x01)

#define CCP_TIMER2_PRESCALER_DIV_1          1
#define CCP_TIMER2_PRESCALER_DIV_4          4
#define CCP_TIMER2_PRESCALER_DIV_16         16

#define CCP_TIMER2_POSTSCALER_DIV_1         1
#define CCP_TIMER2_POSTSCALER_DIV_2         2 
#define CCP_TIMER2_POSTSCALER_DIV_3         3
#define CCP_TIMER2_POSTSCALER_DIV_4         4
#define CCP_TIMER2_POSTSCALER_DIV_5         5
#define CCP_TIMER2_POSTSCALER_DIV_6         6
#define CCP_TIMER2_POSTSCALER_DIV_7         7
#define CCP_TIMER2_POSTSCALER_DIV_8         8
#define CCP_TIMER2_POSTSCALER_DIV_9         9
#define CCP_TIMER2_POSTSCALER_DIV_10        10   
#define CCP_TIMER2_POSTSCALER_DIV_11        11   
#define CCP_TIMER2_POSTSCALER_DIV_12        12  
#define CCP_TIMER2_POSTSCALER_DIV_13        13    
#define CCP_TIMER2_POSTSCALER_DIV_14        14    
#define CCP_TIMER2_POSTSCALER_DIV_15        15    
#define CCP_TIMER2_POSTSCALER_DIV_16        16    
/* ----------------Macro Functions Declarations----------------*/
#define CCP1_SET_MODE(_CONFIG)           (CCP1CONbits.CCP1M=_CONFIG)
#define CCP2_SET_MODE(_CONFIG)           (CCP2CONbits.CCP2M=_CONFIG)

/* ----------------Data Type Declarations----------------*/
typedef enum{
    CCP_CAPTURE_MODE_SELECT=0,
    CCP_COMPARE_MODE_SELECT,
    CCP_PWM_MODE_SEELCT
}ccp_mode_t;
typedef union{
    struct{
        uint8 ccp_low;
        uint8 ccp_high;
    };
    struct{
        uint16 ccp_16_bit;
    };
}CCP_PERIOD_REG_T;
typedef enum{
    CCP1_INST,
    CCP2_INST
}ccp_inst_t;
typedef enum{
    CCP1_CCP2_TIMER3,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1
}ccp_capture_timer_t;
typedef struct{
    ccp_inst_t ccp_inst;
    ccp_mode_t ccp_mode;
    uint8 ccp_mode_variant;
    pin_config_t pin;
    ccp_capture_timer_t ccp_capture_timer;
    #if CCP1_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* ccp1_interrupt_handler)(void);
    interrupt_priority_cfg ccp1_priority;
    #endif
    #if CCP2_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* ccp2_interrupt_handler)(void);
    interrupt_priority_cfg ccp2_priority;
    #endif
    #if (CCP1_CFG_SELECT_MODE==CCP_CFG_PWM_MODE_SELECT || CCP2_CFG_SELECT_MODE==CCP_CFG_PWM_MODE_SELECT)
    uint32 pwm_frequency;
    uint8 timer2_prescaler;
    uint8 timer2_postscaler;
    #endif
}ccp_t;
/* ----------------Functions Declarations----------------*/
Std_ReturnType ccp_init(const ccp_t* ccp_obj);
Std_ReturnType ccp_deinit(const ccp_t* ccp1_obj);
#if CCP1_CFG_SELECT_MODE==CCP_CFG_CAPTURE_MODE_SELECT
Std_ReturnType ccp_capture_IsCaptureReady(uint8* status);
Std_ReturnType ccp_capture_read_value(uint16* value);
#endif
#if CCP1_CFG_SELECT_MODE==CCP_CFG_COMPARE_MODE_SELECT
Std_ReturnType ccp_compare_IsCompareComplete(uint8* status);
Std_ReturnType ccp_compare_set_value(const ccp_t* ccp1_obj,uint16 value);
#endif
#if CCP1_CFG_SELECT_MODE==CCP_CFG_PWM_MODE_SELECT
Std_ReturnType ccp_pwm_set_duty(const ccp_t* ccp_obj,const uint8 duty);
Std_ReturnType ccp_pwm_start(const ccp_t* ccp_obj);
Std_ReturnType ccp_pwm_stop(const ccp_t* ccp_obj);
#endif
#endif	/* HAL_CCP1_H */

