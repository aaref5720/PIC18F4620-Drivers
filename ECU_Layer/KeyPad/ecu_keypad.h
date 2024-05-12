/* 
 * File:   ecu_keypad.h
 * Author: Abdelrahman Aref 
 *
 * Created on October 6, 2023, 8:08 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */
#include"ecu_keypad_cfg.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */
#define ECU_KEYPAD_ROWS    4
#define ECU_KEYPAD_COLUMNS 4 

/* Section: Macro Functions Declarations */


/* Section: Data Type Declarations */
typedef struct
{
    uint8 PORT : 3;
    uint8 PIN : 3;
}keypad_row_t;

typedef struct
{
    uint8 PORT : 3;
    uint8 PIN : 3;
}keypad_column_t;

typedef struct{
    keypad_row_t keypad_row_pins[ECU_KEYPAD_ROWS];
    keypad_column_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/* Section: Function Declarations */

/**
 * @brief Initialize the keypad assigned pins
 * @param _keypad_obj pointer to the keypad configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);

/**
 * @brief Get the value of the button pressed by the user and performing the scanning algorithm
 * @param _keypad_obj pointer to the keypad configurations
 * @param value Value of the button pressed by the user
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);


#endif	/* ECU_KEYPAD_H */

