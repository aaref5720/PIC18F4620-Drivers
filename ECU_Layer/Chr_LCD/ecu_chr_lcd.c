/* 
 * File:   ecu_chr_lcd.c
 * Author: Abdelrahman Aref
 *
 * Created on October 7, 2023, 8:27 PM
 */

#include"ecu_chr_lcd.h"

static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column);
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column);

/**
 * Initialize the 4-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t lcd_pins = {.PORT = lcd->rs.PORT,
                                 .PIN = lcd->rs.PIN,
                                 .DIRECTION = GPIO_DIRECTION_OUTPUT,
                                 .LOGIC = GPIO_LOW};
        ret = gpio_pin_intialize(&(lcd_pins));
        
        lcd_pins.PORT = lcd->en.PORT;
        lcd_pins.PIN = lcd->en.PIN;
        lcd_pins.DIRECTION = GPIO_DIRECTION_OUTPUT;
        lcd_pins.LOGIC = GPIO_LOW;        
        ret = gpio_pin_intialize(&(lcd_pins));
        
        for(counter = 0; counter < 4; counter++)
        {
            lcd_pins.PORT = lcd->data[counter].PORT;
            lcd_pins.PIN = lcd->data[counter].PIN;
            lcd_pins.DIRECTION = GPIO_DIRECTION_OUTPUT;
            lcd_pins.LOGIC = GPIO_LOW;   
            
            ret = gpio_pin_intialize(&(lcd_pins));
        }
        
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80);
    }
    return ret;
}

/**
 * Send a command to the 4-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param command The command to send.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;

    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t rs_pin = {.PORT = lcd->rs.PORT,
                               .PIN = lcd->rs.PIN,
                               .DIRECTION = GPIO_DIRECTION_OUTPUT,
                               .LOGIC = GPIO_LOW,};
        
        ret = gpio_pin_write_logic(&(rs_pin), GPIO_LOW);
        ret = lcd_send_4bits(lcd, command >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, command);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * Send character data to the 4-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param data The character data to send.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;

    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t rs_pin = {.PORT = lcd->rs.PORT,
                               .PIN = lcd->rs.PIN,
                               .DIRECTION = GPIO_DIRECTION_OUTPUT,
                               .LOGIC = GPIO_LOW,};
        
        ret = gpio_pin_write_logic(&(rs_pin), GPIO_HIGH);
        ret = lcd_send_4bits(lcd, data >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, data);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

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
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret;
}

/**
 * Send a string to the 4-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param str The string to send to the LCD.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

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
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd, row, column);
        
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

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
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos * 8)));
        
        for(lcd_counter = 0; lcd_counter <= 7; lcd_counter++)
        {
            ret = lcd_4bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

/**
 * Initialize the 8-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t lcd_pins = {.PORT = lcd->rs.PORT,
                                 .PIN = lcd->rs.PIN,
                                 .DIRECTION = GPIO_DIRECTION_OUTPUT,
                                 .LOGIC = GPIO_LOW};
        ret = gpio_pin_intialize(&(lcd_pins));
        
        lcd_pins.PORT = lcd->en.PORT;
        lcd_pins.PIN = lcd->en.PIN;
        lcd_pins.DIRECTION = GPIO_DIRECTION_OUTPUT;
        lcd_pins.LOGIC = GPIO_LOW;        
        ret = gpio_pin_intialize(&(lcd_pins));
        
        for(counter = 0; counter < 8; counter++)
        {
            lcd_pins.PORT = lcd->data[counter].PORT;
            lcd_pins.PIN = lcd->data[counter].PIN;
            lcd_pins.DIRECTION = GPIO_DIRECTION_OUTPUT;
            lcd_pins.LOGIC = GPIO_LOW;   
            
            ret = gpio_pin_intialize(&(lcd_pins));
        }
        
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, 0x80);
    }
    return ret;
}

/**
 * Send a command to the 8-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param command The command to send.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;

    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t data_pins[8];
        pin_config_t rs_pin = {.PORT = lcd->rs.PORT,
                               .PIN = lcd->rs.PIN,
                               .DIRECTION = GPIO_DIRECTION_OUTPUT,
                               .LOGIC = GPIO_LOW,};
        
        ret = gpio_pin_write_logic(&(rs_pin), GPIO_LOW);
        
        for(counter = 0; counter < 8; counter++)
        {
            data_pins[counter].PORT = lcd->data[counter].PORT;
            data_pins[counter].PIN = lcd->data[counter].PIN;
            data_pins[counter].DIRECTION = GPIO_DIRECTION_OUTPUT;
            data_pins[counter].LOGIC = GPIO_LOW;   
        }
        for(counter = 0; counter < 8; counter++)
        {
            ret = gpio_pin_write_logic(&(data_pins[counter]), (command >> counter) & 0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * Send character data to the 8-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param data The character data to send.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;

    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t data_pins[8];
        pin_config_t rs_pin = {.PORT = lcd->rs.PORT,
                               .PIN = lcd->rs.PIN,
                               .DIRECTION = GPIO_DIRECTION_OUTPUT,
                               .LOGIC = GPIO_LOW,};
        
        ret = gpio_pin_write_logic(&(rs_pin), GPIO_HIGH);
        
        for(counter = 0; counter < 8; counter++)
        {
            data_pins[counter].PORT = lcd->data[counter].PORT;
            data_pins[counter].PIN = lcd->data[counter].PIN;
            data_pins[counter].DIRECTION = GPIO_DIRECTION_OUTPUT;
            data_pins[counter].LOGIC = GPIO_LOW;   
        }
        for(counter = 0; counter < 8; counter++)
        {
            ret = gpio_pin_write_logic(&(data_pins[counter]), (data >> counter) & 0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

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
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_char_data(lcd, data);
    }
    return ret;
}

/**
 * Send a string to the 8-bit LCD module.
 *
 * @param lcd Pointer to the LCD configurations.
 * @param str The string to send to the LCD.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

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
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor(lcd, row, column);
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

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
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos * 8)));
        for(lcd_counter = 0; lcd_counter <= 7; lcd_counter++)
        {
            ret = lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

/**
 * Convert an 8-bit unsigned integer to a string representation.
 *
 * @param value The value to convert.
 * @param str The output string.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if (NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, '\0', 4);
        sprintf(str, "%i", value);
    }
    return ret;
}

/**
 * Convert a 16-bit unsigned integer to a string representation.
 *
 * @param value The value to convert.
 * @param str The output string.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if (NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        
        while(Temp_String[DataCounter] != '\0')
        {
            str[DataCounter] = Temp_String[DataCounter];
            DataCounter++;
        }
    }
    return ret;
}

/**
 * Convert a 32-bit unsigned integer to a string representation.
 *
 * @param value The value to convert.
 * @param str The output string.
 * @return Status of the function.
 *         (E_OK) : The function completed successfully.
 *         (E_NOT_OK) : The function encountered an issue.
 */
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if (NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, '\0', 11);
        sprintf(str, "%i", value);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param _data_command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command)
{
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
         pin_config_t data_pins[4];
        for(counter = 0; counter < 4; counter++)
        {
            data_pins[counter].PORT = lcd->data[counter].PORT;
            data_pins[counter].PIN = lcd->data[counter].PIN;
            data_pins[counter].DIRECTION = GPIO_DIRECTION_OUTPUT;
            data_pins[counter].LOGIC = GPIO_LOW;   
        } 
        ret = gpio_pin_write_logic(&(data_pins[0]), (_data_command >> 0) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(data_pins[1]), (_data_command >> 1) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(data_pins[2]), (_data_command >> 2) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(data_pins[3]), (_data_command >> 3) & (uint8)0x01);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t en_pin = {.PORT = lcd->en.PORT,
                               .PIN = lcd->en.PIN,
                               .DIRECTION = GPIO_DIRECTION_OUTPUT,
                               .LOGIC = GPIO_HIGH,};
        
        ret = gpio_pin_write_logic(&(en_pin), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(en_pin), GPIO_LOW);   
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t en_pin = {.PORT = lcd->en.PORT,
                               .PIN = lcd->en.PIN,
                               .DIRECTION = GPIO_DIRECTION_OUTPUT,
                               .LOGIC = GPIO_LOW,};
        
        ret = gpio_pin_write_logic(&(en_pin), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(en_pin), GPIO_LOW);   
    }
    return ret;
}

/**
 * 
 * @param lcd Pointer to the LCD configuration parameters defined by the user
 * @param row Which row you need to print your character
 * @param coulmn Which column you need to print your character
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        column--;
        switch(row)
        {
            case ROW1 : ret = lcd_8bit_send_command(lcd, (0x80 + column)); break;
            case ROW2 : ret = lcd_8bit_send_command(lcd, (0xc0 + column)); break;
            case ROW3 : ret = lcd_8bit_send_command(lcd, (0x94 + column)); break;
            case ROW4 : ret = lcd_8bit_send_command(lcd, (0xd4 + column)); break;
            default : ;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        column--;
        switch(row)
        {
            case ROW1 : ret = lcd_4bit_send_command(lcd, (0x80 + column)); break;
            case ROW2 : ret = lcd_4bit_send_command(lcd, (0xc0 + column)); break;
            case ROW3 : ret = lcd_4bit_send_command(lcd, (0x94 + column)); break;
            case ROW4 : ret = lcd_4bit_send_command(lcd, (0xd4 + column)); break;
            default : ;
        }
    }
    return ret;
}

