#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "graphics.h"
#include "game.h"
#include "start_screen.h"
#include "score_screen.h"


int main(){
    char* wordsFile = "words.txt";
    //initialise the screen
    setupTerminal();
    //start screen loop
    bool gameStarted = false, gamePlayed = false;
    // get length of file 
    int nWords;
    
    char** words = getWords(wordsFile, &nWords);
    startScreenState screenState;
    initStartScreenValues(&screenState);
    while(1){
        erase();
        //main logic of start menu goes here
        char c = getch();
        
        if(c == ESCAPE_KEY){ //the escape key, in ascii
            c = getch();
            if(c == -1){ //no char detected
                printWord(5, 3, "Exiting", bold);
                refresh();
                usleep(1000000);
                break;
            }
            c = ESCAPE_KEY;
        } 
        
        renderStartScreen(&screenState, c, &gameStarted);
        refresh();

        char lineOfWords[MAX_LINE_LENGTH], nextLineOfWords[MAX_LINE_LENGTH];
        bool isCharCorrect[MAX_LINE_LENGTH] = {[0 ... MAX_LINE_LENGTH - 1] = true};
        int currentLinePosition = 0, currentLineLength, nextLineLength;
        getLineFromFile(lineOfWords, &currentLineLength, words, nWords);
        usleep(100000);
        getLineFromFile(nextLineOfWords, &nextLineLength, words, nWords);

        int correctCharsWritten = 0, allCharErrors = 0, correctedErrors = 0;
        if(gameStarted){
            //variables for timer handling
            long startTime;
            bool firstCharTyped = false;
            int totalTime = screenState.timeMenuValues[screenState.selectedTimeMenuIndex];
            int timeLeft = totalTime;
            char* timerStringFormat = "Time left: %d";
            char timerString[20];
            
            //main game loop
            while(gameStarted){
                erase();

                // main logic goes here
                //render main line
                renderLine(10, 40, lineOfWords, currentLinePosition, isCharCorrect);
                //render line below
                renderLine(12, 40, nextLineOfWords, -1, isCharCorrect); //-1 signifies the line is inactive

                //render timer
                sprintf(timerString, timerStringFormat, timeLeft);
                printWord(5, 20, timerString, normal); //need to format string

                refresh();

                //handle keyboard input 
                int c = getch();
                if(!firstCharTyped && c == -1){ // no char has been typed yet
                    continue; //this waits for the user to type a char to start the timer
                }
                if(!firstCharTyped){
                    startTime = time(NULL); 
                    firstCharTyped = true;
                }
                if((int)((time(NULL) - startTime)) != totalTime - timeLeft){// update timeLeft value
                    timeLeft--;
                    if(timeLeft < 1){
                        gameStarted = false;
                        gamePlayed = true;
                        break;
                    }
                }

                if(c == ESCAPE_KEY){
                    gameStarted = false;
                    gamePlayed = true;
                    break;
                }
                if(c != -1){ //key was pressed
                    if(c == BACKSPACE){
                        if(currentLinePosition > 0){currentLinePosition--;}
                    }
                    else{
                        if(c == lineOfWords[currentLinePosition]){ //correct char typed
                            correctCharsWritten++;
                            isCharCorrect[currentLinePosition] = true;
                        }
                        else{
                            isCharCorrect[currentLinePosition] = false;
                        }
                        currentLinePosition++;
                    }
                }

                //refresh data when cursor is at the end of the current line
                if(currentLinePosition == currentLineLength - 1){ //-1 is so it does not draw the '\0'
                    //curent line is the previous next line
                    for(int i=0; i < MAX_LINE_LENGTH; i++){
                        lineOfWords[i] = nextLineOfWords[i];
                    }
                    currentLineLength = nextLineLength;
                    //need to fetch anoter line from the file
                    getLineFromFile(nextLineOfWords, &nextLineLength, words, nWords);
                    currentLinePosition = 0;
                }
                usleep(10000);
            }
            if(gamePlayed){
                // usleep(1000000);
                //render score screen
                renderEndScreen(screenState, correctCharsWritten, allCharErrors);            
            }
        }
        usleep(10000);
    }


    endwin();
    for(int i = 0; i < nWords; i++){free(words[i]);}
    free(words);
    
    return 0;
}