/* /
 * File:   hal_eeprom.c
 * Author: ADHAM KHALED
 *
 * Created on August 24, 2023, 5:10 PM
 */
#include "hal_eeprom.h"
/**
 * @brief write byte in eeprom
 * @param add the address to write in
 * @param data the data to be written
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eeprom_write_byte(uint16 add,uint8 data){
    Std_ReturnType retVal=E_OK;
    uint8 interrupt_status=INTCONbits.GIE;
    EEADR=(uint8)(add&0xFF);
    EEADRH=(uint8)((add>>8)&0x03);
    EEDATA=data;
    EECON1bits.EEPGD=EEPROM_ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS=EEPROM_ACCESS_FLASH_EEPROM_MEMORY;
    EECON1bits.WREN=EEPROM_ALLOW_WRITE_CYCLES;
    INTERRUPT_GlobalInterruptDisable();
    EECON2=0x55;
    EECON2=0x0AA;
    EECON1bits.WR=EEPROM_INITIATE_DATA_WRTIE_EARSE;
    while(EECON1bits.WR);
    EECON1bits.WREN=EEPROM_INHIBT_WRITE_CYCLES;
    INTCONbits.GIE=interrupt_status;
    return retVal;
}
/**
 * @brief read byte from eeprom
 * @param add the addres to read data from 
 * @param data variable to save the data read in
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType eeprom_read_byte(uint16 add,uint8 *data){
    Std_ReturnType retVal=E_OK;
    if(NULL==data){
        retVal=E_NOT_OK;
    }
    else{
        EEADR=(uint8)(add&0xFF);
        EEADRH=(uint8)((add>>8)&0x03);
        EECON1bits.EEPGD=EEPROM_ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS=EEPROM_ACCESS_FLASH_EEPROM_MEMORY;
        EECON1bits.RD=EEPROM_INITIATE_DATA_READ;
        NOP();
        NOP();
        *data=EEDATA;
    }
    return retVal;
}
