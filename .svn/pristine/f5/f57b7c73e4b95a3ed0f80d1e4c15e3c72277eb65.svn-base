/*
 * SessionManager.cpp
 *
 *  Created on: 2013-5-21
 *      Author: YangQi
 */

#include "SessionManager.h"
#include "ServerCommon.h"


void* ProcessSessionThread(void *arg)
{
	SessionManager *sessionManager = ServerCommon::GetSessionManager();
	for(;;)
	{
		sessionManager->UpdateSession();
	}
	return 0;
}

SessionManager::SessionManager()
{
	pthread_mutex_init(&m_ExcuteLock,0);
	pthread_mutex_init(&m_SendLock,0);
	pthread_create(&m_etid,0,ProcessSessionThread,0);		//process event thread
	//pthread_create(&m_etid2,0,process_event_thread2,0);
}


void SessionManager::UpdateSession()
{
	pthread_mutex_lock(&m_ExcuteLock);
	if(m_ExcuteSessions.empty())
		pthread_cond_wait(&m_connid,&m_ExcuteLock);
	map<int,Session*>::iterator iter ;
	for(iter = m_ExcuteSessions.begin();iter != m_ExcuteSessions.end();)
	{
		iter->second->ProcessSession();

		pthread_mutex_lock(&m_SendLock);
		m_SendSessions.insert(make_pair(iter->first,iter->second));
		pthread_mutex_unlock(&m_SendLock);

		struct epoll_event ev;
		ev.data.fd = iter->first;
		ev.events = EPOLLOUT | EPOLLET;
		epoll_ctl(NetLink::epfd,EPOLL_CTL_MOD,iter->first,&ev);
		m_ExcuteSessions.erase(iter++);
	}
	//std::cout<<"Excuet size:"<<m_ExcuteSessions.size()<<std::endl;
	pthread_mutex_unlock(&m_ExcuteLock);
}

void SessionManager::AddSession(Session *session)
{
	pthread_mutex_lock(&m_ExcuteLock);
	m_ExcuteSessions.insert(make_pair(session->m_sockfd,session));
	//pthread_cond_signal(&m_connid);
	pthread_cond_broadcast(&m_connid);
	pthread_mutex_unlock(&m_ExcuteLock);
}

void SessionManager::SendSessionData(int sockfd)
{
	pthread_mutex_lock(&m_SendLock);
	if(m_SendSessions.empty())
		return ;
	map<int,Session*>::iterator iter = m_SendSessions.find(sockfd);
	if(iter == m_SendSessions.end())
		return ;
	//std::cout<<"send size:"<<m_SendSessions.size()<<std::endl;
	if(iter->second->FlushSendBuff() < 0)
	{
		delete iter->second;
		m_SendSessions.erase(iter);
	}
	//如果长链接就不用释放 直到client不在线
	delete iter->second;
	m_SendSessions.erase(iter);
	close(sockfd);
	pthread_mutex_unlock(&m_SendLock);
}

SessionManager::~SessionManager()
{
	pthread_mutex_destroy(&m_ExcuteLock);
	pthread_mutex_destroy(&m_SendLock);
}

void SessionManager::DisconnectAllClient()
{
	map<int,Session*>::iterator iter ;
	for(iter = m_ExcuteSessions.begin();iter != m_ExcuteSessions.end();iter++)
	{
		close(iter->first);
	}
	for(iter = m_SendSessions.begin();iter != m_SendSessions.end();iter++)
	{
		close(iter->first);
	}
}
