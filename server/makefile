all:
	gcc	-c	mainSER.h	-g
	gcc	-c	mainSER.c	-g
	gcc	-c	initSER.c	-g
	gcc	-c	serverSER.c	-g
	gcc	-o	LD34Server	mainSER.o	initSER.o	serverSER.o	-ljansson	-lws2_32	-g