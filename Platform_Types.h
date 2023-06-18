/*  
 *  This file is a part of micro SOME/IP project.
 *  
 *  Copyright (C) 2021-2023 DJS Studio E-mail: ddsilence@sina.cn
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
/****************************************************************************************************
 * @file    Filename:           Platform_Types.h
 * @date    Date:               2023-06-16
 * @version Version:            0.0.1
 * @brief   Description:        Header file of AUTOSAR platform common definition. 
 ***************************************************************************************************/
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************************************
 * INCLUDES
 ***************************************************************************************************/



/****************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 ***************************************************************************************************/
/**
 * @brief   [SWS_BSW_00059]
 *          Define Published information elements
 */
#define PLATFORM_VENDOR_ID                      (65535U)
#define PLATFORM_MODULE_ID                      (199U)

/* AUTOSAR Software Specification Document Version Information */
#define PLATFORM_AR_RELEASE_MAJOR_VERSION       (22U)
#define PLATFORM_AR_RELEASE_MINOR_VERSION       (11U)
#define PLATFORM_AR_RELEASE_REVISION_VERSION    (0U)

/* Component Version Information */
#define PLATFORM_SW_MAJOR_VERSION               (0U)
#define PLATFORM_SW_MINOR_VERSION               (1U)
#define PLATFORM_SW_PATCH_VERSION               (0U)

/**
 * @brief   [SWS_Platform_00064]
 * @enum    CPU_TYPE_8    Indicating a 8 bit processor
 * @enum    CPU_TYPE_16   Indicating a 16 bit processor
 * @enum    CPU_TYPE_32   Indicating a 32bit processor
 * @enum    CPU_TYPE_64   Indicating a 64bit processor
 */
#define CPU_TYPE_8                              (8U)
#define CPU_TYPE_16                             (16U)
#define CPU_TYPE_32                             (32U)
#define CPU_TYPE_64                             (64U)

/**
 * @brief   [SWS_Platform_00038]
 * @enum    MSB_FIRST   The most significant bit is the first bit of the bit
 *                      sequence.
 * @enum    LSB_FIRST   The least significant bit is the first bit of the bit
 *                      sequence.
 */
#define MSB_FIRST                               (0U)
#define LSB_FIRST                               (1U)

/**
 * @brief   [SWS_Platform_00039]
 * @enum    HIGH_BYTE_FIRST     Within uint16, the high byte is located before
 *                              the low byte.
 * @enum    LOW_BYTE_FIRST      Within uint16, the low byte is located before
 *                              the high byte.
 */
#define HIGH_BYTE_FIRST                         (0U)
#define LOW_BYTE_FIRST                          (1U)

#ifndef TRUE
#define TRUE                                    (1U)
#endif

#ifndef FALSE
#define FALSE                                   (0U)
#endif

/**
 * @brief   [SWS_Platform_00064]
 *          This symbol shall be defined as #define having one of the values CPU_TYPE_8, CPU_TYPE_16,
 *          CPU_TYPE_32 or CPU_TYPE_64 according to the platform.
 */
#define CPU_TYPE                                (CPU_TYPE_32)

/**
 * @brief   [SWS_Platform_00038]
 *          This symbol shall be defined as #define having one of the values MSB_FIRST or LSB_FIRST
 *          according to the platform.
 */
#define CPU_BIT_ORDER                           (LSB_FIRST)        /* little endian bit ordering */

/**
 * @brief   [SWS_Platform_00039]
 *          This symbol shall be defined as #define having one of the values HIGH_BYTE_FIRST or LOW_
 *          BYTE_FIRST according to the platform.
 */
#define CPU_BYTE_ORDER                          (LOW_BYTE_FIRST)   /* little endian byte ordering */

/****************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 ***************************************************************************************************/



/****************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 ***************************************************************************************************/
/**
 * @brief   [SWS_Platform_00026]
 *          This standard AUTOSAR type shall only be used together with the definitions TRUE and FALSE.
 *          Range: FALSE, TRUE
 */
