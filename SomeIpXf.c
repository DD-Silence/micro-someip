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
#define SOMEIPXF_TAG_LENGTH                                     (2U)

#define SOMEIPXF_UTF8_BOM_LENGTH                                (3U)
#define SOMEIPXF_UTF16_BOM_LENGTH                               (2U)


/****************************************************************************************************
 *  LOCAL FUNCTION MACROS
 ***************************************************************************************************/
#define SOMEIPXF_16BIT_HB(Value)                                ((uint8)((Value) >> 8))
#define SOMEIPXF_16BIT_LB(Value)                                ((uint8)(Value))

#define SOMEIPXF_U8_FROM_PTR_U8(Ptr)                            (Ptr[0])
#define SOMEIPXF_U16_FROM_PTR_U8(Ptr)                           (((uint16)Ptr[0]) | (((uint16)Ptr[1]) << 8))
#define SOMEIPXF_U32_FROM_PTR_U8(Ptr)                           (((uint32)Ptr[0]) | (((uint32)Ptr[1]) << 8) | (((uint32)Ptr[2]) << 16) | (((uint32)Ptr[3]) << 24))

#define SOMEIPXF_VOID_OFFSET_U8(VoidPtr, Offset)                (&((uint8 *)(VoidPtr))[Offset])
#define SOMEIPXF_VOID_OFFSET(VoidPtr, Offset)                   ((void *)SOMEIPXF_VOID_OFFSET_U8(VoidPtr, Offset))

#define SOMEIPXF_VALID_OF_TAG(Tag)                              (Tag.Valid)
#define SOMEIPXF_WIRETYPE_OF_TAG(Tag)                           (Tag.WireType)

#define SOMEIPXF_KIND_OF_MEMBER_CONFIG(Config)                  (Config.Kind)
#define SOMEIPXF_DATA_OF_MEMBER_CONFIG(Config)                  (Config.Data)
#define SOMEIPXF_DATA_OFFSET_OF_MEMBER_CONFIG(Config)           (Config.DataOffset)
#define SOMEIPXF_SPECIAL_SIZE_OF_MEMBER_CONFIG(Config)          (Config.SpecialSize)
#define SOMEIPXF_SPECIAL_OFFSET_OF_MEMBER_CONFIG(Config)        (Config.SpecialOffset)

#define SOMEIPXF_LENGTH_OF_BASE_CONFIG(Id)                      (SomeIpXf_Config->BaseCfgs[Id].Length)
#define SOMEIPXF_ALIGNMENT_OF_BASE_CONFIG(Id)                   (SomeIpXf_Config->BaseCfgs[Id].Alignment)
#define SOMEIPXF_ENDIAN_OF_BASE_CONFIG(Id)                      (SomeIpXf_Config->BaseCfgs[Id].Endian)
#define SOMEIPXF_TAG_OF_BASE_CONFIG(Id)                         (SomeIpXf_Config->BaseCfgs[Id].Tag)
#define SOMEIPXF_VALID_OF_TAG_OF_BASE_CONFIG(Id)                (SOMEIPXF_VALID_OF_TAG(SOMEIPXF_TAG_OF_BASE_CONFIG(Id)))
#define SOMEIPXF_WIRETYPE_OF_TAG_OF_BASE_CONFIG(Id)             (SOMEIPXF_WIRETYPE_OF_TAG(SOMEIPXF_TAG_OF_BASE_CONFIG(Id)))

