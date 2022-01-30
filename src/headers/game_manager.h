#ifndef GAME_MANAGER_H_INCLUDE
#define GAME_MANAGER_H_INCLUDE

#include "node.h"

typedef struct
{
	node_t *game_list;
} game_manager_t;

game_manager_t *create_game_manager();

void add_game(game_manager_t *, const char *);
void run_game_manager(game_manager_t *);

#endif