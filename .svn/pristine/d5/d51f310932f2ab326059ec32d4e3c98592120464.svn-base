/*
 * NetLink.cpp
 *
 *  Created on: 2013-5-21
 *      Author: YangQi
 */

#include "NetLink.h"
#include "ServerCommon.h"
#include "Common.h"
#include "MsgDef.h"


int NetLink::epfd = 0;
int NetLink::listenfd = 0;
struct epoll_event NetLink::events[MAX_EVENT_NUM];
NetLink::NetLink()
{

}

NetLink::~NetLink()
{
	close(listenfd);
}

int NetLink::Init()
{
	struct epoll_event ev;
	epfd = epoll_create(MAX_EPOLL_SIZE);
	struct sockaddr_in serveraddr;

	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		printerr("socket ERROR");
		exit(1);
	}
	int i = 1;
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(i));
	SetNoBlock(listenfd);
	ev.data.fd = listenfd;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
	memset((void*)&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(SERVER_PORT);
	if(0 != bind(listenfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)))
	{
		printerr("bind socket error");
		exit(1);
	}
	if(0 != listen(listenfd,SOMAXCONN))
	{
		printerr("listen socket error ");
		exit(1);
	}
	return 0;
}

void* NetLink::AcceptThread(void *arg)
{
	struct sockaddr_in clientaddr;
	SessionManager *sessionManager = ServerCommon::GetSessionManager();
	for(;;)
	{
		int nfds  = epoll_wait(epfd,events,MAX_EVENT_NUM,500);
		for(int i=0;i < nfds;++i)
		{
			if(events[i].data.fd == listenfd)	//new client connect server
			{
				if(events[i].events & EPOLLIN)
				{
					socklen_t clientlen = (socklen_t)sizeof(clientaddr);
					int connfd = accept(listenfd,(struct sockaddr*)&clientaddr,&clientlen);
					if(connfd < 0)
					{
						printerr("connect fd is error");
						exit(1);
					}
					SetNoBlock(connfd);
					struct epoll_event connev;
					connev.data.fd = connfd;
					connev.events = EPOLLIN | EPOLLET;
					epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&connev);
				}
			}
			else if(events[i].events & EPOLLIN)		//received data from client
			{
				if(events[i].data.fd < 0)
					continue;
				Session *s = new Session(events[i].data.fd);
				if(!s->RecvData())
				{
					close(events[i].data.fd);
					continue;
				}
				sessionManager->AddSession(s);
			}
			else if(events[i].events & EPOLLOUT)
			{
				sessionManager->SendSessionData(events[i].data.fd);
			}

			else if((events[i].events & EPOLLERR ) || (events[i].events & EPOLLHUP))
			{
				printerr("socket is error");
				close(events[i].data.fd);
			}
		}
	}
	return 0;
}
/*
void* NetLink::ReadThread(void *arg)
{
	SessionManager *sessionManager = ServerCommon::GetSessionManager();
	for(;;)
	{
		int nfds  = epoll_wait(epfd,events,MAX_EVENT_NUM,500);
		for(int i=0;i < nfds;++i)
		{
			if((events[i].events & EPOLLIN) && events[i].data.fd != listenfd)		//received data from client
			{
				if(events[i].data.fd < 0)
					continue;
				Session *s = new Session(events[i].data.fd);
				if(!s->RecvData())
				{
					close(events[i].data.fd);
					continue;
				}
				sessionManager->AddSession(s);
			}
		}
	}
	return 0;
}

void* NetLink::WriteThread(void *arg)
{
	SessionManager *sessionManager = ServerCommon::GetSessionManager();
	for(;;)
	{
		int nfds  = epoll_wait(epfd,events,MAX_EVENT_NUM,500);
		for(int i=0;i < nfds;++i)
		{
			if(events[i].events & EPOLLOUT)
			{
				sessionManager->SendSessionData(events[i].data.fd);
			}
		}
	}
	return 0;
}
*/
void NetLink::SetNoBlock(int socket)
{
	int opts;
	opts = fcntl(socket,F_GETFL);
	if(opts < 0)
	{
		printerr("get fcntl  error");
		exit(1);
	}
	opts |= O_NONBLOCK;
	if(fcntl(socket,F_SETFL,opts)<0)
	{
		printerr("set fcntl error");
		exit(1);
	}
}

