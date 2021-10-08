#include <unistd.h>
#include <ncurses.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>


int main(){
    //initialise the screen
    initscr();
    cbreak();
    curs_set(FALSE);
    noecho();
    nodelay(stdscr, TRUE);    
    while(1){
        clear();
        mvaddch(10, 10, 'k');
        mvaddch(11, 10, 'u');
        mvaddch(12, 10, 'r');

        int c = getch();
        if(c == 'q'){
            break;
        }
        usleep(10000);
    }
    endwin();
    return 0;
}