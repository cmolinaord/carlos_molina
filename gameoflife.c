#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gameoflife.h"

struct world
{
	bool *cells[2];
	int size_x;
	int size_y;
};

static void fix_coords(const struct world *w, int *x, int *y);
static bool get_cell(const struct world *w, int x, int y);
static void set_cell(struct world *w, int buf, int x, int y, bool val);
static int count_neighbors(const struct world *w, int x, int y);
static void init_pattern(struct world *w);


struct world *world_alloc(int size_x, int size_y)
{
	struct world *w;
	bool *w0,*w1;

	w = (struct world *)malloc(sizeof(struct world));
	if (!w)
		return NULL;

	w0 = (bool *)malloc(size_x * size_y * sizeof(bool));
	if (!w0) {
		free(w);
		return NULL;
	}
	w1 = (bool *)malloc(size_x * size_y * sizeof(bool));
	if (!w1) {
		free(w);
		free(w0);
		return NULL;
	}

	w->cells[0] = w0;
	w->cells[1] = w1;
	w->size_x   = size_x;
	w->size_y   = size_y;

	init_pattern(w);
	return w;
}

static void init_pattern(struct world *w)
{
	for (int i = 0; i < w->size_x; i++)
		for (int j = 0; j < w->size_y; j++) {
			set_cell(w, 0, i, j, false);
		}
	set_cell(w, 0, 1, 2, true);
	set_cell(w, 0, 2, 3, true);
	set_cell(w, 0, 3, 1, true);
	set_cell(w, 0, 3, 2, true);
	set_cell(w, 0, 3, 3, true);
}

void world_free(struct world *w)
{
	free(w->cells[0]);
	free(w->cells[1]);
	free(w);
}

void world_print(const struct world *w)
{
	//Print the world stored in cells[0]
	int size_x = w->size_x;
	int size_y = w->size_y;

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++)
			printf("%s ", get_cell(w, i, j) ? "#" : ".");
		printf("\n");
	}
}

void world_iterate(struct world *w)
{
	int size_x = w->size_x;
	int size_y = w->size_y;

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			int neighbors = count_neighbors(w, i, j);
			bool next = (get_cell(w, i, j) && neighbors == 2) || neighbors == 3;
			//set cells in world[1]
			set_cell(w, 1, i, j, next);
		}
	}
	// Put the new world in cells[0] and the old world in cells[1]
	bool *aux = w->cells[1];
	w->cells[1] = w->cells[0];
	w->cells[0] = aux;
}

int count_neighbors(const struct world *w, int x, int y)
{
	int count=0;
	count += get_cell(w, x - 1, y - 1);
	count += get_cell(w, x - 1, y    );
	count += get_cell(w, x - 1, y + 1);
	count += get_cell(w, x    , y - 1);
	count += get_cell(w, x    , y + 1);
	count += get_cell(w, x + 1, y - 1);
	count += get_cell(w, x + 1, y    );
	count += get_cell(w, x + 1, y + 1);
	return count;
}

static void fix_coords(const struct world *w, int *x, int *y)
{
	int size_x = w->size_x;
	int size_y = w->size_y;

	if (*x == -1)
		*x += size_x;
	else if (*x == size_x)
		*x -= size_x;
	if (*y == -1)
		*y += size_y;
	else if (*y == size_y)
		*y -= size_y;
}


static bool get_cell(const struct world *w, int x, int y)
{
	fix_coords(w, &x, &y);
	return w->cells[0][x * w->size_y + y];
}

static void set_cell(struct world *w, int buf, int x, int y, bool val)
{
	int offset = x * w->size_y + y;
	*(w->cells[buf] + offset) = val;
}