#define SOMEIPXF_LENGTH_FIELD_SIZE_OF_STRUCT_CONFIG(Id)         (SomeIpXf_Config->StructCfgs[Id].LengthFieldSize)
#define SOMEIPXF_ALIGNMENT_OF_STRUCT_CONFIG(Id)                 (SomeIpXf_Config->StructCfgs[Id].Alignment)
#define SOMEIPXF_ENDIAN_OF_STRUCT_CONFIG(Id)                    (SomeIpXf_Config->StructCfgs[Id].Endian)
#define SOMEIPXF_TAG_OF_STRUCT_CONFIG(Id)                       (SomeIpXf_Config->StructCfgs[Id].Tag)
#define SOMEIPXF_VALID_OF_TAG_OF_STRUCT_CONFIG(Id)              (SOMEIPXF_VALID_OF_TAG(SOMEIPXF_TAG_OF_STRUCT_CONFIG(Id)))
#define SOMEIPXF_WIRETYPE_OF_TAG_OF_STRUCT_CONFIG(Id)           (SOMEIPXF_WIRETYPE_OF_TAG(SOMEIPXF_TAG_OF_STRUCT_CONFIG(Id)))
#define SOMEIPXF_MEMBER_NUMBER_OF_STRUCT_CONFIG(Id)             (SomeIpXf_Config->StructCfgs[Id].MemberNumber)
#define SOMEIPXF_MEMBERS_OF_STRUCT_CONFIG(Id)                   (SomeIpXf_Config->StructCfgs[Id].Members)
#define SOMEIPXF_KIND_OF_MEMBER_OF_STRUCT_CONFIG(Id, MemberId)  (SOMEIPXF_KIND_OF_MEMBER_CONFIG(SOMEIPXF_MEMBERS_OF_STRUCT_CONFIG(Id)[MemberId]))
#define SOMEIPXF_DATA_OF_MEMBER_OF_STRUCT_CONFIG(Id, MemberId)  (SOMEIPXF_DATA_OF_MEMBER_CONFIG(SOMEIPXF_MEMBERS_OF_STRUCT_CONFIG(Id)[MemberId]))
#define SOMEIPXF_DATA_OFFSET_OF_MEMBER_OF_STRUCT_CONFIG(Id, MemberId)                           \
    (SOMEIPXF_DATA_OFFSET_OF_MEMBER_CONFIG(SOMEIPXF_MEMBERS_OF_STRUCT_CONFIG(Id)[MemberId]))
#define SOMEIPXF_SPECIAL_SIZE_OF_MEMBER_OF_STRUCT_CONFIG(Id, MemberId)                          \
    (SOMEIPXF_SPECIAL_SIZE_OF_MEMBER_CONFIG(SOMEIPXF_MEMBERS_OF_STRUCT_CONFIG(Id)[MemberId]))
#define SOMEIPXF_SPECIAL_OFFSET_OF_MEMBER_OF_STRUCT_CONFIG(Id, MemberId)                        \
    (SOMEIPXF_SPECIAL_OFFSET_OF_MEMBER_CONFIG(SOMEIPXF_MEMBERS_OF_STRUCT_CONFIG(Id)[MemberId]))

#define SOMEIPXF_KIND_OF_STRING_FIXED_CONFIG(Id)                (SomeIpXf_Config->StringFixedCfgs[Id].Kind)
#define SOMEIPXF_LENGTH_OF_STRING_FIXED_CONFIG(Id)              (SomeIpXf_Config->StringFixedCfgs[Id].Length)
#define SOMEIPXF_ALIGNMENT_OF_STRING_FIXED_CONFIG(Id)           (SomeIpXf_Config->StringFixedCfgs[Id].Alignment)
#define SOMEIPXF_CONVERT_OF_STRING_FIXED_CONFIG(Id)             (SomeIpXf_Config->StringFixedCfgs[Id].Convert)
#define SOMEIPXF_TAG_OF_STRING_FIXED_CONFIG(Id)                 (SomeIpXf_Config->StringFixedCfgs[Id].Tag)
#define SOMEIPXF_VALID_OF_TAG_OF_STRING_FIXED_CONFIG(Id)        (SOMEIPXF_VALID_OF_TAG(SOMEIPXF_TAG_OF_STRING_FIXED_CONFIG(Id)))
#define SOMEIPXF_WIRETYPE_OF_TAG_OF_STRING_FIXED_CONFIG(Id)     (SOMEIPXF_WIRETYPE_OF_TAG(SOMEIPXF_TAG_OF_STRING_FIXED_CONFIG(Id)))

#define SOMEIPXF_KIND_OF_STRING_FLEXED_CONFIG(Id)               (SomeIpXf_Config->StringFlexedCfgs[Id].Kind)
#define SOMEIPXF_LENGTH_MAX_OF_STRING_FLEXED_CONFIG(Id)         (SomeIpXf_Config->StringFlexedCfgs[Id].LengthMax)
#define SOMEIPXF_LENGTH_FIELD_SIZE_OF_STRING_FLEXED_CONFIG(Id)  (SomeIpXf_Config->StringFlexedCfgs[Id].LengthFieldSize)
#define SOMEIPXF_ALIGNMENT_OF_STRING_FLEXED_CONFIG(Id)          (SomeIpXf_Config->StringFlexedCfgs[Id].Alignment)
#define SOMEIPXF_CONVERT_OF_STRING_FLEXED_CONFIG(Id)            (SomeIpXf_Config->StringFlexedCfgs[Id].Convert)
#define SOMEIPXF_TAG_OF_STRING_FLEXED_CONFIG(Id)                (SomeIpXf_Config->StringFlexedCfgs[Id].Tag)
#define SOMEIPXF_VALID_OF_TAG_OF_STRING_FLEXED_CONFIG(Id)       (SOMEIPXF_VALID_OF_TAG(SOMEIPXF_TAG_OF_STRING_FIXED_CONFIG(Id)))
#define SOMEIPXF_WIRETYPE_OF_TAG_OF_STRING_FLEXED_CONFIG(Id)    (SOMEIPXF_WIRETYPE_OF_TAG(SOMEIPXF_TAG_OF_STRING_FIXED_CONFIG(Id)))

