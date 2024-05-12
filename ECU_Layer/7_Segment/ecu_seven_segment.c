/* 
 * File:   ecu_seven_segment.c
 * Author: Abdelrahman Aref
 *
 * Created on October 6, 2023, 2:13 PM
 */

#include"ecu_seven_segment.h"

/**
 * This Interface to make the needed GPIO and segment initialization
 * @param seg pointer to the segment configurations 
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segment_intialize(const segment_t *seg)
{
    Std_ReturnType ret = E_OK;
    if(NULL == seg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {.PORT = seg->segment_pin_cfg[SEGMENT_PIN0].PORT, .PIN = seg->segment_pin_cfg[SEGMENT_PIN0].PIN, 
                            .DIRECTION = GPIO_DIRECTION_OUTPUT, .LOGIC = seg->segment_pin_cfg[SEGMENT_PIN0].LED_State};
        ret = gpio_pin_intialize(&pin);
        
        pin.PORT = seg->segment_pin_cfg[SEGMENT_PIN1].PORT; 
        pin.PIN = seg->segment_pin_cfg[SEGMENT_PIN1].PIN; 
        pin.DIRECTION = GPIO_DIRECTION_OUTPUT; 
        pin.LOGIC = seg->segment_pin_cfg[SEGMENT_PIN1].LED_State;
        ret = gpio_pin_intialize(&pin);
        
        pin.PORT = seg->segment_pin_cfg[SEGMENT_PIN2].PORT; 
        pin.PIN = seg->segment_pin_cfg[SEGMENT_PIN2].PIN; 
        pin.DIRECTION = GPIO_DIRECTION_OUTPUT; 
        pin.LOGIC = seg->segment_pin_cfg[SEGMENT_PIN2].LED_State;
        ret = gpio_pin_intialize(&pin);
        
        pin.PORT = seg->segment_pin_cfg[SEGMENT_PIN3].PORT;
        pin.PIN = seg->segment_pin_cfg[SEGMENT_PIN3].PIN; 
        pin.DIRECTION = GPIO_DIRECTION_OUTPUT;
        pin.LOGIC = seg->segment_pin_cfg[SEGMENT_PIN3].LED_State;
        ret = gpio_pin_intialize(&pin);        
    }
    return ret;
}

/**
 * Write a number to the segment 0 ~ 9
 * @param seg pointer to the segment configurations 
 * @param number the needed number to show
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number)
{
    Std_ReturnType ret = E_OK;
    if(NULL == seg || number > 9)
    {
        ret = E_NOT_OK;
    }
    else
    {  
        pin_config_t pins[4] = {pins[0].PORT = seg->segment_pin_cfg[SEGMENT_PIN0].PORT, pins[0].PIN = seg->segment_pin_cfg[SEGMENT_PIN0].PIN, 
                                pins[0].DIRECTION = GPIO_DIRECTION_OUTPUT, pins[0].LOGIC = seg->segment_pin_cfg[SEGMENT_PIN0].LED_State,
        
                                pins[1].PORT = seg->segment_pin_cfg[SEGMENT_PIN1].PORT, pins[1].PIN = seg->segment_pin_cfg[SEGMENT_PIN1].PIN, 
                                pins[1].DIRECTION = GPIO_DIRECTION_OUTPUT, pins[1].LOGIC = seg->segment_pin_cfg[SEGMENT_PIN1].LED_State,
        
                                pins[2].PORT = seg->segment_pin_cfg[SEGMENT_PIN2].PORT, pins[2].PIN = seg->segment_pin_cfg[SEGMENT_PIN2].PIN, 
                                pins[2].DIRECTION = GPIO_DIRECTION_OUTPUT, pins[2].LOGIC = seg->segment_pin_cfg[SEGMENT_PIN2].LED_State,        
       
                                pins[3].PORT = seg->segment_pin_cfg[SEGMENT_PIN3].PORT, pins[3].PIN = seg->segment_pin_cfg[SEGMENT_PIN3].PIN, 
                                pins[3].DIRECTION = GPIO_DIRECTION_OUTPUT, pins[3].LOGIC = seg->segment_pin_cfg[SEGMENT_PIN3].LED_State,    
        };
        
        ret = gpio_pin_write_logic(&(pins[SEGMENT_PIN0]), ((number) & 0x01));
        ret = gpio_pin_write_logic(&(pins[SEGMENT_PIN1]), ((number >> 1) & 0x01));
        ret = gpio_pin_write_logic(&(pins[SEGMENT_PIN2]), ((number >> 2) & 0x01));
        ret = gpio_pin_write_logic(&(pins[SEGMENT_PIN3]), ((number >> 3) & 0x01));

    }
    return ret;   
}