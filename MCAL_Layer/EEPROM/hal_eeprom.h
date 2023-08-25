/* 
 * File:   hal_eeprom.h
 * Author: ADHAM KHALED
 *
 * Created on August 24, 2023, 5:10 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H
/* ----------------Includes----------------*/
#include "../mcal_std_types.h"
#include "C:\Program Files (x86)\Microchip\MPLABX\v5.35\packs\Microchip\PIC18Fxxxx_DFP\1.2.26\xc8\pic\include\proc\pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"  
/* ----------------Macro Declarations---------------*/
#define EEPROM_ACCESS_FLASH_PROGRAM_MEMORY        1
#define EEPROM_ACCESS_EEPROM_PROGRAM_MEMORY       0
#define EEPROM_ACCESS_CONFG_REGISTERS             1
#define EEPROM_ACCESS_FLASH_EEPROM_MEMORY         0
#define EEPROM_ALLOW_WRITE_CYCLES                 1
#define EEPROM_INHIBT_WRITE_CYCLES                0
#define EEPROM_INITIATE_DATA_WRTIE_EARSE          1
#define EEPROM_INITIATE_DATA_READ                 1


/* ----------------Macro Functions Declarations----------------*/
/* ----------------Data Type Declarations----------------*/

/* ----------------Functions Declarations----------------*/
/**
 * @brief write byte in eeprom
 * @param add the address to write in
 * @param data the data to be written
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eeprom_write_byte(uint16 add,uint8 data);
/**
 * @brief read byte from eeprom
 * @param add the addres to read data from 
 * @param data variable to save the data read in
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eeprom_read_byte(uint16 add,uint8 *data);
#endif	/* HAL_EEPROM_H */

