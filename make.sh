#!/bin/bash
echo "Compiling..."

NAME=cursed_life
SRC=cursed_life.c

#C_FLAGS=-std=c99 -Wall -Wextra -pedantic -o

gcc -std=c99 -Wall -Wextra -pedantic -o $NAME $SRC

echo "Done!"
