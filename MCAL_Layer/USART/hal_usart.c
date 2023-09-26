/* 
 * File:   hal_usart.c
 * Author: ADHAM KHALED
 *
 * Created on September 25, 2023, 2:00 PM
 */
#include "hal_usart.h"
static interrupt_handler EUSART_RxInterruptHandler=NULL;
static interrupt_handler EUSART_TxInterruptHandler=NULL;
static interrupt_handler EUSART_FramingErrorHandler=NULL;
static interrupt_handler EUSART_OverrunErrorHandler=NULL;
/**
 * @brief helper function for usart tx interrupt
 */
void EUSART_TX_ISR(void){
    EUSART_TX_InterruptDisable();
    if(EUSART_TxInterruptHandler){
        EUSART_TxInterruptHandler();
    }else { /* Nothing */}
}
/**
 * @brief helper funciton for usart rx interrupt 
 */
void EUSART_RX_ISR(void){
    if(EUSART_RxInterruptHandler){
        EUSART_RxInterruptHandler();
    }else { /* Nothing */}
    if(EUSART_FramingErrorHandler){
        EUSART_FramingErrorHandler();
    }else { /* Nothing */}
    if(EUSART_OverrunErrorHandler){
        EUSART_OverrunErrorHandler();
    }else { /* Nothing */}
}
static void eusart_baud_rate_calculations(const usart_t *_eusart);
static void eusrat_async_tx_init(const usart_t* _eusart);
static void eusrat_async_rx_init(const usart_t* _eusart);
/**
 * @brief initialize usart while running asynchronous
 * @param _eusart refrence to usart configurations @ref usart_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_init(const usart_t *_eusart){
    Std_ReturnType retVal=E_OK;
    if(NULL==_eusart){
        retVal=E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN=EUSART_MODULE_DISABLE;
        TRISCbits.RC7 = 1;   
        TRISCbits.RC6 = 1;
        eusart_baud_rate_calculations(_eusart);
        eusrat_async_tx_init(_eusart);
        eusrat_async_rx_init(_eusart);
        RCSTAbits.SPEN=EUSART_MODULE_ENABLE;
    }
    return retVal;
}
/**
 * @brief deinitialize usart while running asynchronous
 * @param _eusart refrence to usart configurations @ref usart_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_deinit(const usart_t *_eusart){
    Std_ReturnType retVal=E_OK;
    if(NULL==_eusart){
        retVal=E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN=EUSART_MODULE_DISABLE;
    }
    return retVal;
}
/**
 * @brief recieve byte throw asynchronous usart but with blocking
 * @param _data pointer to save the data in
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_ReadByteBlocking(uint8 *_data){
    Std_ReturnType retVal=E_OK;
    if(NULL==_data){
        retVal=E_NOT_OK;
    }
    else{
        while(!PIR1bits.RCIF);
        *_data=RCREG;
    }
    return retVal;
}
/**
 * @brief recieve byte throw asynchronous usart but without blocking
 * @param _data pointer to save the data in
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_ReadByteNonBlocking(uint8 *_data){
    Std_ReturnType retVal=E_OK;
    if(NULL==_data){
        retVal=E_NOT_OK;
    }
    else{
        if(1 == PIR1bits.RCIF){
        *_data = RCREG;
        retVal = E_OK;
        }
        else{
        retVal = E_NOT_OK;
        }
    }
    return retVal;
}
/**
 * @brief restart usart in case of overrunning error
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_RX_Restart(void){
    Std_ReturnType retVal=E_OK;
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1; 
    return retVal;
}
/**
 * @brief send byte throw asynchronous usart but with blocking
 * @param _data the data to be sent
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_WriteByteBlocking(uint8 _data){
    Std_ReturnType retVal=E_OK;
    while(!TXSTAbits.TRMT);
#if EUSART_TX_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
    EUSART_TX_InterruptEnable();
#endif
    TXREG=_data;
}
/**
 * @brief send string throw asynchronous usart but with blocking
 * @param _data refrence to the string to be sent
 * @param str_len length of the string
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_WriteStringBlocking(uint8 *_data, uint16 str_len){
    Std_ReturnType retVal=E_OK;
    if(NULL==_data){
        retVal=E_NOT_OK;
    }
    else{
        uint16 counter=0;
        for(counter=0;counter<str_len;counter++){
            retVal|=eusart_async_WriteByteBlocking(_data[counter]);
        }
    }
    return retVal;
}
/**
 * @brief send byte throw asynchronous usart but without blocking
 * @param _data the data to be sent
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_WriteByteNonBlocking(uint8 _data){
    Std_ReturnType retVal=E_OK;
    return retVal
    
}
/**
 * @brief send string throw asynchronous usart but without blocking
 * @param _data refrence to the string to be sent
 * @param str_len length of the string
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_WriteStringNonBlocking(uint8 *_data, uint16 str_len){
    Std_ReturnType retVal=E_OK;
    if(NULL==_data){
        retVal=E_NOT_OK;
    }
    else{

    }
    return retVal;
}
/* static helper function to intialize baud rate */
static void eusart_baud_rate_calculations(const usart_t *_eusart){
    float baud_temp=0;
    switch(_eusart->baudrate_gen_gonfig){
        case BAUDRATE_ASYN_8BIT_lOW_SPEED:
            TXSTAbits.SYNC=EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH=EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16=EUSART_08BIT_BAUDRATE_GEN;
            baud_temp=((_XTAL_FREQ/(float)_eusart->baudrate)/64)-1;
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC=EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH=EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16=EUSART_16BIT_BAUDRATE_GEN;
            baud_temp=((_XTAL_FREQ/(float)_eusart->baudrate)/16)-1;
            break;
        case BAUDRATE_ASYN_16BIT_lOW_SPEED:
            TXSTAbits.SYNC=EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH=EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16=EUSART_16BIT_BAUDRATE_GEN;
            baud_temp=((_XTAL_FREQ/(float)_eusart->baudrate)/16)-1;
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC=EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH=EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16=EUSART_16BIT_BAUDRATE_GEN;
            baud_temp=((_XTAL_FREQ/(float)_eusart->baudrate)/4)-1;
            break;
        case BAUDRATE_SYN_8BIT:
            TXSTAbits.SYNC=EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16=EUSART_08BIT_BAUDRATE_GEN;
            baud_temp=((_XTAL_FREQ/(float)_eusart->baudrate)/4)-1;
            break;
        case BAUDRATE_SYN_16BIT:
            TXSTAbits.SYNC=EUSART_ASYNCHRONOUS_MODE;
            BAUDCONbits.BRG16=EUSART_16BIT_BAUDRATE_GEN;
            baud_temp=((_XTAL_FREQ/(float)_eusart->baudrate)/4)-1;
            break;
        default: ;
    }
    SPBRG=(uint8)((uint32)baud_temp);
    SPBRGH=(uint8)(((uint32)baud_temp)>>8);
}
/* static helper function to intialize tx */
static void eusrat_async_tx_init(const usart_t* _eusart){
    if(EUSART_ASYNCHRONOUS_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        EUSART_TxInterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
        /* EUSART Transmit Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
            /* Interrupt Configurations */ 
#if EUSART_TX_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
            EUSART_TX_InterruptEnable();
            /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
            INTERRUPT_PriorityLevelEnable();
            if(INTERRUPT_HIGH_PRIORITY == _eusart->usart_tx_cfg.usart_tx_int_priority){
                /* Enables all high-priority interrupts */
                INTERRUPT_GlobalInterruptHighEnable();
                EUSART_TX_HighPrioritySet();
            }
            else if(INTERRUPT_LOW_PRIORITY == _eusart->usart_tx_cfg.usart_tx_int_priority){
                /* Enables all unmasked peripheral interrupts */
                INTERRUPT_GlobalInterruptLowEnable();
                EUSART_TX_LowPrioritySet();
            }
            else{ /* Nothing */ }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
        }
        else{ /* Nothing */}

        /* EUSART  9-Bit Transmit Configuration */
        if(EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
        }
        else{ /* Nothing */}
    }
    else { /* Nothing */}
}
/* static helper function to initalize rx */
static void eusrat_async_rx_init(const usart_t* _eusart){
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
        EUSART_RxInterruptHandler = _eusart->EUSART_RxDefaultInterruptHandler;
        EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
        EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
        /* EUSART Receiver Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
            /* Interrupt Configurations */ 
#if EUSART_RX_INTERRUPT_ENABLE==INTERRUPT_FEATURE_ENABLE
            EUSART_RX_InterruptEnable();
            /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
            INTERRUPT_PriorityLevelEnable();
            if(INTERRUPT_HIGH_PRIORITY == _eusart->usart_rx_cfg.usart_rx_int_priority){
                /* Enables all high-priority interrupts */
                INTERRUPT_GlobalInterruptHighEnable();
                EUSART_RX_HighPrioritySet();
            }
            else if(INTERRUPT_LOW_PRIORITY == _eusart->usart_rx_cfg.usart_rx_int_priority){
                /* Enables all unmasked peripheral interrupts */
                INTERRUPT_GlobalInterruptLowEnable();
                EUSART_RX_LowPrioritySet();
            }
            else{ /* Nothing */ }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
        }
        else{ /* Nothing */}

        /* EUSART  9-Bit Receiver Configuration */
        if(EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
        }
        else{ /* Nothing */}
    }
    else { /* Nothing */}
}