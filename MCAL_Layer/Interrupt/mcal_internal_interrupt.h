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
/* This macro enables interrupt for timer0 */
#define TIMER0_InterruptEnable()           (INTCONbits.TMR0IE=1)
/* This macro disables interrupt for timer0 */
#define TIMER0_InterruptDisable()          (INTCONbits.TMR0IE=0)
/* This macro clears the interrupt flag for timer0 */
#define TIMER0_InterruptFlagClear()        (INTCONbits.TMR0IF=0)   
#endif

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the timer0 interrupt priority to high priority */
#define TIMER0_HighPrioritySet()           (INTCON2bits.TMR0IP=1)
/* This macro set the timer0 interrupt priority to low priority */
#define TIMER0_LowPrioritySet()            (INTCON2bits.TMR0IP=0)
#endif

#if TIMER1_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for timer1 */
#define TIMER1_InterruptEnable()           (PIE1bits.TMR1IE=1)
/* This macro disables interrupt for timer1 */
#define TIMER1_InterruptDisable()          (PIE1bits.TMR1IE=0)
/* This macro clears the interrupt flag for timer1 */
#define TIMER1_InterruptFlagClear()        (PIR1bits.TMR1IF=0)   
#endif

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the timer1 interrupt priority to high priority */
#define TIMER1_HighPrioritySet()           (IPR1bits.TMR1IP=1)
/* This macro set the timer1 interrupt priority to low priority */
#define TIMER1_LowPrioritySet()            (IPR1bits.TMR1IP=0)
#endif

#if TIMER2_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for timer2 */
#define TIMER2_InterruptEnable()           (PIE1bits.TMR2IE=1)
/* This macro disables interrupt for timer2 */
#define TIMER2_InterruptDisable()          (PIE1bits.TMR2IE=0)
/* This macro clears the interrupt flag for timer2 */
#define TIMER2_InterruptFlagClear()        (PIR1bits.TMR2IF=0)   
#endif

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the timer2 interrupt priority to high priority */
#define TIMER2_HighPrioritySet()           (IPR1bits.TMR2IP=1)
/* This macro set the timer2 interrupt priority to low priority */
#define TIMER2_LowPrioritySet()            (IPR1bits.TMR2IP=0)
#endif

#if TIMER3_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for timer3 */
#define TIMER3_InterruptEnable()           (PIE2bits.TMR3IE=1)
/* This macro disables interrupt for timer3 */
#define TIMER3_InterruptDisable()          (PIE2bits.TMR3IE=0)
/* This macro clears the interrupt flag for timer3 */
#define TIMER3_InterruptFlagClear()        (PIR2bits.TMR3IF=0)   
#endif

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the timer3 interrupt priority to high priority */
#define TIMER3_HighPrioritySet()           (IPR2bits.TMR3IP=1)
/* This macro set the timer3 interrupt priority to low priority */
#define TIMER3_LowPrioritySet()            (IPR2bits.TMR3IP=0)
#endif

#if CCP1_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for CCP1 */
#define CCP1_InterruptEnable()           (PIE1bits.CCP1IE=1)
/* This macro disables interrupt for CCP1 */
#define CCP1_InterruptDisable()          (PIE1bits.CCP1IE=0)
/* This macro clears the interrupt flag for CCP1 */
#define CCP1_InterruptFlagClear()        (PIR1bits.CCP1IF=0)   
#endif
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the CCP1 interrupt priority to high priority */
#define CCP1_HighPrioritySet()           (IPR1bits.CCP1IP=1)
/* This macro set the CCP1 interrupt priority to low priority */
#define CCP1_LowPrioritySet()            (IPR1bits.CCP1IP=0)
#endif

#if CCP2_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for CCP2 */
#define CCP2_InterruptEnable()           (PIE2bits.CCP2IE=1)
/* This macro disables interrupt for CCP2 */
#define CCP2_InterruptDisable()          (PIE2bits.CCP2IE=0)
/* This macro clears the interrupt flag for CCP2 */
#define CCP2_InterruptFlagClear()        (PIR2bits.CCP2IF=0)   
#endif
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the CCP2 interrupt priority to high priority */
#define CCP2_HighPrioritySet()           (IPR2bits.CCP2IP=1)
/* This macro set the CCP2 interrupt priority to low priority */
#define CCP2_LowPrioritySet()            (IPR2bits.CCP2IP=0)
#endif

#if EUSART_TX_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for EUSART TX */
#define EUSART_TX_InterruptEnable()           (PIE1bits.TXIE=1)
/* This macro disables interrupt for EUSART TX */
#define EUSART_TX_InterruptDisable()          (PIE1bits.TXIE=0)
#endif
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the EUSART TX interrupt priority to high priority */
#define EUSART_TX_HighPrioritySet()           (IPR1bits.TXIP=1)
/* This macro set the EUSART TX interrupt priority to low priority */
#define EUSART_TX_LowPrioritySet()            (IPR1bits.TXIP=0)
#endif

#if EUSART_RX_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for EUSART RX */
#define EUSART_RX_InterruptEnable()           (PIE1bits.RCIE=1)
/* This macro disables interrupt for EUSART RX */
#define EUSART_RX_InterruptDisable()          (PIE1bits.RCIE=0)
#endif
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the EUSART RX interrupt priority to high priority */
#define EUSART_RX_HighPrioritySet()           (IPR1bits.RCIP=1)
/* This macro set the EUSRAT RX interrupt priority to low priority */
#define EUSART_RX_LowPrioritySet()            (IPR1bits.RCIP=0)
#endif

#if MSSP_I2C_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables interrupt for MSSP I2C */
#define MSSP_I2C_InterruptEnable()             (PIE1bits.SSPIE=1)
#define MSSP_I2C_BUS_COL_InterruptEnable()     (PIE2bits.BCLIE=1)
/* This macro disables interrupt for MSSP I2C */
#define MSSP_I2C_InterruptDisable()            (PIE1bits.SSPIE=0)
#define MSSP_I2C_BUS_COL_InterruptEnable()     (PIE2bits.BCLIE=0)
/* This macro clears the interrupt flag for MSSP I2C */
#define MSSP_I2C_InterruptFlagClear()          (PIR1bits.SSPIF=0)
#define MSSP_I2C_BUS_COL_InterruptFlagClear()  (PIR2bits.BCLIF=0)
#endif
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the MSSP I2C interrupt priority to high priority */
#define MSSP_I2C_HighPrioritySet()           (IPR1bits.SSPIP=1)
#define MSSP_I2C_BUS_COL_HighPrioritySet()   (IPR2bits.BCLIP=1)
/* This macro set the MSSP I2C interrupt priority to low priority */
#define MSSP_I2C_LowPrioritySet()            (IPR1bits.MSSIP=0)
#define MSSP_I2C_BUS_COL_HighPrioritySet()   (IPR2bits.BCLIP=0)
#endif
/* ----------------Data Type Declarations----------------*/
/* ----------------Functions Declarations----------------*/
#endif	/* MCAL_INTERNAL_INTERRUPT_H */

