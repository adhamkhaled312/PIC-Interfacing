/* 
 * File:   hal_timer3.h
 * Author: ADHAM KHALED
 *
 * Created on September 2, 2023, 12:38 AM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* ----------------Includes----------------*/
#include "../mcal_std_types.h"
#include "C:\Program Files (x86)\Microchip\MPLABX\v5.35\packs\Microchip\PIC18Fxxxx_DFP\1.2.26\xc8\pic\include\proc\pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* ----------------Macro Declarations---------------*/
#define TIMER3_TIMER_MODE               1 
#define TIMER3_COUNTER_MODE             0 

#define TIMER3_READ_WRITE_8BITS_MODE    1
#define TIMER3_READ_WRITE_16BITS_MODE   0

#define TIMER3_SYNCHRONOUS_MODE         1
#define TIMER3_ASYNCHRONOUS_MODE        0

#define TIMER3_OSCILLATOR_ENABLE_MODE   1
#define TIMER3_OSCILLATOR_DISABLE_MODE  0
/* ----------------Macro Functions Declarations----------------*/
#define TIMER3_ENABLE()                        (T3CONbits.TMR3ON=1)
#define TIMER3_DISABLE()                       (T3CONbits.TMR3ON=0)

#define TIMER3_SYNCHRONIZE_COUNTER_ENABLE()    (T3CONbits.T3SYNC=0)
#define TIMER3_ASYNCHRONIZE_COUNTER_ENABLE()   (T3CONbits.T3SYNC=1)

#define TIMER3_TIMER_MODE_ENABLE()             (T3CONbits.TMR3CS=0)
#define TIMER3_COUNTER_MODE_ENABLE()           (T3CONbits.TMR3CS=1)

#define TIMER3_READ_WRITE_8BITS_MODE_ENABLE()  (T3CONbits.RD16=0)
#define TIMER3_READ_WRITE_16BITS_MODE_ENABLE() (T3CONbits.RD16=1)

/* ----------------Data Type Declarations----------------*/
/**
 * @brief prescaler value select 
 * @note this is used to use less than the frequency of the clock
 */
typedef enum{
    TIMER3_PRESCALER_DIV_1=0,
    TIMER3_PRESCALER_DIV_2,
    TIMER3_PRESCALER_DIV_4,
    TIMER3_PRESCALER_DIV_8,
}timer3_prescaler_select_t;
typedef struct{
    #if TIMER1_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*timer3_interrupt_handler)(void);
    interrupt_priority_cfg priority;           /* @ref interrupt_priority_cfg */
    #endif
    timer3_prescaler_select_t prescaler_value; /* @ref timer1_prescaler_select_t*/
    uint16 preload_value;
    uint8 mode             :1;
    uint8 counter_mode     :1;
    uint8 reg_rw_mode      :1;

}timer3_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize timer3
 * @param timer3 refrence to timer3 configurations @ref timer3_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer3_init(const timer3_t *timer3);
/**
 * @brief write a value to timer3 counter
 * @param timer3 refrence to timer3 configurations @ref timer3_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer3_deinit(const timer3_t *timer3);
/**
 * @brief write a value to timer3 counter
 * @param timer3 refrence to timer3 configurations @ref timer3_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer3_write_value(const timer3_t *timer3,uint16 value);
/**
 * @brief read value from timer3 counter
 * @param timer3 refrence to timer3 configurations @ref timer3_t
 * @param value the value read
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer3_read_value(const timer3_t *timer3,uint16 *value);
#endif	/* HAL_TIMER3_H */

