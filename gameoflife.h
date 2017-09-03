#ifndef _GAMEOFLIFE_H_
#define _GAMEOFLIFE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "config.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

struct world;

struct world *world_alloc(struct config *cfg);
void world_free(struct world *w);

void world_print(const struct world *w);
void world_iterate(struct world *w);

#endif
