/* 
 * File:   ecu_chr_lcd.c
 * Author: ADHAM KHALED
 *
 * Created on August 4, 2023, 9:38 PM
 */
#include "ecu_chr_lcd.h"
static Std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd,uint8 data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column);

/**
 * @brief initialize the 4 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_4bit_initalize(const chr_lcd_4bit_t *lcd){
    Std_ReturnType retVal=E_OK;
    uint8 counter=0;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=gpio_pin_initialize(&(lcd->lcd_rs));
        retVal=gpio_pin_initialize(&(lcd->lcd_en));
        for(counter=0;counter<4;counter++){
            retVal=gpio_pin_initialize(&(lcd->lcd_data[counter]));
        }
        __delay_ms(20);
        retVal=lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
         retVal=lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        retVal=lcd_4bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        retVal=lcd_4bit_send_command(lcd,LCD_CLEAR);
        retVal=lcd_4bit_send_command(lcd,LCD_RETURN_HOME);
        retVal=lcd_4bit_send_command(lcd,LCD_ENTRY_MODE);
        retVal=lcd_4bit_send_command(lcd,LCD_CURSOR_OFF_DISPLAY_ON);
        retVal=lcd_4bit_send_command(lcd,LCD_4BIT_MODE_2_LINE);
        retVal=lcd_4bit_send_command(lcd,0x80);
    }
    return retVal;
}
/**
 * @brief send command for 4 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @param command the command to be sent
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd,uint8 command){
    Std_ReturnType retVal=E_OK;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        retVal=lcd_send_4bit(lcd,command>>4);
        retVal=lcd_4bit_send_enable_signal(lcd);
        retVal=lcd_send_4bit(lcd,command);
        retVal=lcd_4bit_send_enable_signal(lcd);

    }
    return retVal;
}
/**
 * @brief send char for 4 bit lcd to display
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @param data the char to be displayed
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd,uint8 data){
    Std_ReturnType retVal=E_OK;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        retVal=lcd_send_4bit(lcd,data>>4);
        retVal=lcd_4bit_send_enable_signal(lcd);
        retVal=lcd_send_4bit(lcd,data);
        retVal=lcd_4bit_send_enable_signal(lcd);

    }
    return retVal;
}
/**
 * @brief send char to display it on a specific position for 4 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @param row the row to display the char on 
 * @param column the column to display the char on
 * @param data the char to be displayed
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data){
    Std_ReturnType retVal=E_OK;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=lcd_4bit_set_cursor(lcd,row,column);
        retVal=lcd_4bit_send_char_data(lcd,data);
    }
    return retVal;
    
}
/**
 * @brief send string for 4 bit lcd to display
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @param str the string to be displayed
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd,uint8 *str){
    Std_ReturnType retVal=E_OK;
    if(NULL==lcd ){
        retVal=E_OK;
    }
    else{
        while(*str){
            retVal=lcd_4bit_send_char_data(lcd,*str);
            str++;
        }
    }
    return retVal;
    
}
/**
 * @brief send string to display it on a specific position for 4 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @param row the row to display the string on 
 * @param column the column to display the string on
 * @param string the string to be displayed
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 *str){
    Std_ReturnType retVal=E_OK;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=lcd_4bit_set_cursor(lcd,row,column);
        while(*str){
            retVal=lcd_4bit_send_char_data(lcd,*str);
            str++;
        }
    }
    return retVal;
}
/**
 * @brief  send a custom character to display it on specific position for 4 bit lcd 
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @param row the row to display the char on 
 * @param column the column to display the char on
 * @param chr the char to be diplayed
 * @param mem_pos the position in CGRAM to store the custom character
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,const uint8 chr[],uint8 mem_pos){
    Std_ReturnType retVal=E_OK;
    uint8 counter=0;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=lcd_4bit_send_command(lcd,LCD_CGRAM_START+(mem_pos*8));
        for(counter=0;counter<8;counter++){
            retVal=lcd_4bit_send_char_data(lcd,chr[counter]);
        }
        retVal=lcd_4bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    return retVal;
}

/**
 * @brief initialize the 8 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_8bit_initalize(const chr_lcd_8bit_t *lcd){
    Std_ReturnType retVal=E_OK;
    uint8 counter=0;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=gpio_pin_initialize(&(lcd->lcd_rs));
        retVal=gpio_pin_initialize(&(lcd->lcd_en));
        for(counter=0;counter<8;counter++){
            retVal=gpio_pin_initialize(&(lcd->lcd_data[counter]));
        }
        __delay_ms(20);
        retVal=lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
         retVal=lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        retVal=lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        retVal=lcd_8bit_send_command(lcd,LCD_CLEAR);
        retVal=lcd_8bit_send_command(lcd,LCD_RETURN_HOME);
        retVal=lcd_8bit_send_command(lcd,LCD_ENTRY_MODE);
        retVal=lcd_8bit_send_command(lcd,LCD_CURSOR_OFF_DISPLAY_ON);
        retVal=lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        retVal=lcd_8bit_send_command(lcd,0x80);
    }
    return retVal;
}
/**
 * @brief send command for 8 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @param command the command to be sent
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd,uint8 command){
    Std_ReturnType retVal=E_OK;
    uint8 counter=0;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        for(counter=0;counter<8;counter++){
            retVal=gpio_pin_write_logic(&(lcd->lcd_data[counter]),(command>>counter)&(uint8)0x01);
        }
        retVal=lcd_8bit_send_enable_signal(lcd);
    }
    return retVal;
}
/**
 * @brief send char for 8 bit lcd to display
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @param data the char to be displayed
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd,uint8 data){
    Std_ReturnType retVal=E_OK;
    uint8 counter=0;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        for(counter=0;counter<8;counter++){
            retVal=gpio_pin_write_logic(&(lcd->lcd_data[counter]),(data>>counter)&(uint8)0x01);
        }
        retVal=lcd_8bit_send_enable_signal(lcd);
    }
    return retVal;
}
/**
 * @brief send char to displayed it on specific position for 8 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @param row the row to display the char on 
 * @param column the column to display the char on
 * @param data the char to be displayed
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data){
    Std_ReturnType retVal=E_OK;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=lcd_8bit_set_cursor(lcd,row,column);
        retVal=lcd_8bit_send_char_data(lcd,data);
    }
    return retVal;
    
}
/**
 * @brief send string for 8 bit lcd tp display
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @param str the string to be displayed
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd,uint8 *str){
    Std_ReturnType retVal=E_OK;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        while(*str){
            retVal=lcd_8bit_send_char_data(lcd,*str);
            str++;
        }
    }
    return retVal;
}
/**
 * @brief send string to display it on specific position for 8 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @param row the row to display the string on 
 * @param column the column to display the string on
 * @param str the string to be displayed
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 *str){
    Std_ReturnType retVal=E_OK;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=lcd_8bit_set_cursor(lcd,row,column);
        while(*str){
            retVal=lcd_8bit_send_char_data(lcd,*str);
            str++;
        }

    }
    return retVal;
    
}
/**
 * @brief  send a custom character to display it on specific position for 8 bit lcd 
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @param row the row to display the char on 
 * @param column the column to display the char on
 * @param chr the char to be diplayed
 * @param mem_pos the position in CGRAM to store the custom character
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,const uint8 chr[],uint8 mem_pos){
    Std_ReturnType retVal=E_OK;
    uint8 counter=0;
    if(NULL==lcd){
        retVal=E_OK;
    }
    else{
        retVal=lcd_8bit_send_command(lcd,LCD_CGRAM_START+(mem_pos*8));
        for(counter=0;counter<8;counter++){
            retVal=lcd_8bit_send_char_data(lcd,chr[counter]);
        }
        retVal=lcd_8bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    return retVal;
}
/**
 * @brief convert uint8 number to string
 * @param value the number to be converted
 * @param str the string to store the number in 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType convert_byte_to_string(uint8 value,uint8 *str){
    Std_ReturnType retVal=E_OK;
    if(NULL==str){
        retVal=E_NOT_OK;
    }
    else{
        memset(str,'\0',4);
        sprintf(str,"%i",value);
    } 
    return retVal;
}
/**
 * @brief convert uint16 number to string
 * @param value the number to be converted
 * @param str the string to store the number in 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType convert_short_to_string(uint16 value,uint8 *str){
    Std_ReturnType retVal=E_OK;
    if(NULL==str){
        retVal=E_NOT_OK;
    }
    else{
    memset(str,'\0',6);
    sprintf(str,"%i",value);
    } 
    return retVal;
}
/**
 * @brief convert uint32 number to string
 * @param value the number to be converted
 * @param str the string to store the number in 
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType convert_int_to_string(uint32 value,uint8 *str){
    Std_ReturnType retVal=E_OK;
    if(NULL==str){
        retVal=E_NOT_OK;
    }
    else{
        memset(str,'\0',11);
        sprintf(str,"%i",value);
    } 
    return retVal;
}
/**
 * @brief static function to send 4 bits to a 4 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @param data_command the 4 bits to be sent
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd,uint8 data_command){
    Std_ReturnType retVal=E_OK;
    retVal=gpio_pin_write_logic(&(lcd->lcd_data[0]),(data_command>>0)& (uint8)0x01);
    retVal=gpio_pin_write_logic(&(lcd->lcd_data[1]),(data_command>>1)& (uint8)0x01);
    retVal=gpio_pin_write_logic(&(lcd->lcd_data[2]),(data_command>>2)& (uint8)0x01);
    retVal=gpio_pin_write_logic(&(lcd->lcd_data[3]),(data_command>>3)& (uint8)0x01);
}
/**
 * @brief static function to send the enable signal to a 4 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd){
    Std_ReturnType retVal=E_OK;
    retVal=gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
    __delay_us(5);
    retVal=gpio_pin_write_logic(&(lcd->lcd_en),LOW);
}
/**
 * @brief static function to send the enable signal to a 8 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType retVal=E_OK;
    retVal=gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
    __delay_us(5);
    retVal=gpio_pin_write_logic(&(lcd->lcd_en),LOW);
}
/**
 * @brief static function to set the cursor to a specific position for 8 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @param row the row to set the cursor on
 * @param column the column to set the cursor on
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column){
    Std_ReturnType retVal=E_OK;
    column--;
    switch (row)
    {
    case ROW1:
        retVal=lcd_8bit_send_command(lcd,(0x80+column));
        break;
    case ROW2:
        retVal=lcd_8bit_send_command(lcd,(0xC0+column));
        break;
    case ROW3:
        retVal=lcd_8bit_send_command(lcd,(0x94+column));
        break;
    case ROW4:
        retVal=lcd_8bit_send_command(lcd,(0xD4+column));
        break;
    default:
        retVal=E_NOT_OK;
        break;
    }
}
/**
 * @brief static function to set the cursor to a specific position for 4 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @param row the row to set the cursor on
 * @param column the column to set the cursor on
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column){
    Std_ReturnType retVal=E_OK;
    column--;
    switch (row)
    {
    case ROW1:
        retVal=lcd_4bit_send_command(lcd,(0x80+column));
        break;
    case ROW2:
        retVal=lcd_4bit_send_command(lcd,(0xC0+column));
        break;
    case ROW3:
        retVal=lcd_4bit_send_command(lcd,(0x94+column));
        break;
    case ROW4:
        retVal=lcd_4bit_send_command(lcd,(0xD4+column));
        break;
    default:
        retVal=E_NOT_OK;
        break;
    }    
}
