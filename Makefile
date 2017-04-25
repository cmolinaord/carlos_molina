CFLAGS = -Wall -Werror

.PHONY : all clean

all: gameoflife

gameoflife: main.c gameoflife.c
	gcc main.c gameoflife.c -o gameoflife

main.o: main.c gameoflife.h
	gcc -c main.c

gameoflife.o: gameoflife.c gameoflife.h
	gcc -c gameoflife.c

clean:
	rm *.o *.gch

uninstall:
	rm gameoflife
