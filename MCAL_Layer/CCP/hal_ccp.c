/* 
 * File:   hal_ccp1.c
 * Author: ADHAM KHALED
 *
 * Created on September 17, 2023, 1:55 PM
 */
#include "hal_ccp.h"
static interrupt_handler ccp1_InterruptHandler=NULL;
static interrupt_handler ccp2_InterruptHandler=NULL;
static void ccp_interrupt_config(const ccp_t* ccp_obj);
static void ccp_pwm_cfg(const ccp_t* ccp_obj);
static void ccp_capture_timer_select(const ccp_t* ccp_obj);
static Std_ReturnType ccp_capture_cfg(const ccp_t* ccp_obj);
static Std_ReturnType ccp_compare_cfg(const ccp_t* ccp_obj);
void CCP1_ISR(void){
    CCP1_InterruptFlagClear();
    if(ccp1_InterruptHandler){
        ccp1_InterruptHandler();
    }
}
void CCP2_ISR(void){
    CCP2_InterruptFlagClear();
    if(ccp2_InterruptHandler){
        ccp2_InterruptHandler();
    }
}
Std_ReturnType ccp_init(const ccp_t* ccp_obj){
    Std_ReturnType retVal=E_OK;
    if(NULL==ccp_obj){
        retVal=E_NOT_OK;
    }
    else{
        if(CCP1_INST==ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if(CCP2_INST==ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        if(CCP_CAPTURE_MODE_SELECT==ccp_obj->ccp_mode){
            retVal=ccp_capture_cfg(ccp_obj);
        }
        else if(CCP_COMPARE_MODE_SELECT==ccp_obj->ccp_mode){
            retVal=ccp_compare_cfg(ccp_obj);
        }
        #if (CCP1_CFG_SELECT_MODE==CCP_CFG_PWM_MODE_SELECT || CCP2_CFG_SELECT_MODE==CCP_CFG_PWM_MODE_SELECT)
        else if(CCP_PWM_MODE_SEELCT==ccp_obj->ccp_mode){    
            ccp_pwm_cfg(ccp_obj);
        }
        #endif
        retVal=gpio_pin_initialize(&(ccp_obj->pin));
        ccp_interrupt_config(ccp_obj);
    }
    return retVal;
}
Std_ReturnType ccp_deinit(const ccp_t* ccp_obj){
    Std_ReturnType retVal=E_OK;
    if(NULL==ccp_obj){
        retVal=E_NOT_OK;
    }
    else{
        if(CCP1_INST==ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
            #if CCP1_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP1_InterruptDisable();
            #endif
        }
        else if(CCP2_INST==ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
            #if CCP2_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP2_InterruptDisable();
            #endif
        }
    }
    return retVal;
}
#if (CCP1_CFG_SELECT_MODE==CCP_CFG_CAPTURE_MODE_SELECT || CCP2_CFG_SELECT_MODE==CCP_CFG_CAPTURE_MODE_SELECT)
Std_ReturnType ccp_capture_IsCaptureReady(uint8* status){
    Std_ReturnType retVal=E_OK;
    if(NULL==status){
        retVal=E_NOT_OK;
    }
    else{
        if(PIR1bits.CCP1IF==CCP_CAPTURE_READY){
            *status=CCP_CAPTURE_READY;
            CCP1_InterruptFlagClear();
        }
        else{
            *status=CCP_CAPTURE_NOT_READY;
        }
    }
    return retVal;
}
Std_ReturnType ccp_capture_read_value(uint16* value){
    Std_ReturnType retVal=E_OK;
    CCP_PERIOD_REG_T capture_temp_value;
    if(NULL==value){
        retVal=E_NOT_OK;
    }
    else{
        capture_temp_value.ccp_low=CCPR1L;
        capture_temp_value.ccp_high=CCPR1H;
        *value=capture_temp_value.ccp_16_bit;
    }
    return retVal;
}
#endif
#if (CCP1_CFG_SELECT_MODE==CCP_CFG_COMPARE_MODE_SELECT || CCP2_CFG_SELECT_MODE==CCP_CFG_COMPARE_MODE_SELECT)
Std_ReturnType ccp_compare_IsCompareComplete(uint8* status){
    Std_ReturnType retVal=E_OK;
    if(NULL==status){
        retVal=E_NOT_OK;
    }
    else{
        if(PIR1bits.CCP1IF==CCP_COMPARE_READY){
            *status=CCP_COMPARE_READY;
            CCP1_InterruptFlagClear();
        }
        else{
            *status=CCP_COMPARE_NOT_READY;
        }
    }
    return retVal;
}
Std_ReturnType ccp_compare_set_value(const ccp_t* ccp_obj,uint16 value){
    Std_ReturnType retVal=E_OK;
    if(NULL==ccp_obj){
        retVal=E_NOT_OK;
    }
    else{
        CCP_PERIOD_REG_T capture_temp_value;
        capture_temp_value.ccp_16_bit=value;
        if(CCP1_INST==ccp_obj->ccp_inst){
            CCPR1L=capture_temp_value.ccp_low;
            CCPR1H=capture_temp_value.ccp_high;
        }
        else if(CCP2_INST==ccp_obj->ccp_inst){
            CCPR2L=capture_temp_value.ccp_low;
            CCPR2H=capture_temp_value.ccp_high;
        }
    }
    return retVal;
}   
#endif
#if (CCP1_CFG_SELECT_MODE==CCP_CFG_PWM_MODE_SELECT || CCP2_CFG_SELECT_MODE==CCP_CFG_PWM_MODE_SELECT)
Std_ReturnType ccp_pwm_set_duty(const ccp_t* ccp_obj,const uint8 duty){
    Std_ReturnType retVal=E_OK;
    if(NULL==ccp_obj){
        retVal=E_NOT_OK;
    }
    else{
        uint16 duty_temp=(uint16)((PR2+1)*(duty/100.0)*4);
        if(CCP1_INST==ccp_obj->ccp_inst){
            CCP1CONbits.DC1B=(uint8)(duty_temp&0x0003);
            CCPR1L=(uint8)(duty_temp>>2);
        }
        else if(CCP2_INST==ccp_obj->ccp_inst){
            CCP2CONbits.DC2B=(uint8)(duty_temp&0x0003);
            CCPR2L=(uint8)(duty_temp>>2);
        }
    }
    return retVal;
}
Std_ReturnType ccp_pwm_start(const ccp_t* ccp_obj){
    Std_ReturnType retVal=E_OK;
    if(NULL==ccp_obj){
        retVal=E_NOT_OK;
    }
    else{
        if(CCP1_INST==ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M=CCP_PMW_MODE;
        }
        else if(CCP2_INST==ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M=CCP_PMW_MODE;
        }
    }
    return retVal;
}
Std_ReturnType ccp_pwm_stop(const ccp_t* ccp_obj){
    Std_ReturnType retVal=E_OK;
    if(NULL==ccp_obj){
        retVal=E_NOT_OK;
    }
    else{
        if(CCP1_INST==ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M=CCP_MODULE_DISABLE;
        }
        else if(CCP2_INST==ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M=CCP_MODULE_DISABLE;
        }
    }
    return retVal;
}
#endif

static void ccp_interrupt_config(const ccp_t* ccp_obj){
    #if CCP1_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP1_InterruptEnable();
    CCP1_InterruptFlagClear();
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelEnable();
    if(INTERRUPT_HIGH_PRIORITY==ccp_obj->ccp1_priority){
        INTERRUPT_GlobalInterruptHighEnable();
        CCP1_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY==ccp_obj->ccp1_priority){
        INTERRUPT_GlobalInterruptLowEnable();
        CCP1_LowPrioritySet();
    }
    #else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    #endif
    ccp1_InterruptHandler=ccp_obj->ccp1_interrupt_handler;
    #endif
    #if CCP2_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP2_InterruptEnable();
    CCP2_InterruptFlagClear();
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelEnable();
    if(INTERRUPT_HIGH_PRIORITY==ccp_obj->ccp2_priority){
        INTERRUPT_GlobalInterruptHighEnable();
        CCP2_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY==ccp_obj->ccp2_priority){
        INTERRUPT_GlobalInterruptLowEnable();
        CCP2_LowPrioritySet();
    }
    #else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    #endif
    ccp2_InterruptHandler=ccp_obj->ccp2_interrupt_handler;
    #endif
}
#if (CCP1_CFG_SELECT_MODE==CCP_CFG_PWM_MODE_SELECT || CCP2_CFG_SELECT_MODE==CCP_CFG_PWM_MODE_SELECT)
static void ccp_pwm_cfg(const ccp_t* ccp_obj){
    if(CCP1_INST==ccp_obj->ccp_inst){
        if(CCP_PMW_MODE==ccp_obj->ccp_mode_variant){
            CCP1_SET_MODE(CCP_PMW_MODE);
        }
        else{ /* Nothing */}   
    }
    else if(CCP2_INST==ccp_obj->ccp_inst){
        if(CCP_PMW_MODE==ccp_obj->ccp_mode_variant){
            CCP2_SET_MODE(CCP_PMW_MODE);
        }
        else{/* Nothing */}
}   
    PR2=(uint8)((_XTAL_FREQ/(ccp_obj->pwm_frequency*4.0*ccp_obj->timer2_postscaler*ccp_obj->timer2_prescaler))-1);
}
#endif
static void ccp_capture_timer_select(const ccp_t* ccp_obj){
    if(ccp_obj->ccp_capture_timer==CCP1_CCP2_TIMER1){
        T3CONbits.T3CCP1=0;
        T3CONbits.T3CCP2=0;
    }
    else if(ccp_obj->ccp_capture_timer==CCP1_CCP2_TIMER3){
        T3CONbits.T3CCP1=0;
        T3CONbits.T3CCP2=1;
    }
    else if(ccp_obj->ccp_capture_timer==CCP1_TIMER1_CCP2_TIMER3){
        T3CONbits.T3CCP1=1;
        T3CONbits.T3CCP2=0;
    }
    
}
static Std_ReturnType ccp_compare_cfg(const ccp_t* ccp_obj){
    Std_ReturnType retVal=E_OK;
    if(CCP1_INST==ccp_obj->ccp_inst){
        switch (ccp_obj->ccp_mode_variant){
            case CCP_COMPARE_MODE_TOGGLE:
                CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE);
                break;
            case CCP_COMPARE_MODE_SET_PIN_LOW:
                CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH:
                CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                break;
            case CCP_COMPARE_MODE_GEN_INTERRUPT:
                CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_INTERRUPT);
                break;
            case CCP_COMPARE_MODE_GEN_EVENT:
                CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                break;
            default:
                retVal=E_NOT_OK;
                break;
            }
        }
    else if(CCP2_INST==ccp_obj->ccp_inst){
        switch (ccp_obj->ccp_mode_variant){
            case CCP_COMPARE_MODE_TOGGLE:
                CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE);
                break;
            case CCP_COMPARE_MODE_SET_PIN_LOW:
                CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH:
                CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                break;
            case CCP_COMPARE_MODE_GEN_INTERRUPT:
                CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_INTERRUPT);
                break;
            case CCP_COMPARE_MODE_GEN_EVENT:
                CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                break;
            default:
                retVal=E_NOT_OK;
                break;
            }
}
    ccp_capture_timer_select(ccp_obj);
    return retVal;
}
static Std_ReturnType ccp_capture_cfg(const ccp_t* ccp_obj){
    Std_ReturnType retVal=E_OK;
    if(CCP1_INST==ccp_obj->ccp_inst){
        switch (ccp_obj->ccp_mode_variant){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE:
                CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE:
                CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE:
                CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                break;
            default:
                retVal=E_NOT_OK;
                break;
            }
        }
    else if(CCP2_INST==ccp_obj->ccp_inst){
        switch (ccp_obj->ccp_mode_variant){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE:
                CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE:
                CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE:
                CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                break;
            default:
                retVal=E_NOT_OK;
                break;
            }
}
    ccp_capture_timer_select(ccp_obj);
    return retVal;
}