/* 
 * File:   mcal_external_interrupt.c
 * Author: ADHAM KHALED
 *
 * Created on August 22, 2023, 7:06 PM
 */
#include "mcal_external_interrupt.h"
/* Pointer to function to hold callbacks for INTx */
static interrupt_handler INT0_interrupt_handler=NULL;
static interrupt_handler INT1_interrupt_handler=NULL;
static interrupt_handler INT2_interrupt_handler=NULL;
/* Pointer to function to hold callbacks for RBx */
static interrupt_handler RB4_interrupt_handler_High=NULL;
static interrupt_handler RB4_interrupt_handler_Low=NULL;
static interrupt_handler RB5_interrupt_handler_High=NULL;
static interrupt_handler RB5_interrupt_handler_Low=NULL;
static interrupt_handler RB6_interrupt_handler_High=NULL;
static interrupt_handler RB6_interrupt_handler_Low=NULL;
static interrupt_handler RB7_interrupt_handler_High=NULL;
static interrupt_handler RB7_interrupt_handler_Low=NULL;


static Std_ReturnType interrupt_INTx_enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_priority_init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_pin_init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_edge_init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_flag_clear(const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void (*interrupt_handler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*interrupt_handler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*interrupt_handler)(void));
static Std_ReturnType interrupt_INTx_set_interrupt_handler(const interrupt_INTx_t *int_obj);
/**
 * @brief initialize the INTx external interrupt
 * @param int_obj refrence to the interrupt configurations @ref interrupt_INTx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType interrupt_INTx_Init (const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal=E_OK;
    if(NULL==int_obj){
        retVal=E_NOT_OK;
    }
    else{
        retVal=interrupt_INTx_disable(int_obj);
        retVal|=interrupt_INTx_flag_clear(int_obj);
        retVal|=interrupt_INTx_edge_init(int_obj);
        retVal|=interrupt_INTx_pin_init(int_obj);
        retVal|=interrupt_INTx_set_interrupt_handler(int_obj);
        retVal|=interrupt_INTx_enable(int_obj);
    }
    return retVal;
}
/**
 * @brief de initilaize the INTx external interrupt (Disable)
 * @param int_obj refrence to the interrupt configurations @ref interrupt_INTx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType interrupt_INTx_DeInit (const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal=E_OK;
    if(NULL==int_obj){
        retVal=E_NOT_OK;
    }
    else{
        retVal=interrupt_RBx_disable(int_obj);
    }
    return retVal;
}
/**
 * @brief external interrupt INT 0 Helper function 
 * 
 */
void INT0_ISR(void){
    EXT_INT0_InterruptFlagClear();
    if(INT0_interrupt_handler){
        INT0_interrupt_handler();
    }
}
/**
 * @brief external interrupt INT 1 Helper function 
 * 
 */
void INT1_ISR(void){
    EXT_INT1_InterruptFlagClear();
    if(INT1_interrupt_handler){
        INT1_interrupt_handler();
    }
}
/**
 * @brief external interrupt INT 2 Helper function 
 * 
 */
void INT2_ISR(void){
    EXT_INT2_InterruptFlagClear();
    if(INT2_interrupt_handler){
        INT2_interrupt_handler();
    }      
}
/**
 * @brief external interrupt RB 4 Helper function 
 * 
 */
void RB4_ISR(uint8 src){
    EXT_RBX_InterruptFlagClear();
    if(1==src){
        if(RB4_interrupt_handler_Low){
            RB4_interrupt_handler_Low();
        }
    }
    else if(0==src){
        if(RB4_interrupt_handler_High){
            RB4_interrupt_handler_High();
        }      

    }    
}
/**
 * @brief external interrupt RB 5 Helper function 
 * 
 */
void RB5_ISR(uint8 src){
    EXT_RBX_InterruptFlagClear();
    if(1==src){
        if(RB5_interrupt_handler_Low){
            RB5_interrupt_handler_Low();
        }
    }
    else if(0==src){
        if(RB5_interrupt_handler_High){
            RB5_interrupt_handler_High();
        }      

    }    
}
/**
 * @brief external interrupt RB 6 Helper function 
 * 
 */
