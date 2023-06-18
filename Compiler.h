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
 * @brief   Description:        Header file of compiler abstraction.
 ***************************************************************************************************/
#ifndef COMPILER_H
#define COMPILER_H

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************************************
 * INCLUDES
 ***************************************************************************************************/

#include "Compiler_Cfg.h"

/****************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 ***************************************************************************************************/
/**
 * @brief   [SWS_BSW_00059]
 *          Define Published information elements
 */
#define COMPILER_VENDOR_ID                      (65535U)
#define COMPILER_MODULE_ID                      (198U)

/* AUTOSAR Software Specification Document Version Information */
#define COMPILER_AR_RELEASE_MAJOR_VERSION       (22U)
#define COMPILER_AR_RELEASE_MINOR_VERSION       (11U)
#define COMPILER_AR_RELEASE_REVISION_VERSION    (0U)

/* Component Version Information */
#define COMPILER_SW_MAJOR_VERSION               (0U)
#define COMPILER_SW_MINOR_VERSION               (1U)
#define COMPILER_SW_PATCH_VERSION               (0U)

/**
 * @brief   [SWS_BSW_00036]
 *          Perform Inter Module Checks
 */
#if !defined(DISABLE_MCAL_ASR_VER_CHECK)
#if ((COMPILER_AR_RELEASE_MAJOR_VERSION != COMPILER_CFG_GEN_AR_RELEASE_MAJOR_VERSION)        \
    || (COMPILER_AR_RELEASE_MINOR_VERSION != COMPILER_CFG_GEN_AR_RELEASE_MINOR_VERSION)      \
    || (COMPILER_AR_RELEASE_REVISION_VERSION != COMPILER_CFG_GEN_AR_RELEASE_REVISION_VERSION))
#error "Opps, Compiler.h and Compiler_Cfg.h AutoSAR version not match!"
#endif
#endif  /* !DISABLE_MCAL_ASR_VER_CHECK */
#if !defined(DISABLE_MCAL_SW_VER_CHECK)
#if ((COMPILER_SW_MAJOR_VERSION != COMPILER_CFG_GEN_SW_MAJOR_VERSION)       \
    || (COMPILER_SW_MINOR_VERSION != COMPILER_CFG_GEN_SW_MINOR_VERSION)     \
    || (COMPILER_SW_PATCH_VERSION != COMPILER_CFG_GEN_SW_PATCH_VERSION))
#error "Opps, Compiler.h and Compiler_Cfg.h Software version not match!"
#endif
#endif  /* !DISABLE_MCAL_SW_VER_CHECK */

/**
 * @brief   [SWS_COMPILER_00046]
 *          The memory class AUTOMATIC shall be provided as empty definition, used for
 *          the declaration of local pointers.
 */
#define AUTOMATIC

/**
 * @brief   [SWS_COMPILER_00059]
 *          The memory class TYPEDEF shall be provided as empty definition. This memory
 *          class shall be used within type definitions, where no memory qualifier can be
 *          specified. This can be necessary for defining pointer types, with e.g. P2VAR,
 *          where the macros require two parameters. First parameter can be specified in the
 *          type definition (distance to the memory location referenced by the pointer), but
 *          the second one (memory allocation of the pointer itself) cannot be defined at this
 *          time. Hence, memory class TYPEDEF shall be applied.
 */
#define TYPEDEF

/**
 * @brief   [SWS_Std_00031]
 *          The compiler abstraction shall provide the NULL_PTR define with a void pointer
 *          to zero definition.
 */
#define NULL_PTR ((void *)0)

/**
 * @brief   [SWS_COMPILER_00010]]
 *          The compiler abstraction shall define a symbol for the target compiler according
 *          to the following naming convention:
 *          <COMPILERNAME>_C_<PLATFORMNAME>_
 *          The following is the complier supported by micro SOME/IP:
 *          _ARMGCC_C_      (for arm-none-eabi-gcc)
 *          _GCC_C_         (for gnu-gcc)
 *          _MSC_VER        (for msc)
 */
#if (defined(__GNUC__))
#if (defined(__ARM_EABI__))
    #define _ARMGCC_C_
#else
    #define _GCC_C_
#endif /* defined(__ARM_EABI__) */
#elif (defined(_MSC_VER))
    #define _MSVC_C_
#else
    #error "Compilor not supported yet!"
#endif /* (defined(__GNUC__)) */

/**
 * @brief [SWS_COMPILER_00057]
 *        The compiler abstraction shall provide the INLINE define for abstraction of the
 *        keyword inline.
 *        [SWS_COMPILER_00060]
 *        The compiler abstraction shall provide the LOCAL_INLINE define for abstraction
 *        of the keyword inline in functions with "static" scope.
 */
#if defined(_ARMGCC_C_)
#define INLINE inline
#define LOCAL_INLINE static inline
#endif /* defined(_ARMGCC_C_) */

