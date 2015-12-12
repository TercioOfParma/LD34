#include <jansson/jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <winsock2.h>


const static int SUCCESS = 1;
const static int FAIL = 2;
const static int GAME_WON = 3;
const static char *OPTIONS_FILE = "optionsSER.json";
const static int MAXIMUM_UNITS = 1000;
const static int SENDING_BRACKET = 10;
const static int NO_SIDES = 4;
const static int SIZE_WELCOME = 1000000;
const static char *WELCOME_COMMAND = "meep";
typedef struct
{
	int PORT_ADDRESS;
	const char *SERVER_NAME, *SERVER_WELCOME;
}options;

typedef struct
{
	short x,y;
	char alive,dest, inCombat, xVel,yVel,side;

}unitData;
typedef struct
{
	char code, holder;
	short x,y,sideOneNumber,sideTwoNumber;

}node;

//init functions
char *loadJsonFile(const char *filename, int *success);
options initOptions(const char *jsonFile, int *success);
int getFileSize(FILE *sizeToGet, int *success);
WSADATA startWinsock(int *success);
SOCKET initSocket(int *success);
struct sockaddr_in getServerDetails(options *opt, int *success);
void deinit();
void bindSocket(struct sockaddr_in serverDetails, SOCKET sock, int *isSuccess);
void listenForPackets(struct sockaddr_in serverDetails, SOCKET sock, struct sockaddr_in recieved, options *opt, int *isSuccess);