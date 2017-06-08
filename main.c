#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "config.h"
#include "gameoflife.h"

int main(int argc, char *argv[])
{
	int i = 0;

	struct config cfg;
	struct world *w;

	if (!config_parse_argv(&cfg, argc, argv)) {
		printf("ERROR: bad input\n");
		config_print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	else if (cfg.show_help) {
		config_print_usage(argv[0]);
		return EXIT_SUCCESS;
	}

	w = world_alloc(&cfg);
	if (!w) {
		perror("Cannot allocate world");
		exit(EXIT_FAILURE);
	}

	do {
		printf("\033cIteration %d\n", i++);
		world_print(w);
		world_iterate(w);
	} while (getchar() != 'q');
	world_free(w);

	// Print config that has been used (for debbug)
	config_print(&cfg);
	
	return EXIT_SUCCESS;
}
