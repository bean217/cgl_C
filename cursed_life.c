#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

void init() {
        initscr();
        cbreak();
        noecho();
}

void endit() {
        endwin();
}

int main(void) {
	init();
	
	int i = 0;
	int j = 0;
	
	while (i < 10) {
		printw("Hello World !!!");
		refresh();
		getch();
		clear();
		for (j = 0; j < i; j++) {printw(" ");}
		i++;
	}

	endit();	
}
