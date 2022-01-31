#ifndef GAME_MANAGER_H_INCLUDE
#define GAME_MANAGER_H_INCLUDE

#include "node.h"
#include "result_manager.h"

typedef struct
{
	node_t *game_list;
	short count_players;
	result_manager_t *result_manager;
} game_manager_t;

game_manager_t *game_manager_new();

void add_game(game_manager_t *game_manager, char *username );
void run_game_manager(game_manager_t *game_manager);
void game_manager_destroy(game_manager_t *game_manager);

#endif