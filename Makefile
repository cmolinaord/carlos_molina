CFLAGS = -Wall -Werror
.PHONY : all debug clean uninstall

all: gameoflife

gameoflife: main.o gameoflife.o
	gcc main.o gameoflife.o -o gameoflife

main.o: main.c gameoflife.h
	gcc -c main.c

gameoflife.o: gameoflife.c gameoflife.h
	gcc -c gameoflife.c

debug:
	gcc -B -g -c main.c
	gcc -B -g -c gameoflife.c
	gcc -B -g main.o gameoflife.o -o gameoflife.dbg
	echo "...q" | valgrind --leak-check=full ./gameoflife.dbg
clean:
	rm -v *.o *.gch

uninstall:
	rm -v gameoflife gameoflife.dbg
