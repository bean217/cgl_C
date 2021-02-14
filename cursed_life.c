#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cgl.h"
#include "curse_lib.h"

void init() {
	initscr(); // initializes stdscr
        cbreak(); // allows CTRL-C to escape stdscr
        noecho(); // disable character echoing
	curs_set(0); // hide default cursor
	keypad(stdscr, TRUE);
	refresh();
}

void endit() {
        endwin();
}


int main(void) {
	// Game game = new Game();
	// make game.windows = make_scenes_and_windows()
	// Scene current scene = Game.scenes[0];
	char ch;
	init();
	WINDOW * win = newwin(LINES, COLS, 0, 0);
	box(win, 0, 0);
	
	while ((ch = getch()) != 'q') {
		for(0 /* each window in scene*/ ) {
			//window.draw();
		}
		wrefresh(win);
		wclear(win);
	}

	endit();	
}
