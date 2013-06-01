/*
 * Session.h
 *
 *  Created on: 2013-5-22
 *      Author: YangQi
 */

#ifndef SESSION_H_
#define SESSION_H_

#include "Common.h"

#define MAX_BUFF_DATA 10240

class Session
{
public:
	Session(int sockfd);
	~Session();

	bool 	RecvData();
	int 	FlushSendBuff();
	void 	SendData(const char *data,int size);
	void 	ProcessSession();
	void	MsgPlayerLoginHandle();
public:
	int 	m_sockfd;

private:
	char	m_recvBuff[MAX_BUFF_DATA];
	int 	m_recvSize;
	//int 	m_recvPos;

	char	m_sendBuff[MAX_BUFF_DATA];
	int		m_sendSize;
};


#endif /* SESSION_H_ */