#if defined(_GCC_C_)
#define INLINE
#define LOCAL_INLINE
#endif /* defined(_GCC_C_) */

#if defined(_MSVC_C_)
#define INLINE
#define LOCAL_INLINE
#endif /* defined(_MSVC_C_) */

/**
 * @brief   [SWS_COMPILER_00057]
 *          The compiler abstraction shall define the FUNC macro for the declaration and
 *          definition of functions that ensures correct syntax of function declarations as
 *          required by a specific compiler.
 * 
 * @param   retype      return type of the function
 * @param   memclass    classification of the function itself
 */
#define FUNC(rettype, memclass) rettype

/**
 * @brief   [SWS_COMPILER_00057]
 *          The compiler abstraction shall define the FUNC_P2CONST macro for the
 *          declaration and definition of functions returning a pointer to a constant. This shall
 *          ensure the correct syntax of function declarations as required by a specific
 *          compiler.
 * 
 * @param   retype      return type of the function
 * @param   ptrclass    defines the classification of the pointer’s distance
 * @param   memclass    classification of the function itself
 */
#define FUNC_P2CONST(rettype, ptrclass, memclass) const ptrclass rettype * memclass

/**
 * @brief   [SWS_COMPILER_00063]
 *          The compiler abstraction shall define the FUNC_P2VAR macro for the declaration
 *          and definition of functions returning a pointer to a variable. This shall ensure the 
 *          correct syntax of function declarations as required by a specific compiler.
 * 
 * @param   retype      return type of the function
 * @param   ptrclass    defines the classification of the pointer’s distance
 * @param   memclass    classification of the function itself
 */
#define FUNC_P2VAR(rettype, ptrclass, memclass) ptrclass rettype * memclass

/**
 * @brief   [SWS_COMPILER_00006]
 *          The compiler abstraction shall define the P2VAR macro for the declaration and
 *          definition of pointers in RAM, pointing to variables.
 * 
 * @param   ptrtype     type of the referenced variable
 * @param   memclass    classification of the pointer’s variable itself
 * @param   ptrclass    defines the classification of the pointer’s distance
 */
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *

/**
 * @brief   [SWS_COMPILER_00013]
 *          The compiler abstraction shall define the P2CONST macro for the declaration
 *          and definition of pointers in RAM pointing to constants
 * 
 * @param   ptrtype     type of the referenced constant
 * @param   memclass    classification of the pointer’s variable itself
 * @param   ptrclass    defines the classification of the pointer’s distance
 */
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

/**
 * @brief   [SWS_COMPILER_00013]
 *          The compiler abstraction shall define the P2CONST macro for the declaration
 *          and definition of pointers in RAM pointing to constants
 * 
 * @param   ptrtype     type of the referenced variable
 * @param   memclass    classification of the pointer’s variable itself
 * @param   ptrclass    defines the classification of the pointer’s distance
 */
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const

/**
 * @brief   [SWS_COMPILER_00032]
 *          The compiler abstraction shall define the CONSTP2CONST macro for the
 *          declaration and definition of constant pointers accessing constants.
 * 
 * @param   ptrtype     type of the referenced constant
 * @param   memclass    classification of the pointer’s variable itself
 * @param   trclass     defines the classification of the pointer’s distance
 */
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

/**
 * @brief   [SWS_COMPILER_00039]
 *          The compiler abstraction shall define the P2FUNC macro for the type definition of
 *          pointers to functions.
 * 
 * @param   rettype     return type of the function
 * @param   ptrclass    defines the classification of the pointer’s distance
 * @param   fctname     function name respectively name of the defined type
 */
#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname)

/**
 * @brief   [SWS_COMPILER_00065]
 *          The compiler abstraction shall define the CONSTP2FUNC macro for the type
 *          definition of constant pointers to functions.
 * 
 * @param   rettype     return type of the function
 * @param   ptrclass    defines the classification of the pointer’s distance
 * @param   fctname     function name respectively name of the defined type
 */
#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const fctname)

/**
 * @brief   [SWS_COMPILER_00023]
 *          The compiler abstraction shall define the CONST macro for the declaration and
 *          definition of constants.
 * 
 * @param   consttype   type of the constant
 * @param   memclass    classification of the constant itself
 */
#define CONST(type, memclass) const type

/**
 * @brief   [SWS_COMPILER_00026]
 *          The compiler abstraction shall define the VAR macro for the declaration and
 *          definition of variables.
 * 
 * @param   vartype     type of the variable
 * @param   memclass    classification of the constant itself
 */
#define VAR(vartype, memclass) vartype

/****************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 ***************************************************************************************************/



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

#endif /* COMPILER_H */

/****************************************************************************************************
 *  END OF FILE: Compiler.h
 ***************************************************************************************************/
