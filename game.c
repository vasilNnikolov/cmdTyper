#include <stdlib.h>
#include <stdio.h>
#include "game.h"

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