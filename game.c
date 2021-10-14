#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "game.h"
#include "graphics.h"

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
    words = (char**)malloc(sizeof(char*) * (*nWords));
    int wordIndex = 0, charIndex = 0;
    char c;
    while((c = fgetc(file)) != EOF){
        if(c == '\n'){
            words[wordIndex][charIndex] = '\0';
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

void getLineFromFile(char* line, int* lineLength, char** words, int nWords){
    clock_t start = clock();
    double randomTime = (double)start/CLOCKS_PER_SEC;
    srand((int)(randomTime*1000000));
    int i = 0; 
    while(i < MAX_LINE_LENGTH - 1){
        char* randomWord = words[rand() % nWords];
        if(i + strlen(randomWord) < MAX_LINE_LENGTH - 1){
            for(int j=0; j < strlen(randomWord); j++){
                line[j + i] = randomWord[j];
            }
            line[i + strlen(randomWord)] = ' ';
            i += strlen(randomWord) + 1;
        }
        else{break;}
    }
    line[i] = '\0';
    *lineLength = i + 1;
}


void renderLine(int lineHeight, int lineMiddle, char* line, int currentLinePosition, bool* isCharCorrect){
    if(currentLinePosition == -1){// signifies line is inactive, shoud all be drawn in normal
        printWord(lineMiddle - strlen(line)/2, lineHeight, line, normal);
    }
    else{
        int lineLen = strlen(line);
        for(int i=0; i < currentLinePosition; i++){
            if(!isCharCorrect[i]){
                attron(underlined);
                mvaddch(lineHeight, lineMiddle - lineLen/2 + i, line[i]);
                attroff(underlined);
            }
            else{
                mvaddch(lineHeight, lineMiddle - lineLen/2 + i, line[i]);
            }
        }

        attron(highlited);
        mvaddch(lineHeight, lineMiddle - lineLen/2 + currentLinePosition, line[currentLinePosition]);
        attroff(highlited);

        for(int i=currentLinePosition + 1; i < lineLen - 1; i++){
            mvaddch(lineHeight, lineMiddle - lineLen/2 + i, line[i]);
        }
    }
}