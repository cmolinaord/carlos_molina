#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gameoflife.h"

int main()
{
	int i = 0;
	int size_x = 14;
	int size_y = 14;

	struct world *w;
	w = world_alloc(size_x, size_y);
	do {
		printf("\033cIteration %d\n", i++);
		world_print(w);
		world_iterate(w);
	} while (getchar() != 'q');
	world_free(w);

	return EXIT_SUCCESS;
}
