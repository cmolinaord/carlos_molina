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

int main()
{
	int i = 0;

	bool world_1[W_SIZE_X][W_SIZE_Y];
	bool world_2[W_SIZE_X][W_SIZE_Y];

	world_init(world_1);

	do {
		printf("\033cIteration %d\n", i++);
		world_print(world_1);
		world_step(world_1, world_2);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void world_init(bool world_1[W_SIZE_X][W_SIZE_Y])
{
	// Inicializar mundo a fase
	for (int i=0; i<W_SIZE_X; i++)
		for (int j=0; j<W_SIZE_Y; j++)
			world_1[i][j]=false;

	/* Inicializar con el patrón del glider:
	*           . # .
	*           . . #
	*           # # #
	*/
	world_1[1][2]=true;
	world_1[2][3]=true;
	world_1[3][1]=true;
	world_1[3][2]=true;
	world_1[3][3]=true;
/*
	world_1[4][24]=true;
	world_1[5][23]=true;
	world_1[6][23]=true;
	world_1[6][24]=true;
	world_1[6][25]=true;
	*/
}

void world_print(bool world_1[W_SIZE_X][W_SIZE_Y])
{
	// Imprimir solo las coordenadas activas
	for (int i=0; i<W_SIZE_X; i++)
	{
		for (int j=0; j<W_SIZE_Y; j++)
			printf("%s ", world_get_cell(world_1, i, j) ? "#" : ".");
		printf("\n");
	}
}

void world_step(bool world_1[W_SIZE_X][W_SIZE_Y], bool world_2[W_SIZE_X][W_SIZE_Y])
{
	for (int i=0; i<W_SIZE_X; i++)
	{
		for (int j=0; j<W_SIZE_Y; j++)
		{
			int neighbors=world_count_neighbors(world_1, i, j);
			world_2[i][j] = (world_1[i][j] && neighbors == 2) || neighbors == 3;
		}
	}
	// Copiar el mundo auxiliar sobre el antiguo
	world_copy(world_1, world_2);
}

int world_count_neighbors(bool world_1[W_SIZE_X][W_SIZE_Y], int i, int j)
{
	int count=0;
	count += world_get_cell(world_1, i - 1, j - 1);
	count += world_get_cell(world_1, i - 1, j    );
	count += world_get_cell(world_1, i - 1, j + 1);
	count += world_get_cell(world_1, i    , j - 1);
	count += world_get_cell(world_1, i    , j + 1);
	count += world_get_cell(world_1, i + 1, j - 1);
	count += world_get_cell(world_1, i + 1, j    );
	count += world_get_cell(world_1, i + 1, j + 1);
	return count;
}

bool world_get_cell(bool world_1[W_SIZE_X][W_SIZE_Y], int i, int j)
{
	if (i == -1)
		i += W_SIZE_X;
	else if (i == W_SIZE_X)
		i -= W_SIZE_X;
	if (j == -1)
		j += W_SIZE_Y;
	else if (j == W_SIZE_Y)
		j -= W_SIZE_Y;

	return world_1[i][j];
}

void world_copy(bool world_1[W_SIZE_X][W_SIZE_Y], bool world_2[W_SIZE_X][W_SIZE_Y])
{
	for (int i=0; i<W_SIZE_X; i++)
			for (int j=0; j<W_SIZE_Y; j++)
				world_1[i][j]=world_2[i][j];
}
