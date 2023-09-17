/* 
 * File:   hal_timer1.c
 * Author: ADHAM KHALED
 *
 * Created on September 1, 2023, 12:44 PM
 */
#include "hal_timer1.h"
static inline void timer1_mode_cfg(const timer1_t *timer1);
static inline void timer1_register_rw_cfg(const timer1_t *timer1);
static inline void timer1_oscillator_cfg(const timer1_t *timer1);
static uint16 timer1_preload=0;
static interrupt_handler timer1_InterruptHandler=NULL;
void TIMER1_ISR(void){
    TIMER1_InterruptFlagClear();
    TMR1H=(timer1_preload)>>8;
    TMR1L=timer1_preload;
    if(timer1_InterruptHandler){
        timer1_InterruptHandler();
    }
}
/**
 * @brief initialize timer1
 * @param timer1 refrence to timer1 configurations @ref timer1_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer1_init(const timer1_t *timer1){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer1){
        retVal=E_NOT_OK;
    }
    else{
        TIMER1_DISABLE();
        T1CONbits.T1CKPS=timer1->prescaler_value;
        timer1_mode_cfg(timer1);
        timer1_register_rw_cfg(timer1);
        timer1_oscillator_cfg(timer1);
        TMR1H=(timer1->preload_value)>>8;
        TMR1L=(uint8)(timer1->preload_value);
        timer1_preload=timer1->preload_value;
        #if TIMER1_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY==timer1->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER1_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY==timer1->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER1_LowPrioritySet();
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        timer1_InterruptHandler=timer1->timer1_interrupt_handler;
        #endif
        TIMER1_ENABLE();
    }
    return retVal;
}
/**
 * @brief write a value to timer1 counter
 * @param timer1 refrence to timer1 configurations @ref timer1_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer1_deinit(const timer1_t *timer1){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer1){
        retVal=E_NOT_OK;
    }
    else{
        TIMER1_DISABLE();
        TIMER1_InterruptDisable();
    }
    return retVal;
}
/**
 * @brief write a value to timer1 counter
 * @param timer1 refrence to timer1 configurations @ref timer1_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer1_write_value(const timer1_t *timer1,uint16 value){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer1){
        retVal=E_NOT_OK;
    }
    else{
        TMR1H=value>>8;
        TMR1L=value;
    }
    return retVal;
}
/**
 * @brief read value from timer1 counter
 * @param timer1 refrence to timer1 configurations @ref timer1_t
 * @param value the value read
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer1_read_value(const timer1_t *timer1,uint16 *value){
    Std_ReturnType retVal=E_OK;
    uint8 l_tmr1l=0;
    uint8 l_tmr1h=0;
    if(NULL==timer1 || NULL==value){
        retVal=E_NOT_OK;
    }
    else{
        l_tmr1l=TMR1L;
        l_tmr1h=TMR1H;
        *value=(uint16)(l_tmr1l+(l_tmr1h<<8));
    }
    return retVal;
}
static inline void timer1_mode_cfg(const timer1_t *timer1){
    if(TIMER1_TIMER_MODE==timer1->mode){
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(TIMER1_COUNTER_MODE==timer1->mode){
        TIMER1_COUNTER_MODE_ENABLE();
        if(TIMER1_ASYNCHRONOUS_MODE==timer1->counter_mode){
            TIMER1_ASYNCHRONIZE_COUNTER_ENABLE();
        }
        else if(TIMER1_SYNCHRONOUS_MODE==timer1->counter_mode){
            TIMER1_SYNCHRONIZE_COUNTER_ENABLE();
        }
    }
}
static inline void timer1_register_rw_cfg(const timer1_t *timer1){
    if(TIMER1_READ_WRITE_8BITS_MODE==timer1->reg_rw_mode){
        TIMER1_READ_WRITE_8BITS_MODE_ENABLE();

    }
    else if(TIMER1_READ_WRITE_16BITS_MODE==timer1->reg_rw_mode){
        TIMER1_READ_WRITE_16BITS_MODE_ENABLE();
        
    }
}
static inline void timer1_oscillator_cfg(const timer1_t *timer1){
    if(TIMER1_OSCILLATOR_ENABLE_MODE==timer1->oscillator_mode){
        TIMER1_OSCILLATOR_ENABLE();
    }
    else if(TIMER1_OSCILLATOR_DISABLE_MODE==timer1->oscillator_mode){
        TIMER1_OSCILLATOR_DISABLE();
    }
} 