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
 * @file    Filename:           SomeIpXf.c
 * @date    Date:               2023-06-16
 * @version Version:            0.0.1
 * @brief   Description:        Source file of SOME/IP transformer implementation
 ***************************************************************************************************/
/****************************************************************************************************
 *  INCLUDES
 ***************************************************************************************************/

#include "SomeIp_Types.h"
#include "SomeIpXf.h"

/****************************************************************************************************
 *  LOCAL CONSTANT MACROS
 ***************************************************************************************************/
#define SOMEIPXF_TAG_LENGTH                             (2U)


/****************************************************************************************************
 *  LOCAL FUNCTION MACROS
 ***************************************************************************************************/
#define SOMEIPXF_16BIT_HB(Value)                        ((uint8)((Value) >> 8))
#define SOMEIPXF_16BIT_LB(Value)                        ((uint8)(Value))

#define SOMEIPXF_VOID_OFFSET(VoidPtr, Offset)           ((void *)(&((uint8 *)(VoidPtr))[Offset]))

#define SOMEIPXF_VALID_OF_TAG(Tag)                      (Tag.Valid)
#define SOMEIPXF_WIRETYPE_OF_TAG(Tag)                   (Tag.WireType)

#define SOMEIPXF_KIND_OF_MEMBER_CONFIG(Config)          (Config.Kind)
#define SOMEIPXF_MEMBER_OF_MEMBER_CONFIG(Config)        (Config.Member)
#define SOMEIPXF_OFFSET_OF_MEMBER_CONFIG(Config)        (Config.Offset)

#define SOMEIPXF_LENGTH_OF_BASE_CONFIG(Id)              (SomeIpXf_Config->BaseCfgs[Id].Length)
#define SOMEIPXF_ALIGNMENT_OF_BASE_CONFIG(Id)           (SomeIpXf_Config->BaseCfgs[Id].Alignment)
#define SOMEIPXF_ENDIAN_OF_BASE_CONFIG(Id)              (SomeIpXf_Config->BaseCfgs[Id].Endian)
#define SOMEIPXF_TAG_OF_BASE_CONFIG(Id)                 (SomeIpXf_Config->BaseCfgs[Id].Tag)
#define SOMEIPXF_VALID_OF_TAG_OF_BASE_CONFIG(Id)        (SOMEIPXF_VALID_OF_TAG(SOMEIPXF_TAG_OF_BASE_CONFIG(Id)))
#define SOMEIPXF_WIRETYPE_OF_TAG_OF_BASE_CONFIG(Id)     (SOMEIPXF_WIRETYPE_OF_TAG(SOMEIPXF_TAG_OF_BASE_CONFIG(Id)))

#define SOMEIPXF_LENGTH_FIELD_SIZE_OF_STRUCT_CONFIG(Id)                             \
    (SomeIpXf_Config->StructCfgs[Id].LengthFileSize)
#define SOMEIPXF_ALIGNMENT_OF_STRUCT_CONFIG(Id)         (SomeIpXf_Config->StructCfgs[Id].Alignment)
#define SOMEIPXF_ENDIAN_OF_STRUCT_CONFIG(Id)            (SomeIpXf_Config->StructCfgs[Id].Endian)
#define SOMEIPXF_TAG_OF_STRUCT_CONFIG(Id)               (SomeIpXf_Config->StructCfgs[Id].Tag)
#define SOMEIPXF_VALID_OF_TAG_OF_STRUCT_CONFIG(Id)      (SOMEIPXF_VALID_OF_TAG(SOMEIPXF_TAG_OF_STRUCT_CONFIG(Id)))
#define SOMEIPXF_WIRETYPE_OF_TAG_OF_STRUCT_CONFIG(Id)   (SOMEIPXF_WIRETYPE_OF_TAG(SOMEIPXF_TAG_OF_STRUCT_CONFIG(Id)))
#define SOMEIPXF_MEMBER_NUMBER_OF_STRUCT_CONFIG(Id)     (SomeIpXf_Config->StructCfgs[Id].MemberNumber)
#define SOMEIPXF_MEMBERS_OF_STRUCT_CONFIG(Id)           (SomeIpXf_Config->StructCfgs[Id].Members)
#define SOMEIPXF_KIND_OF_MEMBERS_OF_STRUCT_CONFIG(Id, MemberId)                     \
    (SOMEIPXF_KIND_OF_MEMBER_CONFIG(SOMEIPXF_MEMBERS_OF_STRUCT_CONFIG(Id)[MemberId]))
#define SOMEIPXF_MEMBER_OF_MEMBERS_OF_STRUCT_CONFIG(Id, MemberId)                   \
    (SOMEIPXF_MEMBER_OF_MEMBER_CONFIG(SOMEIPXF_MEMBERS_OF_STRUCT_CONFIG(Id)[MemberId]))
#define SOMEIPXF_OFFSET_OF_MEMBERS_OF_STRUCT_CONFIG(Id, MemberId)                   \
    (SOMEIPXF_OFFSET_OF_MEMBER_CONFIG(SOMEIPXF_MEMBERS_OF_STRUCT_CONFIG(Id)[MemberId]))

