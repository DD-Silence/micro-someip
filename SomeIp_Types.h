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
 * @file    Filename:           SomeIp_Types.h
 * @date    Date:               2023-06-16
 * @version Version:            0.0.1
 * @brief   Description:        Header file of SOME/IP types
 ***************************************************************************************************/
#ifndef SOMEIP_TYPES_H
#define SOMEIP_TYPES_H

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
/**
 * @brief
 * @implements
 */
#define SOMEIP_MEMBER_TYPE_BOOLEAN              (0U)
#define SOMEIP_MEMBER_TYPE_UINT8                (1U)
#define SOMEIP_MEMBER_TYPE_UINT16               (2U)
#define SOMEIP_MEMBER_TYPE_UINT32               (3U)
#define SOMEIP_MEMBER_TYPE_UINT64               (4U)
#define SOMEIP_MEMBER_TYPE_SINT8                (5U)
#define SOMEIP_MEMBER_TYPE_SINT16               (6U)
#define SOMEIP_MEMBER_TYPE_SINT32               (7U)
#define SOMEIP_MEMBER_TYPE_SINT64               (8U)
#define SOMEIP_MEMBER_TYPE_FLOAT32              (9U)
#define SOMEIP_MEMBER_TYPE_FLOAT64              (10U)
#define SOMEIP_MEMBER_TYPE_STRUCT               (11U)
#define SOMEIP_MEMBER_TYPE_STRING               (12U)
#define SOMEIP_MEMBER_TYPE_ARRAY                (12U)
#define SOMEIP_MEMBER_TYPE_UNION                (13U)

/**
 * @brief
 * @implements
 */
#define SOMEIP_WIRE_TYPE_8BIT                   (0U)
#define SOMEIP_WIRE_TYPE_16BIT                  (1U)
#define SOMEIP_WIRE_TYPE_32BIT                  (2U)
#define SOMEIP_WIRE_TYPE_64BIT                  (3U)
#define SOMEIP_WIRE_TYPE_COMPLEX_CONFIGURED     (4U)
#define SOMEIP_WIRE_TYPE_COMPLEX_LENGTH_ONE     (5U)
#define SOMEIP_WIRE_TYPE_COMPLEX_LENGTH_TWO     (6U)
#define SOMEIP_WIRE_TYPE_COMPLEX_LENGTH_FOUR    (7U)

/****************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 ***************************************************************************************************/



/****************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 ***************************************************************************************************/
/**
 * @brief
 * @implements
 */
typedef struct
{
    uint32 MessageId;
    uint32 Length;
    uint32 RequestId;
    uint8 ProtocolVersion;
    uint8 InterfaceVersion;
    uint8 MessageType;
    uint8 ReturnCode;
} SomeIp_HeadType;

/**
 * @brief
 * @implements
 */
typedef struct
{
    SomeIp_HeadType Head;
    uint8 *Payload;
} SomeIp_MessageType;

/**
 * @brief
 * @implements
 */
typedef struct
{
    uint8 WireType;
    uint16 DataId;
} SomeIp_MemberTagType;

/**
 * @brief
 * @implements
 */
typedef struct
{
    uint8 LengthSize;
    uint32 Length;
} SomeIp_MemberLengthType;

/**
 * @brief
 * @implements
 */
typedef struct SomeIp_MemberType_Tag SomeIp_MemberType;

struct SomeIp_PrimitiveType
{
    
};

struct SomeIp_MemberType_Tag
{
    uint8 type;
    const SomeIp_MemberTagType *Tag;
    const SomeIp_MemberLengthType *Length;
    uint8 AlignSize;
    uint8 *payload;
    uint32 childrenNumber;
    SomeIp_MemberType *children;
    SomeIp_MemberType *parent;
};

/****************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 ***************************************************************************************************/



/****************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 ***************************************************************************************************/



#ifdef __cplusplus
}
#endif

#endif /* SOMEIP_TYPES_H */

/****************************************************************************************************
 *  END OF FILE: SomeIp_Types.h
 ***************************************************************************************************/

