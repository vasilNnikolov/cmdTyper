#ifndef GAME_H
#define GAME_H

#define MAX_WORD_LENGTH 15
#define MAX_LINE_LENGTH 40

int lineCount(char* filename);

char** getWords(char* filename, int* nWords);

#endif