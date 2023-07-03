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
 * @file    Filename:           SomeIpXf.h
 * @date    Date:               2023-06-16
 * @version Version:            0.0.1
 * @brief   Description:        Header file. of SOME/IP transformer implementation
 ***************************************************************************************************/
#ifndef SOMEIPXF_H
#define SOMEIPXF_H

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************************************
 * INCLUDES
 ***************************************************************************************************/

#include "Std_Types.h"

/****************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 ***************************************************************************************************/
#define SOMEIPXF_E_OK                   (0x00U)
#define SOMEIPXF_E_UNINIT               (0x01U)
#define SOMEIPXF_E_INIT_FAILED          (0x02U)
#define SOMEIPXF_E_PARAM                (0x03U)
#define SOMEIPXF_E_PARAM_POINTER        (0x04U)


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
Std_ReturnType SomeIpXf_SerializeBase(SomeIpXf_DataType MemberId, void *Value, uint8 *Buffer, uint32 *BufferLength, uint32 Level);
Std_ReturnType SomeIpXf_SerializeStruct(SomeIpXf_DataType MemberId, void *Value, uint8 *Buffer, uint32 *BufferLength, uint32 Level);
Std_ReturnType SomeIpXf_SerializeStringFixed(SomeIpXf_DataType MemberId, void *Value, uint8 *Buffer, uint32 *BufferLength, uint32 Level);
Std_ReturnType SomeIpXf_SerializeStringFlexed(SomeIpXf_DataType MemberId, void *Value, uint32 StringLength, uint8 *Buffer, uint32 *BufferLength, uint32 Level);
Std_ReturnType SomeIpXf_SerializeArray(SomeIpXf_DataType MemberId, void *Value, uint32 ArrayNumber, uint8 *Buffer, uint32 *BufferLength, uint32 Level);


#ifdef __cplusplus
}
#endif

#endif /* SOMEIP_SERIALIZER_H */

/****************************************************************************************************
 *  END OF FILE: SomeIp_Serializer.h
 ***************************************************************************************************/

