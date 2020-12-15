/// File: curse_lib.h
/// Description: Provides functions for creating windows
///     and menus using the curses.h library
/// Author: Benjamin Piro, benpiro1118@gmail.com
/// Date: 12/13/2020

#ifndef _CURSE_LIB_H_
#define CURSE _CURSE_LIB_H_
#include <curses.h>

/*
typedef void (*Action)(void);

typedef struct Button_t {
	char ** text;
	Action action; // placeholder
} Button;
*/

typedef struct Menu_t {
	int height;
	int width;
	int starty;
	int startx;
	char *title;
	char **buttons;
	WINDOW * win;
} Menu;

Menu *create_menu(int height, int width, int starty, int startx, char * title);

WINDOW *create_win(int height, int width, int starty, int startx);
#endif
