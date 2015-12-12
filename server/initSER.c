#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "mainSER.h"
#endif



char *loadJsonFile(const char *filename, int *success)
{
	FILE *jsonFile = fopen(filename, "rb");
	int fileSize, result, looper;
	char *fileContents, *truncatedContents;
	if(!jsonFile)
	{
		fprintf(stderr, "fopen has failed : %s \n", strerror(errno));
		*success = FAIL;
		return NULL;
	}
	fileSize = getFileSize(jsonFile, success);
	if(!fileSize)
	{
		return NULL;
	
	}
	fileContents = malloc(sizeof(char) * fileSize);
	if(!fileContents)
	{
		fprintf(stderr, "malloc has failed : %s", strerror(errno));
		*success = FAIL;
		return NULL;
	
	}
	fread(fileContents,1,fileSize, jsonFile);
	fileContents[fileSize] = '\0';
	return fileContents;
}
int getFileSize(FILE *sizeToGet, int *success)
{
	int fileSize = 0;
	fseek(sizeToGet,0,SEEK_END);
	fileSize = ftell(sizeToGet);
	rewind(sizeToGet);
	if(errno > 0)
	{
		fprintf(stderr, "ftell has failed : %s", strerror(errno));
		*success = FAIL;
		return 0;
	}
	return fileSize;

}

void deinit()
{
	WSACleanup();
}

WSADATA startWinsock(int *success)
{
	WSADATA temp;
	if(WSAStartup(MAKEWORD(2,2), &temp) != 0)
	{
		fprintf(stderr, "WSAStartup has failed : %s \n", WSAGetLastError());
		*success = FAIL;
		return temp;

	}
	return temp;
}
options initOptions(const char *jsonFile, int *success)
{
	options tempOpt;
	json_t *tempJsonHandle, *optionsData;
	json_error_t errorHandle;
	tempJsonHandle = json_loads(jsonFile, 0,&errorHandle);
	if(!tempJsonHandle)
	{
		fprintf(stderr, "json_loads has failed : %s \n", errorHandle.text);
		*success = FAIL;
		return tempOpt;
	
	}
	
	optionsData = json_array_get(tempJsonHandle, 0);
	if(!json_is_object(optionsData))
	{
		fprintf(stderr,"json_object_get failed, didn't get an object\n");
		*success = FAIL;
		json_decref(tempJsonHandle);
		return tempOpt;
	
	}
	tempOpt.SERVER_NAME = json_string_value(json_object_get(optionsData,"SERVER_NAME"));
	tempOpt.SERVER_WELCOME = json_string_value(json_object_get(optionsData,"SERVER_WELCOME"));
	tempOpt.PORT_ADDRESS = json_integer_value(json_object_get(optionsData,"PORT_ADDRESS"));

	return tempOpt;
}
SOCKET initSocket(int *success)
{
	SOCKET temp;
	temp = socket(AF_INET, SOCK_DGRAM, 0);
	if(!temp)
	{
		fprintf(stderr, "socket has failed : %d\n", WSAGetLastError());
		*success = FAIL;
		return temp;
	}

	return temp;
}

struct sockaddr_in getServerDetails(options *opt, int *success)
{
		struct sockaddr_in temp;
		temp.sin_family = AF_INET;
		temp.sin_addr.s_addr = INADDR_ANY;
		temp.sin_port = htons(opt->PORT_ADDRESS);

		return temp;

}