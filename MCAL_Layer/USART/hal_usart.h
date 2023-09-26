/* 
 * File:   hal_usart.h
 * Author: ADHAM KHALED
 *
 * Created on September 25, 2023, 2:00 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H
/* ----------------Includes----------------*/
#include "../mcal_std_types.h"
#include "C:\Program Files (x86)\Microchip\MPLABX\v5.35\packs\Microchip\PIC18Fxxxx_DFP\1.2.26\xc8\pic\include\proc\pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "hal_usart_cfg.h"
/* ----------------Macro Declarations---------------*/
/* Enable / Disable EUSART Module */
#define EUSART_MODULE_ENABLE   1
#define EUSART_MODULE_DISABLE  0

/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE  		1
#define EUSART_ASYNCHRONOUS_MODE 		0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  	0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN  		1
#define EUSART_08BIT_BAUDRATE_GEN  		0

/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE  0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE  0

/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0
/* EUSART Receiver Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE  0
/* EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE  0
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0
/* ----------------Macro Functions Declarations----------------*/

/* ----------------Data Type Declarations----------------*/
/* baud rate configurations */
typedef enum{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;
/* data type for tx configurations */
typedef struct{
    interrupt_priority_cfg usart_tx_int_priority;
	uint8 usart_tx_enable : 1;
	uint8 usart_tx_interrupt_enable : 1;
	uint8 usart_tx_9bit_enable : 1;
    uint8 usart_tx_reserved : 5;
}usart_tx_cfg_t;
/* data type for rx configurations */
typedef struct{
    interrupt_priority_cfg usart_rx_int_priority;
	uint8 usart_rx_enable : 1;
	uint8 usart_rx_interrupt_enable : 1;
	uint8 usart_rx_9bit_enable : 1;
    uint8 usart_rx_reserved : 5;
}usart_rx_cfg_t;
typedef union{
	struct{
		uint8 usart_tx_reserved : 6;
		uint8 usart_ferr : 1;
		uint8 usart_oerr : 1;
	};
	uint8 status;
}usart_error_status_t;
/* data type for usart to be used by the user */
typedef struct{
    uint32 baudrate;
    baudrate_gen_t baudrate_gen_gonfig;
    usart_tx_cfg_t usart_tx_cfg;
	usart_rx_cfg_t usart_rx_cfg;
	usart_error_status_t error_status;
	void (*EUSART_TxDefaultInterruptHandler)(void);
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
}usart_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize usart while running asynchronous
 * @param _eusart refrence to usart configurations @ref usart_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_init(const usart_t *_eusart);
/**
 * @brief deinitialize usart while running asynchronous
 * @param _eusart refrence to usart configurations @ref usart_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_deinit(const usart_t *_eusart);
/**
 * @brief recieve byte throw asynchronous usart but with blocking
 * @param _data pointer to save the data in
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_ReadByteBlocking(uint8 *_data);
/**
 * @brief recieve byte throw asynchronous usart but without blocking
 * @param _data pointer to save the data in
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_ReadByteNonBlocking(uint8 *_data);
/**
 * @brief restart usart in case of overrunning error
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_RX_Restart(void);
/**
 * @brief send byte throw asynchronous usart but with blocking
 * @param _data the data to be sent
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_WriteByteBlocking(uint8 _data);
/**
 * @brief send string throw asynchronous usart but with blocking
 * @param _data refrence to the string to be sent
 * @param str_len length of the string
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_WriteStringBlocking(uint8 *_data, uint16 str_len);
/**
 * @brief send byte throw asynchronous usart but without blocking
 * @param _data the data to be sent
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_WriteByteNonBlocking(uint8 _data);
/**
 * @brief send string throw asynchronous usart but without blocking
 * @param _data refrence to the string to be sent
 * @param str_len length of the string
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eusart_async_WriteStringNonBlocking(uint8 *_data, uint16 str_len);
#endif	/* HAL_USART_H */

