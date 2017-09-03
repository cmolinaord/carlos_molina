#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "gameoflife.h"


struct world
{
	bool *cells[2];
	int nrows;
	int ncols;
};

static void fix_coords(const struct world *w, int *x, int *y);
static bool get_cell(const struct world *w, int x, int y);
static void set_cell(struct world *w, int buf, int x, int y, bool val);
static int count_neighbors(const struct world *w, int x, int y);
static void init_pattern(struct world *w, int mode);


struct world *world_alloc(struct config *cfg)
{
	struct world *w;
	bool *w0,*w1;

	int ncols = cfg->ncols;
	int nrows = cfg->nrows;
	int mode = cfg->init_mode;

	w = (struct world *)malloc(sizeof(struct world));
	if (!w)
		return NULL;

	w0 = (bool *)malloc(nrows * ncols * sizeof(bool));
	if (!w0) {
		free(w);
		return NULL;
	}
	w1 = (bool *)malloc(nrows * ncols * sizeof(bool));
	if (!w1) {
		free(w);
		free(w0);
		return NULL;
	}

	w->cells[0] = w0;
	w->cells[1] = w1;
	w->nrows   = nrows;
	w->ncols   = ncols;

	init_pattern(w, mode);
	return w;
}

static void init_pattern(struct world *w, int mode)
{
	for (int i = 0; i < w->nrows; i++)
		for (int j = 0; j < w->ncols; j++)
			set_cell(w, 0, i, j, false);

	// default || glider
	if (mode == 0 || mode == 1) {
		set_cell(w, 0, 1, 2, true);
		set_cell(w, 0, 2, 3, true);
		set_cell(w, 0, 3, 1, true);
		set_cell(w, 0, 3, 2, true);
		set_cell(w, 0, 3, 3, true);
	}

	//random
	else if (mode == 2) {
		time_t t;
		srand((unsigned) time(&t));
		for (int i = 0; i < w->nrows; i++)
			for (int j = 0; j < w->ncols; j++)
				set_cell(w, 0, i, j, rand() & 1);
	}
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
	for (int i = 0; i < w->nrows; i++) {
		for (int j = 0; j < w->ncols; j++)
			printf("%s ", get_cell(w, i, j) ? COLOR_GREEN "o" COLOR_RESET
			: COLOR_RED "x" COLOR_RESET);
		printf("\n");
	}
}

void world_iterate(struct world *w)
{
	for (int i = 0; i < w->nrows; i++) {
		for (int j = 0; j < w->ncols; j++) {
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
	if (*x == -1)
		*x += w->nrows;
	else if (*x == w->nrows)
		*x -= w->nrows;
	if (*y == -1)
		*y += w->ncols;
	else if (*y == w->ncols)
		*y -= w->ncols;
}


static bool get_cell(const struct world *w, int x, int y)
{
	fix_coords(w, &x, &y);
	return w->cells[0][x * w->ncols + y];
}

static void set_cell(struct world *w, int buf, int x, int y, bool val)
{
	int offset = x * w->ncols + y;
	*(w->cells[buf] + offset) = val;
}
