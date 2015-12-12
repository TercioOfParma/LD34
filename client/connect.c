#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "main.h"
#endif



int connectToServer(int *isSuccess, struct sockaddr_in details, SOCKET soc)
{
	char *message = WELCOME_COMMAND;
	char recieveback[SIZE_WELCOME];
	struct sockaddr_in temp;
	int sizeofTemp = sizeof(temp);
	if(sendto((SOCKET )soc, message, strlen(message), 0, (const struct sockaddr *)&details, sizeof(details)) < 0)
	{
		fprintf(stderr, "Message send has failed : %s \n", WSAGetLastError());
		*isSuccess = FAIL;
		return FAIL;
	
	}
	recvfrom(soc, recieveback, SIZE_WELCOME, 0, &temp, &sizeofTemp);
	fprintf(stderr, "%s\n", recieveback);
	return SUCCESS;
	
}