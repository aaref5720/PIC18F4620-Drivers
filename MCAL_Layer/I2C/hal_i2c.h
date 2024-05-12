/* 
 * File:   hal_i2c.h
 * Author: Abdelrahman Aref
 *
 * Created on May 12, 2024, 12:19 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/* ----------------- Includes -----------------*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/
/* Slew Rate Enable/Disable */
#define I2C_SLEW_RATE_DISABLE 1
#define I2C_SLEW_RATE_ENABLE  0
/* SMBus Enable/Disable */
#define I2C_SMBus_ENABLE      1
#define I2C_SMBus_DISABLE     0
/* Slave Mode Data/Address Indication */
#define I2C_LAST_RT_BYTE_DATA	  1
#define I2C_LAST_RT_BYTE_ADDRESS  0
/* Stop Condition Indication */
#define I2C_STOP_BIT_DETECTED     1
#define I2C_STOP_BIT_NOT_DETECTED 0
/* Start Condition Indication */
#define I2C_START_BIT_DETECTED     1
#define I2C_START_BIT_NOT_DETECTED 0
/* I2C : Master or Slave Mode */
#define I2C_MSSP_MASTER_MODE 1
#define I2C_MSSP_SLAVE_MODE  0
/* Master Synchronous Serial Port Mode Select */
#define I2C_SLAVE_MODE_7BIT_ADDRESS					0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS				0x07U
#define I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE	0x0EU
#define I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE	0x0FU
#define I2C_MASTER_MODE_DEFINED_CLOCK				0x08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED			0x0BU
/* General Call Enable */
#define I2C_GENERAL_CALL_ENABLE   1
#define I2C_GENERAL_CALL_DISABLE  0
/* Master Mode Receive Enable */
#define I2C_MASTER_RECEIVE_ENABLE   1
#define I2C_MASTER_RECEIVE_DISABLE  0
/* Acknowledge Status bit (Master Transmit mode only) */
#define I2C_ACK_RECEIVED_FROM_SLAVE     0
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE 1
/* Acknowledge Data bit (Master Receive mode only) */
#define I2C_MASTER_SEND_ACK  0
#define I2C_MASTER_SEND_NACK 1

/* ----------------- Macro Functions Declarations -----------------*/
/* Slew Rate Enable/Disable */
#define I2C_SLEW_RATE_DISABLE_CFG()         (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_ENABLE_CFG()          (SSPSTATbits.SMP = 0)
/* SMBus Enable/Disable */
#define I2C_SMBus_DISABLE_CFG()             (SSPSTATbits.CKE = 0)
#define I2C_SMBus_ENABLE_CFG()              (SSPSTATbits.CKE = 1)
/* General Call Enable */
#define I2C_GENERAL_CALL_DISABLE_CFG()      (SSPCON2bits.GCEN = 0)
#define I2C_GENERAL_CALL_ENABLE_CFG()       (SSPCON2bits.GCEN = 1)
/* Master Mode Receive Enable */
#define I2C_MASTER_RECEIVE_DISABLE_CFG()    (SSPCON2bits.RCEN = 0)
#define I2C_MASTER_RECEIVE_ENABLE_CFG()     (SSPCON2bits.RCEN = 1)
/* Master Synchronous Serial Port Enable */
#define MSSP_MODULE_ENABLE_CFG()            (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE_CFG()           (SSPCON1bits.SSPEN = 0)
/* Clock Stretch */
#define I2C_CLOCK_STRETCH_ENABLE()          (SSPCON1bits.CKP = 0)
#define I2C_CLOCK_STRETCH_DISABLE()         (SSPCON1bits.CKP = 1)

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
	uint8 i2c_mode_cfg;             /* Master Synchronous Serial Port Mode Select */
    uint8 i2c_slave_address;        /* I2C Slave Address */
	uint8 i2c_mode : 1;				/* I2C : Master or Slave Mode */
	uint8 i2c_slew_rate : 1; 		/* Slew Rate Enable/Disable */
	uint8 i2c_SMBus_control : 1; 	/* SMBus Enable/Disable */
	uint8 i2c_general_call : 1;		/* General Call Enable/Disable */
	uint8 i2c_master_rec_mode : 1; 	/* Master Receive Mode Enable/Disable */
	uint8 i2c_reserved : 3; 
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    interrupt_priority_cfg mssp_i2c_priority;
    interrupt_priority_cfg mssp_i2c_bc_priority;
    #endif
