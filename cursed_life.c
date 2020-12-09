#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	init();
	
	WINDOW * win = newwin(nlines, ncols, y0, x0);

	endit();	
}

void init() {
	initscr();
	cbreak();
	noecho();
}

void endit() {
	endwin();
}
