CFLAGS = -Wall -Werror
.PHONY : all clean uninstall

all: gameoflife

gameoflife: main.o gameoflife.o
	gcc main.o gameoflife.o -o gameoflife

main.o: main.c gameoflife.h
	gcc -c main.c

gameoflife.o: gameoflife.c gameoflife.h
	gcc -c gameoflife.c

clean:
	rm *.o *.gch

uninstall:
	rm gameoflife
