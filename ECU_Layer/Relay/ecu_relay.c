/* 
 * File:   ecu_relay.c
 * Author: Abdelrahman Aref
 *
 * Created on October 2, 2023, 10:32 PM
 */

#include"ecu_relay.h"

/* Section: Function Declarations */
/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the relay OFF or ON.
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_intialize(const RELAY_t *relay)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == relay)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        pin_config_t relay_pin = {.PORT = relay->PORT, .PIN = relay->PIN, .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = relay->Relay_State};
        ret = gpio_pin_intialize(&relay_pin);
    }
    return ret;
}

/**
 * @brief Turn the relay on
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_turn_on(const RELAY_t *relay)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == relay)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        pin_config_t relay_pin = {.PORT = relay->PORT, .PIN = relay->PIN, .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = GPIO_HIGH};
        ret = gpio_pin_write_logic(&relay_pin, GPIO_HIGH); 
    }
    return ret;
}

/**
 * @brief Turn the relay off
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_turn_off(const RELAY_t *relay)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == relay)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        pin_config_t relay_pin = {.PORT = relay->PORT, .PIN = relay->PIN, .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = GPIO_LOW};
        ret = gpio_pin_write_logic(&relay_pin, GPIO_LOW); 
    }
    return ret;
}