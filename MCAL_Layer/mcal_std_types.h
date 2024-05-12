/* 
 * File:   mcal_std_types.h
 * Author: Abdelrahman Aref
 *
 * Created on September 29, 2023, 1:35 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : Includes */
#include"mcal_std_libraries.h"
#include"compiler.h"

/* Section: Macro Functions Declarations */


/* Section: Data Type Declarations */
typedef unsigned char    uint8; 
typedef unsigned short   uint16; 
typedef unsigned long    uint32; 

typedef unsigned char    sint8; 
typedef unsigned short   sint16; 
typedef signed long      sint32;

typedef uint8            Std_ReturnType;

/* Section: Macro Declarations */
#define STD_HIGH                0x01u
#define STD_LOW                 0x00u

#define STD_ACTIVE              0x01u
#define STD_IDLE                0x00u

#define STD_ON                  0x01u
#define STD_OFF                 0x00u

#define E_OK            (Std_ReturnType)0x00u
#define E_NOT_OK        (Std_ReturnType)0x01u

#define ZERO_INIT       0

/* Section: Function Declarations */

#endif	/* MCAL_STD_TYPES_H */

