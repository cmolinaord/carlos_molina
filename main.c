#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gameoflife.h"

int main()
{
	int i = 0;
	int nrows = 14;
	int ncols = 14;

	struct world *w;
	w = world_alloc(nrows, ncols);
	do {
		printf("\033cIteration %d\n", i++);
		world_print(w);
		world_iterate(w);
	} while (getchar() != 'q');
	world_free(w);

	return EXIT_SUCCESS;
}
