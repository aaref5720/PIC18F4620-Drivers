/* 
 * File:   ecu_keypad.h
 * Author: Abdelrahman Aref 
 *
 * Created on October 6, 2023, 8:08 PM
 */

#include"ecu_keypad.h"

static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
                                                                        {'7', '8', '9', '/'},
                                                                        {'4', '5', '6', '*'},
                                                                        {'1', '2', '3', '-'},
                                                                        {'#', '0', '=', '+'}
                                                                     };

/**
 * @brief Initialize the keypad assigned pins
 * @param _keypad_obj pointer to the keypad configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj)
{
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = 0, columns_counter = 0;
    
    if(NULL == _keypad_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        for(rows_counter = 0; rows_counter < ECU_KEYPAD_ROWS; rows_counter++)
        {
            pin_config_t row_element = {.PORT = _keypad_obj->keypad_row_pins[rows_counter].PORT,
                                        .PIN = _keypad_obj->keypad_row_pins[rows_counter].PIN,
                                        .DIRECTION = GPIO_DIRECTION_OUTPUT,
                                        .LOGIC = GPIO_LOW};
            
            ret = gpio_pin_intialize(&(row_element));
        }
        for(columns_counter = 0; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++)
        {
            pin_config_t column_element = {.PORT = _keypad_obj->keypad_columns_pins[ECU_KEYPAD_COLUMNS].PORT,
                                           .PIN = _keypad_obj->keypad_columns_pins[ECU_KEYPAD_COLUMNS].PIN,
                                           .DIRECTION = GPIO_DIRECTION_INPUT,
                                           .LOGIC = GPIO_LOW};
            ret = gpio_pin_direction_intialize(&(column_element));
        }
    }
    return ret;
}

/**
 * @brief Get the value of the button pressed by the user and performing the scanning algorithm
 * @param _keypad_obj pointer to the keypad configurations
 * @param value Value of the button pressed by the user
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value)
{
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = 0, columns_counter = 0, counter = 0;
    logic_t column_logic = 0;
    pin_config_t row_element[ECU_KEYPAD_ROWS];
    pin_config_t column_element[ECU_KEYPAD_COLUMNS];
    
    if(NULL == _keypad_obj || NULL == value)
    {
        ret = E_NOT_OK;
    }
    else
    {   
        for(rows_counter = 0; rows_counter < ECU_KEYPAD_ROWS; rows_counter++)
        {
            row_element[rows_counter].PORT = _keypad_obj->keypad_row_pins[rows_counter].PORT;
            row_element[rows_counter].PIN = _keypad_obj->keypad_row_pins[rows_counter].PIN;
            row_element[rows_counter].DIRECTION = GPIO_DIRECTION_OUTPUT;
            row_element[rows_counter].LOGIC = GPIO_LOW;
        }
        
        for(columns_counter = 0; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++)
        {
            column_element[columns_counter].PORT = _keypad_obj->keypad_columns_pins[rows_counter].PORT;
            column_element[columns_counter].PIN = _keypad_obj->keypad_columns_pins[rows_counter].PIN;
            column_element[columns_counter].DIRECTION = GPIO_DIRECTION_INPUT;
            column_element[columns_counter].LOGIC = GPIO_LOW;
        }
        
        for(rows_counter = 0; rows_counter < ECU_KEYPAD_ROWS; rows_counter++)
        {
            for(counter = 0; counter < ECU_KEYPAD_ROWS; counter++)
            {
                ret = gpio_pin_write_logic(&(row_element[counter]), GPIO_LOW);
            }
            
            ret = gpio_pin_write_logic(&(row_element[rows_counter]), GPIO_HIGH);
            __delay_ms(15);
            
            for(columns_counter = 0; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++)
            {
                ret = gpio_pin_read_logic(&(column_element[columns_counter]), &column_logic);
                if(GPIO_HIGH == column_logic)
                {
                    *value = btn_values[rows_counter][columns_counter];
                }
            }
        }
    }
    return ret;  
}
