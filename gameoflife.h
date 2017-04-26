#ifndef _GAMEOFLIFE_H_
#define _GAMEOFLIFE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define tamanio mundo
#define W_SIZE_X 25
#define W_SIZE_Y 40
// Las primeras y ultmas columnas/filas son parte del borde y no juegan

void world_init(bool world_1[W_SIZE_X][W_SIZE_Y]);
void world_print(bool world_1[W_SIZE_X][W_SIZE_Y]);
void world_step(bool world_1[W_SIZE_X][W_SIZE_Y], bool world_2[W_SIZE_X][W_SIZE_Y]);
int world_count_neighbors(bool world_1[W_SIZE_X][W_SIZE_Y], int i, int j);
bool world_get_cell(bool world_1[W_SIZE_X][W_SIZE_Y], int i, int j);
void world_copy(bool world_1[W_SIZE_X][W_SIZE_Y], bool world_2[W_SIZE_X][W_SIZE_Y]);

#endif
