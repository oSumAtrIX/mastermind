#ifndef _H_INCLUDE
#define CLI_H_INCLUDE

typedef struct
{
	node_t *game_list;
} game_manager_t;

void game_manager_init();
void add_game(const char *foruser);
void start();