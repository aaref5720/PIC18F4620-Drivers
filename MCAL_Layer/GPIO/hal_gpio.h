/* 
 * File:   hal_gpio.h
 * Author: Abdelrahman Aref
 * 
 * Created on September 29, 2023, 1:31 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H




/* Section : Includes */

#include "../mcal_std_types.h"
#include "../device_config.h"
#include "pic18f4620.h"
#include "hal_gpio_cfg.h"


/* Section: Macro Declarations */
#define BIT_MASK                     (uint8)1
#define PIN_MAX_NUMBER               8
#define PORT_MAX_NUMBER              5
#define GPIO_PORT_PIN_CONFIGURATIONS CONFIG_ENABLE
#define PORT_MASK                    0xff


/* Section: Macro Functions Declarations */
#define HWREG8(_x)                        (*((volatile uint8 *) _x)) 

#define SET_BIT(REG, BIT_POSITION)        (REG |= (BIT_MASK << BIT_POSITION))
#define CLEAR_BIT(REG, BIT_POSITION)      (REG &= ~(BIT_MASK << BIT_POSITION))
#define TOGGLE_BIT(REG, BIT_POSITION)     (REG ^= (BIT_MASK << BIT_POSITION))
#define READ_BIT(REG, BIT_POSITION)       ((REG >> BIT_POSITION) & BIT_MASK) 

/* Section: Data Type Declarations */
typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum
{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}PIN_INDEX_t;

typedef enum
{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}PORT_INDEX_t;

typedef struct
{
    uint8 PORT       : 3;       /* @ref  PORT_INDEX_t */
    uint8 PIN        : 3;       /* @ref  PIN_INDEX_t */
    uint8 DIRECTION  : 1;       /* @ref  direction_t */
    uint8 LOGIC      : 1;       /* @ref  logic_t */
}pin_config_t;

/* Section: Function Declarations */
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config, direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t pin_logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config, logic_t *pin_logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t *pin_config);

Std_ReturnType gpio_port_direction_intialize(PORT_INDEX_t PORT_INDEX, uint8 direction);
Std_ReturnType gpio_port_get_direction_status(PORT_INDEX_t PORT_INDEX, uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(PORT_INDEX_t PORT_INDEX, uint8 pin_logic);
Std_ReturnType gpio_port_read_logic(PORT_INDEX_t PORT_INDEX, uint8 *port_logic);
Std_ReturnType gpio_port_toggle_logic(PORT_INDEX_t PORT_INDEX);



#endif	/* HAL_GPIO_H */

