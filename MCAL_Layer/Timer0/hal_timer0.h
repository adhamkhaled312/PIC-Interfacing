/* 
 * File:   hal_timer0.h
 * Author: ADHAM KHALED
 *
 * Created on August 31, 2023, 1:37 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H
/* ----------------Includes----------------*/
#include "../mcal_std_types.h"
#include "C:\Program Files (x86)\Microchip\MPLABX\v5.35\packs\Microchip\PIC18Fxxxx_DFP\1.2.26\xc8\pic\include\proc\pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* ----------------Macro Declarations---------------*/
#define TIMER0_PRESCALER_ENABLE_CFG     1
#define TIMER0_PRESCALER_DISABLE_CFG    0

#define TIMER0_RISING_EDGE_CFG          1
#define TIMER0_FALLING_EDGE_CFG         0

#define TIMER0_TIMER_MODE               1 
#define TIMER0_COUNTER_MODE             0 

#define TIMER0_8BIT_MODE               1
#define TIMER0_16BIT_MODE               0
/* ----------------Macro Functions Declarations----------------*/
#define TIMER0_ENABLE()              (T0CONbits.TMR0ON=1)
#define TIMER0_DISABLE()             (T0CONbits.TMR0ON=0)

#define TIMER0_PRESCALER_ENABLE()    (T0CONbits.PSA=0)
#define TIMER0_PRESCALER_DISABLE()   (T0CONbits.PSA=1)

#define TIMER0_RISING_EDGE_ENABLE()  (T0CONbits.T0SE=0)
#define TIMER0_FALLING_EDGE_ENABLE() (T0CONbits.T0SE=1)

#define TIMER0_TIMER_MODE_ENABLE()   (T0CONbits.T0CS=0)
#define TIMER0_COUNTER_MODE_ENABLE() (T0CONbits.T0CS=1)

#define TIMER0_8BITS_MODE_ENABLE()   (T0CONbits.T08BIT=1)
#define TIMER0_16BITS_MODE_ENABLE()   (T0CONbits.T08BIT=0)

/* ----------------Data Type Declarations----------------*/
/**
 * @brief prescaler value select 
 * @note this is used to use less than the frequency of the clock
 */
typedef enum{
    TIMER0_PRESCALER_DIV_2=0,
    TIMER0_PRESCALER_DIV_4,
    TIMER0_PRESCALER_DIV_8,
    TIMER0_PRESCALER_DIV_16,
    TIMER0_PRESCALER_DIV_32,
    TIMER0_PRESCALER_DIV_64,
    TIMER0_PRESCALER_DIV_128,
    TIMER0_PRESCALER_DIV_256
}timer0_prescaler_select_t;

typedef struct{
    #if TIMER0_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*timer0_interrupt_handler)(void);
    interrupt_priority_cfg priority;           /* @ref interrupt_priority_cfg */
    #endif
    timer0_prescaler_select_t prescaler_value; /* @ref timer0_prescaler_select_t*/
    uint16 preload_value;
    uint8 prescaler_enable :1;
    uint8 coutner_edge     :1;
    uint8 mode             :1;
    uint8 regitser_size    :1;
}timer0_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize timer0
 * @param timer0 refrence to timer0 configurations @ref timer0_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer0_init(const timer0_t *timer0);
/**
 * @brief write a value to timer0 counter
 * @param timer0 refrence to timer0 configurations @ref timer0_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer0_deinit(const timer0_t *timer0);
/**
 * @brief write a value to timer0 counter
 * @param timer0 refrence to timer0 configurations @ref timer0_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer0_write_value(const timer0_t *timer0,uint16 value);
/**
 * @brief read value from timer0 counter
 * @param timer0 refrence to timer0 configurations @ref timer0_t
 * @param value the value read
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer0_read_value(const timer0_t *timer0,uint16 *value);

#endif	/* HAL_TIMER0_H */

