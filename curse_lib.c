/// File: curse_lib.c
/// Description: Provides functions for creating windows
///	and menus using the curses.h library
/// Author: Benjamin Piro, benpiro1118@gmail.com
/// Date: 12/13/2020

#include <curses.h>
#include <stdlib.h>
/*
Menu *create_menu(int height, int width, int starty, int startx, char * title) {
	Menu *menu = NULL;
	menu = (Menu *)calloc(1, sizeof(Menu));
	menu->height = height;
	menu->width = width;
	menu->starty = starty;
	menu->startx = startx;
	menu->title = title;
}
*/

WINDOW *create_win(int height, int width, int starty, int startx) {
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);
	wrefresh(local_win);
	return local_win;
}
