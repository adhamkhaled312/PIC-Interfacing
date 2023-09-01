/* 
 * File:   hal_timer1.h
 * Author: ADHAM KHALED
 *
 * Created on September 1, 2023, 12:44 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H
/* ----------------Includes----------------*/
#include "../mcal_std_types.h"
#include "C:\Program Files (x86)\Microchip\MPLABX\v5.35\packs\Microchip\PIC18Fxxxx_DFP\1.2.26\xc8\pic\include\proc\pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* ----------------Macro Declarations---------------*/

#define TIMER1_TIMER_MODE               1 
#define TIMER1_COUNTER_MODE             0 

#define TIMER1_READ_WRITE_8BITS_MODE    1
#define TIMER1_READ_WRITE_16BITS_MODE   0

#define TIMER1_SYNCHRONOUS_MODE         1
#define TIMER1_ASYNCHRONOUS_MODE        0

#define TIMER1_OSCILLATOR_ENABLE_MODE   1
#define TIMER1_OSCILLATOR_DISABLE_MODE  0
/* ----------------Macro Functions Declarations----------------*/
#define TIMER1_ENABLE()                        (T1CONbits.TMR1ON=1)
#define TIMER1_DISABLE()                       (T1CONbits.TMR1ON=0)

#define TIMER1_SYSTEM_CLOCK_STATUS()           (T1CONbits.T1RUN)

#define TIMER1_SYNCHRONIZE_COUNTER_ENABLE()    (T1CONbits.T1SYNC=0)
#define TIMER1_ASYNCHRONIZE_COUNTER_ENABLE()   (T1CONbits.T1SYNC=1)

#define TIMER1_TIMER_MODE_ENABLE()             (T1CONbits.TMR1CS=0)
#define TIMER1_COUNTER_MODE_ENABLE()           (T1CONbits.TMR1CS=1)

#define TIMER1_OSCILLATOR_ENABLE()             (T1CONbits.T1OSCEN=1)
#define TIMER1_OSCILLATOR_DISABLE()          (T1CONbits.T1OSCEN=0)

#define TIMER1_READ_WRITE_8BITS_MODE_ENABLE()  (T1CONbits.RD16=0)
#define TIMER1_READ_WRITE_16BITS_MODE_ENABLE() (T1CONbits.RD16=1)

/* ----------------Data Type Declarations----------------*/
/**
 * @brief prescaler value select 
 * @note this is used to use less than the frequency of the clock
 */
typedef enum{
    TIMER1_PRESCALER_DIV_1=0,
    TIMER1_PRESCALER_DIV_2,
    TIMER1_PRESCALER_DIV_4,
    TIMER1_PRESCALER_DIV_8,
}timer1_prescaler_select_t;
typedef struct{
    #if TIMER1_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*timer1_interrupt_handler)(void);
    interrupt_priority_cfg priority;           /* @ref interrupt_priority_cfg */
    #endif
    timer1_prescaler_select_t prescaler_value; /* @ref timer1_prescaler_select_t*/
    uint16 preload_value;
    uint8 mode             :1;
    uint8 counter_mode     :1;
    uint8 oscillator_mode  :1;
    uint8 reg_rw_mode      :1;

}timer1_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize timer1
 * @param timer1 refrence to timer1 configurations @ref timer1_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer1_init(const timer1_t *timer1);
/**
 * @brief write a value to timer1 counter
 * @param timer1 refrence to timer1 configurations @ref timer1_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer1_deinit(const timer1_t *timer1);
/**
 * @brief write a value to timer1 counter
 * @param timer1 refrence to timer1 configurations @ref timer1_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer1_write_value(const timer1_t *timer1,uint16 value);
/**
 * @brief read value from timer1 counter
 * @param timer1 refrence to timer1 configurations @ref timer1_t
 * @param value the value read
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer1_read_value(const timer1_t *timer1,uint16 *value);

#endif	/* HAL_TIMER1_H */

