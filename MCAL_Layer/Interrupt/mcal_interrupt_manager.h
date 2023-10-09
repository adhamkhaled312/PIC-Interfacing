/* 
 * File:   mcal_interrupt_manager.h
 * Author: ADHAM KHALED
 *
 * Created on August 22, 2023, 7:06 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H
/* ----------------Includes----------------*/
#include "mcal_interrupt_config.h"
/* ----------------Macro Declarations---------------*/

/* ----------------Macro Functions Declarations----------------*/

/* ----------------Data Type Declarations----------------*/

/* ----------------Functions Declarations----------------*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 src);
void RB5_ISR(uint8 src);
void RB6_ISR(uint8 src);
void RB7_ISR(uint8 src);
void ADC_ISR(void);
void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);
void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