#define SOMEIPXF_LENGTH_MAX_OF_ARRAY_CONFIG(Id)                 (SomeIpXf_Config->ArrayCfgs[Id].LengthMax)
#define SOMEIPXF_LENGTH_FIELD_SIZE_OF_ARRAY_CONFIG(Id)          (SomeIpXf_Config->ArrayCfgs[Id].LengthFieldSize)
#define SOMEIPXF_ALIGNMENT_OF_ARRAY_CONFIG(Id)                  (SomeIpXf_Config->ArrayCfgs[Id].Alignment)
#define SOMEIPXF_ENDIAN_OF_ARRAY_CONFIG(Id)                     (SomeIpXf_Config->ArrayCfgs[Id].Endian)
#define SOMEIPXF_TAG_OF_ARRAY_CONFIG(Id)                        (SomeIpXf_Config->ArrayCfgs[Id].Tag)
#define SOMEIPXF_VALID_OF_TAG_OF_ARRAY_CONFIG(Id)               (SOMEIPXF_VALID_OF_TAG(SOMEIPXF_TAG_OF_ARRAY_CONFIG(Id)))
#define SOMEIPXF_WIRETYPE_OF_TAG_OF_ARRAY_CONFIG(Id)            (SOMEIPXF_WIRETYPE_OF_TAG(SOMEIPXF_TAG_OF_ARRAY_CONFIG(Id)))
#define SOMEIPXF_ELEMENT_OF_ARRAY_CONFIG(Id)                    (SomeIpXf_Config->ArrayCfgs[Id].Element)
#define SOMEIPXF_KIND_OF_ELEMENT_OF_ARRAY_CONFIG(Id)            (SOMEIPXF_ELEMENT_OF_ARRAY_CONFIG(Id)->Kind)
#define SOMEIPXF_DATA_OF_ELEMENT_OF_ARRAY_CONFIG(Id)            (SOMEIPXF_ELEMENT_OF_ARRAY_CONFIG(Id)->Data)
#define SOMEIPXF_DATA_OFFSET_OF_MEMBER_OF_ARRAY_CONFIG(Id)      (SOMEIPXF_ELEMENT_OF_ARRAY_CONFIG(Id)->DataOffset)
#define SOMEIPXF_SPECIAL_SIZE_OF_MEMBER_OF_ARRAY_CONFIG(Id)     (SOMEIPXF_ELEMENT_OF_ARRAY_CONFIG(Id)->SpecialSize)
#define SOMEIPXF_SPECIAL_OFFSET_OF_MEMBER_OF_ARRAY_CONFIG(Id)   (SOMEIPXF_ELEMENT_OF_ARRAY_CONFIG(Id)->SpecialOffset)


/****************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 ***************************************************************************************************/
const uint8 SomeIpXf_Utf8Bom[3] = {0xEFU, 0xBBU, 0xBFU};
const uint8 SomeIpXf_Utf16BeBom[2] = {0xFEU, 0xFFU};
const uint8 SomeIpXf_Utf16LeBom[2] = {0xFFU, 0xFEU};


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

