#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "player.c"
#include "gamerules.h"
#include "row.c"
#include "node.h"

void destroy_game(game_t *game)
{
	int i;
	destroy_player(game->player);
	free(game->code);
	for (i = 0; i < PLAYER_LIVES; i++) {
		destroy_row(game->rows[i].data);
		remove_node(game->rows, game->rows + i);
	}
	free(game);
}

void set_code(game_t *game)
{
	int i;

	srand(time(NULL));

	for (i = 0; i < CODE_LENGTH; i++)
		game->code[i] = available_colors[rand() % (C_PEGS + 1)];

	game->current_state = GUESS;
}

int add_guess(game_t *game, char *guess)
{
	game->player->lives--;
	game->current_state = EVALUATE_RESULT;

	set_guess(game->rows[PLAYER_LIVES - game->player->lives].data, guess);
	return 0;
}

int evaluate_result(game_t *game)
{
	if (game->player->lives == 0)
	{
		game->current_state = END;
		return 0;
	}

	/* cmpcode */
	if (0) {
		game->current_state = END;
		return 1;
	}

	game->current_state = GUESS;
	return -1;
}

game_t *create_game(const char *playername)
{
	int i;

	game_t *game = malloc(sizeof(game_t));
	game->player = create_player(playername);
	game->code = malloc(sizeof(char) * CODE_LENGTH);

	game->rows = malloc(PLAYER_LIVES * sizeof(node_t *));
	for (i = 0; i < PLAYER_LIVES; i++)
		game->rows[i].data = create_row();

	game->current_state = GENERATE_CODE;

	return game;
}