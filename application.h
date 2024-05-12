/* 
 * File:   application.h
 * Author: Abdelrahman Aref
 *
 * Created on September 29, 2023, 1:50 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */
#include "ECU_Layer/LED/ecu_led.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/Timer0/hal_timer0.h"
#include "ECU_Layer/LM35/ecu_lm35_sensor.h"
#include "MCAL_Layer/Timer1/hal_timer1.h"
#include "MCAL_Layer/Timer2/hal_timer2.h"
#include "MCAL_Layer/CCP/hal_ccp.h"
#include "MCAL_Layer/I2C/hal_i2c.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */
void application_intialize(void);

#endif	/* APPLICATION_H */