Std_ReturnType SomeIpXf_SerializeBase(SomeIpXf_DataType MemberId, void *Value, uint8 *Buffer, uint32 *BufferLength, uint32 Level)
{
    Std_ReturnType Ret = SOMEIPXF_E_OK;
    uint8 LengthNeeded = 0U;
    boolean IsTagValid = FALSE;

    if ((NULL_PTR == Buffer) || (NULL_PTR == Value) || (NULL_PTR == BufferLength))
    {
        Ret = SOMEIPXF_E_PARAM_POINTER;
    }
    else if (MemberId >= SomeIpXf_Config->BaseCfgNumber)
    {
        Ret = SOMEIPXF_E_PARAM;
    }
    else
    {
        LengthNeeded = SOMEIPXF_LENGTH_OF_BASE_CONFIG(MemberId);
        IsTagValid = SOMEIPXF_VALID_OF_TAG_OF_BASE_CONFIG(MemberId);

        /* Reserve room for tag */
        if (TRUE == IsTagValid)
        {
            LengthNeeded = LengthNeeded + SOMEIPXF_TAG_LENGTH;
        }

        /*  Check whether buffer is enough */
        if (*BufferLength < LengthNeeded)
        {
            Ret = SOMEIPXF_E_PARAM;
        }
        else
        {
            /* Check base lenghth fullfill tag wiretype */
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

        /* Construct tag */
        if (TRUE == IsTagValid)
        {
            uint16 Tag = SomeIpXf_ConstructTagType(&SOMEIPXF_TAG_OF_BASE_CONFIG(MemberId));

            Buffer[Position] = SOMEIPXF_16BIT_HB(Tag);
            Position++;
            Buffer[Position] = SOMEIPXF_16BIT_LB(Tag);
            Position++;
        }

        /* Construct data */
        if (SOMEIPXF_ENDIAN_MOTO == SOMEIPXF_ENDIAN_OF_BASE_CONFIG(MemberId))
        {
            for (sint8 Index = (sint8)SOMEIPXF_LENGTH_OF_BASE_CONFIG(MemberId) - 1; Index >= 0; Index--)
            {
                Buffer[Position] = ((uint8 *)Value)[Index];
                Position++;
            }
        }
        else
        {
            for (uint8 Index = 0U; Index < SOMEIPXF_LENGTH_OF_BASE_CONFIG(MemberId); Index++)
            {
                Buffer[Position] = ((uint8 *)Value)[Index];
                Position++;
            }
        }
        *BufferLength = *BufferLength - LengthNeeded;
    }
    return Ret;
}

Std_ReturnType SomeIpXf_SerializeStruct(SomeIpXf_DataType MemberId, void *Value, uint8 *Buffer, uint32 *BufferLength, uint32 Level)
{
    Std_ReturnType Ret = SOMEIPXF_E_OK;
    uint8 LengthNeeded = 0U;
    boolean IsTagValid = FALSE;
    uint8 LengthSize = 0U;

    if ((NULL_PTR == Buffer) || (NULL_PTR == Value) || (NULL_PTR == BufferLength))
    {
        Ret = SOMEIPXF_E_PARAM_POINTER;
    }
    else if (MemberId >= SomeIpXf_Config->StructCfgNumber)
    {
        Ret = SOMEIPXF_E_PARAM;
    }
    else
    {
        LengthNeeded = 0U;
        IsTagValid = SOMEIPXF_VALID_OF_TAG_OF_STRUCT_CONFIG(MemberId);
        LengthSize = SOMEIPXF_LENGTH_FIELD_SIZE_OF_STRUCT_CONFIG(MemberId);

        /* Reserve room for tag */
        if (TRUE == IsTagValid)
        {
            LengthNeeded = LengthNeeded + SOMEIPXF_TAG_LENGTH;
        }
    
        /* Reserve room for lenght field */
        switch (LengthSize)
        {
        case SOMEIPXF_LENGTH_FIELD_SIZE_0BIT:
            break;
        
        case SOMEIPXF_LENGTH_FIELD_SIZE_8BIT:
            LengthNeeded = LengthNeeded + 1U;
            break;
        
        case SOMEIPXF_LENGTH_FIELD_SIZE_16BIT:
            LengthNeeded = LengthNeeded + 2U;
            break;

        case SOMEIPXF_LENGTH_FIELD_SIZE_32BIT:
            LengthNeeded = LengthNeeded + 4U;
            break;

        default:
            Ret = SOMEIPXF_E_PARAM;
            break;
        }

        /* Check whether buffer is enough for minimal length */
        if (*BufferLength < LengthNeeded)
        {
            Ret = SOMEIPXF_E_PARAM;
        }
        else
        {
            /* Check lenght field size fullfill tag wire type */
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
        uint32 Position = 0U;
        uint32 LengthLeft = *BufferLength - LengthNeeded;
        uint32 LengthLeftBackup = LengthLeft;

        /* Construct tag */
        if (TRUE == IsTagValid)
        {
            uint16 Tag = SomeIpXf_ConstructTagType(&SOMEIPXF_TAG_OF_STRUCT_CONFIG(MemberId));

            Buffer[Position] = SOMEIPXF_16BIT_HB(Tag);
            Position++;
            Buffer[Position] = SOMEIPXF_16BIT_LB(Tag);
            Position++;
        }

        Position = LengthNeeded;
        /* Construct every member */
        for (uint32 SubMember = 0U; SubMember < SOMEIPXF_MEMBER_NUMBER_OF_STRUCT_CONFIG(MemberId); SubMember++)
        {
            if (Ret != SOMEIPXF_E_OK)
            {
                break;
            }

            switch (SOMEIPXF_KIND_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember))
            {
            case SOMEIPXF_DATA_KIND_BASE:
                Ret = SomeIpXf_SerializeBase(SOMEIPXF_DATA_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember),
                                       SOMEIPXF_VOID_OFFSET(Value, SOMEIPXF_DATA_OFFSET_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember)),
                                       &Buffer[Position], &LengthLeft, Level - 1U);
                break;
            
            case SOMEIPXF_DATA_KIND_STRUCT:
                Ret = SomeIpXf_SerializeStruct(SOMEIPXF_DATA_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember),
                                         SOMEIPXF_VOID_OFFSET(Value, SOMEIPXF_DATA_OFFSET_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember)),
                                         &Buffer[Position], &LengthLeft, Level - 1U);
                break;

            case SOMEIPXF_DATA_KIND_STRING_FIXED:
                Ret = SomeIpXf_SerializeStringFixed(SOMEIPXF_DATA_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember),
                                              SOMEIPXF_VOID_OFFSET(Value, SOMEIPXF_DATA_OFFSET_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember)),
                                              &Buffer[Position], &LengthLeft, Level - 1U);
                break;

            case SOMEIPXF_DATA_KIND_STRING_FLEXED:
            {
                uint32 MemberLength = 0U;
                uint8 *PtrLength = SOMEIPXF_VOID_OFFSET_U8(Value, SOMEIPXF_SPECIAL_OFFSET_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember));

                switch (SOMEIPXF_SPECIAL_SIZE_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember))
                {
                case 0:
                    break;

                case 1:
                    MemberLength = SOMEIPXF_U8_FROM_PTR_U8(PtrLength);
                    break;

                case 2:
                    MemberLength = SOMEIPXF_U16_FROM_PTR_U8(PtrLength);
                    break;

                case 4:
                    MemberLength = SOMEIPXF_U32_FROM_PTR_U8(PtrLength);
                    break;
                
                default:
                    break;
                }

                if (MemberLength > 0U)
                {
                    Ret = SomeIpXf_SerializeStringFlexed(SOMEIPXF_DATA_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember),
                                                         SOMEIPXF_VOID_OFFSET(Value, SOMEIPXF_DATA_OFFSET_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember)),
                                                         MemberLength, &Buffer[Position], &LengthLeft, Level - 1U);
                }
                else
                {
                    Ret = SOMEIPXF_E_PARAM;
                }
                break;
            }

            case SOMEIPXF_DATA_KIND_ARRAY:
            {
                uint32 ArrayNumber = 0U;
                uint8 *PtrLength = SOMEIPXF_VOID_OFFSET_U8(Value, SOMEIPXF_SPECIAL_OFFSET_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember));

                switch (SOMEIPXF_SPECIAL_SIZE_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember))
                {
                case 0:
                    break;

                case 1:
                    ArrayNumber = SOMEIPXF_U8_FROM_PTR_U8(PtrLength);
                    break;

                case 2:
                    ArrayNumber = SOMEIPXF_U16_FROM_PTR_U8(PtrLength);
                    break;

                case 4:
                    ArrayNumber = SOMEIPXF_U32_FROM_PTR_U8(PtrLength);
                    break;
                
                default:
                    break;
                }

                Ret = SomeIpXf_SerializeArray(SOMEIPXF_DATA_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember),
                                              SOMEIPXF_VOID_OFFSET(Value, SOMEIPXF_DATA_OFFSET_OF_MEMBER_OF_STRUCT_CONFIG(MemberId, SubMember)),
                                              ArrayNumber, &Buffer[Position], &LengthLeft, Level - 1U);
                break;

            default:
                break;
            }
            Position = Position + (LengthLeftBackup - LengthLeft);
            LengthLeftBackup = LengthLeft;
            }    
        }
        /* TODO: support option member */
    }
    return Ret;
}

