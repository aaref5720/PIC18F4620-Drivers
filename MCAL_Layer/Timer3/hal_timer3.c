/* 
 * File:   hal_timer3.c
 * Author: Abdelrahman Aref
 *
 * Created on April 29, 2024, 5:33 PM
 */

#include "hal_timer3.h"

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*TMR3_InterruptHandler)(void) = NULL;
#endif

static uint16 timer3_preload = ZERO_INIT;
static inline void Timer3_Mode_Select(const timer3_t *_timer);
    
 /**
 * @Summary Initializes Timer3
 * @Description This routine initializes Timer3 with the provided configurations.
 *              This routine must be called before any other Timer3 routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param _timer Pointer to the Timer3 configurations
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer3_Init(const timer3_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER3_MODULE_DISABLE();
        TIMER3_PRESCALER_SELECT(_timer->timer3_prescaler_value);
        Timer3_Mode_Select(_timer);
        TMR3H = (_timer->timer3_preload_value) >> 8;
        TMR3L = (uint8)(_timer->timer3_preload_value);
        timer3_preload = _timer->timer3_preload_value;
/* Interrupt Configurations */        
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        TMR3_InterruptHandler = _timer->TMR3_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
        {
            /* Enables all high-priority interrupts */
            /*INTERRUPT_GlobalInterruptHighEnable();
            TIMER3_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority)
        {
            /* Enables all unmasked peripheral interrupts */
            /*INTERRUPT_GlobalInterruptLowEnable();
            TIMER3_LowPrioritySet();
        }
        else{ /* Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif      
#endif
        TIMER3_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary De-initializes Timer3
 * @Description This routine de-initializes Timer3 and returns it to its default state.
 *              This routine should be called when Timer3 is no longer needed.
 * @Preconditions Timer3 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer3 configurations
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer3_DeInit(const timer3_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER3_MODULE_DISABLE();
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary Writes a value to Timer3
 * @Description This routine writes the provided value to Timer3.
 * @Preconditions Timer3 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer3 configurations
 * @param _value Value to be written to Timer3
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _value)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR3H = (_value) >> 8;
        TMR3L = (uint8)(_value);
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary Reads the current value of Timer3
 * @Description This routine reads the current value of Timer3 and stores it in the provided variable.
 * @Preconditions Timer3 must be initialized before calling this routine.
 * @param _timer Pointer to the Timer3 configurations
 * @param _value Pointer to store the read value of Timer3
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_value)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_tmr3l = ZERO_INIT, l_tmr3h = ZERO_INIT;
    
    if((NULL == _timer) || (NULL == _value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        *_value = (uint16)((l_tmr3h << 8) + l_tmr3l);
        ret = E_OK;
    }
    return ret;
}

static inline void Timer3_Mode_Select(const timer3_t *_timer)
{
    if(TIMER3_TIMER_MODE == _timer->timer3_mode)
    {
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(TIMER3_COUNTER_MODE == _timer->timer3_mode)
    {
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_ASYNC_COUNTER_MODE == _timer->timer3_counter_mode)
        {
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_SYNC_COUNTER_MODE == _timer->timer3_counter_mode)
        {
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}
   

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void TMR3_ISR(void)
{
    TIMER3_InterruptFlagClear();
    
    TMR3H = (timer3_preload) >> 8;
    TMR3L = (uint8)(timer3_preload);
    
    if(TMR3_InterruptHandler)
    {
        TMR3_InterruptHandler();
    } 
}
#endif
