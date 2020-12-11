/// File: cgl.c
/// Description: Backend implementation for Conway's "Game of Life" (cgl). Does
///	not provide a means of displaying cgl, this must be done through other means.
/// Author: Benjamin Piro, benpiro1118@gmail.com
/// Date: 12/10/2020

#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cgl.h"

static bool USE_WRAP = false;

void toggle_UW() {
	USE_WRAP = !USE_WRAP;
}

void init_cgl(int rows, int cols, char start[rows][cols], Cell grid[rows][cols]) {
	int i, j;
	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			if (start[j][i] != 0) {
				grid[j][i].live_state = 1;
			} else {
				grid[j][i].live_state = 0;
			}
		}
	}
}

void grid_cpy(int rows, int cols, Cell grid[rows][cols], char grid_cpy[rows][cols]) {
	int i, j;
	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			grid_cpy[j][i] = grid[j][i].live_state;
		}
	}
}

static int mod(int m, int n) {
	int result = m % n;
	if (result < 0) result += n;
	return result;
}

char nowrap_gln(int row, int col, int rows, int cols, char live_states[rows][cols]) {
	char sum = 0;
	// top left
	if (row > 0 && col > 0) { if (live_states[row - 1][col - 1]) sum++; }
	// top right
	if (row > 0 && col < cols - 1) { if (live_states[row - 1][col + 1]) sum++; }
	// bottom left
	if (row < rows - 1 && col > 0) { if (live_states[row + 1][col - 1]) sum++; }
	// bottom right
	if (row < rows - 1 && col < cols - 1) { if (live_states[row + 1][col + 1]) sum++; }
	// top
	if (row > 0) { if (live_states[row - 1][col]) sum++; }
	// left
	if (col > 0) { if (live_states[row][col - 1]) sum++; }
	// right
	if (col < cols - 1) { if (live_states[row][col + 1]) sum++; }
	// bottom
	if (row < rows - 1) { if (live_states[row + 1][col]) sum++; }
	return sum;
}

char wrap_gln(int row, int col, int rows, int cols, char live_states[rows][cols]) {
	char sum = 0;
	// top left
	if (live_states[mod(row - 1, rows)][mod(cols - 1, cols)]) sum++;
	// top right
	if (live_states[mod(row - 1, rows)][mod(cols + 1, cols)]) sum++;
	// bottom left
	if (live_states[mod(row + 1, rows)][mod(cols - 1, cols)]) sum++;
	// bottom right
	if (live_states[mod(row + 1, rows)][mod(cols + 1, cols)]) sum++;
	// top
	if (live_states[mod(row - 1, rows)][col]) sum++;
	// left
	if (live_states[row][mod(col - 1, cols)]) sum++;
	// right
	if (live_states[row][mod(col + 1, cols)]) sum++;
	// bottom
	if (live_states[mod(row + 1, rows)][col]) sum++;
	return sum;
}

char get_live_neighbors(int row, int col, int rows, int cols, char live_states[rows][cols]) {
	if (USE_WRAP) return nowrap_gln(row, col, rows, cols, live_states);
	else return wrap_gln(row, col, rows, cols, live_states);
}

void get_next_gen(int rows, int cols, Cell grid[rows][cols]) {
	char live_states[rows][cols];
	grid_cpy(rows, cols, grid, live_states);
}



/*
unsigned int getLiveNeighbors(Cell grid[HEIGHT][WIDTH], CellPtr_t cell, int row, int col) {
	unsigned int sum = 0;
	if (row > 0 && col > 0) { if (grid[row - 1][col - 1].live_state) sum++; }
	if (row > 0 && col < WIDTH - 1) { if (grid[row - 1][col + 1].live_state) sum++; }
	if (row < HEIGHT - 1 && col > 0) { if (grid[row + 1][col - 1].live_state) sum++; }
	if (row < HEIGHT - 1 && col < WIDTH - 1) { if (grid[row + 1][col + 1].live_state) sum++; }
	if (row > 0) { if (grid[row - 1][col].live_state) sum++; }
	if (row < HEIGHT - 1) { if (grid[row + 1][col].live_state) sum++; }
	if (col > 0) { if (grid[row][col - 1].live_state) sum++; }
	if (col < WIDTH - 1) { if (grid[row][col + 1].live_state) sum++; }
	return sum;
}
*/