/****************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 ***************************************************************************************************/



/****************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 ***************************************************************************************************/



/****************************************************************************************************
 *  GLOBAL DATA
 ***************************************************************************************************/
extern SomeIpXf_ConfigType *SomeIpXf_Config;


/****************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 ***************************************************************************************************/
static uint16 SomeIpXf_ConstructTagType(const SomeIpXf_MemberTagType *Tag);
static void SomeIpXf_ParseTagType(SomeIpXf_MemberTagType *Tag, const uint16 Value);


/****************************************************************************************************
 *  FUNCTION IMPLEMETATION
 ***************************************************************************************************/
static INLINE uint16 SomeIpXf_ConstructTagType(const SomeIpXf_MemberTagType *Tag)
{
    return ((((uint16)Tag->WireType & 0x7U) << 12) | (Tag->DataId));
}

static INLINE void SomeIpXf_ParseTagType(SomeIpXf_MemberTagType *Tag, const uint16 Value)
{
    Tag->WireType = TRUE;
    Tag->WireType = (SomeIpXf_WireKindType)((Value >> 12) & 0x7U);
    Tag->DataId = Value & (0x0FFFU);
}

Std_ReturnType SomeIpXf_SerializeBase(SomeIpXf_MemberType MemberId, void *Value, uint8 *Buffer, uint32 *Length, uint32 Level)
{
    Std_ReturnType Ret = SOMEIPXF_E_OK;
    uint8 LengthNeeded = 0U;
    boolean IsTagValid = FALSE;

    if ((NULL_PTR == Buffer) || (NULL_PTR == Value) || (NULL_PTR == Length))
    {
        Ret = SOMEIPXF_E_PARAM_POINTER;
    }
    else if (MemberId >= SomeIpXf_Config->BaseConfigNumber)
    {
        Ret = SOMEIPXF_E_PARAM;
    }
    else
    {
        LengthNeeded = SOMEIPXF_LENGTH_OF_BASE_CONFIG(MemberId);
        IsTagValid = SOMEIPXF_VALID_OF_TAG_OF_BASE_CONFIG(MemberId);

        if (TRUE == IsTagValid)
        {
            LengthNeeded += SOMEIPXF_TAG_LENGTH;
        }

        if (*Length < LengthNeeded)
        {
            Ret = SOMEIPXF_E_PARAM;
        }
        else
        {
            switch (SOMEIPXF_WIRETYPE_OF_TAG_OF_BASE_CONFIG(MemberId))
            {
            case SOMEIP_WIRE_KIND_8BIT:
                if (SOMEIPXF_LENGTH_OF_BASE_CONFIG(MemberId) != 1U)
                {
                    Ret = SOMEIPXF_E_PARAM;
                }
                break;
            
            case SOMEIP_WIRE_KIND_16BIT:
                if (SOMEIPXF_LENGTH_OF_BASE_CONFIG(MemberId) != 2U)
                {
                    Ret = SOMEIPXF_E_PARAM;
                }
                break;

            case SOMEIP_WIRE_KIND_32BIT:
                if (SOMEIPXF_LENGTH_OF_BASE_CONFIG(MemberId) != 4U)
                {
                    Ret = SOMEIPXF_E_PARAM;
                }
                break;

            case SOMEIP_WIRE_KIND_64BIT:
                if (SOMEIPXF_LENGTH_OF_BASE_CONFIG(MemberId) != 8U)
                {
                    Ret = SOMEIPXF_E_PARAM;
                }
                break;
            
            default:
                Ret = SOMEIPXF_E_PARAM;
                break;
            }
        }
    }

    if (E_OK == Ret)
    {
        uint8 Position = 0U;

        if (TRUE == IsTagValid)
        {
            uint16 Tag = SomeIpXf_ConstructTagType(&SOMEIPXF_TAG_OF_BASE_CONFIG(MemberId));

            Buffer[Position] = SOMEIPXF_16BIT_HB(Tag);
            Position++;
            Buffer[Position] = SOMEIPXF_16BIT_LB(Tag);
            Position++;
        }

        if (SOMEIPXF_ENDIAN_MOTO == SOMEIPXF_ENDIAN_OF_BASE_CONFIG(MemberId))
        {
            for (sint8 Index = (sint8)SOMEIPXF_LENGTH_OF_BASE_CONFIG(MemberId) - 1; Index >= 0; Index--)
            {
                Buffer[Position] = ((uint8 *)Value)[Index];
            }
        }
        else
        {
            for (uint8 Index = 0U; Index < SOMEIPXF_LENGTH_OF_BASE_CONFIG(MemberId); Index++)
            {
                Buffer[Position] = ((uint8 *)Value)[Index];
            }
        }
        *Length = *Length - LengthNeeded;
    }
    return Ret;
}

