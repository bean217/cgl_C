/// File: cgl.h
/// Description: Backend implementation for Conway's "Game of Life" (cgl). Does
///     not provide a means of displaying cgl, this must be done through other means.
/// Author: Benjamin Piro, benpiro1118@gmail.com
/// Date: 12/10/2020

#ifndef _CGL_H_
#define _CGL_H_

#include <stdbool.h>

typedef struct CellStruct_t {
	unsigned int live_state : 1;
	unsigned int neighbors : 3;	
} Cell;

void init_cgl(int rows, int cols, char start[rows][cols], Cell [rows][cols]);

#endif
