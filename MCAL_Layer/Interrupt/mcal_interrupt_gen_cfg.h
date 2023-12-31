/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: ADHAM KHALED
 *
 * Created on August 22, 2023, 8:15 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

#define INTERRUPT_FEATURE_ENABLE        1       
//#define INTERRUPT_PRIORITY_LEVELS_ENABLE             INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_EXTERNAL_INTX_FEATURE_ENABLE       INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_EXTERNAL_ONCHANGE_FEATURE_ENABLE   INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_ENABLE                         INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_ENABLE                      INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_ENABLE                      INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_ENABLE                      INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_ENABLE                      INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUPT_ENABLE                        INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_ENABLE                        INTERRUPT_FEATURE_ENABLE
#define EUSART_TX_INTERRUPT_ENABLE                   INTERRUPT_FEATURE_ENABLE
#define EUSART_RX_INTERRUPT_ENABLE                   INTERRUPT_FEATURE_ENABLE
#define MSSP_I2C_INTERRUPT_ENABLE                    INTERRUPT_FEATURE_ENABLE
#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

