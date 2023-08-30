/* 
 * File:   mcal_internal_interrupt.h
 * Author: ADHAM KHALED
 *
 * Created on August 22, 2023, 7:05 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

#include "mcal_interrupt_config.h"
/* ----------------Includes----------------*/
#include "mcal_interrupt_config.h"
/* ----------------Macro Declarations---------------*/
/* ----------------Macro Functions Declarations----------------*/
#if ADC_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for ADC */
#define ADC_InterruptEnable()           (PIE1bits.ADIE=1)
/* This macro disables interrupt for ADC */
#define ADC_InterruptDisable()          (PIE1bits.ADIE=0)
/* This macro clears the interrupt flag for ADC */
#define ADC_InterruptFlagClear()        (PIR1bits.ADIF=0)   
#endif

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the ADC interrupt priority to high priority */
#define ADC_HighPrioritySet()           (IPR1bits.ADIP=1)
/* This macro set the ADC interrupt priority to low priority */
#define ADC_LowPrioritySet()            (IPR1bits.ADIP=0)

#endif
/* ----------------Data Type Declarations----------------*/
/* ----------------Functions Declarations----------------*/
#endif	/* MCAL_INTERNAL_INTERRUPT_H */

