#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

#include "graphics.h"
#include "game.h"


int main(){
    char* wordsFile = "words.txt";
    //initialise the screen
    setupTerminal();

    // get length of file 
    int nWords;
    char lineOfWords[MAX_WORD_LENGTH];
    
    char** words = getWords(wordsFile, &nWords);
    while(1){
        clear();

        // main logic goes here

        // get random word
        char* word = words[rand()%nWords];
        printWord(5, 5, word, MAX_WORD_LENGTH, highlited);
        usleep(1000000);

        int c = getch();
        if(c == 'q'){
            break;
        }
        usleep(10000);
    }
    endwin();
    for(int i = 0; i < nWords; i++){free(words[i]);}
    free(words);
    
    return 0;
}