/* 
 * File:   hal_timer3.c
 * Author: ADHAM KHALED
 *
 * Created on September 2, 2023, 12:38 AM
 */
#include "hal_timer3.h"
static inline void timer3_mode_cfg(const timer3_t *timer3);
static inline void timer3_register_rw_cfg(const timer3_t *timer3);
static uint16 timer3_preload=0;
static interrupt_handler timer3_InterruptHandler=NULL;
void TIMER3_ISR(void){
    TIMER3_InterruptFlagClear();
    TMR3H=(timer3_preload)>>8;
    TMR3L=timer3_preload;
    if(timer3_InterruptHandler){
        timer3_InterruptHandler();
    }
}
/**
 * @brief initialize timer3
 * @param timer3 refrence to timer3 configurations @ref timer3_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer3_init(const timer3_t *timer3){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer3){
        retVal=E_NOT_OK;
    }
    else{
        TIMER3_DISABLE();
        T3CONbits.T3CKPS=timer3->prescaler_value;
        timer3_mode_cfg(timer3);
        timer3_register_rw_cfg(timer3);
        TMR3H=(timer3->preload_value)>>8;
        TMR3L=(uint8)(timer3->preload_value);
        timer3_preload=timer3->preload_value;
        #if TIMER3_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY==timer3->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER3_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY==timer3->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER3_LowPrioritySet();
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        timer3_InterruptHandler=timer3->timer3_interrupt_handler;
        #endif
        TIMER3_ENABLE();
    }
    return retVal;
}
/**
 * @brief write a value to timer3 counter
 * @param timer3 refrence to timer3 configurations @ref timer3_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer3_deinit(const timer3_t *timer3){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer3){
        retVal=E_NOT_OK;
    }
    else{
        TIMER3_DISABLE();
        TIMER3_InterruptDisable();
    }
    return retVal;
}
/**
 * @brief write a value to timer3 counter
 * @param timer3 refrence to timer3 configurations @ref timer3_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer3_write_value(const timer3_t *timer3,uint16 value){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer3){
        retVal=E_NOT_OK;
    }
    else{
        TMR3H=value>>8;
        TMR3L=value;
    }
    return retVal;
}
/**
 * @brief read value from timer3 counter
 * @param timer3 refrence to timer3 configurations @ref timer3_t
 * @param value the value read
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer3_read_value(const timer3_t *timer3,uint16 *value){
    Std_ReturnType retVal=E_OK;
    uint8 l_tmr3l=0;
    uint8 l_tmr3h=0;
    if(NULL==timer3 || NULL==value){
        retVal=E_NOT_OK;
    }
    else{
        l_tmr3l=TMR3L;
        l_tmr3h=TMR3H;
        *value=(uint16)(l_tmr3l+(l_tmr3h<<8));
    }
    return retVal;
}
static inline void timer3_mode_cfg(const timer3_t *timer3){
    if(TIMER3_TIMER_MODE==timer3->mode){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(TIMER3_COUNTER_MODE==timer3->mode){
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_ASYNCHRONOUS_MODE==timer3->counter_mode){
            TIMER3_ASYNCHRONIZE_COUNTER_ENABLE();
        }
        else if(TIMER3_SYNCHRONOUS_MODE==timer3->counter_mode){
            TIMER3_SYNCHRONIZE_COUNTER_ENABLE();
        }
    }
}
static inline void timer3_register_rw_cfg(const timer3_t *timer3){
    if(TIMER3_READ_WRITE_8BITS_MODE==timer3->reg_rw_mode){
        TIMER3_READ_WRITE_8BITS_MODE_ENABLE();
    }
    else if(TIMER3_READ_WRITE_16BITS_MODE==timer3->reg_rw_mode){
        TIMER3_READ_WRITE_16BITS_MODE_ENABLE();
    }
}
