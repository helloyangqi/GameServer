/*
 * ServerCommon.cpp
 *
 *  Created on: 2013-5-21
 *      Author: YangQi
 */
#include "ServerCommon.h"
#include "DBService.h"

static PlayerManager	*sgPlayerManager = 0;
static SessionManager 	*sgSessionManager = 0;


void ServerCommon::init()
{
	sgPlayerManager = new PlayerManager;
	sgSessionManager = new SessionManager;
}

PlayerManager* ServerCommon::GetPlayerManager()
{
	if(sgPlayerManager == 0)
		sgPlayerManager = new PlayerManager;
	return sgPlayerManager;
}

SessionManager* ServerCommon::GetSessionManager()
{
	if(sgSessionManager == 0)
		sgSessionManager = new SessionManager;
	return sgSessionManager;
}


int ServerCommon::InitServer()
{
	if(DBService::InitDataBase() == -1)
	{
		exit(1);
	}
	return 0;
}
