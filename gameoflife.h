#ifndef _GAMEOFLIFE_H_
#define _GAMEOFLIFE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "config.h"

struct world;

struct world *world_alloc(struct config *cfg);
void world_free(struct world *w);

void world_print(const struct world *w);
void world_iterate(struct world *w);

#endif
