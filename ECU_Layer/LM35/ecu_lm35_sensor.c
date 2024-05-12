/* 
 * File:   ecu_lm35_sensor.c
 * Author: Abdelrahman Aref
 *
 * Created on April 25, 2024, 9:02 PM
 */

#include"ecu_lm35_sensor.h"

/**
 * @brief Initializes the LM35 sensor and associated ADC.
 * @param sensor Pointer to the LM35 sensor structure.
 * @return Status of the function:
 *         - E_OK: Success
 *         - E_NOT_OK: Failure
 */
Std_ReturnType LM35_Init(LM35_Sensor_t *sensor)
{

    Std_ReturnType ret = E_NOT_OK;
    
    if (NULL == sensor) 
    {
        return E_NOT_OK; // ADC initialization failed
    }
    else
    {
        // Initialize the ADC with the provided configuration
        ret = ADC_Init(&(sensor->adc_config));
        
        // Initialize the temperature variable to 0
        sensor->temperature = 0.0; 
        
        ret =  E_OK;
    }
    
    return ret;
}

/**
 * @brief Gets the latest temperature reading from the LM35 sensor in Celsius.
 * @param sensor Pointer to the LM35 sensor structure.
 * @return Status of the function:
 *         - E_OK: Success
 *         - E_NOT_OK: Failure
 */
Std_ReturnType LM35_GetTemperatureCelsius(LM35_Sensor_t *sensor)
{

    Std_ReturnType ret = E_NOT_OK;
    
    if (NULL == sensor) 
    {
        return E_NOT_OK; // ADC initialization failed
    }
    else
    {
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        Std_ReturnType ret = ADC_StartConversion_Interrupt(&(sensor->adc_config), sensor->channel);
        
#else
        // If interrupt feature is not enabled, use blocking ADC conversion
        adc_result_t conversion_result;
        Std_ReturnType ret = ADC_GetConversion_Blocking(&(sensor->adc_config), sensor->channel, &conversion_result);
        
        sensor->temperature = (conversion_result * 4.88f);
        sensor->temperature /= 10;
#endif
        
        ret =  E_OK;
    }
    
    return ret;
}

/**
 * @brief Gets the latest temperature reading from the LM35 sensor in Fahrenheit.
 * @param sensor Pointer to the LM35 sensor structure.
 * @return Status of the function:
 *         - E_OK: Success
 *         - E_NOT_OK: Failure
 */
Std_ReturnType LM35_GetTemperatureFahrenheit(LM35_Sensor_t *sensor)
{

    Std_ReturnType ret = E_NOT_OK;
    
    if (NULL == sensor) 
    {
        return E_NOT_OK; // ADC initialization failed
    }
    else
    {
        ret = LM35_GetTemperatureCelsius(sensor);
        
        sensor->temperature = (sensor->temperature * 9.0 / 5.0) + 32;
        
        ret =  E_OK;
    }
    
    return ret; 
}