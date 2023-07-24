/* 
 * File:   mcal_std_types.h
 * Author: ADHAM KHALED
 *
 * Created on July 21, 2023, 4:10 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H
/* ----------------Includes----------------*/
#include "std_libraries.h"
#include "compiler.h"
/* ----------------Macro Functions Declarations----------------*/
/* ----------------Data Type Declarations----------------*/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef uint8 Std_ReturnType; 

/* ----------------Macro Declarations---------------*/
#define STD_HIGH    0x01
#define STD_LOW     0x00

#define STD_ON      0x01
#define STD_OFF     0x00

#define STD_ACTIVE  0x01
#define STD_IDLE    0x00

#define E_OK        ((Std_ReturnType)0x01)
#define E_NOT_OK       ((Std_ReturnType)0x00)
/* ----------------Functions Declarations----------------*/

#endif	/* MCAL_STD_TYPES_H */

