#include <curses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "cgl.h"
#include "curse_lib.h"

void init() {
	initscr(); // initializes stdscr
        cbreak(); // allows CTRL-C to escape stdscr
        noecho(); // disable character echoing
	curs_set(0); // hide default cursor
	refresh();
}

void endit() {
        endwin();
}

void draw() {
	WINDOW *win;
	win = newwin(LINES, COLS, 0, 0);
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

void resizeHandler(int);

void resizeHandler(int sig) {
	//int nh, nw;
	//getmaxyx(stdscr, nh, nw);
	erase();
	refresh();
	draw();
	signal(SIGWINCH, resizeHandler);
}

int main(void) {
	init();
	draw();
	signal(SIGWINCH, resizeHandler);
	while (getch() != 'q') {}
/*
	//menus();

	//custom_menu();

	//my_menu();
	
	WINDOW *win;
	win = newwin(LINES, COLS, 0, 0);

	box(win, 0, 0);
	mvwprintw(win, 1, 1, "COLS = %d, LINES = %d", COLS, LINES);
	char *str = "Game of Life";
	int y, x;
	getmaxyx(win, y, x);
	mvwprintw(win, y / 3, (x - strlen(str)) / 2, "%s", str);

	// display options
	char *choices[] = {"Play", "Options", "Quit", (char *)NULL};
	int i = 0;
	while (choices[i] != (char *)NULL) {
		mvwprintw(win, (y / 2) + i, (x - strlen(choices[i])) / 2, "%s", choices[i]);	
		i++;
	}
	wrefresh(win);

	int key;
	while ((key = getch()) != 'q') {
		if (key == KEY_RESIZE) {
			endwin();
			refresh();
			
			werase(win);
			wresize(win, (LINES < 25) ? 25 : LINES, (COLS < 75) ? 75 : COLS);
			
			box(win, 0, 0);
			mvwprintw(win, 1, 1, "COLS = %d, LINES = %d", COLS, LINES);
			getmaxyx(win, y, x);
			mvwprintw(win, y / 3, (x - strlen(str)) / 2, "%s", str);
			char *choices[] = {"Play", "Options", "Quit", (char *)NULL};
			int i = 0;
			while (choices[i] != (char *)NULL) {
				mvwprintw(win, (y / 2) + i, (x - strlen(choices[i])) / 2, "%s", choices[i]);
				i++;
			}
			wrefresh(win);
		}
		

	}
*/
	/*
	WINDOW *win;
	
	int height = 3;
	int width = 10;
	int starty = (LINES - height) / 2;
	int startx = (COLS - width) / 2;
	refresh();
	win = create_win(height, width, starty, startx);
	int oldLines = LINES;
	int oldCols = COLS;
	while (1) {
		if (LINES != oldLines || COLS != oldCols) {
			resizeterm(LINES, COLS);	
		}
		oldLines = LINES;
		oldCols = COLS;
		starty = (LINES - height) / 2;
		startx = (COLS - height) / 2;
		mvwin(win, starty, startx);
		wrefresh(win);
		refresh();
		if (getch() == 'k') break;
	}
*/	

	/*
	int rows, cols, i, j;
	rows = 40;
	cols = 80;
	Cell grid[rows][cols];

	char start[rows][cols];

	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			start[j][i] = 0;
		}
	}

	init_cgl(rows, cols, start, grid);

	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			if (grid[j][i].live_state != 0) printf("*");
			else printf(" ");
		}
		printf("\n");
	}
	*/

	endit();	
}
