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
 * @file    Filename:           Compiler.h
 * @date    Date:               2023-06-16
 * @version Version:            0.0.1
 * @brief   Description:        Configuration header file of compiler abstraction.
 ***************************************************************************************************/
#ifndef COMPLIER_CFG_H
#define COMPLIER_CFG_H

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
/* AUTOSAR Software Specification Document Version Information */
#define COMPILER_CFG_GEN_AR_RELEASE_MAJOR_VERSION       (22U)
#define COMPILER_CFG_GEN_AR_RELEASE_MINOR_VERSION       (11U)
#define COMPILER_CFG_GEN_AR_RELEASE_REVISION_VERSION	(0U)

/* Component Version Information */
#define COMPILER_CFG_GEN_SW_MAJOR_VERSION               (0U)
#define COMPILER_CFG_GEN_SW_MINOR_VERSION               (1U)
#define COMPILER_CFG_GEN_SW_PATCH_VERSION               (0U)

/****************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 ***************************************************************************************************/
/* PORT begin */
#define PORT_PUBLIC_CODE                /* API functions                      */
#define PORT_PUBLIC_CONST               /* API constants                      */
#define PORT_PRIVATE_CODE               /* Internal functions                 */
#define PORT_PRIVATE_DATA               /* Module internal data               */
#define PORT_PRIVATE_CONST              /* Internal ROM Data                  */
#define PORT_APPL_CODE                  /* callbacks of the Application       */
#define PORT_APPL_CONST                 /* Applications' ROM Data             */
#define PORT_APPL_DATA                  /* Applications' RAM Data             */
#define PORT_FAST_DATA                  /* 'Near' RAM Data                    */
#define PORT_FAST_CODE                  /* API functions                      */
#define PORT_FAST_CONST                 /* API constants                      */
#define PORT_FAST_DATA                  /* API constants                      */
#define PORT_CONFIG_CONST               /* Desc. Tables -> Config-dependent   */
#define PORT_CONFIG_DATA                /* Config. dependent (reg. size) data */
#define PORT_INIT_DATA                  /* Data which is initialized during Startup */
#define PORT_NOINIT_DATA                /* Data which is not initialized during Startup */
#define PORT_CONST                      /* Data Constants Memory class for global variables which are initialized after every reset */
#define PORT_VAR_NOINIT                 /* Memory class for global variables which are initialized by driver    */
#define PORT_CODE
#define PORT_CALLOUT_CODE
#define PORT_VAR_POWER_ON_INIT
#define PORT_VAR_FAST
#define PORT_REGSPACE
/* PORT end */

/* DIO begin */
#define DIO_PUBLIC_CODE                /* API functions                       */
#define DIO_PUBLIC_CONST               /* API constants                       */
#define DIO_PRIVATE_CODE               /* Internal functions                  */
#define DIO_PRIVATE_DATA               /* Module internal data                */
#define DIO_PRIVATE_CONST              /* Internal ROM Data                   */
#define DIO_APPL_CODE                  /* callbacks of the Application        */
#define DIO_APPL_CONST                 /* Applications' ROM Data              */
#define DIO_APPL_DATA                  /* Applications' RAM Data              */
#define DIO_FAST_DATA                  /* 'Near' RAM Data                     */
#define DIO_FAST_CODE                  /* API functions                       */
#define DIO_FAST_CONST                 /* API constants                       */
#define DIO_FAST_DATA                  /* API constants                       */
#define DIO_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define DIO_CONFIG_DATA                /* Config. dependent (reg. size) data  */
#define DIO_INIT_DATA                  /* Data which is initialized during Startup */
#define DIO_NOINIT_DATA                /* Data which is not initialized during Startup */
#define DIO_CONST                      /* Data Constants                      */
#define DIO_VAR                        /* Memory class for global variables which are initialized after every reset  */
#define DIO_VAR_NOINIT                 /* Memory class for global variables which are initialized by driver     */
#define DIO_CODE
#define DIO_CALLOUT_CODE
#define DIO_VAR_POWER_ON_INIT
#define DIO_VAR_FAST
#define DIO_REGSPACE
/* DIO end */

/* DET begin */
#define DET_PUBLIC_CODE                /* API functions                       */
#define DET_PUBLIC_CONST               /* API constants                       */
#define DET_PRIVATE_CODE               /* Internal functions                  */
#define DET_PRIVATE_DATA               /* Module internal data                */
#define DET_PRIVATE_CONST              /* Internal ROM Data                   */
#define DET_APPL_CODE                  /* callbacks of the Application        */
#define DET_APPL_CONST                 /* Applications' ROM Data              */
#define DET_APPL_DATA                  /* Applications' RAM Data              */
#define DET_FAST_DATA                  /* 'Near' RAM Data                     */
#define DET_FAST_CODE                  /* API functions                       */
#define DET_FAST_CONST                 /* API constants                       */
#define DET_FAST_DATA                  /* API constants                       */
#define DET_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define DET_CONFIG_DATA                /* Config. dependent (reg. size) data  */
#define DET_INIT_DATA                  /* Data which is initialized during Startup */
#define DET_NOINIT_DATA                /* Data which is not initialized during Startup */
#define DET_CONST                      /* Data Constants                      */
#define DET_VAR                        /* Memory class for global variables which are initialized after every reset  */
#define DET_VAR_NOINIT                 /* Memory class for global variables which are initialized by driver     */
#define DET_CODE
#define DET_CALLOUT_CODE
#define DET_VAR_POWER_ON_INIT
#define DET_VAR_FAST
#define DET_REGSPACE
/* DET end */

/****************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 ***************************************************************************************************/



/****************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 ***************************************************************************************************/



/****************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 ***************************************************************************************************/



#ifdef __cplusplus
}
#endif

#endif /* COMPLIER_CFG_H */

/****************************************************************************************************
 *  END OF FILE: Complier_Cfg.h
 ***************************************************************************************************/
