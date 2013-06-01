/*
 * MsgDef.h
 *
 *  Created on: 2013-5-22
 *      Author: YangQi
 */

#ifndef MSGDEF_H_
#define MSGDEF_H_

enum MsgType
{
	CM_PlayerLoginMsg = 6,
	MC_PlayerLoginSuccess,
};

struct MSGHead
{
	int msgid;
	int clientid;
	int errcode;
	int datalen;
	MSGHead():msgid(0),clientid(0),errcode(0),datalen(0){}
};

struct MsgNewPlayer
{
	MSGHead header;
	char name[16];
	int sex;
};

struct MsgLoginSuccess
{
	MSGHead header;
	char gsip[16];		//game server ip address
	unsigned short	gprot;	//game server port
};

#endif /* MSGDEF_H_ */