Std_ReturnType SomeIpXf_SerializeStruct(SomeIpXf_MemberType MemberId, void *Value, uint8 *Buffer, uint32 *Length, uint32 Level)
{
    Std_ReturnType Ret = SOMEIPXF_E_OK;
    uint8 LengthNeeded = 0U;
    boolean IsTagValid = FALSE;
    uint8 LengthSize = 0U;

    if ((NULL_PTR == Buffer) || (NULL_PTR == Value) || (NULL_PTR == Length))
    {
        Ret = SOMEIPXF_E_PARAM_POINTER;
    }
    else if ((MemberId >= SomeIpXf_Config->StructConfigNumber) || (0U == Level))
    {
        Ret = SOMEIPXF_E_PARAM;
    }
    else
    {
        LengthNeeded = 0U;
        IsTagValid = SOMEIPXF_VALID_OF_TAG_OF_STRUCT_CONFIG(MemberId);
        LengthSize = SOMEIPXF_LENGTH_FIELD_SIZE_OF_STRUCT_CONFIG(MemberId);

        if (TRUE == IsTagValid)
        {
            LengthNeeded += SOMEIPXF_TAG_LENGTH;
        }
    
        switch (LengthSize)
        {
        case SOMEIPXF_LENGTH_FIELD_SIZE_0BIT:
            break;
        
        case SOMEIPXF_LENGTH_FIELD_SIZE_8BIT:
            LengthNeeded += 1U;
            break;
        
        case SOMEIPXF_LENGTH_FIELD_SIZE_16BIT:
            LengthNeeded += 2U;
            break;

        case SOMEIPXF_LENGTH_FIELD_SIZE_32BIT:
            LengthNeeded += 4U;
            break;

        default:
            Ret = SOMEIPXF_E_PARAM;
            break;
        }

        if (*Length < LengthNeeded)
        {
            Ret = SOMEIPXF_E_PARAM;
        }
        else
        {
            switch (SOMEIPXF_WIRETYPE_OF_TAG_OF_BASE_CONFIG(MemberId))
            {            
            case SOMEIP_WIRE_KIND_COMPLEX_CONFIGURED:
                if ((SOMEIPXF_LENGTH_FIELD_SIZE_8BIT != LengthSize) && (SOMEIPXF_LENGTH_FIELD_SIZE_16BIT != LengthSize) &&
                    (SOMEIPXF_LENGTH_FIELD_SIZE_32BIT != LengthSize))
                {
                    Ret = SOMEIPXF_E_PARAM;
                }
                break;

            case SOMEIP_WIRE_KIND_COMPLEX_LENGTH_ONE:
                if (SOMEIPXF_LENGTH_FIELD_SIZE_8BIT != LengthSize)
                {
                    Ret = SOMEIPXF_E_PARAM;
                }
                break;

            case SOMEIP_WIRE_KIND_COMPLEX_LENGTH_TWO:
                if (SOMEIPXF_LENGTH_FIELD_SIZE_16BIT != LengthSize)
                {
                    Ret = SOMEIPXF_E_PARAM;
                }
                break;

            case SOMEIP_WIRE_KIND_COMPLEX_LENGTH_FOUR:
                if (SOMEIPXF_LENGTH_FIELD_SIZE_32BIT != LengthSize)
                {
                    Ret = SOMEIPXF_E_PARAM;
                }
                break;

            default:
                Ret = SOMEIPXF_E_PARAM;
                break;
            }
        }
    }

    if (E_OK == Ret)
    {
        uint8 Position = 0U;
        uint32 LengthLeft = *Length - LengthNeeded;

        if (TRUE == IsTagValid)
        {
            uint16 Tag = SomeIpXf_ConstructTagType(&SOMEIPXF_TAG_OF_STRUCT_CONFIG(MemberId));

            Buffer[Position] = SOMEIPXF_16BIT_HB(Tag);
            Position++;
            Buffer[Position] = SOMEIPXF_16BIT_LB(Tag);
            Position++;
        }

        for (uint32 SubMember = 0U; SubMember < SOMEIPXF_MEMBER_NUMBER_OF_STRUCT_CONFIG(MemberId); SubMember++)
        {
            switch (SOMEIPXF_KIND_OF_MEMBERS_OF_STRUCT_CONFIG(MemberId, SubMember))
            {
            case SOMEIPXF_MEMBER_KIND_BASE:
                SomeIpXf_SerializeBase(SOMEIPXF_MEMBER_OF_MEMBERS_OF_STRUCT_CONFIG(MemberId, SubMember),
                                    SOMEIPXF_VOID_OFFSET(Value, SOMEIPXF_OFFSET_OF_MEMBERS_OF_STRUCT_CONFIG(MemberId, SubMember)),
                                    &Buffer[LengthNeeded], &LengthLeft, Level - 1U);
                break;
            
            case SOMEIPXF_MEMBER_KIND_STRUCT:
                SomeIpXf_SerializeStruct(SOMEIPXF_MEMBER_OF_MEMBERS_OF_STRUCT_CONFIG(MemberId, SubMember),
                                    SOMEIPXF_VOID_OFFSET(Value, SOMEIPXF_OFFSET_OF_MEMBERS_OF_STRUCT_CONFIG(MemberId, SubMember)),
                                    &Buffer[LengthNeeded], &LengthLeft, Level - 1U);
                break;

            default:
                break;
            }
        }
    }
    return Ret;
}

/****************************************************************************************************
 *  END OF FILE: SomeIp_Serializer.c
 ***************************************************************************************************/
