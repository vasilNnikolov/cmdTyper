#ifndef START_SCREEN_H
#define START_SCREEN_H

#define ESCAPE_KEY 27
#include "game.h"

typedef struct startScreenState{
    char timeMenuItems[4][MAX_WORD_LENGTH];
    int timeMenuValues[4]; //in seconds
    int selectedTimeMenuIndex;

    char diffucultyMenuItems[4][MAX_WORD_LENGTH];   
    int selectedDifficultyMenuIndex;

    int currentActiveMenu;
} startScreenState;
void initStartScreenValues(startScreenState* screenState);

void switchStartScreenStates(startScreenState* screenState, char c);

void renderStartScreen(startScreenState* screenState, char c);
#endif