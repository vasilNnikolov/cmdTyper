#include "score_screen.h"
#include "graphics.h"

#include <unistd.h>

void renderEndScreen(startScreenState screenState, int correctCharsWritten, int totalCharErrors){
    while(1){
        erase();

        printWord(18, 5, "GAME OVER", bold);

        float wpm = correctCharsWritten/(float)5;
        char wordsPerMinute[30];
        float timePerRound = screenState.timeMenuValues[screenState.selectedTimeMenuIndex];
        sprintf(wordsPerMinute, "Words per minute: %.1f", wpm*60/timePerRound);

        printWord(18, 8, wordsPerMinute, normal);
        refresh();

        char c = getch();
        
        if(c == ESCAPE_KEY){
            break;
        }
        
        usleep(10000);
    }

}