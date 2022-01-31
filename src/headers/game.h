#ifndef GAME_H_INCLUDE
#define GAME_H_INCLUDE

#include "player.h"
#include "row.h"
#include "node.h"

enum game_state
{
	GENERATE_CODE = 0,
	GUESS = 1,
	EVALUATE_RESULT = 2,
	END = 3
};

typedef struct
{
	player_t *player;
	char *code;
	row_t **rows;
	int result;
	enum game_state current_state;
} game_t;

void game_destroy(void *game);
game_t *game_new(char *username);
void set_code(game_t *game, char *code);
void add_guess(game_t *game, char *guess);
int evaluate_result(game_t *game);
int compare_code(char *code, row_t *row);

#endif