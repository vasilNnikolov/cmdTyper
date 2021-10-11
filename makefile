CC = gcc

typer: typer.o graphics.o game.o
	$(CC) typer.o graphics.o game.o -lncurses -lm -o typer 

typer.o: typer.c
	$(CC) -c typer.c

graphics.o: graphics.c graphics.h
	$(CC) -c graphics.c

game.o: game.c game.h
	$(CC) -c game.c

clean:
	rm typer *.o