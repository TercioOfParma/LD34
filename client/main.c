#ifndef INCLUDE_LOCK
#define INCLUDE_LOCK
#include "main.h"
#endif

int main(int argc, char *argv[])
{
	char *jsonOptions, *welcomeMSG;
	options opt;
	unitData **sides[NO_SIDES];
	node **map;
	SDL_Window *win;
	SDL_Renderer *rend;
	SDL_Event eventHandle;
	SDL_Texture *welcome;
	SDL_Rect welcomeRect;
	TTF_Font *defaultFont;
	WSADATA winsockStuff;
	SOCKET sock;
	struct sockaddr_in serverDeets;
	int isSuccess = SUCCESS;
	int isConnected = FAIL;
	int i, noFrames;
	
	
	jsonOptions = loadJsonFile(OPTIONS_FILE, &isSuccess);
	opt = initOptions(jsonOptions, &isSuccess);
	win = initSDL(&opt, &isSuccess);
	rend = createRenderer(win,&isSuccess);
	winsockStuff = startWinsock(&isSuccess);
	sock = initSocket(&isSuccess);
	serverDeets = getServerDetails(&opt, &isSuccess);
	defaultFont = LoadFont(opt.FONT_PATH, 10, &isSuccess);
	welcomeRect.x = 100;
	welcomeRect.y = 0;
	map = initNodes(&isSuccess);
	for(i = 0; i < NO_SIDES; i++)
	{
		sides[i] = initUnits(&isSuccess);
	
	}
	
	while(isSuccess == SUCCESS)
	{
		if(isConnected == FAIL)
		{
			welcomeMSG = connectToServer(&isSuccess, serverDeets, sock);
			welcome = renderScore(defaultFont, &welcomeRect, rend, welcomeMSG, DEFAULT);
			if(strcmp(welcomeMSG,FAIL_COMMAND) != 0 && strcmp(welcomeMSG, " ") != 0)
			{	
				isConnected = SUCCESS;
			
			}
		}
		while(SDL_PollEvent(&eventHandle) > 0)
		{
			if(eventHandle.type == SDL_QUIT)
			{
				isSuccess = FAIL;
			
			}
		
		}
		SDL_RenderClear(rend);
		SDL_SetRenderDrawColor(rend,255,255,255,0);
		SDL_RenderCopy(rend, welcome, NULL, &welcomeRect);
		SDL_RenderPresent(rend);
		noFrames++;
		if(noFrames == SENDING_BRACKET)
		{
			noFrames = 0;
		
		}
	
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