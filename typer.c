#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>

#include "graphics.h"
#include "game.h"
#include "start_screen.h"


int main(){
    char* wordsFile = "words.txt";
    //initialise the screen
    setupTerminal();
    //start screen loop
    bool gameStarted = false;
    // get length of file 
    int nWords;
    char lineOfWords[MAX_WORD_LENGTH];
    
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
        
        renderStartScreen(&screenState, c);
        refresh();

        if(gameStarted){
            //main game loop
            while(1){
                erase();

                // main logic goes here

                // get random word
                char* word = words[rand()%nWords];
                printWord(5, 5, word, highlited); 
                usleep(1000000);

                int c = getch();
                if(c == ESCAPE_KEY){
                    break;
                }
                //refresh();
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