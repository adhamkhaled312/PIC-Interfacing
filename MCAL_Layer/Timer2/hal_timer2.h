/* 
 * File:   hal_timer2.h
 * Author: ADHAM KHALED
 *
 * Created on September 1, 2023, 10:36 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H
/* ----------------Includes----------------*/
#include "../mcal_std_types.h"
#include "C:\Program Files (x86)\Microchip\MPLABX\v5.35\packs\Microchip\PIC18Fxxxx_DFP\1.2.26\xc8\pic\include\proc\pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* ----------------Macro Declarations---------------*/
#define TIMER2_PRESCALER_DIV_1          0
#define TIMER2_PRESCALER_DIV_4          1
#define TIMER2_PRESCALER_DIV_16         2

/* ----------------Macro Functions Declarations----------------*/
#define TIMER2_ENABLE()                        (T2CONbits.TMR2ON=1)
#define TIMER2_DISABLE()                       (T2CONbits.TMR2ON=0)

#define TIMER2_PRESCALER_SET(VALUE)            (T2CONbits.T2CKPS=VALUE)
#define TIMER2_POSTSCALER_SET(VALUE)           (T2CONbits.TOUTPS=VALUE)

/* ----------------Data Type Declarations----------------*/
typedef enum{
    TIMER2_POSTSCALER_DIV_1=0,
    TIMER2_POSTSCALER_DIV_2,
    TIMER2_POSTSCALER_DIV_3,
    TIMER2_POSTSCALER_DIV_4,
    TIMER2_POSTSCALER_DIV_5,
    TIMER2_POSTSCALER_DIV_6,
    TIMER2_POSTSCALER_DIV_7,
    TIMER2_POSTSCALER_DIV_8,
    TIMER2_POSTSCALER_DIV_9,
    TIMER2_POSTSCALER_DIV_10,
    TIMER2_POSTSCALER_DIV_11,
    TIMER2_POSTSCALER_DIV_12,
    TIMER2_POSTSCALER_DIV_13,
    TIMER2_POSTSCALER_DIV_14,
    TIMER2_POSTSCALER_DIV_15,
    TIMER2_POSTSCALER_DIV_16
}timer2_postscaler_select_t;
typedef struct{
    #if TIMER2_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*timer2_interrupt_handler)(void);
    interrupt_priority_cfg priority;           /* @ref interrupt_priority_cfg */
    #endif
    timer2_postscaler_select_t postscaler_value; /* @ref timer2_postcaler_select_t*/
    uint8 preload_value;
    uint8 prescaler_value :2;
}timer2_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize timer2
 * @param timer2 refrence to timer2 configurations @ref timer2_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer2_init(const timer2_t *timer2);
/**
 * @brief write a value to timer2 counter
 * @param timer2 refrence to timer2 configurations @ref timer2_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer2_deinit(const timer2_t *timer2);
/**
 * @brief write a value to timer2 counter
 * @param timer2 refrence to timer2 configurations @ref timer2_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer2_write_value(const timer2_t *timer2,uint8 value);
/**
 * @brief read value from timer2 counter
 * @param timer2 refrence to timer1 configurations @ref timer2_t
 * @param value the value read
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer2_read_value(const timer2_t *timer2,uint8 *value);
#endif	/* HAL_TIMER2_H */

