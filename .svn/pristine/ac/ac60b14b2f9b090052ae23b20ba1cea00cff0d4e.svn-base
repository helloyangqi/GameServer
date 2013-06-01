/*
 * SessionManager.h
 *
 *  Created on: 2013-5-21
 *      Author: YangQi
 */

#ifndef SessionManager_H_
#define SessionManager_H_

#include <pthread.h>
#include "Common.h"
#include <tr1/unordered_map>

class SessionManager
{
public:
	SessionManager();
	~SessionManager();

	void AddSession(Session *session);
	void UpdateSession();
	void SendSessionData(int sockfd);
	void DisconnectAllClient();
private:
	pthread_mutex_t m_ExcuteLock,m_SendLock;
	std::tr1::unordered_map<int,Session*> m_ExcuteSessions;
	std::tr1::unordered_map<int,Session*> m_SendSessions;
	pthread_cond_t m_connid;
	pthread_t m_etid;	//process event thread
};


#endif /* SessionManager_H_ */
