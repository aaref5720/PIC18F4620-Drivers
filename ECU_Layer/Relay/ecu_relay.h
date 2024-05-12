/* 
 * File:   ecu_relay.h
 * Author: Abdelrahman Aref
 *
 * Created on October 2, 2023, 10:32 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section : Includes */
#include"ecu_relay_cfg.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */
#define Relay_OFF  0
#define Relay_ON   1

/* Section: Macro Functions Declarations */


/* Section: Data Type Declarations */

typedef struct
{
    uint8 PORT      : 4 ;
    uint8 PIN       : 3 ;
    uint8 Relay_State : 1 ;
}RELAY_t;

/* Section: Function Declarations */
/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the relay OFF or ON.
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_intialize(const RELAY_t *relay);

/**
 * @brief Turn the relay on
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_turn_on(const RELAY_t *relay);

/**
 * @brief Turn the relay off
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_turn_off(const RELAY_t *relay);

#endif	/* ECU_RELAY_H */

