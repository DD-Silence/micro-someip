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
 * @file    Filename:           Std_Types.h
 * @date    Date:               2023-06-16
 * @version Version:            0.0.1
 * @brief   Description:        Header file AUTOSAR Stanard types.
 ***************************************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************************************
 * INCLUDES
 ***************************************************************************************************/

#include "Platform_Types.h"
#include "Compiler.h"

/****************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 ***************************************************************************************************/
/**
 * @brief   [SWS_BSW_00059]
 *          Define Published information elements
 */
#define STD_TYPES_VENDOR_ID                     (65535U)
#define STD_TYPES_MODULE_ID                     (197U)

/* AUTOSAR Software Specification Document Version Information */
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION      (22U)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION      (11U)
#define STD_TYPES_AR_RELEASE_REVISION_VERSION   (0U)

/* Component Version Information */
#define STD_TYPES_SW_MAJOR_VERSION              (0U)
#define STD_TYPES_SW_MINOR_VERSION              (1U)
#define STD_TYPES_SW_PATCH_VERSION              (0U)

/**
 * @brief   [SWS_Std_00007]
 */
/**
 * @brief   [SWS_Dio_00185]
 * @enum    STD_LOW             Physical state 0V
 * @enum    STD_HIGH            Physical state 5V or 3.3V
 */
#define STD_HIGH                                (0x01U)        /* Physical state 5V or 3.3V */
#define STD_LOW                                 (0x00U)        /* Physical state 0V */

/**
 * @brief   [SWS_Std_00013]
 */
#define STD_ACTIVE                              (0x01U)         /* Logical state active */
#define STD_IDLE                                (0x00U)         /* Logical state idle */

/**
 * @brief   [SWS_Std_00010]
 */
#define STD_ON                                  (0x01U)
#define STD_OFF                                 (0x00U)

/****************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 ***************************************************************************************************/



/****************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 ***************************************************************************************************/
/**
 * @brief   [SWS_Std_00005]
 *          This type can be used as standard API return type which is shared between the RTE and the BSW
 *          modules.
 */
typedef uint8 Std_ReturnType;

/**
 * @brief   [SWS_Std_00006]
 *          Because E_OK is already defined within OSEK, the symbol E_OK has to be shared.
 */
/**
 * @brief   [SWS_Std_00005]
 * @enum    E_OK           0                 [SWS_Std_00006]
 * @enum    E_NOT_OK       1                 [SWS_Std_00006]
 * @enum    0x02-0x3F      0x02-0x3F         Available to user specific errors
 */
#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK                                    (0x00U)
typedef unsigned char StatusType;   /* OSEK compliance */
#endif
#define E_NOT_OK                                (0x01U)

/**
 * @brief   [SWS_Std_00015]
 *          This type shall be used to request the version of a BSW module using the <Module name>_Get
 *          VersionInfo() function.
 */
typedef struct
{
   uint16 vendorID;
   uint16 moduleID;
   uint8  sw_major_version;
   uint8  sw_minor_version;
   uint8  sw_patch_version;
} Std_VersionInfoType;

/****************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 ***************************************************************************************************/



/****************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 ***************************************************************************************************/



#ifdef __cplusplus
}
#endif

#endif /* STD_TYPES_H */

/****************************************************************************************************
 *  END OF FILE: Std_Types.h
 ***************************************************************************************************/
