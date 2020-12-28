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

typedef struct Game_t Game_t;

typedef struct {
	Game_t * game;
} Scene_t;

struct Game_t {
	Scene_t ** scenes;
};

typedef struct {
	Scene_t * scene;
} Window_t;

typedef struct {
	Window_t * window;
} Text_t;

typedef struct BUTTON_TYPE {
	Window_t * window;
	void (*action)(struct BUTTON_TYPE *);
} Button_t;

typedef union {
	Text_t text;
	Button_t button;
} Component_t;
#endif
