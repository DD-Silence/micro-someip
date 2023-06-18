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
 * @file    Filename:           SomeIp_Serializer.c
 * @date    Date:               2023-06-16
 * @version Version:            0.0.1
 * @brief   Description:        Source file of SOME/IP serializer implementation
 ***************************************************************************************************/
/****************************************************************************************************
 *  INCLUDES
 ***************************************************************************************************/

#include "SomeIp_Types.h"

/****************************************************************************************************
 *  LOCAL CONSTANT MACROS
 ***************************************************************************************************/
#define SOMEIP_WIRE_TYPE_OFFSET         (12U)


/****************************************************************************************************
 *  LOCAL FUNCTION MACROS
 ***************************************************************************************************/



/****************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 ***************************************************************************************************/



/****************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 ***************************************************************************************************/



/****************************************************************************************************
 *  GLOBAL DATA
 ***************************************************************************************************/



/****************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 ***************************************************************************************************/
static uint16 SomeIp_ConstructTagType(const SomeIp_MemberTagType *Tag);
static void SomeIp_ParseTagType(SomeIp_MemberTagType *Tag, const uint16 Value);


/****************************************************************************************************
 *  FUNCTION IMPLEMETATION
 ***************************************************************************************************/
static INLINE uint16 SomeIp_ConstructTagType(const SomeIp_MemberTagType *Tag)
{
    return (((uint16)Tag->WireType << SOMEIP_WIRE_TYPE_OFFSET) | (Tag->DataId));
}

static INLINE void SomeIp_ParseTagType(SomeIp_MemberTagType *Tag, const uint16 Value)
{
    Tag->WireType = (uint8)(Value >> 12U);
    Tag->DataId = Value & (0x0FFFU);
}


/****************************************************************************************************
 *  END OF FILE: SomeIp_Serializer.c
 ***************************************************************************************************/
