#include <unistd.h>
#include <ncurses.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 15
#define MAX_LINE_LENGTH 40

typedef enum states{highlited=A_STANDOUT, underlined=A_UNDERLINE, normal=A_NORMAL} state;

int lineCount(char* filename){
    FILE *fp = fopen(filename, "r");
    char c;
    int lineCount = 0;
    if(fp == NULL)
    {
        printf ( "Could not open file test.c" ) ;
        return 1;
    }
    while(1)
    {
        c = fgetc ( fp ) ; // reading the file
        if(c == EOF){break;}
        if(c == '\n'){lineCount++;}
        // printf("%c", c);
    }
    fclose(fp); // Closing the file
    return lineCount;
}

void printWord(int x, int y, char* word, int word_length, state attr){
    attron(attr);
    mvaddstr(y, x, word);
    attroff(attr);
}

char** getWords(char* filename, int* nWords){
    char** words;
    FILE* file = fopen(filename, "r");
    if(!file){
        perror(filename);
        exit(1);
    }
    *nWords = lineCount(filename); 
    printf("%d\n", *nWords);
    words = (char**)malloc(sizeof(char*) * (*nWords));
    int wordIndex = 0, charIndex = 0;
    char c;
    while((c = fgetc(file)) != EOF){
        if(c == '\n'){
            wordIndex++;
            charIndex = 0;
        }
        else{
            if(charIndex == 0){
                words[wordIndex] = (char*)malloc(sizeof(char) * MAX_WORD_LENGTH);
            }
            //to prevent overflow
            if(charIndex < MAX_WORD_LENGTH){
                words[wordIndex][charIndex++] = c;
            }
        }
    }
    return words;
}

int main(){
    char* wordsFile = "words.txt";
    //initialise the screen
    initscr();
    cbreak();
    curs_set(FALSE);
    noecho();
    nodelay(stdscr, TRUE);   

    // get length of file 
    int nWords;
    char** words = getWords(wordsFile, &nWords);
    char lineOfWords[]
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

int main2(){
    char* wordsFile = "words.txt";
    int nWords;
    char** words = getWords(wordsFile, &nWords);

    for(int i = 0; i < nWords; i++){
        printf("%s\n", words[i]);
    }

    free(words);

    return 0;
}