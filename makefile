CC = gcc

typer: typer.o 
	$(CC) -o typer typer.o -lncurses -lm

typer.o: typer.c
	$(CC) -c typer.c -lncurses -lm

clean:
	rm typer typer.o 