Std_ReturnType SomeIpXf_SerializeStringFixed(SomeIpXf_DataType MemberId, void *Value, uint8 *Buffer, uint32 *BufferLength, uint32 Level)
{
    Std_ReturnType Ret = SOMEIPXF_E_OK;
    uint32 LengthNeeded = 0U;
    boolean IsTagValid = FALSE;
    uint32 StringLength = 0U;
    uint32 Position = 0U;

    if ((NULL_PTR == Buffer) || (NULL_PTR == Value) || (NULL_PTR == BufferLength))
    {
        Ret = SOMEIPXF_E_PARAM_POINTER;
    }
    else if (MemberId >= SomeIpXf_Config->StringFixedCfgNumber)
    {
        Ret = SOMEIPXF_E_PARAM;
    }
    else
    {
        LengthNeeded = SOMEIPXF_LENGTH_OF_STRING_FIXED_CONFIG(MemberId);
        IsTagValid = SOMEIPXF_VALID_OF_TAG_OF_STRING_FIXED_CONFIG(MemberId);
        StringLength = SOMEIPXF_LENGTH_OF_STRING_FIXED_CONFIG(MemberId);

        /* Reserve room for tag */
        if (TRUE == IsTagValid)
        {
            LengthNeeded = LengthNeeded + SOMEIPXF_TAG_LENGTH;
        }
        Position = LengthNeeded;

        /* Reserve room for string content */
        switch (SOMEIPXF_KIND_OF_STRING_FIXED_CONFIG(MemberId))
        {
        case SOMEIPXF_STRING_KIND_LEGACY:
            if (0x00U == ((uint8 *)Value)[StringLength - 1])
            {
                LengthNeeded = LengthNeeded + StringLength;
            }
            else
            {
                Ret = SOMEIPXF_E_PARAM;
            }
            break;

        case SOMEIPXF_STRING_KIND_UTF8:
            if (0x00U == ((uint8 *)Value)[StringLength - 1])
            {
                LengthNeeded = LengthNeeded + StringLength + SOMEIPXF_UTF8_BOM_LENGTH;
            }
            else
            {
                Ret = SOMEIPXF_E_PARAM;
            }
            break;

        case SOMEIPXF_STRING_KIND_UTF16:
            /* Check if UTF16 is length of even */
            if (0x01U == (StringLength & 0x01U))
            {
                if ((0x00U == ((uint8 *)Value)[StringLength - 1]) && (0x00U == ((uint8 *)Value)[StringLength - 2]))
                {
                    LengthNeeded = LengthNeeded + StringLength + SOMEIPXF_UTF16_BOM_LENGTH;
                }
                else
                {
                    Ret = SOMEIPXF_E_PARAM;
                }
            }
            else
            {
                Ret = SOMEIPXF_E_PARAM;
            }
            break;

        default:
            Ret = SOMEIPXF_E_PARAM;
            break;
        }

        /* Check whether buffer is enough for minimal length */
        if (*BufferLength < LengthNeeded)
        {
            Ret = SOMEIPXF_E_PARAM;
        }
        else
        {
            switch (SOMEIPXF_KIND_OF_STRING_FIXED_CONFIG(MemberId))
            {
            case SOMEIPXF_STRING_KIND_LEGACY:
                for (uint32 Index = 0U; Index < StringLength; Index++)
                {
                    Buffer[Position] = ((uint8 *)Value)[Index];
                    Position++;
                }
                break;

            case SOMEIPXF_STRING_KIND_UTF8:
                Buffer[Position] = SomeIpXf_Utf8Bom[0];
                Position++;
                Buffer[Position] = SomeIpXf_Utf8Bom[1];
                Position++;
                Buffer[Position] = SomeIpXf_Utf8Bom[2];
                Position++;
                for (uint32 Index = 0U; Index < StringLength; Index++)
                {
                    Buffer[Position] = ((uint8 *)Value)[Index];
                    Position++;
                }
                break;

            case SOMEIPXF_STRING_KIND_UTF16:
                if (TRUE == SOMEIPXF_CONVERT_OF_STRING_FIXED_CONFIG(MemberId))
                {
                    Buffer[Position] = SomeIpXf_Utf16BeBom[0];
                    Position++;
                    Buffer[Position] = SomeIpXf_Utf16BeBom[1];
                    Position++;
                    for (uint32 Index = 0U; Index < StringLength; Index++)
                    {
                        if (0x00U == (Index & 0x01))
                        {
                            Buffer[Position + 1] = ((uint8 *)Value)[Index];
                        }
                        else
                        {
                            Buffer[Position - 1] = ((uint8 *)Value)[Index];
                        }
                        Position++;
                    }
                }
                else
                {
                    Buffer[Position] = SomeIpXf_Utf16LeBom[0];
                    Position++;
                    Buffer[Position] = SomeIpXf_Utf16LeBom[1];
                    Position++;
                    for (uint32 Index = 0U; Index < StringLength; Index++)
                    {
                        Buffer[Position] = ((uint8 *)Value)[Index];
                        Position++;
                    }
                    break;
                }
            }
        }
    }
    return Ret;
}

