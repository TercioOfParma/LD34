#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "main.h"
#endif

int main(int argc, char *argv[])
{
	char *jsonOptions;
	options opt;
	unitData **sides[NO_SIDES];
	SDL_Window *win;
	SDL_Renderer *rend;
	SDL_Event eventHandle;
	WSADATA winsockStuff;
	SOCKET sock;
	struct sockaddr_in serverDeets;
	int isSuccess = SUCCESS;
	int isConnected = FAIL;
	
	jsonOptions = loadJsonFile(OPTIONS_FILE, &isSuccess);
	opt = initOptions(jsonOptions, &isSuccess);
	win = initSDL(&opt, &isSuccess);
	rend = createRenderer(win,&isSuccess);
	winsockStuff = startWinsock(&isSuccess);
	sock = initSocket(&isSuccess);
	serverDeets = getServerDetails(&opt, &isSuccess);
	
	printf("Size of UnitData : %d", sizeof(unitData));
	while(isSuccess == SUCCESS)
	{
		if(isConnected == FAIL)
		{
			isConnected = connectToServer(&isSuccess, serverDeets, sock);
		
		}
		while(SDL_PollEvent(&eventHandle) > 0)
		{
			if(eventHandle.type == SDL_QUIT)
			{
				isSuccess = FAIL;
			
			}
		
		}
	
	}
	deinit();
	return 0;

}