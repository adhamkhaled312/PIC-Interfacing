/* 
 * File:   mcal_external_interrupt.h
 * Author: ADHAM KHALED
 *
 * Created on August 22, 2023, 7:06 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* ----------------Includes----------------*/
#include "mcal_interrupt_config.h"
/* ----------------Macro Declarations---------------*/
/* ----------------Macro Functions Declarations----------------*/
#if INTERRUPT_EXTERNAL_INTX_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables external interrupt INT0 */
#define EXT_INT0_InterruptEnable()      (INTCONbits.INT0IE=1)
/* This macro disables external interrupt INT0 */
#define EXT_INT0_InterruptDisable()     (INTCONbits.INT0IE=0)
/* This macro clears the interrupt flag for external interrupt INT0 */
#define EXT_INT0_InterruptFlagClear()   (INTCONbits.INT0IF=0)
/* This macro set the edge detect for external interrupt INT0 to rising edge */
#define EXT_INT0_RisingEdgeSet()        (INTCON2bits.INTEDG0=1)
/* This macro set the edge detect for external interrupt INT0 to falling edge */
#define EXT_INT0_FallingEdgeSet()       (INTCON2bits.INTEDG0=0)

/* This macro enables external interrupt INT1 */
#define EXT_INT1_InterruptEnable()      (INTCON3bits.INT1IE=1)
/* This macro disables external interrupt INT1 */
#define EXT_INT1_InterruptDisable()     (INTCON3bits.INT1IE=0)
/* This macro clears the interrupt flag for external interrupt INT1 */
#define EXT_INT1_InterruptFlagClear()   (INTCON3bits.INT1IF=0)
/* This macro set the edge detect for external interrupt INT1 to rising edge */
#define EXT_INT1_RisingEdgeSet()        (INTCON2bits.INTEDG1=1)
/* This macro set the edge detect for external interrupt INT1 to falling edge */
#define EXT_INT1_FallingEdgeSet()       (INTCON2bits.INTEDG1=0)

/* This macro enables external interrupt INT2 */
#define EXT_INT2_InterruptEnable()      (INTCON3bits.INT2IE=1)
/* This macro disables external interrupt INT2 */
#define EXT_INT2_InterruptDisable()     (INTCON3bits.INT2IE=0)
/* This macro clears the interrupt flag for external interrupt INT2 */
#define EXT_INT2_InterruptFlagClear()   (INTCON3bits.INT2IF=0)
/* This macro set the edge detect for external interrupt INT2 to rising edge */
#define EXT_INT2_RisingEdgeSet()        (INTCON2bits.INTEDG2=1)
/* This macro set the edge detect for external interrupt INT2 to falling edge */
#define EXT_INT2_FallingEdgeSet()       (INTCON2bits.INTEDG2=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the INT1 external interrupt priority to high priority */
#define EXT_INT1_HighPrioritySet()      (INTCON3bits.INT1IP=1)
/* This macro set the INT1 external interrupt priority to low priority */
#define EXT_INT1_LowPrioritySet()       (INTCON3bits.INT1IP=0)
/* This macro set the INT2 external interrupt priority to high priority */
#define EXT_INT2_HighPrioritySet()      (INTCON3bits.INT2IP=1)
/* This macro set the INT2 external interrupt priority to low priority */
#define EXT_INT2_LowPrioritySet()       (INTCON3bits.INT2IP=0)

#endif

#endif

#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enables the external interrupt RBx */
#define EXT_RBX_InterruptEnable()        (INTCONbits.RBIE=1)
/* This macro disables the external interrupt RBx */
#define EXT_RBX_InterruptDisable()       (INTCONbits.RBIE=0)
/* This macro clears the interrupt flag for external interrupt RBx */
#define EXT_RBX_InterruptFlagClear()     (INTCONbits.RBIF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro set the RBx external interrupt priority to high priority */
#define EXT_RBX_HighPrioritySet()      (INTCON2bits.RBIP=1)
/* This macro set the RBx external interrupt priority to low priority */
#define EXT_RBX_LowPrioritySet()       (INTCON2bits.RBIP=0)
#endif
#endif
/* ----------------Data Type Declarations----------------*/
typedef enum{
    INTERRUPT_EXTERNAL_INT0=0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_src;

typedef enum{
    INTERRUPT_FALLING_EDGE=0,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_edge;

typedef struct{
    void (* EXT_InterruptHandler)(void);
    pin_config_t pin;
    interrupt_INTx_src src;
    interrupt_INTx_edge edge;
    interrupt_priority_cfg priority;
}interrupt_INTx_t;

typedef struct{
    void (* EXT_InterruptHandler_High)(void);
    void (* EXT_InterruptHandler_Low)(void);
    pin_config_t pin;
    interrupt_priority_cfg priority;

}interrupt_RBx_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize the INTx external interrupt
 * @param int_obj refrence to the interrupt configurations @ref interrupt_INTx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType interrupt_INTx_Init (const interrupt_INTx_t *int_obj);
/**
 * @brief de initilaize the INTx external interrupt (Disable)
 * @param int_obj refrence to the interrupt configurations @ref interrupt_INTx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType interrupt_INTx_DeInit (const interrupt_INTx_t *int_obj);
/**
 * @brief intialize RBx external interrupt
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType interrupt_RBx_Init (const interrupt_RBx_t *int_obj);
/**
 * @brief de intialize RBx external interrupt
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType interrupt_RBx_DeInit (const interrupt_RBx_t *int_obj);
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

