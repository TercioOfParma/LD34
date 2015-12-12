#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "main.h"
#endif



char *connectToServer(int *isSuccess, struct sockaddr_in details, SOCKET soc)
{
	char *message = WELCOME_COMMAND;
	char recieveback[SIZE_WELCOME];
	char *returner;
	struct sockaddr_in temp;
	int sizeofTemp = sizeof(temp);
	int sizeofMsg;
	if(sendto((SOCKET )soc, message, strlen(message), 0, (const struct sockaddr *)&details, sizeof(details)) < 0)
	{
		fprintf(stderr, "Message send has failed : %s \n", WSAGetLastError());
		*isSuccess = FAIL;
		return FAIL_COMMAND;
	
	}
	recvfrom(soc, recieveback, SIZE_WELCOME, 0, &temp, &sizeofTemp);
	recvfrom(soc, &sizeofMsg, sizeof(int), 0, &temp, &sizeofTemp);
	sizeofMsg = ntohl(sizeofMsg);
	recieveback[sizeofMsg] = '\0';
	returner = recieveback;
	fprintf(stderr, "%s\n", returner);
	return returner;
	
}