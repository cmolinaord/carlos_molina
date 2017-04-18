#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define tamanio mundo
#define W_SIZE_X 10
#define W_SIZE_Y 10

void world_init(bool world_1[W_SIZE_X][W_SIZE_Y]);
void world_print(bool world_1[W_SIZE_X][W_SIZE_Y]);
void world_step(/* Recibo dos mundos */);
int world_count_neighbors(/* Recibo un mundo y unas coordenadas */);
bool world_get_cell(/* Recibo un mundo y unas coordenadas */);
void world_copy(/* Recibo dos mundos */);

int main()
{
	int i = 0;

	bool world_1[W_SIZE_X][W_SIZE_Y];
	bool world_2[W_SIZE_X][W_SIZE_Y];

	world_init(world_1);

	do {
		printf("\033cIteration %d\n", i++);
		world_print(world_1);
		// TODO: Itera
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void world_init(bool world_1[W_SIZE_X][W_SIZE_Y])
{
	// Inicializar mundo a fase
	for (int i=0; i<W_SIZE_X; i++)
	{
		for (int j=0; j<W_SIZE_Y; j++)
		{
			world_1[i][j]=false;
		}
	}

	/* Inicializar con el patrón del glider:
	*           . # .
	*           . . #
	*           # # #
	*/
	world_1[0][1]=true;
	world_1[1][2]=true;
	world_1[2][0]=true;
	world_1[2][1]=true;
	world_1[2][2]=true;

}

void world_print(bool world_1[W_SIZE_X][W_SIZE_Y])
{
	printf("Imprimir\n");
	// Imprimir mundo
	for (int i=0; i<W_SIZE_X; i++)
	{
		for (int j=0; j<W_SIZE_Y; j++)
		{
			if (world_1[i][j])
				printf("# ");
			else
				printf(". ");
		}
		printf("\n");
	}
}

void world_step(/* Recibo dos mundos */)
{
	/*
	 * TODO:
	 * - Recorrer el mundo célula por célula comprobando si nace, sobrevive
	 *   o muere.
	 *
	 * - No se puede cambiar el estado del mundo a la vez que se recorre:
	 *   Usar un mundo auxiliar para guardar el siguiente estado.
	 *
	 * - Copiar el mundo auxiliar sobre el mundo principal
	 */
}

int world_count_neighbors(/* Recibo un mundo y unas coordenadas */)
{
	// Devuelve el número de vecinos
}

bool world_get_cell(/* Recibo un mundo y unas coordenadas */)
{
	/*
	 * TODO: Devuelve el estado de la célula de posición indicada
	 * (¡cuidado con los límites del array!)
	 */
}

void world_copy(/* Recibo dos mundos */)
{
	// TODO: copia el mundo segundo mundo sobre el primero
}
