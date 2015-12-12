all:
	gcc	-c	main.h	-g
	gcc	-c	main.c	-g
	gcc	-c	init.c	-g
	gcc	-c	connect.c
	gcc	-o	LD34Client	main.o	init.o	connect.o	-lmingw32	-lSDL2Main	-lSDL2	-lSDL2_image	-lSDL2_ttf	-lSDL2_mixer	-ljansson	-lws2_32	-g