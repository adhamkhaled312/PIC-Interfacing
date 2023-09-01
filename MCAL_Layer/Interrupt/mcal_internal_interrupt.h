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

#if TIMER0_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for ADC */
#define TIMER0_InterruptEnable()           (INTCONbits.TMR0IE=1)
/* This macro disables interrupt for ADC */
#define TIMER0_InterruptDisable()          (INTCONbits.TMR0IE=0)
/* This macro clears the interrupt flag for ADC */
#define TIMER0_InterruptFlagClear()        (INTCONbits.TMR0IF=0)   
#endif

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the ADC interrupt priority to high priority */
#define TIMER0_HighPrioritySet()           (INTCON2bits.TMR0IP=1)
/* This macro set the ADC interrupt priority to low priority */
#define TIMER0_LowPrioritySet()            (INTCON2bits.TMR0IP=0)
#endif

#if TIMER1_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for ADC */
#define TIMER1_InterruptEnable()           (PIE1bits.TMR1IE=1)
/* This macro disables interrupt for ADC */
#define TIMER1_InterruptDisable()          (PIE1bits.TMR1IE=0)
/* This macro clears the interrupt flag for ADC */
#define TIMER1_InterruptFlagClear()        (PIR1bits.TMR1IF=0)   
#endif

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the ADC interrupt priority to high priority */
#define TIMER1_HighPrioritySet()           (IPR1bits.TMR1IP=1)
/* This macro set the ADC interrupt priority to low priority */
#define TIMER1_LowPrioritySet()            (IPR1bits.TMR1IP=0)
#endif

#if TIMER2_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for ADC */
#define TIMER2_InterruptEnable()           (PIE1bits.TMR2IE=1)
/* This macro disables interrupt for ADC */
#define TIMER2_InterruptDisable()          (PIE1bits.TMR2IE=0)
/* This macro clears the interrupt flag for ADC */
#define TIMER2_InterruptFlagClear()        (PIR1bits.TMR2IF=0)   
#endif

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the ADC interrupt priority to high priority */
#define TIMER2_HighPrioritySet()           (IPR1bits.TMR2IP=1)
/* This macro set the ADC interrupt priority to low priority */
#define TIMER2_LowPrioritySet()            (IPR1bits.TMR2IP=0)
#endif
/* ----------------Data Type Declarations----------------*/
/* ----------------Functions Declarations----------------*/
#endif	/* MCAL_INTERNAL_INTERRUPT_H */

