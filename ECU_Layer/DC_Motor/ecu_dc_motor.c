/* 
 * File:   ecu_dc_motor.c
 * Author: Abdelrahman Aref
 *
 * Created on October 2, 2023, 11:28 PM
 */
#include"ecu_dc_motor.h"

/**
 * @brief Initialize the assigned pins to be OUTPUT and turn the motor OFF or ON.
 * @param dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_intialize(const DC_MOTOR_t *dc_motor)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        pin_config_t dc_motor_pin_1 = {.PORT = dc_motor->dc_motor_pins[0].PORT, .PIN = dc_motor->dc_motor_pins[0].PIN,
                                     .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = dc_motor->dc_motor_pins[0].DC_Motor_PIN_State};
        
         pin_config_t dc_motor_pin_2 = {.PORT = dc_motor->dc_motor_pins[1].PORT, .PIN = dc_motor->dc_motor_pins[1].PIN,
                                     .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = dc_motor->dc_motor_pins[1].DC_Motor_PIN_State};
         
        ret = gpio_pin_intialize(&dc_motor_pin_1);
        ret = gpio_pin_intialize(&dc_motor_pin_2);
        
    }
    return ret;
}

/**
 * @brief Move the motor to the right direction
 * @param dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right(const DC_MOTOR_t *dc_motor)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        pin_config_t dc_motor_pin_1 = {.PORT = dc_motor->dc_motor_pins[0].PORT, .PIN = dc_motor->dc_motor_pins[0].PIN,
                                     .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = dc_motor->dc_motor_pins[0].DC_Motor_PIN_State};
        
         pin_config_t dc_motor_pin_2 = {.PORT = dc_motor->dc_motor_pins[1].PORT, .PIN = dc_motor->dc_motor_pins[1].PIN,
                                     .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = dc_motor->dc_motor_pins[1].DC_Motor_PIN_State};
         
        ret = gpio_pin_write_logic(&dc_motor_pin_1, GPIO_HIGH);
        ret = gpio_pin_write_logic(&dc_motor_pin_2, GPIO_LOW);
        
    }
    return ret;
}

/**
 * @brief Move the motor to the left direction
 * @param dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left(const DC_MOTOR_t *dc_motor)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        pin_config_t dc_motor_pin_1 = {.PORT = dc_motor->dc_motor_pins[0].PORT, .PIN = dc_motor->dc_motor_pins[0].PIN,
                                     .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = dc_motor->dc_motor_pins[0].DC_Motor_PIN_State};
        
         pin_config_t dc_motor_pin_2 = {.PORT = dc_motor->dc_motor_pins[1].PORT, .PIN = dc_motor->dc_motor_pins[1].PIN,
                                     .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = dc_motor->dc_motor_pins[1].DC_Motor_PIN_State};
         
        ret = gpio_pin_write_logic(&dc_motor_pin_1, GPIO_LOW);
        ret = gpio_pin_write_logic(&dc_motor_pin_2, GPIO_HIGH);
        
    }
    return ret;   
}

/**
 * @brief stop the motor movement
 * @param dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(const DC_MOTOR_t *dc_motor)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        pin_config_t dc_motor_pin_1 = {.PORT = dc_motor->dc_motor_pins[0].PORT, .PIN = dc_motor->dc_motor_pins[0].PIN,
                                     .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = dc_motor->dc_motor_pins[0].DC_Motor_PIN_State};
        
         pin_config_t dc_motor_pin_2 = {.PORT = dc_motor->dc_motor_pins[1].PORT, .PIN = dc_motor->dc_motor_pins[1].PIN,
                                     .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = dc_motor->dc_motor_pins[1].DC_Motor_PIN_State};
         
        ret = gpio_pin_write_logic(&dc_motor_pin_1, GPIO_LOW);
        ret = gpio_pin_write_logic(&dc_motor_pin_2, GPIO_LOW);
        
    }
    return ret;  
}