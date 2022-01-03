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
	int i, available_colors[8] = { RED, GREEN, BLUE, YELLOW, VIOLET, ORANGE, PINK, TURQUOISE };

	srand(time(NULL));

	for (i = 0; i < CODE_LENGTH; i++)
		game->code[i] = available_colors[rand() % ((GAME_VARIANT ? 8 : 6) + 1)];

	game->current_state = GUESS;
}

int add_guess(game_t *game, char *guess)
{
	game->player->lives--;
	game->current_state = EVALUATE_RESULT;

	set_guess(game->rows[PLAYER_LIVES - game->player->lives].data, guess);
	return 0;
}

void evaluate_result(game_t *game)
{
	printf("\n%s, your guess was %s\n", game->player->name, ((row_t *)game->rows[PLAYER_LIVES - game->player->lives].data)->guess);
	printf("%s, your code was %s\n", game->player->name, game->code);
	
	if (game->player->lives == 0)
	{
		printf("%s, you lost!\n", game->player->name);
		game->current_state = END;
	}
	else
	{
		printf("%s, you have %d lives left\n", game->player->name, game->player->lives);
		game->current_state = GUESS;
	}

	game->current_state = GUESS;
	/* TODO (compare_code.c) */
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