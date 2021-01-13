# Makefile for cursed_life program

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
CLIBS = -lncurses

cursed_life: cursed_life.o cgl.o curse_lib.o
	$(CC) $(CFLAGS) -o cursed_life cursed_life.o cgl.o curse_lib.o $(CLIBS)

cursed_life.o: cursed_life.c cgl.h curse_lib.h
	$(CC) $(CFLAGS) -c cursed_life.c $(CLIBS)

cgl.o: cgl.c cgl.h
	$(CC) $(CFLAGS) -c cgl.c $(CLIBS)

curse_lib.o: curse_lib.c curse_lib.h
	$(CC) $(CFLAGS) -c curse_lib.c $(CLIBS)