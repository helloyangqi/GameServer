#include <signal.h>
#include "Common.h"
#include "ServerCommon.h"
#include "Session.h"


void DestroySignal(int sigNum)
{
	ServerCommon::GetSessionManager()->DisconnectAllClient();
	close(NetLink::listenfd);
}

void InitSignal()
{
	signal(SIGINT,DestroySignal);
	signal(SIGKILL,DestroySignal);
	signal(SIGQUIT,DestroySignal);
	signal(SIGTERM,DestroySignal);
}

int main(int argc,char* argv[])
{
	InitSignal();
	ServerCommon::InitServer();
	NetLink::Init();
	pthread_t accept_tid;
	/*pthread_t read_tid;
	pthread_t write_tid;
	pthread_create(&accept_tid,0,NetLink::AcceptThread,0);
	pthread_create(&read_tid,0,NetLink::ReadThread,0);*/
	pthread_create(&accept_tid,0,NetLink::AcceptThread,0);
	for(;;)
		sleep(10);

	pthread_join(accept_tid,0);
	return 0;
}
