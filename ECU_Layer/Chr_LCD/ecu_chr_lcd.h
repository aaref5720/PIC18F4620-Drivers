/* 
 * File:   ecu_chr_lcd.h
 * Author: Abdelrahman Aref
 *
 * Created on October 7, 2023, 8:27 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/* Section : Includes */
#include"ecu_chr_lcd_cfg.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */
#define _LCD_CLEAR                                  0X01
#define _LCD_RETURN_HOME                            0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF               0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON                0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF               0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON                0x07
#define _LCD_CURSOR_MOVE_SHIFT_LEFT                 0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT                0x14
#define _LCD_DISPLAY_SHIFT_LEFT                     0x18
#define _LCD_DISPLAY_SHIFT_RIGHT                    0x1C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF    0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON     0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF     0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON      0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF                 0x08
#define _LCD_8BIT_MODE_2_LINE                       0x38
#define _LCD_4BIT_MODE_2_LINE                       0x28

#define _LCD_CGRAM_START                            0x40
#define _LCD_DDRAM_START                            0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

/* Section: Macro Functions Declarations */


/* Section: Data Type Declarations */
typedef struct
{
    uint8 PORT  : 3;
    uint8 PIN   : 3;
}rs_pin_t;

typedef struct
{
    uint8 PORT  : 3;
    uint8 PIN   : 3;
}en_pin_t;

typedef struct
{
    uint8 PORT  : 3;
    uint8 PIN   : 3;
}data_pin_t;

typedef struct
{
    rs_pin_t rs;
    en_pin_t en;
    data_pin_t data[4];
}chr_lcd_4bit_t;

typedef struct
{
    rs_pin_t rs;
    en_pin_t en;
    data_pin_t data[8];
}chr_lcd_8bit_t;

/* Section: Function Declarations */

/**
 * Initialize the 4-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd);

/**
 * Send a command to the 4-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param command The command to send.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command);

/**
 * Send character data to the 4-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param data The character data to send.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data);

/**
 * Send character data to a specific position on the 4-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param row The row where the character data should be placed.
 * @param column The column where the character data should be placed.
 * @param data The character data to send.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data);

/**
 * Send a string to the 4-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param str The string to send to the LCD.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str);

/**
 * Send a string to a specific position on the 4-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param row The row where the string should be placed.
 * @param column The column where the string should be placed.
 * @param str The string to send to the LCD.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str);

/**
 * Send a custom character to the 4-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param row The row where the custom character should be placed.
 * @param column The column where the custom character should be placed.
 * @param _chr The custom character data to send.
 * @param mem_pos The memory position for the custom character.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos);

/**
 * Initialize the 8-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd);

/**
 * Send a command to the 8-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param command The command to send.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command);

/**
 * Send character data to the 8-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param data The character data to send.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data);

/**
 * Send character data to a specific position on the 8-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param row The row where the character data should be placed.
 * @param column The column where the character data should be placed.
 * @param data The character data to send.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data);

/**
 * Send a string to the 8-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param str The string to send to the LCD.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str);

/**
 * Send a string to a specific position on the 8-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param row The row where the string should be placed.
 * @param column The column where the string should be placed.
 * @param str The string to send to the LCD.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str);

/**
 * Send a custom character to the 8-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param row The row where the custom character should be placed.
 * @param column The column where the custom character should be placed.
 * @param _chr The custom character data to send.
 * @param mem_pos The memory position for the custom character.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos);

/**
 * Convert an 8-bit unsigned integer to a string representation.
 *
 * @param value The value to convert.
 * @param str The output string.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str);

/**
 * Convert a 16-bit unsigned integer to a string representation.
 *
 * @param value The value to convert.
 * @param str The output string.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str);

/**
 * Convert a 32-bit unsigned integer to a string representation.
 *
 * @param value The value to convert.
 * @param str The output string.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str);



#endif	/* ECU_CHR_LCD_H */

