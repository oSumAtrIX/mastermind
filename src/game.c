#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "player.c"
#include "gamerules.h"

void destroy_game(game_t *game)
{
	destroy_player(game->player);
	free(game);
}

void set_code(game_t *game)
{
	int i;
	char *code = game->code;

	/* TODO: test if the code is really random */

	if (!code)
		free(code);

	code = malloc(sizeof(char) * CODE_LENGTH);

	srand(time(NULL));
	for (i = 0; i < CODE_LENGTH; i++)
		code[i] = rand() % (TURQUOISE + 1);

	game->current_state = GUESS;
}

int add_guess(game_t *game, char *guess)
{
	game->player->lives--;
	game->current_state = EVALUATE_RESULT;

	game->guesses[PLAYER_LIVES - game->player->lives] = guess;
	return 0;
}

void evaluate_result(game_t *game)
{
	printf("\n%s, your guess was %s\n", game->player->name, game->guesses[PLAYER_LIVES - game->player->lives]);
	printf("%s, your code was %s\n", game->player->name, game->code);
	printf("%s, you have %d lives left\n", game->player->name, game->player->lives);
	
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

	/* TODO: test */
	/* init matrix of guesses */
	game->guesses = malloc(PLAYER_LIVES * sizeof(char *));
	for (i = 0; i < PLAYER_LIVES; i++)
		game->guesses[i] = malloc(CODE_LENGTH * sizeof(char));

	game->current_state = GENERATE_CODE;

	return game;
}