Std_ReturnType SomeIpXf_SerializeStringFlexed(SomeIpXf_DataType MemberId, void *Value, uint32 StringLength, uint8 *Buffer, uint32 *BufferLength, uint32 Level)
{
    Std_ReturnType Ret = SOMEIPXF_E_OK;
    uint32 LengthNeeded = 0U;
    boolean IsTagValid = FALSE;
    uint8 LengthSize = 0U;
    uint32 Position = 0U;
    SomeIpXf_StringKindType Kind = SOMEIPXF_STRING_KIND_LEGACY;

    if ((NULL_PTR == Buffer) || (NULL_PTR == Value) || (NULL_PTR == BufferLength))
    {
        Ret = SOMEIPXF_E_PARAM_POINTER;
    }
    else if ((MemberId >= SomeIpXf_Config->StringFlexedCfgNumber) && (0U == StringLength))
    {
        Ret = SOMEIPXF_E_PARAM;
    }
    else
    {
        IsTagValid = SOMEIPXF_VALID_OF_TAG_OF_STRING_FLEXED_CONFIG(MemberId);
        LengthSize = SOMEIPXF_LENGTH_FIELD_SIZE_OF_STRING_FLEXED_CONFIG(MemberId);
        Kind = SOMEIPXF_KIND_OF_STRING_FLEXED_CONFIG(MemberId);

        /* Reserve room for tag */
        if (TRUE == IsTagValid)
        {
            LengthNeeded = LengthNeeded + SOMEIPXF_TAG_LENGTH;
        }

        /* Reserve room for length field */
        switch (LengthSize)
        {
        case SOMEIPXF_LENGTH_FIELD_SIZE_0BIT:
            break;
        
        case SOMEIPXF_LENGTH_FIELD_SIZE_8BIT:
            LengthNeeded = LengthNeeded + 1U;
            break;
        
        case SOMEIPXF_LENGTH_FIELD_SIZE_16BIT:
            LengthNeeded = LengthNeeded + 2U;
            break;

        case SOMEIPXF_LENGTH_FIELD_SIZE_32BIT:
            LengthNeeded = LengthNeeded + 4U;
            break;

        default:
            Ret = SOMEIPXF_E_PARAM;
            break;
        }
        Position = LengthNeeded;

        /* Reserve room for string content */
        switch (Kind)
        {
        case SOMEIPXF_STRING_KIND_LEGACY:
            if (0x00 == ((uint8 *)Value)[StringLength - 1])
            {
                LengthNeeded = LengthNeeded + StringLength;
            }
            else
            {
                Ret = SOMEIPXF_E_PARAM;
            }
            break;

        case SOMEIPXF_STRING_KIND_UTF8:
            if (0x00 == ((uint8 *)Value)[StringLength - 1])
            {
                LengthNeeded = LengthNeeded + StringLength + SOMEIPXF_UTF8_BOM_LENGTH;
            }
            else
            {
                Ret = SOMEIPXF_E_PARAM;
            }
            break;

        case SOMEIPXF_STRING_KIND_UTF16:
            /* Check if UTF16 is length of even */
            if (0x01U == ((StringLength) & 0x01U))
            {
                if ((0x00 == ((uint8 *)Value)[StringLength - 1]) && (0x00 == ((uint8 *)Value)[StringLength - 2]))
                {
                    LengthNeeded = LengthNeeded + StringLength + SOMEIPXF_UTF16_BOM_LENGTH;
                }
                else
                {
                    Ret = SOMEIPXF_E_PARAM;
                }
            }
            else
            {
                Ret = SOMEIPXF_E_PARAM;
            }
            break;

        default:
            Ret = SOMEIPXF_E_PARAM;
            break;
        }

        /* Check whether buffer is enough for minimal length */
        if (*BufferLength < LengthNeeded)
        {
            Ret = SOMEIPXF_E_PARAM;
        }
        else
        {
            switch (Kind)
            {
            case SOMEIPXF_STRING_KIND_LEGACY:
                for (uint32 Index = 0U; Index < StringLength; Index++)
                {
                    Buffer[Position] = ((uint8 *)Value)[Index];
                    Position++;
                }
                break;

            case SOMEIPXF_STRING_KIND_UTF8:
                Buffer[Position] = SomeIpXf_Utf8Bom[0];
                Position++;
                Buffer[Position] = SomeIpXf_Utf8Bom[1];
                Position++;
                Buffer[Position] = SomeIpXf_Utf8Bom[2];
                Position++;
                for (uint32 Index = 0U; Index < StringLength; Index++)
                {
                    Buffer[Position] = ((uint8 *)Value)[Index];
                    Position++;
                }
                break;

            case SOMEIPXF_STRING_KIND_UTF16:
                if (TRUE == SOMEIPXF_CONVERT_OF_STRING_FLEXED_CONFIG(MemberId))
                {
                    for (uint32 Index = 0U; Index < StringLength; Index++)
                    {
                        if (0x00U == (Index & 0x01))
                        {
                            Buffer[Position + 1] = ((uint8 *)Value)[Index];
                        }
                        else
                        {
                            Buffer[Position - 1] = ((uint8 *)Value)[Index];
                        }
                        Position++;
                    }
                }
                else
                {
                    Buffer[Position] = SomeIpXf_Utf16LeBom[0];
                    Position++;
                    Buffer[Position] = SomeIpXf_Utf16LeBom[1];
                    Position++;
                    for (uint32 Index = 0U; Index < StringLength; Index++)
                    {
                        Buffer[Position] = ((uint8 *)Value)[Index];
                        Position++;
                    }
                }
                break;

            default:
                Ret = SOMEIPXF_E_PARAM;
                break;
            }
        }
    }
    return Ret;
}

