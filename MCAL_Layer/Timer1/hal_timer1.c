/* 
 * File:   hal_timer1.c
 * Author: Abdelrahman Aref
 *
 * Created on April 29, 2024, 11:22 AM
 */

#include"hal_timer1.h"

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static volatile void (*TMR1_InterruptHandler)(void) = NULL;
#endif
    
static volatile uint16 timer1_preload = ZERO_INIT;
static inline void Timer1_Mode_Select(const timer1_t *_timer);



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
Std_ReturnType Timer1_Init(const timer1_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
        TIMER1_PRESCALER_SELECT(_timer->timer1_prescaler_value);
        Timer1_Mode_Select(_timer);
        TMR1H = (_timer->timer1_preload_value) >> 8;
        TMR1L = (uint8)(_timer->timer1_preload_value);
        timer1_preload = _timer->timer1_preload_value;
/* Interrupt Configurations */        
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear();
        TMR1_InterruptHandler = _timer->TMR1_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            /* Enables all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER1_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            /* Enables all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER1_LowPrioritySet();
        }
        else{ /* Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif      
#endif
        TIMER1_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;    
}

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
Std_ReturnType Timer1_DeInit(const timer1_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;   
}

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
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR1H = (_value) >> 8;
        TMR1L = (uint8)(_value);
        ret = E_OK;
    }
    return ret;    
}

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
Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_value)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_tmr1l = ZERO_INIT, l_tmr1h = ZERO_INIT;
    
    if((NULL == _timer) || (NULL == _value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr1l = TMR1L;
        l_tmr1h = TMR1H;
        *_value = (uint16)((l_tmr1h << 8) + l_tmr1l);
        ret = E_OK;
    }
    return ret;   
}


void TMR1_ISR(void)
{
    TIMER1_InterruptFlagClear();     /* Clear the interrupt flag */
    TMR1H = (timer1_preload) >> 8;   /* Initialize the pre-loaded value again */
    TMR1L = (uint8)(timer1_preload); /* Initialize the pre-loaded value again */
    if(TMR1_InterruptHandler)
    {
        TMR1_InterruptHandler();     /* Call the callback function */
    }
}


static inline void Timer1_Mode_Select(const timer1_t *_timer)
{
    if(TIMER1_TIMER_MODE == _timer->timer1_mode)
    {
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(TIMER1_COUNTER_MODE == _timer->timer1_mode)
    {
        TIMER1_COUNTER_MODE_ENABLE();
        if(TIMER1_ASYNC_COUNTER_MODE == _timer->timer1_counter_mode)
        {
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_SYNC_COUNTER_MODE == _timer->timer1_counter_mode)
        {
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}