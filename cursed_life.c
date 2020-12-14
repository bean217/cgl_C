#include <curses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cgl.h"
#include "curse_lib.h"

void init() {
        initscr();
        cbreak();
        noecho();

	//struct winsize w;

	//ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	//printf("ROWS: %d\n", w.ws_row);
	//printf("COLS: %d\n", w.ws_col);
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

void print_menu(WINDOW *menu_win, int highlight) {
	int x, y, i;
	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	char *choices[] = {"Play", "Options", "Exit", (char *)NULL};
	int n_choices = 3;
	for (i = 0; i < n_choices; ++i) {
		if (highlight == i + 1) {
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		} else {
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		}
		++y;
	}
	wrefresh(menu_win);
}

void report_choice(int mouse_x, int mouse_y, int *p_choice) {
	int i, j, choice;
	int startx = 0;
	int starty = 0;
	i = startx + 2;
	j = starty + 3;
	char *choices[] = {"Play", "Options", "Exit", (char *)NULL};
        int n_choices = 3;
	for (choice = 0; choice < n_choices; ++choice) {
		if (mouse_y == j + choice && mouse_x >= i && mouse_x <= i + strlen(choices[choice])) {
			if (choice == n_choices - 1) *p_choice = -1;
			else *p_choice = choice + 1;
			break;
		}
	}
}

void mouse_menu() {
	int WIDTH = 30;
	int HEIGHT = 10;
	int startx = 0;
	int starty = 0;

	char *choices[] = {"Play", "Options", "Exit", (char *)NULL};
	int n_choices = 3;

	int x, choice = 0;
	WINDOW *menu_win;
	MEVENT event;

	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	attron(A_REVERSE);
	mvprintw(23, 1, "Click on Exit to quit (Works best in a virtual console)");
	refresh();
	attroff(A_REVERSE);

	// print menu for first time
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	print_menu(menu_win, 1);

	// get all mouse events
	mousemask(ALL_MOUSE_EVENTS, NULL);

	int c, exit;
	exit = 0;
	while (1) {
		c = wgetch(menu_win);
		switch (c) {
			case KEY_MOUSE:
				if (getmouse(&event) == OK) {
					// when user clicks left button
					if (event.bstate & BUTTON1_PRESSED) {
						report_choice(event.x + 1, event.y + 1, &choice);
						if (choice == -1) exit = 1;
						if (!exit) {
							mvprintw(22, 1, "Choice made is : %d String Chosen is \"%10s\"", choice, choices[choice - 1]);
							refresh();
						}
					}
				}
				if (!exit) {
					print_menu(menu_win, choice);
				}
				break;
		}
		if (exit) break;
	}
}

int main(void) {
	init();

	//menus();
	mouse_menu();

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