Std_ReturnType SomeIpXf_SerializeArray(SomeIpXf_DataType MemberId, void *Value, uint32 ArrayNumber, uint8 *Buffer, uint32 *BufferLength, uint32 Level)
{
    Std_ReturnType Ret = SOMEIPXF_E_OK;
    uint32 LengthNeeded = 0U;
    boolean IsTagValid = FALSE;
    uint8 LengthSize = 0U;

    if ((NULL_PTR == Buffer) || (NULL_PTR == Value) || (NULL_PTR == BufferLength))
    {
        Ret = SOMEIPXF_E_PARAM_POINTER;
    }
    else if ((MemberId >= SomeIpXf_Config->StringFlexedCfgNumber) && (0U == ArrayNumber))
    {
        Ret = SOMEIPXF_E_PARAM;
    }
    else
    {
        IsTagValid = SOMEIPXF_VALID_OF_TAG_OF_ARRAY_CONFIG(MemberId);
        LengthSize = SOMEIPXF_LENGTH_FIELD_SIZE_OF_ARRAY_CONFIG(MemberId);

        /* Reserve room for tag */
        if (TRUE == IsTagValid)
        {
            LengthNeeded = LengthNeeded + SOMEIPXF_TAG_LENGTH;
        }

        /* Reserve room for length field */
        switch (LengthSize)
        {
        case SOMEIPXF_LENGTH_FIELD_SIZE_0BIT:
            break;
        
        case SOMEIPXF_LENGTH_FIELD_SIZE_8BIT:
            LengthNeeded = LengthNeeded + 1U;
            break;
        
        case SOMEIPXF_LENGTH_FIELD_SIZE_16BIT:
            LengthNeeded = LengthNeeded + 2U;
            break;

        case SOMEIPXF_LENGTH_FIELD_SIZE_32BIT:
            LengthNeeded = LengthNeeded + 4U;
            break;

        default:
            Ret = SOMEIPXF_E_PARAM;
            break;
        }

        /* Check whether buffer is enough for minimal length */
        if (*BufferLength < LengthNeeded)
        {
            Ret = SOMEIPXF_E_PARAM;
        }
        else
        {
            uint32 Position = LengthNeeded;g

            for (uint32 Index = 0U; Index < ArrayNumber; Index++)
            {
                
            }
        }
    }
    return Ret;
}

/****************************************************************************************************
 *  END OF FILE: SomeIp_Serializer.c
 ***************************************************************************************************/
