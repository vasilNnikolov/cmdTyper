#ifndef GAME_H
#define GAME_H
#include <stdbool.h>

#define MAX_WORD_LENGTH 15
#define MAX_LINE_LENGTH 40
#define BACKSPACE 127

int lineCount(char* filename);

char** getWords(char* filename, int* nWords);

void getLineFromFile(char* line, int* lineLength, char** words, int nWords);

void renderLine(char* line, int currentLinePosition, bool* isCharCorrect);

#endif