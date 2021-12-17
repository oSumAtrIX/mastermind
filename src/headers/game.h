#ifndef GAME_H_INCLUDE
#define GAME_H_INCLUDE

#include "player.h"

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
	enum game_state current_state;

	char *code;
	char **guesses;
} game_t;

void destroy_game(game_t *game);
game_t *create_game(const char *playername);
void set_code(game_t *game);
int add_guess(game_t *game, char *guess);
void evaluate_result(game_t *game);

#endif