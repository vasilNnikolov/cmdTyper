#include "start_screen.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "graphics.h"

void initStartScreenValues(startScreenState* screenState){
    strcpy(screenState->timeMenuItems[0], "30 seconds");
    strcpy(screenState->timeMenuItems[1], "1 minute");
    strcpy(screenState->timeMenuItems[2], "2 minutes");
    strcpy(screenState->timeMenuItems[3], "5 minutes");

    screenState->timeMenuValues[0] = 30;
    screenState->timeMenuValues[1] = 60;
    screenState->timeMenuValues[2] = 120;
    screenState->timeMenuValues[3] = 300;

    screenState->selectedTimeMenuIndex = 1;

    strcpy(screenState->diffucultyMenuItems[0], "Easy");
    strcpy(screenState->diffucultyMenuItems[1], "Normal");
    strcpy(screenState->diffucultyMenuItems[2], "Hard");
    strcpy(screenState->diffucultyMenuItems[3], "Cum");

    screenState->selectedDifficultyMenuIndex = 1;

    screenState->currentActiveMenu = 0;
}

void switchStartScreenStates(startScreenState* screenState, char c){
    if(c == ESCAPE_KEY){
        // getch();
        c = getch();
        int dt = 10000;
        switch (c)
        {
        //switching menus
        case 'C': //right arrow
            screenState->currentActiveMenu++;
            screenState->currentActiveMenu = (2 + screenState->currentActiveMenu % 2)%2;
            break;
        case 'D': //right arrow
            screenState->currentActiveMenu--;
            screenState->currentActiveMenu = (2 + screenState->currentActiveMenu % 2)%2;
            break;

        //moving through menu items 
        case 'A': //arrow up
            switch(screenState->currentActiveMenu){
                case 0:
                    screenState->selectedTimeMenuIndex--;
                    screenState->selectedTimeMenuIndex = (4 + screenState->selectedTimeMenuIndex % 4)%4;
                    usleep(dt);
                    break;
                case 1:
                    screenState->selectedDifficultyMenuIndex--;
                    screenState->selectedDifficultyMenuIndex = (4 + screenState->selectedDifficultyMenuIndex % 4)%4;
                    usleep(dt);
                    break;
            }
            break;
        case 'B': //arrow up
            switch(screenState->currentActiveMenu){
                case 0:
                    screenState->selectedTimeMenuIndex++;
                    screenState->selectedTimeMenuIndex = screenState->selectedTimeMenuIndex % 4;
                    usleep(dt);
                    break;
                case 1:
                    screenState->selectedDifficultyMenuIndex++;
                    screenState->selectedDifficultyMenuIndex = screenState->selectedDifficultyMenuIndex % 4;
                    usleep(dt);
                    break;
            }
            break;
        }
    }
}

void renderStartScreen(startScreenState* screenState, char c){
    switchStartScreenStates(screenState, c);

    //actual rendering of the text
    printWord(5, 3, "CMD typing test", bold);

    //render menus
    int timeMenuLength = sizeof(screenState->timeMenuValues)/sizeof(screenState->timeMenuValues[0]);
    int difficultyMenuLength = sizeof(screenState->diffucultyMenuItems)/sizeof(screenState->diffucultyMenuItems[0]);
    textState state;
    switch(screenState->currentActiveMenu){
        case 0: //time menu is active
            for(int i=0; i < timeMenuLength; i++){
                if(i == screenState->selectedTimeMenuIndex) {state = highlited;}
                else {state = normal;}
                printWord(5, 8+2*i, screenState->timeMenuItems[i], state);
            }
            for(int i=0; i < difficultyMenuLength; i++){
                if(i == screenState->selectedDifficultyMenuIndex) {state = underlined;}
                else {state = normal;}
                printWord(20, 8+2*i, screenState->diffucultyMenuItems[i], state);
            }
            break;

        case 1: //difficulty menu is active
            for(int i=0; i < difficultyMenuLength; i++){
                if(i == screenState->selectedDifficultyMenuIndex) {state = highlited;}
                else {state = normal;}
                printWord(20, 8+2*i, screenState->diffucultyMenuItems[i], state);
            }
            for(int i=0; i < timeMenuLength; i++){
                if(i == screenState->selectedTimeMenuIndex) {state = underlined;}
                else {state = normal;}
                printWord(5, 8+2*i, screenState->timeMenuItems[i], state);
            }
    }
}