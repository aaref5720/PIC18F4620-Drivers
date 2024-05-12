/* 
 * File:   hal_timer2.h
 * Author: Abdelrahman Aref
 *
 * Created on April 29, 2024, 4:47 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* ----------------- Includes -----------------*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/
/* Timer2 Input Clock Post-scaler */
#define TIMER2_POSTSCALER_DIV_BY_1       0
#define TIMER2_POSTSCALER_DIV_BY_2       1
#define TIMER2_POSTSCALER_DIV_BY_3       2
#define TIMER2_POSTSCALER_DIV_BY_4       3
#define TIMER2_POSTSCALER_DIV_BY_5       4
#define TIMER2_POSTSCALER_DIV_BY_6       5
#define TIMER2_POSTSCALER_DIV_BY_7       6
#define TIMER2_POSTSCALER_DIV_BY_8       7
#define TIMER2_POSTSCALER_DIV_BY_9       8
#define TIMER2_POSTSCALER_DIV_BY_10      9
#define TIMER2_POSTSCALER_DIV_BY_11      10
#define TIMER2_POSTSCALER_DIV_BY_12      11
#define TIMER2_POSTSCALER_DIV_BY_13      12
#define TIMER2_POSTSCALER_DIV_BY_14      13
#define TIMER2_POSTSCALER_DIV_BY_15      14
#define TIMER2_POSTSCALER_DIV_BY_16      15

/* Timer2 Input Clock Pre-scaler */
#define TIMER2_PRESCALER_DIV_BY_1        0
#define TIMER2_PRESCALER_DIV_BY_4        1
#define TIMER2_PRESCALER_DIV_BY_16       2

/* ----------------- Macro Functions Declarations -----------------*/
/* Enable or Disable Timer1 Module */
#define TIMER2_MODULE_ENABLE()              (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()             (T2CONbits.TMR2ON = 0)

/* Timer2 Input Clock Post-scaler */
#define TIMER2_PRESCALER_SELECT(_PRESCALER_) (T2CONbits.T2CKPS = _PRESCALER_)

/* Timer2 Input Clock Post-scaler */
#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_) (T2CONbits.TOUTPS = _POSTSCALER_)

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TMR2_InterruptHandler)(void);
    
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    interrupt_priority_cfg priority;
    #endif
#endif
    uint8 timer2_preload_value;
    uint8 timer2_postscaler_value;
    uint8 timer2_prescaler_value;
}timer2_t;

/* ----------------- Software Interfaces Declarations -----------------*/


/**
 * @Summary Initializes Timer2
 * @Description This routine initializes Timer2 with the provided configurations.
 *              This routine must be called before any other Timer2 routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param _timer Pointer to the Timer2 configurations
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer2_Init(const timer2_t *_timer);

/**
 * @Summary De-initializes Timer2
 * @Description This routine de-initializes Timer2 and returns it to its default state.
 *              This routine should be called when Timer2 is no longer needed.
 * @Preconditions Timer2 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer2 configurations
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);

/**
 * @Summary Writes a value to Timer2
 * @Description This routine writes the provided value to Timer2.
 * @Preconditions Timer2 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer2 configurations
 * @param _value Value to be written to Timer2
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value);

/**
 * @Summary Reads the current value of Timer2
 * @Description This routine reads the current value of Timer2 and stores it in the provided variable.
 * @Preconditions Timer2 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer2 configurations
 * @param _value Pointer to store the read value of Timer2
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value);


#endif	/* HAL_TIMER2_H */

