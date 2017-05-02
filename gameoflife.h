#ifndef _GAMEOFLIFE_H_
#define _GAMEOFLIFE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define tamanio mundo
#define W_SIZE_X 25
#define W_SIZE_Y 40
// Las primeras y ultmas columnas/filas son parte del borde y no juegan

struct world {
	bool now[W_SIZE_X][W_SIZE_Y];
	bool next[W_SIZE_X][W_SIZE_Y];
};

void world_init(struct world *w);
void world_print(const struct world *w);
void world_step(struct world *w);
int world_count_neighbors(const struct world *w, int i, int j);
bool world_get_cell(const struct world *w, int i, int j);
void world_copy(struct world *w);

#endif
