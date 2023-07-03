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
#define SOMEIP_DATA_TYPE_BOOLEAN                (0U)
#define SOMEIP_DATA_TYPE_UINT8                  (1U)
#define SOMEIP_DATA_TYPE_UINT16                 (2U)
#define SOMEIP_DATA_TYPE_UINT32                 (3U)
#define SOMEIP_DATA_TYPE_UINT64                 (4U)
#define SOMEIP_DATA_TYPE_SINT8                  (5U)
#define SOMEIP_DATA_TYPE_SINT16                 (6U)
#define SOMEIP_DATA_TYPE_SINT32                 (7U)
#define SOMEIP_DATA_TYPE_SINT64                 (8U)
#define SOMEIP_DATA_TYPE_FLOAT32                (9U)
#define SOMEIP_DATA_TYPE_FLOAT64                (10U)
#define SOMEIP_DATA_TYPE_STRUCT                 (11U)
#define SOMEIP_DATA_TYPE_STRING                 (12U)
#define SOMEIP_DATA_TYPE_ARRAY                  (12U)
#define SOMEIP_DATA_TYPE_UNION                  (13U)

/**
 * @brief
 * @implements
 */
#define SOMEIP_MESSAGE_TYPE_REQUEST             (0x00U)
#define SOMEIP_MESSAGE_TYPE_REQUEST_NO_RETURN   (0x01U)
#define SOMEIP_MESSAGE_TYPE_RESPONSE            (0x80U)
#define SOMEIP_MESSAGE_TYPE_ERROR               (0x81U)


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
    uint16 ServideId;
    uint16 MethodId;
} SomeIp_MessageIdType;

/**
 * @brief
 * @implements
 */
typedef struct
{
    uint16 ClientId;
    uint16 SessionId;
} SomeIp_RequestIdType;

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
typedef enum
{
    SOMEIP_WIRE_KIND_8BIT = 0U,
    SOMEIP_WIRE_KIND_16BIT,
    SOMEIP_WIRE_KIND_32BIT,
    SOMEIP_WIRE_KIND_64BIT,
    SOMEIP_WIRE_KIND_COMPLEX_CONFIGURED,
    SOMEIP_WIRE_KIND_COMPLEX_LENGTH_ONE,
    SOMEIP_WIRE_KIND_COMPLEX_LENGTH_TWO,
    SOMEIP_WIRE_KIND_COMPLEX_LENGTH_FOUR,
    SOMEIP_WIRE_KIND_MAX
} SomeIpXf_WireKindType;

/**
 * @brief
 * @implements
 */
typedef struct
{
    boolean Valid;
    SomeIpXf_WireKindType WireType;
    uint16 DataId;
} SomeIpXf_MemberTagType;

typedef enum
{
    SOMEIPXF_LENGTH_FIELD_SIZE_0BIT = 0U,
    SOMEIPXF_LENGTH_FIELD_SIZE_8BIT,
    SOMEIPXF_LENGTH_FIELD_SIZE_16BIT,
    SOMEIPXF_LENGTH_FIELD_SIZE_32BIT,
    SOMEIPXF_LENGTH_FIELD_SIZE_MAX
} SomeIpXf_LengthFieldSizeType;

typedef enum
{
    SOMEIPXF_DATA_KIND_BASE,
    SOMEIPXF_DATA_KIND_STRUCT,
    SOMEIPXF_DATA_KIND_STRING_FIXED,
    SOMEIPXF_DATA_KIND_STRING_FLEXED,
    SOMEIPXF_DATA_KIND_ARRAY,
    SOMEIPXF_DATA_KIND_UNION,
    SOMEIPXF_DATA_KIND_MAX
} SomeIpXf_DataKindType;

typedef enum
{
    SOMEIPXF_ALIGNMENT_0BIT = 0U,
    SOMEIPXF_ALIGNMENT_8BIT,
    SOMEIPXF_ALIGNMENT_16BIT,
    SOMEIPXF_ALIGNMENT_32BIT,
    SOMEIPXF_ALIGNMENT_MAX
} SomeIpXf_AlignmentType;

typedef enum
{
    SOMEIPXF_ENDIAN_MOTO = 0U,
    SOMEIPXF_ENDIAN_INTEL,
    SOMEIPXF_ENDIAN_MAX
} SomeIpXf_EndianType;

typedef uint32 SomeIpXf_DataType;

typedef struct
{
    SomeIpXf_DataKindType Kind;
    SomeIpXf_DataType Data;
    uint32 DataOffset;
    uint8 SpecialSize;
    uint32 SpecialOffset;
} SomeIpXf_MemberConfigType;

typedef struct
{
    uint8 Length;
    SomeIpXf_AlignmentType Alignment;
    SomeIpXf_EndianType Endian;
    SomeIpXf_MemberTagType Tag;
} SomeIpXf_BaseConfigType;

typedef struct
{
    uint32 Length;
    SomeIpXf_LengthFieldSizeType LengthFieldSize;
    SomeIpXf_AlignmentType Alignment;
    SomeIpXf_EndianType Endian;
    SomeIpXf_MemberTagType Tag;
    uint32 MemberNumber;
    SomeIpXf_MemberConfigType *Members;
} SomeIpXf_StructConfigType;

typedef enum
{
    SOMEIPXF_STRING_KIND_LEGACY = 0U,
    SOMEIPXF_STRING_KIND_UTF8,
    SOMEIPXF_STRING_KIND_UTF16,
} SomeIpXf_StringKindType;

typedef struct
{
    SomeIpXf_StringKindType Kind;
    uint32 Length;
    SomeIpXf_AlignmentType Alignment;
    boolean Convert;
    SomeIpXf_MemberTagType Tag;
} SomeIpXf_StringFixedConfigType;

typedef struct
{
    SomeIpXf_StringKindType Kind;
    SomeIpXf_LengthFieldSizeType LengthFieldSize;
    SomeIpXf_AlignmentType Alignment;
    boolean Convert;
    SomeIpXf_MemberTagType Tag;
} SomeIpXf_StringFlexedConfigType;

typedef struct
{
    SomeIpXf_DataKindType Kind;
    SomeIpXf_DataType Data;
    uint32 DataOffset;
    uint8 SpecialSize;
    uint32 SpecialOffset;
} SomeIpXf_ElementConfigType;

typedef struct
{
    uint32 LengthMax;
    SomeIpXf_LengthFieldSizeType LengthFieldSize;
    SomeIpXf_AlignmentType Alignment;
    SomeIpXf_EndianType Endian;
    SomeIpXf_MemberTagType Tag;
    SomeIpXf_ElementConfigType *Element;
} SomeIpXf_ArrayConfigType;

typedef struct
{
    SomeIpXf_DataType BaseCfgNumber;
    SomeIpXf_BaseConfigType *BaseCfgs;
    SomeIpXf_DataType StructCfgNumber;
    SomeIpXf_StructConfigType *StructCfgs;
    SomeIpXf_DataType StringFixedCfgNumber;
    SomeIpXf_StringFixedConfigType *StringFixedCfgs;
    SomeIpXf_DataType StringFlexedCfgNumber;
    SomeIpXf_StringFlexedConfigType *StringFlexedCfgs;
    SomeIpXf_DataType ArrayCfgNumber;
    SomeIpXf_ArrayConfigType *ArrayCfgs;
} SomeIpXf_ConfigType;

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

