#include "graphics.h"

void printWord(int x, int y, char* word, textState attr){
    attron(attr);
    mvaddstr(y, x, word);
    attroff(attr);
}

void setupTerminal(){
    initscr();
    cbreak();
    curs_set(FALSE);
    noecho();
    nodelay(stdscr, TRUE);   
}