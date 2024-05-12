/* 
 * File:   hal_usart.h
 * Author: Abdelrahman Aref
 *
 * Created on May 6, 2024, 3:44 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* ----------------- Includes -----------------*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "hal_usart_cfg.h"
#include <string.h>

/* ----------------- Macro Declarations -----------------*/

/* Enable / Disable EUSART Module */
#define EUSART_MODULE_ENABLE   1
#define EUSART_MODULE_DISABLE  0

/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE  		1
#define EUSART_ASYNCHRONOUS_MODE 		0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  	0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN  		1
#define EUSART_08BIT_BAUDRATE_GEN  		0

/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE  0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE  0

/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0
/* EUSART Receiver Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE  0
/* EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE  0
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;

typedef struct{
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    interrupt_priority_cfg usart_tx_int_priority;
#endif
	uint8 usart_tx_enable : 1;
	uint8 usart_tx_interrupt_enable : 1;
	uint8 usart_tx_9bit_enable : 1;
    uint8 usart_tx_reserved : 5;
}usart_tx_cfg_t;

typedef struct{
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    interrupt_priority_cfg usart_rx_int_priority;
#endif
	uint8 usart_rx_enable : 1;
	uint8 usart_rx_interrupt_enable : 1;
	uint8 usart_rx_9bit_enable : 1;
    uint8 usart_rx_reserved : 5;
}usart_rx_cfg_t;

typedef union{
	struct{
		uint8 usart_tx_reserved : 6;
		uint8 usart_ferr : 1;
		uint8 usart_oerr : 1;
	};
	uint8 status;
}usart_error_status_t;

typedef struct{
    uint32 baudrate;
    baudrate_gen_t baudrate_gen_gonfig;
    usart_tx_cfg_t usart_tx_cfg;
	usart_rx_cfg_t usart_rx_cfg;
	usart_error_status_t error_status;
	void (*EUSART_TxDefaultInterruptHandler)(void);
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
}usart_t;

/* ----------------- Software Interfaces Declarations -----------------*/
/**
 * @Summary Initializes the EUSART asynchronous mode.
 * @Description This function initializes the EUSART module for asynchronous communication.
 * @Preconditions None
 * @param _eusart Pointer to the EUSART configurations
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart);

/**
 * @Summary Deinitializes the EUSART asynchronous mode.
 * @Description This function deinitializes the EUSART module previously initialized for asynchronous communication.
 * @Preconditions EUSART_ASYNC_Init() function should have been called before calling this function.
 * @param _eusart Pointer to the EUSART configurations
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart);



/**
 * @Summary Reads a byte from the EUSART asynchronously in a blocking manner.
 * @Description This function reads a byte from the EUSART buffer in a blocking mode.
 * @Preconditions EUSART_ASYNC_Init() function should have been called before calling this function.
 * @param _data Pointer to store the received byte
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *_data);

/**
 * @Summary Reads a byte from the EUSART asynchronously in a non-blocking manner.
 * @Description This function attempts to read a byte from the EUSART buffer in a non-blocking mode.
 * @Preconditions EUSART_ASYNC_Init() function should have been called before calling this function.
 * @param _data Pointer to store the received byte
 * @return Status of the function
 *          (E_OK) : A byte was successfully read
 *          (E_NOT_OK) : No byte was available for reading
 */
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data);

/**
 * @Summary Restarts the RX operation of the EUSART asynchronously.
 * @Description This function restarts the RX operation of the EUSART module.
 * @Preconditions EUSART_ASYNC_Init() function should have been called before calling this function.
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType EUSART_ASYNC_RX_Restart(void);



/**
 * @Summary Writes a byte to the EUSART asynchronously in a blocking manner.
 * @Description This function writes a byte to the EUSART buffer in a blocking mode.
 * @Preconditions EUSART_ASYNC_Init() function should have been called before calling this function.
 * @param _data The byte to be transmitted
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint8 _data);

/**
 * @Summary Writes a string to the EUSART asynchronously in a blocking manner.
 * @Description This function writes a string to the EUSART buffer in a blocking mode.
 * @Preconditions EUSART_ASYNC_Init() function should have been called before calling this function.
 * @param _data Pointer to the string to be transmitted
 * @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue during execution
 */
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8 *_data);

/**
 * @Summary Writes a byte to the EUSART asynchronously in a non-blocking manner.
 * @Description This function attempts to write a byte to the EUSART buffer in a non-blocking mode.
 * @Preconditions EUSART_ASYNC_Init() function should have been called before calling this function.
 * @param _data The byte to be transmitted
 * @return Status of the function
 *          (E_OK) : The byte was successfully queued for transmission
 *          (E_NOT_OK) : The byte could not be queued for transmission
 */
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8 _data);

/**
 * @Summary Writes a string to the EUSART asynchronously in a non-blocking manner.
 * @Description This function attempts to write a string to the EUSART buffer in a non-blocking mode.
 * @Preconditions EUSART_ASYNC_Init() function should have been called before calling this function.
 * @param _data Pointer to the string to be transmitted
 * @param str_len Length of the string to be transmitted
 * @return Status of the function
 *          (E_OK) : The string was successfully queued for transmission
 *          (E_NOT_OK) : The string could not be queued for transmission
 */
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data);


#endif	/* HAL_USART_H */

