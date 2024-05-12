/* 
 * File:   ecu_seven_segment.h
 * Author: Abdelrahman Aref
 *
 * Created on October 6, 2023, 2:13 PM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/* Section : Includes */
#include"ecu_seven_segment_cfg.h"
#include"../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */
#define SEGMENT_PIN0    0
#define SEGMENT_PIN1    1
#define SEGMENT_PIN2    2
#define SEGMENT_PIN3    3

#define LED_OFF         0
#define LED_ON          1

/* Section: Macro Functions Declarations */


/* Section: Data Type Declarations */
typedef enum
{
  SEGMENT_COMMON_ANODE = 0,
  SEGMENT_COMMON_CATHODE 
}segment_type_t;

typedef struct
{
    uint8 PORT  : 3;
    uint8 PIN   : 3;
    uint8 LED_State : 1 ;
}segment_pin_t;

typedef struct
{
    segment_pin_t segment_pin_cfg[4];
    segment_type_t segment_type;
}segment_t;

/* Section: Function Declarations */

/**
 * This Interface to make the needed GPIO and segment initialization
 * @param seg pointer to the segment configurations 
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segment_intialize(const segment_t *seg);

/**
 * Write a number to the segment 0 ~ 9
 * @param seg pointer to the segment configurations 
 * @param number the needed number to show
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number);

#endif	/* ECU_SEVEN_SEGMENT_H */

