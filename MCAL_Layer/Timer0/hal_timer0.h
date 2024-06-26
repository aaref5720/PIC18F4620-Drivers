/* 
 * File:   hal_timer0.h
 * Author: Abdelrahman Aref
 *
 * Created on April 26, 2024, 6:10 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* ----------------- Includes -----------------*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/
#define TIMER0_TIMER_MODE                1
#define TIMER0_COUNTER_MODE              0
#define TIMER0_PRESCALER_ENABLE_CFG      1
#define TIMER0_PRESCALER_DISABLE_CFG     0
#define TIMER0_8BIT_REGISTER_MODE        1
#define TIMER0_16BIT_REGISTER_MODE       0
#define TIMER0_COUNTER_RISING_EDGE_CFG   1
#define TIMER0_COUNTER_FALLING_EDGE_CFG  0

/* ----------------- Macro Functions Declarations -----------------*/
#define TIMER0_PRESCALER_ENABLE()           (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()          (T0CONbits.PSA = 1)
#define TIMER0_RISING_EDGE_ENABLE()         (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE_ENABLE()        (T0CONbits.T0SE = 1)
#define TIMER0_TIMER_MODE_ENABLE()          (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()        (T0CONbits.T0CS = 1)
#define TIMER0_8BIT_REGISTER_MODE_ENABLE()  (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE() (T0CONbits.T08BIT = 0)
#define TIMER0_MODULE_ENABLE()              (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()             (T0CONbits.TMR0ON = 0)

/* ----------------- Data Type Declarations -----------------*/

/**
 * Timer0 Pre-Scaler Select 
 */
typedef enum{
    TIMER0_PRESCALER_DIV_BY_2= 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256
}timer0_prescaler_select_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    
    void (* TMR0_InterruptHandler)(void);
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    interrupt_priority_cfg priority;
    #endif
#endif
    timer0_prescaler_select_t prescaler_value;
    uint16 timer0_preload_value;
    uint8 prescaler_enable : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_mode : 1;
    uint8 timer0_register_size : 1;
    uint8 timer0_reserved : 4;
}timer0_t;

/* ----------------- Software Interfaces Declarations -----------------*/

/**
 * @Summary Initializes Timer0
 * @Description This routine initializes Timer0 with the provided configurations.
 *              This routine must be called before any other Timer0 routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param _timer Pointer to the Timer0 configurations
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer0_Init(const timer0_t *_timer);

/**
 * @Summary De-initializes Timer0
 * @Description This routine de-initializes Timer0 and returns it to its default state.
 *              This routine should be called when Timer0 is no longer needed.
 * @Preconditions Timer0 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer0 configurations
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer0_DeInit(const timer0_t *_timer);

/**
 * @Summary Writes a value to Timer0
 * @Description This routine writes the provided value to Timer0.
 * @Preconditions Timer0 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer0 configurations
 * @param _value Value to be written to Timer0
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 _value);

/**
 * @Summary Reads the current value of Timer0
 * @Description This routine reads the current value of Timer0 and stores it in the provided variable.
 * @Preconditions Timer0 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer0 configurations
 * @param _value Pointer to store the read value of Timer0
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *_value);


#endif	/* HAL_TIMR0_H */

