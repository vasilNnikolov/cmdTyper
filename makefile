CC = gcc

typer: typer.o graphics.o game.o start_screen.o score_screen.o  
	$(CC) typer.o graphics.o game.o start_screen.o score_screen.o -lncurses -lm -o typer 

typer.o: typer.c
	$(CC) -c typer.c

graphics.o: graphics.c graphics.h
	$(CC) -c graphics.c

game.o: game.c game.h
	$(CC) -c game.c

start_screen.o: start_screen.c start_screen.h graphics.h
	$(CC) -c start_screen.c

score_screen.o: score_screen.c score_screen.h 
	$(CC) -c score_screen.c

clean:
	rm typer *.o