/* 
 * File:   ecu_led.c
 * Author: Abdelrahman Aref
 *
 * Created on September 29, 2023, 1:41 PM
 */

#include"ecu_led.h"

/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the led OFF or ON.
 * @param led : pointer to the led module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_intialize(const LED_t *led)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        pin_config_t pin_led = {.PORT = led->PORT, .PIN = led->PIN, .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = led->LED_State};
        ret = gpio_pin_intialize(&pin_led);
    }
    return ret;
}

/**
 * @brief Turn the led on
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_turn_on(const LED_t *led)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        pin_config_t pin_led = {.PORT = led->PORT, .PIN = led->PIN, .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = GPIO_HIGH};
        ret = gpio_pin_write_logic(&pin_led, GPIO_HIGH); 
    }
    return ret; 
}

/**
 * @brief Turn the led off
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_turn_off(const LED_t *led)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        pin_config_t pin_led = {.PORT = led->PORT, .PIN = led->PIN, .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = GPIO_LOW};
        ret = gpio_pin_write_logic(&pin_led, GPIO_LOW);    
    }
    return ret; 
}

/**
 * @brief Toggle the led
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_toggle(const LED_t *led)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        pin_config_t pin_led = {.PORT = led->PORT, .PIN = led->PIN, .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = LED_OFF};
        ret = gpio_pin_toggle_logic(&pin_led);   
    }
    return ret; 
}