void RB6_ISR(uint8 src){
    EXT_RBX_InterruptFlagClear();
    if(1==src){
        if(RB6_interrupt_handler_Low){
            RB6_interrupt_handler_Low();
        }
    }
    else if(0==src){
        if(RB6_interrupt_handler_High){
            RB6_interrupt_handler_High();
        }      

    }      
}
/**
 * @brief external interrupt RB 7 Helper function 
 * 
 */
void RB7_ISR(uint8 src){
    EXT_RBX_InterruptFlagClear();
    if(1==src){
        if(RB7_interrupt_handler_Low){
            RB7_interrupt_handler_Low();
        }
    }
    else if(0==src){
        if(RB7_interrupt_handler_High){
            RB7_interrupt_handler_High();
        }      

    }       
}
/**
 * @brief intialize RBx external interrupt
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType interrupt_RBx_Init (const interrupt_RBx_t *int_obj){
    Std_ReturnType retVal=E_OK;
    if(NULL==int_obj){
        retVal=E_NOT_OK;
    }
    else{
        EXT_RBX_InterruptDisable();
        EXT_RBX_InterruptFlagClear();
        /* initialize the interrupt priority */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY==int_obj->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            EXT_RBX_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY==int_obj->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            EXT_RBX_LowPrioritySet();
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        /* Initialize the call back function */
        switch (int_obj->pin.pin)
        {
        case PIN4:
            RB4_interrupt_handler_High=int_obj->EXT_InterruptHandler_High;
            RB4_interrupt_handler_Low=int_obj->EXT_InterruptHandler_Low;
            break;
        case PIN5:
            RB5_interrupt_handler_High=int_obj->EXT_InterruptHandler_High;
            RB5_interrupt_handler_Low=int_obj->EXT_InterruptHandler_Low;
            break;            
        case PIN6:
            RB6_interrupt_handler_High=int_obj->EXT_InterruptHandler_High;
            RB6_interrupt_handler_Low=int_obj->EXT_InterruptHandler_Low;
            break;        
        case PIN7:
            RB7_interrupt_handler_High=int_obj->EXT_InterruptHandler_High;
            RB7_interrupt_handler_Low=int_obj->EXT_InterruptHandler_Low;
            break;
        default:
            retVal=E_NOT_OK;
            break;
        }
        gpio_pin_direction_initialize(&(int_obj->pin));
        EXT_RBX_InterruptEnable();
    }
    return retVal;
}
/**
 * @brief de intialize RBx external interrupt
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType interrupt_RBx_DeInit (const interrupt_RBx_t *int_obj){
    Std_ReturnType retVal=E_OK;
    if(NULL==int_obj){
        retVal=E_NOT_OK;
    }
    else{
        EXT_RBX_InterruptDisable();
        EXT_RBX_InterruptFlagClear();
    }
    return retVal;
}
/**
 * @brief enable the INTx interrupt source 
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType interrupt_INTx_enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal=E_OK;
    switch(int_obj->src){
        case INTERRUPT_EXTERNAL_INT0:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable(); 
                break;
        case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelEnable()
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptHighEnable();
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_InterruptEnable();
                break;
        case INTERRUPT_EXTERNAL_INT2:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelEnable()
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruptHighEnable();
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_InterruptEnable();
                break;
        default:
            retVal=E_NOT_OK;
    }
    return retVal;
}
/**
 * @brief disable the INTx interrupt source 
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType interrupt_INTx_disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal=E_OK;
    switch(int_obj->src){
        case INTERRUPT_EXTERNAL_INT0:
            EXT_INT0_InterruptDisable();
            break;
        case INTERRUPT_EXTERNAL_INT1:
            EXT_INT1_InterruptDisable();
            break;
        case INTERRUPT_EXTERNAL_INT2:
            EXT_INT2_InterruptDisable();
            break;
        default:
            retVal=E_NOT_OK;
    }
    return retVal;
}
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_INTx_priority_init(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal=E_OK;
    switch(int_obj->src){
        case INTERRUPT_EXTERNAL_INT1:
            if(INTERRUPT_HIGH_PRIORITY==int_obj->priority){
                EXT_INT1_HighPrioritySet();
            }
            else if(INTERRUPT_LOW_PRIORITY==int_obj->priority){
                EXT_INT1_LowPrioritySet();
            }
            else{}
            break;
        case INTERRUPT_EXTERNAL_INT2:
            if(INTERRUPT_HIGH_PRIORITY==int_obj->priority){
                EXT_INT2_HighPrioritySet();
            }
            else if(INTERRUPT_LOW_PRIORITY==int_obj->priority){
                EXT_INT2_LowPrioritySet();
            }
            else{}
            break;
        default:
            retVal=E_NOT_OK;
    }
    return retVal;
}
#endif
/**
 * @brief intialize the pin of the INTx external interrupt 
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType interrupt_INTx_pin_init(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal=E_OK;
    retVal=gpio_pin_direction_initialize(&(int_obj->pin));
    return retVal; 
}
/**
 * @brief intialize the edge of the INTx external interrupt (Rising or Falling)
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType interrupt_INTx_edge_init(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal=E_OK;
    switch(int_obj->src){
        case INTERRUPT_EXTERNAL_INT0:
            if(INTERRUPT_RISING_EDGE==int_obj->edge){
                EXT_INT0_RisingEdgeSet();
            }
            else if(INTERRUPT_FALLING_EDGE==int_obj->edge){
                EXT_INT0_FallingEdgeSet();
            }
            else{}
            break;
        case INTERRUPT_EXTERNAL_INT1:
            if(INTERRUPT_RISING_EDGE==int_obj->edge){
                EXT_INT1_RisingEdgeSet();
            }
            else if(INTERRUPT_FALLING_EDGE==int_obj->edge){
                EXT_INT1_FallingEdgeSet();
            }
            else{}
            break;
        case INTERRUPT_EXTERNAL_INT2:
            if(INTERRUPT_RISING_EDGE==int_obj->edge){
                EXT_INT2_RisingEdgeSet();
            }
            else if(INTERRUPT_FALLING_EDGE==int_obj->edge){
                EXT_INT2_FallingEdgeSet();
            }
            else{}
            break;
        default:
            retVal=E_NOT_OK;
    }
    return retVal;   
}
/**
 * @brief clear the flag of INTx external interrupt 
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType interrupt_INTx_flag_clear(const interrupt_INTx_t *int_obj){
        Std_ReturnType retVal=E_OK;
    switch(int_obj->src){
        case INTERRUPT_EXTERNAL_INT0:
            EXT_INT0_InterruptFlagClear();
            break;
        case INTERRUPT_EXTERNAL_INT1:
            EXT_INT1_InterruptFlagClear();
            break;
        case INTERRUPT_EXTERNAL_INT2:
            EXT_INT2_InterruptFlagClear();
            break;
        default:
            retVal=E_NOT_OK;
    }
    return retVal;   
}
/**
 * @brief set the pointer to function of the INT0 external interrupt to the handler of it in the application layer 
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType INT0_SetInterruptHandler(void (*interrupt_handler)(void)){
    Std_ReturnType retVal=E_OK;
    if(NULL==interrupt_handler){
        retVal=E_NOT_OK;
    }
    else{
        INT0_interrupt_handler=interrupt_handler;
    }
    return retVal;
}
/**
 * @brief set the pointer to function of the INT1 external interrupt to the handler of it in the application layer 
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType INT1_SetInterruptHandler(void (*interrupt_handler)(void)){
    Std_ReturnType retVal=E_OK;
    if(NULL==interrupt_handler){
        retVal=E_NOT_OK;
    }
    else{
        INT1_interrupt_handler=interrupt_handler;
    }
    return retVal;
}
/**
 * @brief set the pointer to function of the INT2 external interrupt to the handler of it in the application layer 
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType INT2_SetInterruptHandler(void (*interrupt_handler)(void)){
    Std_ReturnType retVal=E_OK;
    if(NULL==interrupt_handler){
        retVal=E_NOT_OK;
    }
    else{
        INT2_interrupt_handler=interrupt_handler;
    }
    return retVal;
}
/**
 * @brief set the pointer to function of the INTx external interrupt to the handler of it in the application layer 
 * @param int_obj refrence to the interrupt configurations @ref interrupt_RBx_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType interrupt_INTx_set_interrupt_handler(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal=E_OK;
        switch (int_obj->src)
        {
        case INTERRUPT_EXTERNAL_INT0:
            INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
            break;
        case INTERRUPT_EXTERNAL_INT1:
            INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
            break;
        case INTERRUPT_EXTERNAL_INT2:
            INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
            break;
        default:
            retVal=E_NOT_OK;
            break;
        }
    return retVal;
}