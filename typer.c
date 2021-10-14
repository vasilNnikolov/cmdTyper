#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>

#include "graphics.h"
#include "game.h"
#include "start_screen.h"
int main2(){
    char lineOfWords[MAX_LINE_LENGTH];
    int currentLinePosition = 0, currentLineLength;
    int nWords;
    char* wordsFile = "words.txt";
    char** words = getWords(wordsFile, &nWords);
    getLineFromFile(lineOfWords, &currentLineLength, words, nWords);
    printf("%s\n", lineOfWords);
    return 0;
}

int main(){
    char* wordsFile = "words.txt";
    //initialise the screen
    setupTerminal();
    //start screen loop
    bool gameStarted = false;
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

        char lineOfWords[MAX_LINE_LENGTH], lineWritten[MAX_LINE_LENGTH];
        bool isCharCorrect[MAX_LINE_LENGTH] = {[0 ... MAX_LINE_LENGTH - 1] = true};
        int currentLinePosition = 0, currentLineLength;
        getLineFromFile(lineOfWords, &currentLineLength, words, nWords);
        if(gameStarted){
            //main game loop
            int correctCharsWritten = 0, allCharErrors = 0, correctedErrors = 0;
            while(1){
                erase();

                // main logic goes here
                renderLine(lineOfWords, currentLinePosition, isCharCorrect);

                int c = getch();
                if(c == ESCAPE_KEY){
                    gameStarted = false;
                    break;
                }
                if(c != -1){ //key was pressed
                    if(c == BACKSPACE){
                        if(currentLinePosition > 0){currentLinePosition--;}
                    }
                    else{
                        lineWritten[currentLinePosition] = c;
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
                if(currentLinePosition == currentLineLength - 1){ //-1 is so it does not draw the '\0'
                    //need to fetch anoter line from the file
                    getLineFromFile(lineOfWords, &currentLineLength, words, nWords);
                    currentLinePosition = 0;
                }
                refresh();
                usleep(10000);
            }
        }
        usleep(12000);
    }


    endwin();
    for(int i = 0; i < nWords; i++){free(words[i]);}
    free(words);
    
    return 0;
}