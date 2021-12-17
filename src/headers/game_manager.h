#ifndef CLI_H_INCLUDE
#define CLI_H_INCLUDE

#include "node.h"

typedef struct
{
	node_t *game_list;
} game_manager_t;

void game_manager_init();

void add_game(const char *foruser);
void start();

#endif