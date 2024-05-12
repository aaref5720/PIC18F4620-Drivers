/* 
 * File:   ecu_dc_motor.h
 * Author: Abdelrahman Aref
 *
 * Created on October 2, 2023, 11:28 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Section : Includes */
#include"ecu_dc_motor_cfg.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"
/* Section: Macro Declarations */
#define DC_MOTOR_OFF_STATUS  0x00u
#define DC_MOTOR_ON_STATUS   0x01u

/* Section: Macro Functions Declarations */


/* Section: Data Type Declarations */
typedef struct
{
    uint8 PORT                  : 4 ;
    uint8 PIN                   : 3 ;
    uint8 DC_Motor_PIN_State    : 1 ;
}DC_MOTOR_PIN_t;

typedef struct
{
 DC_MOTOR_PIN_t dc_motor_pins[2];   
}DC_MOTOR_t;

/* Section: Function Declarations */

/**
 * @brief Initialize the assigned pins to be OUTPUT and turn the motor OFF or ON.
 * @param dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_intialize(const DC_MOTOR_t *dc_motor);

/**
 * @brief Move the motor to the right direction
 * @param dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right(const DC_MOTOR_t *dc_motor);

/**
 * @brief Move the motor to the left direction
 * @param dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left(const DC_MOTOR_t *dc_motor);

/**
 * @brief stop the motor movement
 * @param dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(const DC_MOTOR_t *dc_motor);

#endif	/* ECU_DC_MOTOR_H */

