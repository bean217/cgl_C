/// File: curse_lib.c
/// Description: Provides functions for creating windows
///	and menus using the curses.h library
/// Author: Benjamin Piro, benpiro1118@gmail.com
/// Date: 12/13/2020

#include <curses.h>
#include <stdlib.h>
#include <assert.h>
#include "curse_lib.h"

// if the number of scenes is less than 1, scenes unallocated and set to NULL
Game_t * new_game(int num_scenes) {
	Game_t * game = NULL;
	game = (Game_t *)calloc(1, sizeof(Game_t));

	game->scenes = (num_scenes < 1) ? 
		NULL : (Scene_t **)calloc(num_scenes, sizeof(Scene_t *));
	game->num_scenes = num_scenes;
	return game;
}

Scene_t * new_scene(Game_t * game, int num_windows) {
	Scene_t * scene = NULL;
	scene->game = game;
	scene = (Scene_t *)calloc(1, sizeof(Scene_t));
	scene->windows = (num_windows < 1) ? 
		NULL : (Window_t **)calloc(num_windows, sizeof(Window_t *));
	scene->num_windows = num_windows;
	return scene;
}

Window_t * new_window(Scene_t * scene) {
	Window_t * win;
	return win;
}

void del_window(Window_t * window) {

}

void del_scene(Scene_t * scene) {
	int i;
	if (scene->windows != NULL) {
		for (i = 0; i < scene->num_windows; i++) {
			// TODO del_window((scene->windows)[i]);
		}
	}
	free(scene);
}

void del_game(Game_t * game) {
	int i;
	if (game->scenes != NULL) {
		for (i = 0; i < game->num_scenes; i++) {
			// TODO del_scene((game->scenes)[i]);
		}
	}
	free(game);
}
