/*
 * Opcodes.cpp
 *
 *  Created on: 2013-5-31
 *      Author: YangQi
 */

#include "Opcodes.h"
#include "Session.h"

OpcodeHandler opcodeTable[NUM_MSG_TYPES] =
{
		{"MSG_NULL_ACTION",			STATUS_NEVER,		&Session::Handle_NULL					},
		{"STATUS_LOGGEDIN",			STATUS_AUTHED,		&Session::HandlePlayerLoginOpcode		},
		{"SMSG_NEW_WORLD",			STATUS_NEVER,		&Session::Handle_ServerSide				},
		{"CMSG_PLAYER_LOGOUT",		STATUS_LOGGEDIN,	&Session::HandlePlayerLogoutOpcode		}
};
