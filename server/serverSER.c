#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "mainSER.h"
#endif


void bindSocket(struct sockaddr_in  serverDetails, SOCKET sock, int *isSuccess)
{
	if(bind(sock, (struct sockaddr *)&serverDetails, sizeof(serverDetails)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Bind server port error : %d\n", WSAGetLastError());
		*isSuccess = FAIL;
		return;
	}


}


void listenForPackets(struct sockaddr_in serverDetails, SOCKET sock, struct sockaddr_in recieved, options *opt, int *isSuccess)
{
	char recievedFrom[SIZE_WELCOME];
	int size = sizeof(recieved);
	fprintf(stderr, "recieved : %s\n", recievedFrom);
	int retlen;
	if(retlen = recvfrom(sock, recievedFrom, SIZE_WELCOME, 0, (struct sockaddr *) &recieved, &size ) == SOCKET_ERROR)
	{
		fprintf(stderr, "recv from port error : %d\n", WSAGetLastError());
		*isSuccess = FAIL;
		return;
	
	}
	fprintf(stderr, "recieved : %s\n", recievedFrom);
	if(strcmp(recievedFrom, WELCOME_COMMAND) == 0)
	{
		sendto(sock, opt->SERVER_WELCOME, strlen(opt->SERVER_WELCOME),0, (const struct sockaddr *)&recieved,sizeof(recieved));
	
	}


}