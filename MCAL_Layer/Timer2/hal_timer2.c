/* 
 * File:   hal_timer2.c
 * Author: ADHAM KHALED
 *
 * Created on September 1, 2023, 10:36 PM
 */
#include "hal_timer2.h"
static uint8 timer2_preload=0;
static interrupt_handler timer2_InterruptHandler=NULL;
void TIMER2_ISR(void){
    TIMER2_InterruptFlagClear();
    TMR2=timer2_preload;
    if(timer2_InterruptHandler){
        timer2_InterruptHandler();
    }
}
/**
 * @brief initialize timer2
 * @param timer2 refrence to timer2 configurations @ref timer2_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer2_init(const timer2_t *timer2){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer2){
        retVal=E_NOT_OK;
    }
    else{
        TIMER2_DISABLE();
        TIMER2_PRESCALER_SET(timer2->prescaler_value);
        TIMER2_POSTSCALER_SET(timer2->postscaler_value);
        TMR2=timer2->preload_value;
        timer2_preload=timer2->preload_value;
        #if TIMER1_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY==timer1->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER2_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY==timer1->priority){
            INTERRUPT_GlobalInterruptLowEnable()
            TIMER2_LowPrioritySet();
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        timer2_InterruptHandler=timer2->timer2_interrupt_handler;
        #endif
        TIMER2_ENABLE();
    }
    return retVal;
}
/**
 * @brief write a value to timer2 counter
 * @param timer2 refrence to timer2 configurations @ref timer2_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer2_deinit(const timer2_t *timer2){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer2){
        retVal=E_NOT_OK;
    }
    else{
        TIMER2_DISABLE();
        TIMER2_InterruptDisable();
    }
    return retVal;
}
/**
 * @brief write a value to timer2 counter
 * @param timer2 refrence to timer2 configurations @ref timer2_t
 * @param value the value to be written 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer2_write_value(const timer2_t *timer2,uint8 value){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer2){
        retVal=E_NOT_OK;
    }
    else{
        TMR2=value;
    }
    return retVal;
}
/**
 * @brief read value from timer2 counter
 * @param timer2 refrence to timer1 configurations @ref timer2_t
 * @param value the value read
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType timer2_read_value(const timer2_t *timer2,uint8 *value){
    Std_ReturnType retVal=E_OK;
    if(NULL==timer2 || NULL==value){
        retVal=E_NOT_OK;
    }
    else{
        *value=TMR2;
    }
    return retVal;
}