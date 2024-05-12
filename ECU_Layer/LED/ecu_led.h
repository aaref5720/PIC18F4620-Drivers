/* 
 * File:   ecu_led.h
 * Author: Abdelrahman Aref
 *
 * Created on September 29, 2023, 1:41 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include"../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */
#define LED_OFF  0
#define LED_ON   1

/* Section: Macro Functions Declarations */


/* Section: Data Type Declarations */
typedef struct
{
    uint8 PORT      : 4 ;
    uint8 PIN       : 3 ;
    uint8 LED_State : 1 ;
}LED_t;

/* Section: Function Declarations */

/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the led OFF or ON.
 * @param led : pointer to the led module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_intialize(const LED_t *led);

/**
 * @brief Turn the led on
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_turn_on(const LED_t *led);

/**
 * @brief Turn the led off
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_turn_off(const LED_t *led);

/**
 * @brief Toggle the led
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType led_toggle(const LED_t *led);

#endif	/* ECU_LED_H */

