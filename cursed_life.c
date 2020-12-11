#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "cgl.h"

static struct winsize WS;

void init() {
        initscr();
        cbreak();
        noecho();

	ioctl(STDIN_FILENO, TIOCGWINSZ, &WS);
	printf("ROWS: %d\n", WS.ws_row);
	printf("COLS: %d\n", WS.ws_col);

	WINDOW local_win;
	int width, height;

	getmaxyx(&local_win, height, width);
	printf("ROWS: %d\n", height);
	printf("COLS: %d\n", width);
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

	endit();	
}