typedef unsigned char boolean;

/**
 * @brief   [SWS_Platform_00016]
 *          This standard AUTOSAR type shall be of 8 bit signed.
 *          Range: -128 .. +127
 */
typedef signed char sint8;

/**
 * @brief   [SWS_Platform_00013]
 *          This standard AUTOSAR type shall be of 8 bit unsigned.
 *          Range: 0 .. 255
 */
typedef unsigned char uint8;

/**
 * @brief   [SWS_Platform_00017]
 *          This standard AUTOSAR type shall be of 16 bit signed.
 *          Range: -32768 .. +32767
 */
typedef signed short sint16;

/**
 * @brief   [SWS_Platform_00014]
 *          This standard AUTOSAR type shall be of 16 bit unsigned.
 *          Range: 0 .. 65535
 */
typedef unsigned short uint16;

/**
 * @brief   [SWS_Platform_00018]
 *          This standard AUTOSAR type shall be of 32 bit signed.
 *          Range: -2147483648 .. +2147483647
 */
typedef signed long sint32;

/**
 * @brief   [SWS_Platform_00015]
 *          This standard AUTOSAR type shall be of 32 bit unsigned.
 *          Range: 0 .. 4294967295
 */
typedef unsigned long uint32;

/**
 * @brief   [SWS_Platform_00067]
 *          This standard AUTOSAR type shall be of 64 bit signed.
 *          Range: -9223372036854775808 .. 9223372036854775807
 */
typedef signed long long sint64;

/**
 * @brief   [SWS_Platform_00066]
 *          This standard AUTOSAR type shall be 64 bit unsigned.
 *          Range: 0 .. 18446744073709551615
 */
typedef unsigned long long uint64;

/**
 * @brief   [SWS_Platform_00023]
 *          This optimized AUTOSAR type shall be at least 8 bit signed.
 *          Range: At least -128 .. +127
 */
typedef signed int sint8_least;

/**
 * @brief   [SWS_Platform_00020]
 *          This optimized AUTOSAR type shall be at least 8 bit unsigned.
 *          Range: At least 0 .. 255
 */
typedef unsigned int uint8_least;

/**
 * @brief   [SWS_Platform_00024]
 *          This optimized AUTOSAR type shall be at least 16 bit signed.
 *          Range: At least -32768 .. +32767
 */
typedef signed int sint16_least;

/**
 * @brief   [SWS_Platform_00021]
 *          This optimized AUTOSAR type shall be at least 16 bit unsigned.
 *          Range: At least 0 .. 65535
 */
typedef unsigned int uint16_least;

/**
 * @brief   [SWS_Platform_00025]
 *          This optimized AUTOSAR type shall be at least 32 bit signed.
 *          Range: At least -2147483648 .. +2147483647
 */
typedef signed int sint32_least;

/**
 * @brief   [SWS_Platform_00022]
 *          This optimized AUTOSAR type shall be at least 32 bit unsigned.
 *          Range: At least 0 .. 4294967295
 */
typedef unsigned int uint32_least;

/**
 * @brief   [SWS_Platform_00041]
 *          This standard AUTOSAR type shall follow the 32-bit binary interchange format according to IEEE
 *          754-2008 with encoding parameters specified in chapter 3.6, table 3.5, column "binary32".
 *          Range: -3.4028235e+38 .. +3.4028235e+38
 */
typedef float float32;

/**
 * @brief   [SWS_Platform_00041]
 *          This standard AUTOSAR type shall follow the 64-bit binary interchange format according to IEEE
 *          754-2008 with encoding parameters specified in chapter 3.6, table 3.5, column "binary64".
 *          Range: -1.7976931348623157e+308 .. +1.7976931348623157e+308
 */
typedef double float64;

/****************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 ***************************************************************************************************/



/****************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 ***************************************************************************************************/



#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_TYPES_H */

/****************************************************************************************************
 *  END OF FILE: Platform_Types.h
 ***************************************************************************************************/
