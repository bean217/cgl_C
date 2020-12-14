#!/bin/bash
echo "Compiling..."

NAME=cursed_life
SRC=cursed_life.c

#C_FLAGS=-std=c99 -Wall -Wextra -pedantic -o

gcc -std=c99 -Wall -Wextra -pedantic -o $NAME cursed_life.c cgl.c curse_lib.c -lmenu -lncurses

echo "Done!"
