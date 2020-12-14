/// File: curse_lib.h
/// Description: Provides functions for creating windows
///     and menus using the curses.h library
/// Author: Benjamin Piro, benpiro1118@gmail.com
/// Date: 12/13/2020

#include <curses.h>

WINDOW *create_win(int height, int width, int starty, int startx);
