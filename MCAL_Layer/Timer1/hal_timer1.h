/* 
 * File:   hal_timer1.h
 * Author: Abdelrahman Aref
 *
 * Created on April 29, 2024, 11:22 AM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* ----------------- Includes -----------------*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/

/* Timer1 Clock Source (Timer or Counter) */
#define TIMER1_COUNTER_MODE            1
#define TIMER1_TIMER_MODE              0
/* Timer1 External Clock Input Synchronization */
#define TIMER1_ASYNC_COUNTER_MODE      1
#define TIMER1_SYNC_COUNTER_MODE       0
/* Timer1 Oscillator */
#define TIMER1_OSCILLATOR_ENABLE       1
#define TIMER1_OSCILLATOR_DISABLE      0
/* Timer1 Input Clock Pre-scaler */
#define TIMER1_PRESCALER_DIV_BY_1      0
#define TIMER1_PRESCALER_DIV_BY_2      1
#define TIMER1_PRESCALER_DIV_BY_4      2
#define TIMER1_PRESCALER_DIV_BY_8      3
/* 16-Bit Read/Write Mode */
#define TIMER1_RW_REG_8Bit_MODE        0
#define TIMER1_RW_REG_16Bit_MODE       1

/* ----------------- Macro Functions Declarations -----------------*/

/* Enable or Disable Timer1 Module */
#define TIMER1_MODULE_ENABLE()              (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()             (T1CONbits.TMR1ON = 0)
/*  Timer1 Clock Source (Timer or Counter) */
#define TIMER1_TIMER_MODE_ENABLE()          (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()        (T1CONbits.TMR1CS = 1)
/*  Timer1 External Clock Input Synchronization */
#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()  (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()   (T1CONbits.T1SYNC = 0)
/* Timer1 Oscillator */
#define TIMER1_OSC_HW_ENABLE()              (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE()             (T1CONbits.T1OSCEN = 0)
/* Timer1 Input Clock Pre-scaler */
#define TIMER1_PRESCALER_SELECT(_PRESCALER_) (T1CONbits.T1CKPS = _PRESCALER_)
/* Timer1 System Clock Status */
#define TIMER1_SYSTEM_CLK_STATUS()          (T1CONbits.T1RUN)
/* 16-Bit Read/Write Mode */
#define TIMER1_RW_REG_8BIT_MODE_ENABLE()    (T1CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BIT_MODE_ENABLE()   (T1CONbits.RD16 = 1)

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TMR1_InterruptHandler)(void);
    
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    interrupt_priority_cfg priority;
    #endif

#endif
    uint16 timer1_preload_value;        /* Preload value configuration */
    uint8 timer1_prescaler_value : 2;   /* Prescale value configuration */
    uint8 timer1_mode : 1;              /* Timer Mode / Counter Mode */
    uint8 timer1_counter_mode : 1;      /* Synchronous or ASynchronous Counter */
    uint8 timer1_osc_cfg : 1;           /* Timer1 Oscillator or Another source*/
    uint8 timer1_reg_wr_mode : 1;       /* One 16-bit operation or Two 8-bit operations */
    uint8 timer1_reserved : 2;
}timer1_t;

/* ----------------- Software Interfaces Declarations -----------------*/


/**
 * @Summary Initializes Timer1
 * @Description This routine initializes Timer1 with the provided configurations.
 *              This routine must be called before any other Timer1 routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param _timer Pointer to the Timer1 configurations
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer1_Init(const timer1_t *_timer);

/**
 * @Summary De-initializes Timer1
 * @Description This routine de-initializes Timer1 and returns it to its default state.
 *              This routine should be called when Timer1 is no longer needed.
 * @Preconditions Timer1 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer1 configurations
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer1_DeInit(const timer1_t *_timer);

/**
 * @Summary Writes a value to Timer1
 * @Description This routine writes the provided value to Timer1.
 * @Preconditions Timer1 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer1 configurations
 * @param _value Value to be written to Timer1
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value);

/**
 * @Summary Reads the current value of Timer1
 * @Description This routine reads the current value of Timer1 and stores it in the provided variable.
 * @Preconditions Timer1 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer1 configurations
 * @param _value Pointer to store the read value of Timer1
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_value);


#endif	/* HAL_TIMER1_H */

