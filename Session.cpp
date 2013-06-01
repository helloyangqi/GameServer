/*
 * Session.cpp
 *
 *  Created on: 2013-5-22
 *      Author: YangQi
 */
#include "Session.h"
#include "MsgDef.h"
#include "DBService.h"
#include "NetLink.h"
#include "ServerCommon.h"


Session::Session(int sockfd)
:m_sockfd(sockfd)
,m_recvSize(0)
,m_sendSize(0)
{

}

Session::~Session()
{

}

bool Session::RecvData()
{
	int recvSize;
	char recvBuff[MAX_BUFF_DATA];
	recvSize = recv(m_sockfd,recvBuff,MAX_BUFF_DATA,0);
	if(recvSize == 0)
		return false;
	if(recvSize < 0)
	{
		if(errno == EWOULDBLOCK)
			return true;
		return false;
	}
	if( (m_recvSize + recvSize) >= MAX_BUFF_DATA)
		return false;
	memcpy(&m_recvBuff[m_recvSize],recvBuff,recvSize);
	m_recvSize += recvSize;
	return true;
}


void Session::SendData(const char *data,int size)
{
	if((m_sendSize + size) > MAX_BUFF_DATA)
		return ;
	memcpy((void*)&m_sendBuff[m_sendSize],(void*)data,size);
	m_sendSize += size;
}

int Session::FlushSendBuff()
{
	int sendSize;
	sendSize = send(m_sockfd,m_sendBuff,m_sendSize,0);
	if(sendSize <= 0)
		return  -1;
	if(sendSize < m_sendSize)
	{
		memmove((void *)&m_sendBuff[0],(void*)&m_sendBuff[sendSize],m_sendSize - sendSize);
		m_sendSize -= sendSize;
	}
	else
	{
		m_sendBuff[0] = '\0';
		m_sendSize = 0;
	}
	return sendSize;
}
int i = 1;

void Session::ProcessSession()
{
	MSGHead *msghead = (struct MSGHead*)m_recvBuff;
	if(!msghead)
		return ;
	switch(msghead->msgid)
	{
	case CM_PlayerLoginMsg:
	{
		std::cout<<i++<<std::endl;
		MsgPlayerLoginHandle();
		break;
	}
	default:
		break;

	}
}

void Session::MsgPlayerLoginHandle()
{
	MsgNewPlayer *msg = (struct MsgNewPlayer*)m_recvBuff;
	if(!msg)	return ;
	DBService::SearchPlayerInfo(msg->name,msg->sex);
	char ip[] = "192.168.0.222";
	MsgLoginSuccess sendMsg;
	sendMsg.header.msgid = MC_PlayerLoginSuccess;
	memcpy(sendMsg.gsip,ip,sizeof(ip));
	sendMsg.gprot = 2010;
	SendData((char*)&sendMsg,sizeof(sendMsg));
}


/*
bool Session::Update()
{
	DataPacket *packet = NULL
	while(packet = GetTopPacket())
	{
		OpcodeHandler const& opHandle = opcodeTable[packet->GetOpcode];

	}
}
*/
