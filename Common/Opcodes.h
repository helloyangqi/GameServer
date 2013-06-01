/*
 * Opcodes.h
 *
 *  Created on: 2013-5-31
 *      Author: YangQi
 */

#ifndef OPCODES_H_
#define OPCODES_H_

#include "Common.h"

enum Opcodes
{
	MSG_NULL_ACTION	 = 0,
	CMSG_PLAYER_LOGIN,
	SMSG_NEW_WORLD,
	CMSG_PLAYER_LOGOUT,

	NUM_MSG_TYPES
};

enum SessionStatus
{
	STATUS_SUTHED = 0,
	STATUS_LOGGEDIN,
	STATUS_UNHANDLED
};

struct OpcodeHandler
{
	char const* name;
	SessionStatus status;
	void (Session::*handler)(Packet& recvPacket);
};

extern OpcodeHandler opcodeTable[NUM_MSG_TYPES];

inline const char* LookupOpcodeName(uint16 id)
{
	if(id >= NUM_MSG_TYPES)
		return "Received unknown opcode, it's more than max";
	return opcodeTable[id].name;
}

#endif /* OPCODES_H_ */
