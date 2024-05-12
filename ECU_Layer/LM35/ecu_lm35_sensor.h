/* 
 * File:   ecu_lm35_sensor.h
 * Author: Abdelrahman Aref
 *
 * Created on April 25, 2024, 9:02 PM
 */

#ifndef ECU_LM35_SENSOR_H
#define	ECU_LM35_SENSOR_H

/* Section : Includes */
#include "ecu_lm35_sensor_cfg.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/**
 * @struct LM35_Sensor_t
 * @brief Structure to hold LM35 sensor data
 */
typedef struct 
{
    float temperature;              // Variable to store temperature reading
    adc_channel_select_t channel;   // ADC channel connected to the LM35 sensor
    adc_conf_t adc_config;          // ADC configuration 
} LM35_Sensor_t;

/* Section: Function Declarations */

/**
 * @brief Initializes the LM35 sensor and associated ADC if not already initialized.
 * @param sensor Pointer to the LM35 sensor structure.
 * @return Status of the function:
 *         - E_OK: Success
 *         - E_NOT_OK: Failure
 */
Std_ReturnType LM35_Init(LM35_Sensor_t *sensor);


/**
 * @brief Gets the latest temperature reading from the LM35 sensor in Celsius.
 * @param sensor Pointer to the LM35 sensor structure.
 * @return Status of the function:
 *         - E_OK: Success
 *         - E_NOT_OK: Failure
 */
Std_ReturnType LM35_GetTemperatureCelsius(LM35_Sensor_t *sensor);

/**
 * @brief Gets the latest temperature reading from the LM35 sensor in Fahrenheit.
 * @param sensor Pointer to the LM35 sensor structure.
 * @return Status of the function:
 *         - E_OK: Success
 *         - E_NOT_OK: Failure
 */
Std_ReturnType LM35_GetTemperatureFahrenheit(LM35_Sensor_t *sensor);

#endif	/* ECU_LM35_SENSOR_H */

