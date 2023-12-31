/* 
 * File:   hal_gpio.h
 * Author: ADHAM
 *
 * Created on July 21, 2023, 3:18 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
/* ----------------Includes----------------*/
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "C:\Program Files (x86)\Microchip\MPLABX\v5.35\packs\Microchip\PIC18Fxxxx_DFP\1.2.26\xc8\pic\include\proc\pic18f4620.h"
/* ----------------Macro Declarations---------------*/
#define PIN_MAX_NUMBER 8
#define PORT_MAX_NUMBER 5
/* ----------------Macro Functions Declarations----------------*/
#define HWREG8(_X)                  (*((volatile uint8*)_X))
#define SET_BIT(REG,BIT_POS)        (REG|=(1<<BIT_POS))    
#define CLEAR_BIT(REG,BIT_POS)      (REG&=~(1<<BIT_POS))    
#define TOGGLE_BIT(REG,BIT_POS)     (REG^=(1<<BIT_POS))    
#define READ_BIT(REG,BIT_POS)       ((REG>>BIT_POS) &1)          

/* ----------------Data Type Declarations----------------*/
typedef enum{
    LOW=0,
    HIGH
}logic_t;

typedef enum{
    OUTPUT=0,
    INPUT
}direction_t;

typedef enum{
    PIN0=0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}pin_index_t;

typedef enum{
    PORT_A=0,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E
}port_index_t;
typedef struct{
    uint8 port:3;       /* @ref port_index_t*/
    uint8 pin:3;        /* @ref pin_index_t*/
    uint8 direction:1;  /* @ref direction_t*/
    uint8 logic:1;      /* @ref logic_t*/
}pin_config_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief intialize the direction of pin (input or output)
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *pin_config);
/**
 * @brief get the direction of pin (input or output)
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @param direction_status refrence to direction_t to return in it the direction of the pin
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config, direction_t *direction_status);
/**
 * @brief write the logic of pin (HIGH or LOW)
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @param logic_status the logic to be written
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic_status);
/**
 * @brief read the logic of the pin (HIGH or LOW)
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @param logic_status refrence to logic_t to return in it the logic of the pin
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config, logic_t *logic_status);
/**
 * @brief toggle the logic of the pin
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config);
/**
 * @brief initialize pin direction and logic
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin_config);
/**
 * @brief initialize the direction of port (input or output)
 * @param port the port to initilaize its direction @ref port_index_t
 * @param direction_status the direction to initialize the port 
 *                         0:output
 *                         1:input
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */ 
Std_ReturnType gpio_port_direction_initialize(const port_index_t port,uint8 direction_status);
/**
 * @brief get the direction of port
 * @param port the port to get its direction @ref port_index_t
 * @param direction_status refrence to return the direction of the port 
 *                         0:output
 *                         1:input 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_port_get_direction_status(const port_index_t port, uint8 *direction_status);
/**
 * @brief write logic to the port 
 * @param port the port to write its logic @ref port_index_t
 * @param direction_status the logic to write to the port 
 *                         0:LOW
 *                         1:HIGH 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_port_write_logic(const port_index_t port, uint8 logic_status);
/**
 * @brief read logic of the port 
 * @param port the port to read its logic @ref port_index_t
 * @param direction_status refrence to save the logic of the port 
 *                         0:LOW
 *                         1:HIGH 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_port_read_logic(const port_index_t port, uint8 *logic_status);
/**
 * @brief toggle logic of the port
 * @param port the port to toggle its logic @ref port_index_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_port_toggle_logic(const port_index_t port);



#endif	/* HAL_GPIO_H */

