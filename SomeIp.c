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
 * @file    Filename:           SomeIp.c
 * @date    Date:               2023-06-16
 * @version Version:            0.0.1
 * @brief   Description:        Source file of SOME/IP implementation
 ***************************************************************************************************/
/****************************************************************************************************
 *  INCLUDES
 ***************************************************************************************************/

#include "SomeIp.h"

/****************************************************************************************************
 *  LOCAL CONSTANT MACROS
 ***************************************************************************************************/



/****************************************************************************************************
 *  LOCAL FUNCTION MACROS
 ***************************************************************************************************/
#define SOMEIP_CONSTRUCT_U32(hh, hl, lh, ll)    (((hh) << 24) | ((hl) << 16) | ((lh) << 8) | (ll))


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
static void SomeIp_ConstructHeadWithoutLength(const SomeIp_HeadType *head, uint8 *buffer);
static void SomeIp_ConstructHead(const SomeIp_HeadType *head, uint8 *buffer);
static void SomeIp_ParseHead(SomeIp_HeadType *head, const uint8 *buffer);
static SomeIp_MessageIdType SomeIp_ParseMessageId(uint32 Value);
static SomeIp_RequestIdType SomeIp_ParseRequestId(uint32 Value);

/****************************************************************************************************
 *  FUNCTION IMPLEMETATION
 ***************************************************************************************************/
static INLINE void SomeIp_ConstructHeadWithoutLength(const SomeIp_HeadType *head, uint8 *buffer)
{
    uint32 *cursor = (uint32 *)buffer;

    cursor[0] = head->MessageId;
    cursor[2] = head->RequestId;
    cursor[3] = SOMEIP_CONSTRUCT_U32(head->ProtocolVersion, head->InterfaceVersion, 
                                     head->MessageType, head->ReturnCode);
}

static INLINE void SomeIp_ConstructHead(const SomeIp_HeadType *head, uint8 *buffer)
{
    uint32 *cursor = (uint32 *)buffer;

    SomeIp_ConstructHeadWithoutLength(head, buffer);
    cursor[1] = head->Length;
}

static INLINE void SomeIp_ParseHead(SomeIp_HeadType *head, const uint8 *buffer)
{
    uint32 *cursor = (uint32 *)buffer;

    head->MessageId = cursor[0];
    head->Length = cursor[1];
    head->RequestId = cursor[2];
    head->ProtocolVersion = buffer[12];
    head->InterfaceVersion = buffer[13];
    head->MessageType = buffer[14];
    head->ReturnCode = buffer[15];    
}

static INLINE SomeIp_MessageIdType SomeIp_ParseMessageId(uint32 Value)
{
    SomeIp_MessageIdType MessageId =
    {
        .ServideId = (uint16)(Value >> 16),
        .MethodId = (uint16)Value
    };
    return MessageId;
}

static INLINE SomeIp_RequestIdType SomeIp_ParseRequestId(uint32 Value)
{
    SomeIp_RequestIdType RequestId =
    {
        .ClientId = (uint16)(Value >> 16),
        .SessionId = (uint16)Value
    };
    return RequestId;
}

/****************************************************************************************************
 *  END OF FILE: SomeIp.c
 ***************************************************************************************************/
