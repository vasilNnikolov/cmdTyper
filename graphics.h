#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ncurses.h>

typedef enum states{highlited=A_STANDOUT, underlined=A_UNDERLINE, normal=A_NORMAL, bold=A_BOLD} textState;

void printWord(int x, int y, char* word, textState attr);

void setupTerminal();

#endif