#endif   
}i2c_configs_t;

typedef struct{
	uint32 i2c_clock;	/* Master Clock Frequency */
    i2c_configs_t i2c_cfg; /* I2C Configurations */
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*I2C_Report_Write_Collision)(void);	/* Write Collision Indicator */
    void (*I2C_DefaultInterruptHandler)(void); 	/* Default Interrupt Handler */
    void (*I2C_Report_Receive_Overflow)(void); 	/* Receive Overflow Indicator */
#endif    
}mssp_i2c_t;

/* ----------------- Software Interfaces Declarations -----------------*/
/**
 * @Summary Initializes the MSSP I2C module.
 * @Description This function initializes the MSSP I2C module with the provided configuration.
 * @Preconditions None
 * @param i2c_obj Pointer to the MSSP I2C configuration structure
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj);

/**
 * @Summary Deinitializes the MSSP I2C module.
 * @Description This function deinitializes the MSSP I2C module.
 * @Preconditions MSSP_I2C_Init() function should have been called before calling this function.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj);


/**
 * @Summary Sends a start condition in master mode via MSSP I2C.
 * @Description This function sends a start condition in master mode via MSSP I2C.
 * @Preconditions MSSP_I2C_Init() function should have been called before calling this function.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj);

/**
 * @Summary Sends a repeated start condition in master mode via MSSP I2C.
 * @Description This function sends a repeated start condition in master mode via MSSP I2C.
 * @Preconditions MSSP_I2C_Init() function should have been called before calling this function.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj);

/**
 * @Summary Sends a stop condition in master mode via MSSP I2C.
 * @Description This function sends a stop condition in master mode via MSSP I2C.
 * @Preconditions MSSP_I2C_Init() function should have been called before calling this function.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj);


/**
 * @Summary Writes a byte in master mode via MSSP I2C in a blocking manner.
 * @Description This function writes a byte in master mode via MSSP I2C in a blocking manner.
 * @Preconditions MSSP_I2C_Init() function should have been called before calling this function.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure
 * @param i2c_data The byte to be transmitted
 * @param _ack Pointer to store the acknowledgment status
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack);

/**
 * @Summary Reads a byte in master mode via MSSP I2C in a blocking manner.
 * @Description This function reads a byte in master mode via MSSP I2C in a blocking manner.
 * @Preconditions MSSP_I2C_Init() function should have been called before calling this function.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure
 * @param ack Acknowledgment to be sent after receiving the byte
 * @param i2c_data Pointer to store the received byte
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data);


/**
 * @Summary Writes a byte in master mode via MSSP I2C in a non-blocking manner.
 * @Description This function attempts to write a byte in master mode via MSSP I2C in a non-blocking mode.
 * @Preconditions MSSP_I2C_Init() function should have been called before calling this function.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure
 * @param i2c_data The byte to be transmitted
 * @param _ack Pointer to store the acknowledgment status
 * @return Status of the function
 *          (E_OK) : The byte was successfully queued for transmission
 *          (E_NOT_OK) : The byte could not be queued for transmission
 */
Std_ReturnType MSSP_I2C_Master_Write_NBlocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack);

/**
 * @Summary Reads a byte in master mode via MSSP I2C in a non-blocking manner.
 * @Description This function attempts to read a byte in master mode via MSSP I2C in a non-blocking mode.
 * @Preconditions MSSP_I2C_Init() function should have been called before calling this function.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure
 * @param ack Acknowledgment to be sent after receiving the byte
 * @param i2c_data Pointer to store the received byte
 * @return Status of the function
 *          (E_OK) : A byte was successfully read
 *          (E_NOT_OK) : No byte was available for reading
 */
Std_ReturnType MSSP_I2C_Master_Read_NBlocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data);


#endif	/* HAL_I2C_H */

