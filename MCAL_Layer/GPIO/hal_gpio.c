/* 
 * File:   hal_gpio.c
 * Author: Abdelrahman Aref
 *
 * Created on September 29, 2023, 1:31 PM
 */

#include "hal_gpio.h"

/* Reference to the Data Direction Control Registers */
volatile uint8 *TRIS_REGESTERS[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/* Reference to the Port Status Register  */
volatile uint8 *PORT_REGESTERS[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};
/* Reference to the Data Latch Register (Read and Write to Data Latch) */
volatile uint8 *LAT_REGESTERS[]  = {&LATA, &LATB, &LATC, &LATD, &LATE};

/**
 * Initialize the GPIO pin direction.
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has an issue performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *pin_config)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->PORT > (PORT_MAX_NUMBER - 1)|| pin_config->PIN > (PIN_MAX_NUMBER - 1))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        switch(pin_config->DIRECTION)
        {
            case GPIO_DIRECTION_OUTPUT : 
                CLEAR_BIT(*(TRIS_REGESTERS[pin_config->PORT]) , pin_config->PIN);
                break;
                
            case GPIO_DIRECTION_INPUT : 
                SET_BIT(*(TRIS_REGESTERS[pin_config->PORT]) , pin_config->PIN);
                break;
                
            default :
                ret = E_NOT_OK ; 
                break;
        }
    }
    
    return ret;
}
#endif

/**
 * Get the GPIO pin direction status.
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @param direction_status pointer to store the direction status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has an issue performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config, direction_t *direction_status)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->PORT > (PORT_MAX_NUMBER - 1)|| pin_config->PIN > (PIN_MAX_NUMBER - 1) || NULL == direction_status)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        *direction_status = READ_BIT(*(TRIS_REGESTERS[pin_config->PORT]) , pin_config->PIN);
    }
    
    return ret;
}
#endif

/**
 * Write logic to the GPIO pin.
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @param pin_logic logic value to write
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has an issue performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t pin_logic)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->PORT > (PORT_MAX_NUMBER - 1)|| pin_config->PIN > (PIN_MAX_NUMBER - 1))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        switch(pin_logic)
        {
            case GPIO_LOW : 
                CLEAR_BIT(*(LAT_REGESTERS[pin_config->PORT]) , pin_config->PIN);
                break;
                
            case GPIO_HIGH : 
                SET_BIT(*(LAT_REGESTERS[pin_config->PORT]) , pin_config->PIN);
                break;
                
            default :
                ret = E_NOT_OK ; 
                break;
        }
    }
    
    return ret;
}
#endif

/**
 * Read logic from the GPIO pin.
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @param pin_logic pointer to store the read logic value
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has an issue performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config, logic_t *pin_logic)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->PORT > (PORT_MAX_NUMBER - 1)|| pin_config->PIN > (PIN_MAX_NUMBER - 1) || NULL == pin_logic)
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        *pin_logic = READ_BIT(*PORT_REGESTERS[pin_config->PORT] , pin_config->PIN);
    }
    
    return ret;
}
#endif

/**
 * Toggle the logic on the GPIO pin.
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has an issue performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->PORT > (PORT_MAX_NUMBER - 1)|| pin_config->PIN > (PIN_MAX_NUMBER - 1))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        TOGGLE_BIT(*(LAT_REGESTERS[pin_config->PORT]) , pin_config->PIN);
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_intialize(const pin_config_t *pin_config)
{
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->PORT > (PORT_MAX_NUMBER - 1)|| pin_config->PIN > (PIN_MAX_NUMBER - 1))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        ret = gpio_pin_direction_intialize(pin_config);
        ret = gpio_pin_write_logic(pin_config, pin_config->LOGIC);
    }
    
    return ret;  
}
#endif

/**
 * Initialize the GPIO port direction.
 * 
 * @param port GPIO port index
 * @param direction desired direction for the port
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has an issue performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_intialize(PORT_INDEX_t PORT_INDEX, uint8 direction)
{
    Std_ReturnType ret = E_OK ;
    if(PORT_INDEX > (PORT_MAX_NUMBER - 1))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        *(TRIS_REGESTERS[PORT_INDEX]) = direction;
    }
    
    return ret;
}
#endif

/**
 * Get the GPIO port direction status.
 * 
 * @param port GPIO port index
 * @param direction_status pointer to store the direction status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has an issue performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(PORT_INDEX_t PORT_INDEX, uint8 *direction_status)
{
    Std_ReturnType ret = E_OK ;
    if(PORT_INDEX > (PORT_MAX_NUMBER - 1))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        *direction_status = *(TRIS_REGESTERS[PORT_INDEX]) ;
    }
    
    return ret;
}
#endif

/**
 * Write logic to the GPIO port.
 * 
 * @param port GPIO port index
 * @param pin_logic logic value to write to the port
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has an issue performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(PORT_INDEX_t PORT_INDEX, uint8 pin_logic)
{
    Std_ReturnType ret = E_OK ;
    if(PORT_INDEX > (PORT_MAX_NUMBER - 1))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        *(LAT_REGESTERS[PORT_INDEX]) = pin_logic;
 
    }
    
    return ret;
}
#endif

/**
 * Read logic from the GPIO port.
 * 
 * @param port GPIO port index
 * @param port_logic pointer to store the read logic value
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has an issue performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(PORT_INDEX_t PORT_INDEX, uint8 *port_logic)
{
    Std_ReturnType ret = E_OK ;
    if(PORT_INDEX > (PORT_MAX_NUMBER - 1))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        *port_logic = *(PORT_REGESTERS[PORT_INDEX]) ;
    }
    
    return ret;
}
#endif

/**
 * Toggle the logic on the GPIO port.
 * 
 * @param port GPIO port index
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has an issue performing this action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(PORT_INDEX_t PORT_INDEX)
{
    Std_ReturnType ret = E_OK ;
    if(PORT_INDEX > (PORT_MAX_NUMBER - 1))
    {
        ret = E_NOT_OK ; 
    }
    else
    {
        *(LAT_REGESTERS[PORT_INDEX]) ^=  PORT_MASK ;
    }
    
    return ret; 
}
#endif


