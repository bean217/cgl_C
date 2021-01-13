#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cgl.h"
#include "curse_lib.h"

static WINDOW * win;

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

void draw() {
	werase(win);
	box(win, 0, 0);
	mvwprintw(win, 1, 1, "COLS = %d, LINES = %d", COLS, LINES);

	char *str = "Game of Life";
	int y, x;
	getmaxyx(win, y, x);
	mvwprintw(win, y / 3, (x - strlen(str)) / 2, "%s", str);

	char *choices[] = {"Play", "Options", "Exit", (char *)NULL};
	int i = 0;
	while (choices[i] != (char *)NULL) {
		mvwprintw(win, (y / 2) + i, (x - strlen(choices[i])) / 2, "%s", choices[i]);
		i++;
	}
	wrefresh(win);
}


int main(void) {
	init();
	win = newwin(LINES, COLS, 0, 0);
	
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	
	draw();

	int key;
	while ((key = getch()) != 'q') {
		if (key == KEY_RESIZE) {
			// reset stdscr
			endwin();
			refresh();
			// reset stdscr subwindow and resize it
			//werase(win);
			wresize(win, (LINES < 25) ? 25 : LINES, (COLS < 75) ? 75 : COLS);	
		}
		// draw the window
		draw();
	}

	endit();	
}
