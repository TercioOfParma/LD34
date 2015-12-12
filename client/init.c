#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "main.h"
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
SDL_Window *initSDL(options *opt, int *success)
{

	SDL_Window *temp;
	int SDL_Flags, IMG_Flags;
	SDL_Flags = SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO;
	IMG_Flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if(SDL_Init(SDL_Flags) < 0)
	{
		fprintf(stderr, "SDL_Init has failed : %s \n", SDL_GetError());
		*success = FAIL;
		return NULL;
	}
	if(TTF_Init() != 0)
	{
		fprintf(stderr, "TFF_Init has failed : %s \n", TTF_GetError());
		*success = FAIL;
		return NULL;
	}
	temp = SDL_CreateWindow(opt->TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, opt->SCREEN_WIDTH, opt->SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(!temp)
	{
		fprintf(stderr, "SDL_CreateWindow has failed : %s \n");
		*success = FAIL;
		return NULL;
	
	}
	
	return temp;



}
void deinit()
{
	TTF_Quit();
	SDL_Quit();
	WSACleanup();
}

SDL_Renderer *createRenderer(SDL_Window *screen, int *success)
{
	SDL_Renderer *temp;
	int Render_Flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	temp = SDL_CreateRenderer(screen, -1, Render_Flags);
	if(!temp)
	{
		fprintf(stderr, "SDL_CreateRenderer has failed : %s \n", SDL_GetError());
		*success = FAIL;
		return NULL;
	}

	return temp;
}
WSADATA startWinsock(int *success)
{
	WSADATA temp;
	if(WSAStartup(MAKEWORD(2,2), &temp) != 0)
	{
		fprintf(stderr, "WSAStartup has failed : %d \n", WSAGetLastError());
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
	tempOpt.SCREEN_HEIGHT = json_integer_value(json_object_get(optionsData,"SCREEN_HEIGHT"));
	tempOpt.SCREEN_WIDTH = json_integer_value(json_object_get(optionsData,"SCREEN_WIDTH"));
	tempOpt.TITLE = json_string_value(json_object_get(optionsData,"TITLE"));
	tempOpt.RED_FILEPATH = json_string_value(json_object_get(optionsData,"RED_FILEPATH"));
	tempOpt.BLUE_FILEPATH = json_string_value(json_object_get(optionsData,"BLUE_FILEPATH"));
	tempOpt.NODE_FILEPATH = json_string_value(json_object_get(optionsData,"NODE_FILEPATH"));
	tempOpt.IP_ADDRESS_SERVER = json_string_value(json_object_get(optionsData,"IP_ADDRESS_SERVER"));
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
		temp.sin_addr.s_addr = inet_addr(opt->IP_ADDRESS_SERVER);
		temp.sin_port = htons(opt->PORT_ADDRESS);

		return temp;

}