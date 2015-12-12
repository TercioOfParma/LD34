#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "mainSER.h"
#endif

int main(int argc, char *argv[])
{
	char *jsonOptions;
	options opt;
	unitData **sides[NO_SIDES];
	node **map;
	WSADATA winsockStuff;
	SOCKET sock;
	struct sockaddr_in serverDeets, user;
	int isSuccess = SUCCESS;
	int i;
	fprintf(stderr, "-------CARPAL TUNNEL CRUSADERS 1.0 ----------\n");
	
	jsonOptions = loadJsonFile(OPTIONS_FILE, &isSuccess);
	opt = initOptions(jsonOptions, &isSuccess);
	winsockStuff = startWinsock(&isSuccess);
	sock = initSocket(&isSuccess);
	serverDeets = getServerDetails(&opt, &isSuccess);
	bindSocket(serverDeets, sock, &isSuccess);
	map = initNodes(&isSuccess);
	for(i = 0; i < NO_SIDES; i++)
	{
		sides[i] = initUnits(&isSuccess);
	
	}
	
	while(isSuccess == SUCCESS)
	{
		listenForPackets(serverDeets,sock,user, &opt, &isSuccess);
	
	}
	for(i = 0; i < NO_SIDES; i++)
	{
		deinitUnits(sides[i]);
	
	}
	deinitNodes(map);
	closesocket(sock);
	deinit();
	return 0;

}