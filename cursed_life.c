#include <curses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "cgl.h"
#include "curse_lib.h"

void init() {
	struct winsize w;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	printf("ROWS: %d\n", w.ws_row);
	printf("COLS: %d\n", w.ws_col);

	initscr(); // initializes stdscr
        cbreak(); // allows CTRL-C to escape stdscr
        noecho(); // disable character echoing
	curs_set(0); // hide default cursor
}

void endit() {
        endwin();
}

void init_game() {
	WINDOW *cgl_win;
	int startx, starty, width, height;
	int ch;
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color) {
	int length, x, y;
	float temp;

	if (win == NULL) win = stdscr;
	getyx(win, y, x);
	if (startx != 0) x = startx;
	if (starty != 0) y = starty;
	if (width == 0) width = 80;

	length = strlen(string);
	temp = (width - length) / 2;
	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

void menus() {	
	ITEM **my_items;
	int c;
	MENU *my_menu;
	WINDOW *my_menu_win;
	int n_choices, i;

	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);

	// create items
	char *choices[] = {"Play", "Options", "Quit", (char *)NULL};
	n_choices = 3;
	my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	for (i = 0; i < n_choices; ++i) {
		my_items[i] = new_item(choices[i], choices[i]);
	}

	// create menu
	my_menu = new_menu((ITEM **)my_items);

	// create window associated with menu
	my_menu_win = newwin(10, 40, 4, 4);
	keypad(my_menu_win, TRUE);

	// set main and sub windows
	set_menu_win(my_menu, my_menu_win);
	set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));

	// set menu mark to string " * "
	set_menu_mark(my_menu, " * ");

	// print border around main window and print a title
	box(my_menu_win, 0, 0);
	print_in_middle(my_menu_win, 1, 0, 40, "My Menu", COLOR_PAIR(1));
	
	mvwaddch(my_menu_win, 0, 1, ACS_RTEE);
	int t_len = strlen("My Menu");
	for (i = 0; i < t_len; ++i) {
		mvwaddch(my_menu_win, 0, 2 + i, "My Menu"[i]);
	}
	mvwaddch(my_menu_win, 0, 2 + t_len, ACS_LTEE);

	//mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	//mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	//mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
	mvprintw(LINES - 1, 0, "F1 to exit");
	refresh();

	// post menu
	post_menu(my_menu);
	wrefresh(my_menu_win);

	while ((c = wgetch(my_menu_win)) != KEY_F(1)) {
		switch (c) {
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
		}
		wrefresh(my_menu_win);
	}

	// unpost and free all the memory taken up
	unpost_menu(my_menu);
	free_menu(my_menu);
	for (i = 0; i < n_choices; ++i) {
		free_item(my_items[i]);
	}
	
}

void custom_menu() {
	struct winsize w;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	int height = w.ws_row;
	int width = w.ws_col;
	
	WINDOW *win;
	char *choices[] = {"Play", "Options", "Exit", (char *)NULL};
	char item[8];
	int ch, i, n_choices;
	win = newwin(height-2, width-10, 1, 1); // create new window
	box(win, 0, 0); // set default borders
	mvwaddch(win, 0, 1, ACS_RTEE);
	int t_len = strlen("Conway's Game of Life");
	for (i = 0; i < t_len; ++i) {
		mvwaddch(win, 0, 2 + i, "Conway's Game of Life"[i]);
	}
	mvwaddch(win, 0, 2 + t_len, ACS_LTEE);

	n_choices = 3;
	// print menu items and highlight them
	for (i = 0; i < n_choices; i++) {
		if (i == 0) {
			wattron(win, A_STANDOUT); // highlight first item
		} else {
			wattroff(win, A_STANDOUT); // dont on rest
		}
		sprintf(item, "%-7s", choices[i]);
		mvwprintw(win, i+1, 2, "%s", item);
	}
	wrefresh(win); // update terminal screen
	i = 0;
	keypad(win, TRUE); // enables keyboard input
	
	// get user input until user types 'q'
	while ((ch = wgetch(win)) != 'q') {
		sprintf(item, "%-7s", choices[i]);
		mvwprintw(win, i+1, 2, "%s", item);

		// incr/decr highlight based on input
		switch (ch) {
			case KEY_UP:
				i--;
				i = (i < 0) ? 2: i;
				break;
			case KEY_DOWN:
				i++;
				i = (i > n_choices - 1) ? 0 : i;
				break;
		}
		// highlight the next item in the list
		wattron(win, A_STANDOUT);

		sprintf(item, "%-7s", choices[i]);
		mvwprintw(win, i+1, 2, "%s", item);
		wattroff(win, A_STANDOUT);
	}
	delwin(win);
}

int main(void) {
	init();

	//menus();

	custom_menu();

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
