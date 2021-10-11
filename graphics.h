#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ncurses.h>

typedef enum states{highlited=A_STANDOUT, underlined=A_UNDERLINE, normal=A_NORMAL} state;

void printWord(int x, int y, char* word, int word_length, state attr);

void setupTerminal();

#endif