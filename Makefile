CFLAGS = -Wall -Werror
.PHONY : all debug clean uninstall

all: gameoflife

gameoflife: main.o config.o gameoflife.o
	gcc main.o config.o gameoflife.o -o gameoflife

main.o: main.c gameoflife.h
	gcc -c main.c

config.o: config.c config.h
	gcc -c config.c config.h

gameoflife.o: gameoflife.c gameoflife.h
	gcc -c gameoflife.c

debug:
	gcc -g -c main.c
	gcc -g -c gameoflife.c
	gcc -g -c config.c
	gcc -g main.o gameoflife.o config.o -o gameoflife.dbg

clean:
	rm -v *.o *.gch

uninstall:
	rm -v gameoflife gameoflife.dbg
