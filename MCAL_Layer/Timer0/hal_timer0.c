/* 
 * File:   hal_timer0.c
 * Author: ADHAM KHALED
 *
 * Created on August 31, 2023, 1:37 AM
 */
#include "hal_timer0.h"
static inline void timer0_prescaler_cfg(const timer0_t *timer0);
static inline void timer0_mode_cfg(const timer0_t *timer0);
static inline void timer0_register_size_cfg(const timer0_t *timer0);

static uint16 timer0_preload=0;
static interrupt_handler timer0_InterruptHandler=NULL;
/* Helper function for timer0 interrupt */
void TIMER0_ISR(void){
    TIMER0_InterruptFlagClear();
    TMR0H=(timer0_preload)>>8;
    TMR0L=timer0_preload;
    if(timer0_InterruptHandler){
        timer0_InterruptHandler();
    }
}
/**
 * @brief initialize timer0
 * @param timer0 refrence to timer0 configurations @ref timer0_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer0_init(const timer0_t *timer0){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer0){
        retVal=E_NOT_OK;
    }
    else{
        TIMER0_DISABLE();
        timer0_prescaler_cfg(timer0);
        timer0_mode_cfg(timer0);
        timer0_register_size_cfg(timer0);
        TMR0H=(timer0->preload_value)>>8;
        TMR0L=(uint8)(timer0->preload_value);
        timer0_preload=timer0->preload_value;
        #if TIMER0_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY==timer0->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY==timer0->priority){
            INTERRUPT_GlobalInterruptLowEnable()
            TIMER0_LowPrioritySet();
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        timer0_InterruptHandler=timer0->timer0_interrupt_handler;
        #endif
        TIMER0_ENABLE();
    }
    return retVal;
}
/**
 * @brief de initialize timer0
 * @param timer0 refrence to timer0 configurations @ref timer0_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer0_deinit(const timer0_t *timer0){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer0){
        retVal=E_NOT_OK;
    }
    else{
        TIMER0_DISABLE();
        TIMER0_InterruptDisable();
    }
    return retVal;
}
/**
 * @brief write a value to timer0 counter
 * @param timer0 refrence to timer0 configurations @ref timer0_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer0_write_value(const timer0_t *timer0,uint16 value){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer0){
        retVal=E_NOT_OK;
    }
    else{
        TMR0H=value>>8;
        TMR0L=value;
    }
    return retVal;
}
/**
 * @brief read value from timer0 counter
 * @param timer0 refrence to timer0 configurations @ref timer0_t
 * @param value the value read
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer0_read_value(const timer0_t *timer0,uint16 *value){
    Std_ReturnType retVal=E_OK;
    uint8 l_tmr0l=0;
    uint8 l_tmr0h=0;
    if(NULL==timer0 || NULL==value){
        retVal=E_NOT_OK;
    }
    else{
        l_tmr0l=TMR0L;
        l_tmr0h=TMR0H;
        *value=(uint16)(l_tmr0l+(l_tmr0h<<8));
    }
    return retVal;
}
static inline void timer0_prescaler_cfg(const timer0_t *timer0){
    if(TIMER0_PRESCALER_ENABLE_CFG==timer0->prescaler_enable){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS=timer0->prescaler_value;
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG==timer0->prescaler_enable){
        TIMER0_PRESCALER_DISABLE();
    }
}
static inline void timer0_mode_cfg(const timer0_t *timer0){
    if(TIMER0_TIMER_MODE==timer0->mode){
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if(TIMER0_COUNTER_MODE==timer0->mode){
        TIMER0_COUNTER_MODE_ENABLE();
        if(TIMER0_RISING_EDGE_CFG==timer0->coutner_edge){
            TIMER0_RISING_EDGE_ENABLE();
        }
        else if(TIMER0_FALLING_EDGE_CFG==timer0->coutner_edge){
            TIMER0_FALLING_EDGE_ENABLE();
        }
    }
}
static inline void timer0_register_size_cfg(const timer0_t *timer0){
    if(TIMER0_16BIT_MODE==timer0->regitser_size){
        TIMER0_16BITS_MODE_ENABLE();
    }
    else if(TIMER0_8BIT_MODE==timer0->regitser_size){
        TIMER0_8BITS_MODE_ENABLE();
    }
}