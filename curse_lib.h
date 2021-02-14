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
typedef struct Scene_t Scene_t;
typedef struct Window_t Window_t;
typedef struct Text_t Text_t;
typedef struct Button_t Button_t;
typedef union Component_t Component_t;


struct Scene_t {
	Game_t * game;
	Window_t ** windows;
	int num_windows;
};

struct Game_t {
	Scene_t ** scenes;
	int num_scenes;
};

struct Window_t {
	Scene_t * scene;
};

struct Text_t {
	Window_t * window; // reference to parent window
	char * text;
	int length;
};

struct Button_t {
	Window_t * window; // reference to parent window
	void (*action)(Button_t *);
};

union Component_t {
	Text_t text;
	Button_t button;
};

#endif
