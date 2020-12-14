#include <curses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "cgl.h"
#include "curse_lib.h"

void init() {
        initscr();
        cbreak();
        noecho();

	struct winsize w;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	printf("ROWS: %d\n", w.ws_row);
	printf("COLS: %d\n", w.ws_col);
}

void endit() {
        endwin();
}

void init_game() {
	WINDOW *cgl_win;
	int startx, starty, width, height;
	int ch;
}

int main(void) {
	init();

	struct winsize w;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	WINDOW *win;
	
	int height = 3;
	int width = 10;
	int starty = (LINES - height) / 2;
	int startx = (COLS - width) / 2;
	refresh();
	win = create_win(height, width, starty, startx);
	getch();
	getch();
	getch();
	getch();
	delwin(win);
	refresh();
	getch();

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
