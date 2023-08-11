/* 
 * File:   ecu_chr_lcd.h
 * Author: ADHAM KHALED
 *
 * Created on August 4, 2023, 9:38 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H


/* ----------------Includes----------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_chr_lcd_cfg.h"
/* ----------------Macro Declarations---------------*/
#define LCD_CLEAR                       0x01
#define LCD_RETURN_HOME                 0x02
#define LCD_ENTRY_MODE                  0x06
#define LCD_CURSOR_OFF_DISPLAY_ON       0x0C
#define LCD_CURSOR_OFF_DISPLAY_OFF      0x08
#define LCD_CURSOR_ON_BLINK_ON          0x0F
#define LCD_CURSOR_ON_BLINK_OFF         0x0E
#define LCD_CURSOR_MOVE_SHIFT_LEFT      0x10
#define LCD_CURSOR_MOVE_SHIFT_RIGHT     0x14
#define LCD_DISPLAY_SHIFT_RIGHT         0x1C
#define LCD_DISPLAY_SHIFT_LEFT          0x18
#define LCD_8BIT_MODE_2_LINE            0x38
#define LCD_4BIT_MODE_2_LINE            0x28  
#define LCD_CGRAM_START                 0x40
#define LCD_DDRAM_START                 0x80

#define ROW1  1
#define ROW2  2
#define ROW3  3
#define ROW4  4

/* ----------------Macro Functions Declarations----------------*/
/* ----------------Data Type Declarations----------------*/
typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;
/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize the 4 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_4bit_initalize(const chr_lcd_4bit_t *lcd);
/**
 * @brief send command for 4 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @param command the command to be sent
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd,uint8 command);
/**
 * @brief send char for 4 bit lcd to display
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @param data the char to be displayed
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd,uint8 data);
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
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data);
/**
 * @brief send string for 4 bit lcd to display
 * @param lcd refrence to the lcd configurations @ref chr_lcd_4bit_t
 * @param str the string to be displayed
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd,uint8 *str);
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
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 *str);
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
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,const uint8 chr[],uint8 mem_pos);
/**
 * @brief initialize the 8 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_8bit_initalize(const chr_lcd_8bit_t *lcd);
/**
 * @brief send command for 8 bit lcd
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @param command the command to be sent
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd,uint8 command);
/**
 * @brief send char for 8 bit lcd to display
 * @param lcd refrence to the lcd configurations @ref chr_lcd_8bit_t
 * @param data the char to be displayed
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOK): The function had issue to perform this action  
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd,uint8 data);
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
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data);
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd,uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,const uint8 chr[],uint8 mem_pos);

Std_ReturnType convert_byte_to_string(uint8 value,uint8 *str);
Std_ReturnType convert_short_to_string(uint16 value,uint8 *str);
Std_ReturnType convert_int_to_string(uint32 value,uint8 *str);
#endif	/* ECU_CHR_LCD_H */

