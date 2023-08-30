/* 
 * File:   hal_adc.h
 * Author: ADHAM KHALED
 *
 * Created on August 26, 2023, 1:34 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H
/* ----------------Includes----------------*/
#include "../mcal_std_types.h"
#include "C:\Program Files (x86)\Microchip\MPLABX\v5.35\packs\Microchip\PIC18Fxxxx_DFP\1.2.26\xc8\pic\include\proc\pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "hal_adc_cfg.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* ----------------Macro Declarations---------------*/
/**
 * @brief select which pin to be analog
 * @note if you select AN5 to be analog then, A0,A1,A2,A3,A4 are also analog
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY     0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY     0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY     0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY     0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY     0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY     0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY     0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY     0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY     0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY     0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY    0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY    0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY    0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY     0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY    0x0F

#define ADC_RESULT_RIGHT                 0x01
#define ADC_RESULT_LEFT                  0x00

#define ADC_VOLTAGE_REFRENCE_ENABLED     0x01
#define ADC_VOLTAGE_REFRENCE_DISABLED    0x00

#define ADC_CONVERSION_DONE              0x01
#define ADC_CONVERSION_IN_PROGRESS       0x00

/* ----------------Macro Functions Declarations----------------*/
/* A/D convertion status: 1:In progress   0: Idle*/
#define ADC_CONVERTION_STATUS()         (ADCON0bits.GO_nDONE)
#define ADC_CONVERTER_ENABLE()          (ADCON0bits.ADON=1)
#define ADC_CONVERTER_DISABLE()         (ADCON0bits.ADON=0)
#define ADC_START_CONVERSION()          (ADCON0bits.GODONE=1)
/* Voltage refrence is VREF- & VREF+ */
#define ADC_ENABLE_VOLTAGE_REFRENCE()   do{ADCON1bits.VCFG1=1;\
                                           ADCON1bits.VCFG0=1;\
                                        }while(0)
/* Voltage refrence is VSS & VDD */
#define ADC_DISABLE_VOLTAGE_REFRENCE()  do{ADCON1bits.VCFG1=0;\
                                           ADCON1bits.VCFG0=0;\
                                        }while(0)

#define ADC_ANALOG_PORT_CONFIG(_config) (ADCON1bits.PCFG=_config)
#define ADC_RESULT_RIGHT_JUSTIFIED()    (ADCON2bits.ADFM=1)
#define ADC_RESULT_LEFT_JUSTIFIED()     (ADCON2bits.ADFM=0)

/* ----------------Data Type Declarations----------------*/
/**
 * @brief analog channel select
 */
typedef enum{
    ADC_CHANNEL_AN0=0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12

}adc_channel_select_t;
/**
 * @brief acquisition time select
 * @note acquisition time is the time required for ADC to capture the input voltage
 */
typedef enum{
    ADC_0_TAD=0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_acquisition_time_t;
/**
 * @brief converstion clock select
 * @note 
 */
typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2=0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}adc_conversion_clock_t;
typedef struct{
    #if ADC_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*adc_interrupt_handler)(void);
    interrupt_priority_cfg priority;
    #endif
    adc_acquisition_time_t acquisition_time;    /* @ref adc_acquisition_time_t */
    adc_conversion_clock_t converstion_time;   /* @ref adc_converstion_clock_t */
    adc_channel_select_t channel;               /* @ref adc_channel_select_t */           
    uint8 voltage_ref :1;                       /* voltage refrence configuration */
    uint8 result_format:1;                      /* result format (right or left justified) */
}adc_config_t;  

typedef uint16 adc_conversion_result;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize ADC
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_init(const adc_config_t*adc);
/**
 * @brief deinitialize ADC (Disable)
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_DeInit(const adc_config_t*adc);
/**
 * @brief select another channel for the ADC
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @param channel 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_select_channel(const adc_config_t*adc,adc_channel_select_t channel);
/**
 * @brief start conversion
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_start_conversion(const adc_config_t* adc);
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
Std_ReturnType adc_is_conversion_done(const adc_config_t* adc,uint8 *status);
/**
 * @brief return the value of the conversion
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @param data the converted value
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_read_conversion_result(const adc_config_t *adc,adc_conversion_result *data);
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
Std_ReturnType adc_get_conversion_blocking(const adc_config_t *adc,adc_channel_select_t channel,adc_conversion_result *data);
/**
 * @brief return the value of conversion with selecting the channel for conversion 
 *        the function works with interrupt so interrupt must be enabled to use this function
 * @param adc refrence to ADC configurations @ref adc_config_t
 * @param channel the channel for conversion
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType adc_start_conversion_interrupt(const adc_config_t *adc,adc_channel_select_t channel);
#endif	/* HAL_ADC_H */

