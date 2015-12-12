#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "mainSER.h"
#endif

int main(int argc, char *argv[])
{
	char *jsonOptions;
	options opt;
	unitData **sides[NO_SIDES];
	
	WSADATA winsockStuff;
	SOCKET sock;
	struct sockaddr_in serverDeets, user;
	int isSuccess = SUCCESS;
	
	jsonOptions = loadJsonFile(OPTIONS_FILE, &isSuccess);
	opt = initOptions(jsonOptions, &isSuccess);
	winsockStuff = startWinsock(&isSuccess);
	sock = initSocket(&isSuccess);
	serverDeets = getServerDetails(&opt, &isSuccess);
	bindSocket(serverDeets, sock, &isSuccess);
	fprintf(stderr, "%d", isSuccess);
	while(isSuccess == SUCCESS)
	{
		listenForPackets(serverDeets,sock,user, &opt, &isSuccess);
	
	}
	deinit();
	return 0;

}