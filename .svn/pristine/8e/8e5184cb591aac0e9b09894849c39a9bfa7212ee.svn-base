/*
 * NetLink.h
 *
 *  Created on: 2013-5-21
 *      Author: YangQi
 */

#ifndef NETLINK_H_
#define NETLINK_H_
#include <iostream>

#define SERVER_PORT	7878
#define MAX_EVENT_NUM 1024
#define MAX_EPOLL_SIZE  1024
#define EPOLL_TIMEOUT	5000

class NetLink
{
public:
	NetLink();
	~NetLink();
	static int Init();
	static void* AcceptThread(void *arg);
	static void* ReadThread(void *arg);
	static void* WriteThread(void *arg);
	static void SetNoBlock(int socket);

public:
	static int epfd;
	static struct epoll_event events[MAX_EVENT_NUM];
	static int listenfd, nfds;
};


#endif /* NETLINK_H_ */
