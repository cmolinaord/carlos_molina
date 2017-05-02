#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gameoflife.h"

void world_init(struct world *w)
{
	// Inicializar mundo a false
	for (int i=0; i<W_SIZE_X; i++)
		for (int j=0; j<W_SIZE_Y; j++)
		{
			w->now[i][j]=false;
			w->next[i][j]=false;
		}

	w->now[1][2]=true;
	w->now[2][3]=true;
	w->now[3][1]=true;
	w->now[3][2]=true;
	w->now[3][3]=true;
}

void world_print(const struct world *w)
{
	for (int i=0; i<W_SIZE_X; i++)
	{
		for (int j=0; j<W_SIZE_Y; j++)
			printf("%s ", world_get_cell(w, i, j) ? "#" : ".");
		printf("\n");
	}
}

void world_step(struct world *w)
{
	for (int i=0; i<W_SIZE_X; i++)
	{
		for (int j=0; j<W_SIZE_Y; j++)
		{
			int neighbors = world_count_neighbors(w, i, j);
			w->next[i][j] = (w->now[i][j] && neighbors == 2) || neighbors == 3;
		}
	}
	world_copy(w);
}

int world_count_neighbors(const struct world *w, int i, int j)
{
	int count=0;
	count += world_get_cell(w, i - 1, j - 1);
	count += world_get_cell(w, i - 1, j    );
	count += world_get_cell(w, i - 1, j + 1);
	count += world_get_cell(w, i    , j - 1);
	count += world_get_cell(w, i    , j + 1);
	count += world_get_cell(w, i + 1, j - 1);
	count += world_get_cell(w, i + 1, j    );
	count += world_get_cell(w, i + 1, j + 1);
	return count;
}

bool world_get_cell(const struct world *w, int i, int j)
{
	if (i == -1)
		i += W_SIZE_X;
	else if (i == W_SIZE_X)
		i -= W_SIZE_X;
	if (j == -1)
		j += W_SIZE_Y;
	else if (j == W_SIZE_Y)
		j -= W_SIZE_Y;

	return w->now[i][j];
}

void world_copy(struct world *w)
{
	for (int i=0; i<W_SIZE_X; i++)
		for (int j=0; j<W_SIZE_Y; j++)
			w->now[i][j] = w->next[i][j];
}
