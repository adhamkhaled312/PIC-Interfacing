/* 
 * File:   hal_adc.c
 * Author: ADHAM KHALED
 *
 * Created on August 26, 2023, 1:34 PM
 */
#include "hal_adc.h"
static interrupt_handler ADC_InteruuptHandler=NULL;
/* Helper function for ADC interrupt */
void ADC_ISR(void){
    ADC_InterruptFlagClear();
    if(ADC_InteruuptHandler){
        ADC_InteruuptHandler();
    }
}
static inline void adc_input_channel_config(adc_channel_select_t channel);
static inline void select_result_format(const adc_config_t* adc);
static inline void select_voltage_refrence(const adc_config_t* adc);
/**
 * @brief initialize ADC
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_init(const adc_config_t*adc){
    Std_ReturnType retVal=E_OK;
    if(NULL==adc){
        retVal=E_NOT_OK;
    }
    else{
        ADC_CONVERTER_DISABLE();
        ADCON2bits.ACQT=adc->acquisition_time;
        ADCON2bits.ADCS=adc->converstion_time;
        ADCON0bits.CHS=adc->channel;
        #if ADC_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY==adc->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            ADC_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY==adc->priority){
            INTERRUPT_GlobalInterruptLowEnable()
            ADC_LowPrioritySet();
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        ADC_InteruuptHandler=adc->adc_interrupt_handler;
        #endif
        adc_input_channel_config(adc->channel);
        select_voltage_refrence(adc);  
        select_result_format(adc);
        ADC_CONVERTER_ENABLE();
    }
    return retVal;
}
/**
 * @brief deinitialize ADC (Disable)
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_DeInit(const adc_config_t*adc){
    Std_ReturnType retVal=E_OK;
    if(NULL==adc){
        retVal=E_NOT_OK;
    }
    else{
        ADC_CONVERTER_DISABLE();
        #if ADC_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_InterruptDisable();
        #endif
    }
    return retVal;
}
/**
 * @brief select another channel for the ADC
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @param channel 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_select_channel(const adc_config_t*adc,adc_channel_select_t channel){
    Std_ReturnType retVal=E_OK;
    if(NULL==adc){
        retVal=E_NOT_OK;
    }
    else{
        ADCON0bits.CHS=channel;
        adc_input_channel_config(channel);

    }
    return retVal;
}
/**
 * @brief start conversion
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_start_conversion(const adc_config_t* adc){
    Std_ReturnType retVal=E_OK;
    if(NULL==adc){
        retVal=E_NOT_OK;
    }
    else{
        ADC_START_CONVERSION();
    }
    return retVal;
}
/**
 * @brief check if the conversion is finished
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @param status the conversion status
 *               1: conversion is done
 *               0: conversion is in progress
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_is_conversion_done(const adc_config_t* adc,uint8 *status){
    Std_ReturnType retVal=E_OK;
    if(NULL==adc || NULL==status){
        retVal=E_NOT_OK;
    }
    else{
        *status=(uint8)(!(ADC_CONVERTION_STATUS()));
    }
    return retVal;
}
/**
 * @brief return the value of the conversion
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @param data the converted value
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_read_conversion_result(const adc_config_t *adc,adc_conversion_result *data){
    Std_ReturnType retVal=E_OK;
    if(NULL==adc || NULL==data){
        retVal=E_NOT_OK;
    }
    else{
        if(adc->result_format==ADC_RESULT_RIGHT){
            *data=(adc_conversion_result)((ADRESH<<8)+ADRESL);

        }
        else if(adc->result_format==ADC_RESULT_LEFT){
            *data=(adc_conversion_result)(((ADRESH<<8)+ADRESL)>>6);
        }
        else{
            *data=(adc_conversion_result)((ADRESH<<8)+ADRESL);
        }
        
    }
    return retVal;
}
/**
 * @brief return the value of conversion with selecting the channel for conversion 
 *        the function works with blocking (the program stops until conversion is done)
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @param channel the channel for conversion
 * @param data the converted value
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_get_conversion_blocking(const adc_config_t *adc,adc_channel_select_t channel,adc_conversion_result *data){
    Std_ReturnType retVal=E_OK;
    uint8 status;
    if(NULL==adc || NULL==data){
        retVal=E_NOT_OK;
    }
    else{
        retVal=adc_select_channel(adc,channel);
        retVal=adc_start_conversion(adc);
        retVal=adc_is_conversion_done(adc,&status);
        while(ADC_CONVERTION_STATUS());
        retVal=adc_read_conversion_result(adc,data);
    }
    return retVal;
}
/**
 * @brief return the value of conversion with selecting the channel for conversion 
 *        the function works with interrupt so interrupt must be enabled to use this function
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @param channel the channel for conversion
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_start_conversion_interrupt(const adc_config_t *adc,adc_channel_select_t channel){
    Std_ReturnType retVal=E_OK;
    uint8 status;
    if(NULL==adc){
        retVal=E_NOT_OK;
    }
    else{
        retVal=adc_select_channel(adc,channel);
        retVal=adc_start_conversion(adc);

    }
    return retVal;
}
static inline void adc_input_channel_config(adc_channel_select_t channel){
    Std_ReturnType retVal=E_OK;
    switch (channel)
    {
    case ADC_CHANNEL_AN0:
        SET_BIT(TRISA,_TRISA_RA0_POSITION);
        break;  
    case ADC_CHANNEL_AN1:
        SET_BIT(TRISA,_TRISA_RA1_POSITION);
        break;
    case ADC_CHANNEL_AN2:
        SET_BIT(TRISA,_TRISA_RA2_POSITION);
        break;
    case ADC_CHANNEL_AN3:
        SET_BIT(TRISA,_TRISA_RA3_POSITION);
        break;
    case ADC_CHANNEL_AN4:
        SET_BIT(TRISA,_TRISA_RA5_POSITION);
        break;
    case ADC_CHANNEL_AN5:
        SET_BIT(TRISE,_TRISE_RE0_POSITION);
        break;
    case ADC_CHANNEL_AN6:
        SET_BIT(TRISE,_TRISE_RE1_POSITION);
        break;
    case ADC_CHANNEL_AN7:
        SET_BIT(TRISE,_TRISE_RE2_POSITION);
        break;
    case ADC_CHANNEL_AN8:
        SET_BIT(TRISB,_TRISB_RB2_POSITION);
        break;
    case ADC_CHANNEL_AN9:
        SET_BIT(TRISB,_TRISB_RB3_POSITION);
        break;
    case ADC_CHANNEL_AN10:
        SET_BIT(TRISB,_TRISB_RB1_POSITION);
        break;
    case ADC_CHANNEL_AN11:
        SET_BIT(TRISB,_TRISB_RB4_POSITION);
        break;
    case ADC_CHANNEL_AN12:
        SET_BIT(TRISB,_TRISB_RB0_POSITION);
        break;        
    default:
        ;
    }
}
static inline void select_result_format(const adc_config_t* adc){
    if(adc->result_format==ADC_RESULT_RIGHT){
        ADC_RESULT_RIGHT_JUSTIFIED();
    }
    else if(adc->result_format==ADC_RESULT_LEFT){
        ADC_RESULT_LEFT_JUSTIFIED();
    }
    else{
        ADC_RESULT_RIGHT_JUSTIFIED();
    }
}
static inline void select_voltage_refrence(const adc_config_t* adc){
    if(adc->voltage_ref==ADC_VOLTAGE_REFRENCE_ENABLED){
        ADC_ENABLE_VOLTAGE_REFRENCE();
    }
    else if(adc->voltage_ref==ADC_VOLTAGE_REFRENCE_DISABLED){
        ADC_DISABLE_VOLTAGE_REFRENCE();
    }
    else{
        ADC_DISABLE_VOLTAGE_REFRENCE();
    }  
}