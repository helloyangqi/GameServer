/*
 * ServerCommon.h
 *
 *  Created on: 2013-5-21
 *      Author: YangQi
 */

#ifndef SERVERCOMMON_H_
#define SERVERCOMMON_H_

#include "PlayerManager.h"
#include "SessionManager.h"
#include "NetLink.h"

static NetLink sgNetlink;

class ServerCommon
{
public:
	ServerCommon();
	~ServerCommon();

	static void init();
	static PlayerManager* GetPlayerManager();
	static SessionManager* GetSessionManager();
	static int InitServer();

};


#endif /* SERVERCOMMON_H_ */
