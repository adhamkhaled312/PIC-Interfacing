/* 
 * File:   hal_gpio.c
 * Author: ADHAM KHALED
 *
 * Created on July 21, 2023, 3:18 PM
 */
#include "hal_gpio.h"
/* Refrence to the port status registers */
volatile uint8 *port_registers[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
/* Refrence to the data direction registers */
volatile uint8 *tris_registers[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISD};
/* Refrence to the latch registers */
volatile uint8 *lat_registers[]={&LATA,&LATB,&LATC,&LATD,&LATE};

/**
 * @brief intialize the direction of pin (input or output)
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *pin_config){
    Std_ReturnType retVal=E_OK;
    if(NULL==pin_config || pin_config->pin>PIN_MAX_NUMBER-1){
        retVal=E_NOT_OK;
    }
    else{

        switch (pin_config->direction)
        {
        case INPUT:
            SET_BIT(*tris_registers[pin_config->port],pin_config->pin);
            break;
        case OUTPUT:
            CLEAR_BIT(*tris_registers[pin_config->port],pin_config->pin);
            break;
        default:
            retVal=E_NOT_OK;
            break;
        }
    }
    return retVal;
}

/**
 * @brief get the direction of pin (input or output)
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @param direction_status refrence to direction_t to return in it the direction of the pin
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config, direction_t *direction_status){
    Std_ReturnType retVal=E_OK;
    if(NULL==pin_config || NULL==direction_status || pin_config->pin>PIN_MAX_NUMBER-1){
        retVal=E_NOT_OK;
    } 
    else{
        *direction_status=READ_BIT(*tris_registers[pin_config->port],pin_config->pin);
    }
    return retVal;
}

/**
 * @brief write the logic of pin (HIGH or LOW)
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @param logic_status the logic to be written
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic_status){
    Std_ReturnType retVal=E_OK;
    if(NULL==pin_config || pin_config->pin>PIN_MAX_NUMBER-1){
        retVal=E_NOT_OK;
    }   
    else{
        switch (logic_status)
        {
        case LOW:
            CLEAR_BIT(*lat_registers[pin_config->port],pin_config->pin);
            break;
        case HIGH:
            SET_BIT(*lat_registers[pin_config->port],pin_config->pin);
            break;
        default:
            retVal=E_NOT_OK;
            break;
        }
    }
    return retVal;
}
/**
 * @brief read the logic of the pin (HIGH or LOW)
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @param logic_status refrence to logic_t to return in it the logic of the pin
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config, logic_t *logic_status){
    Std_ReturnType retVal=E_OK;
    if(NULL==pin_config || NULL==logic_status || pin_config->pin>PIN_MAX_NUMBER-1){
        retVal=E_NOT_OK;
    } 
    else{
        *logic_status=READ_BIT(*port_registers[pin_config->port],pin_config->pin);
    }
    return retVal;
}

/**
 * @brief toggle the logic of the pin
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config){
    Std_ReturnType retVal=E_OK;
    if(NULL==pin_config || pin_config->pin>PIN_MAX_NUMBER-1){
        retVal=E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*lat_registers[pin_config->port],pin_config->pin);
    }
    return retVal;
}
/**
 * @brief initialize pin direction and logic
 * @param pin_config refrence to the pin properties @ref pin_config_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin_config){
    Std_ReturnType retVal=E_OK;
    if(NULL==pin_config || pin_config->pin>PIN_MAX_NUMBER-1){
        retVal=E_NOT_OK;
    }
    else{
        retVal=gpio_pin_direction_initialize(pin_config);
        retVal=gpio_pin_write_logic(pin_config,pin_config->logic);
    }
    return retVal;
}

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
Std_ReturnType gpio_port_direction_initialize(const port_index_t port,uint8 direction_status){
    Std_ReturnType retVal=E_OK;
    if(port>PORT_MAX_NUMBER-1){
        retVal=E_NOT_OK;
    }
    else{
        *tris_registers[port]=direction_status;
    }
    return retVal;
}
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
Std_ReturnType gpio_port_get_direction_status(const port_index_t port, uint8 *direction_status){
    Std_ReturnType retVal=E_OK;
    if(port>PORT_MAX_NUMBER-1 || NULL==direction_status){
        retVal=E_NOT_OK;
    }
    else{
        *direction_status=*tris_registers[port];
    }
    return retVal;
}
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
Std_ReturnType gpio_port_write_logic(const port_index_t port, uint8 logic_status){
    Std_ReturnType retVal=E_OK;
    if(port>PORT_MAX_NUMBER-1){
        retVal=E_NOT_OK;
    }    
    else{
        *lat_registers[port]=logic_status;
}
    return retVal;
}
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
Std_ReturnType gpio_port_read_logic(const port_index_t port, uint8 *logic_status){
    Std_ReturnType retVal=E_OK;
    if(port>PORT_MAX_NUMBER-1 || NULL==logic_status){
        retVal=E_NOT_OK;
    }   
    else{
        *logic_status=*port_registers[port];
    }
    return retVal;
}

/**
 * @brief toggle logic of the port
 * @param port the port to toggle its logic @ref port_index_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType gpio_port_toggle_logic(const port_index_t port){
    Std_ReturnType retVal=E_OK;
    if(port>PORT_MAX_NUMBER-1){
        retVal=E_NOT_OK;
    }   
    else{
        *lat_registers[port]^=0xFF; /* 0x1111 1111 */
    }
    return retVal;
}