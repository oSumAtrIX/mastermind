#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "player.h"
#include "gamerules.h"
#include "row.h"
#include "node.h"

/**
 * @brief Free the current game object
 * @details This will free the players of the current game, the mallocated code string, the games rows and the game object itself
 * @param game The game object to free
 */
void game_destroy(void *game)
{
	game_t *game_to_free = (game_t *)game;
	int i;
	
	for (i = 0; i < MAX_PLAYER_LIVES; i++)
	{
		row_destroy(game_to_free->rows[i]);
	}

	destroy_player(game_to_free->player);
	free(game_to_free->code);
	free(game_to_free);
}

/**
 * @brief Set the current game's code which will be used to check the players guesses
 * 
 * @param game The game to set the code for
 * @param code The code to set, or empty to generate a random code
 */
void set_code(game_t *game, char *code)
{
	int i;

	if (code)
	{
		strcpy(game->code, code);
	}
	else
	{
		srand(time(NULL));
		for (i = 0; i < CODE_LENGTH; i++)
			game->code[i] = available_colors[rand() % count_pegs];
	}

	game->current_state = GUESS;
}

/**
 * @brief Set the guess for a row.
 * @details This will set the guess for a row and check if the guess is correct. The current row used will be selected by the players lives.
 * @param game The game to set the guess for
 * @param guess The guess to set
 */
void add_guess(game_t *game, char *guess)
{
	set_guess(game->rows[MAX_PLAYER_LIVES - game->player->lives], guess);

	game->current_state = EVALUATE_RESULT;
}

int evaluate_result(game_t *game)
{
	row_t *row;
	compare_code(game->code, row = (row_t *)game->rows[MAX_PLAYER_LIVES - game->player->lives--]);

	if (row->black_pegs == CODE_LENGTH)
	{
		game->current_state = END;
		return 1;
	}

	if (game->player->lives == 0)
	{
		game->current_state = END;
		return 0;
	}
	game->current_state = GUESS;
	return -1;
}

/**
 * @brief Helper function to compare the game's code with the given row's guess
 * @note Credits @Alexander Krendl
 * @param code The code to compare against
 * @param row The row to compare the guess of
 * @return int Always returns 0
 */
int compare_code(char *code, row_t *row)
{
	int i;
	char code_copy[CODE_LENGTH];
	char guess_copy[CODE_LENGTH];
	unsigned short count_correct = 0, count_color_correct = 0;

	strncpy(code_copy, code, CODE_LENGTH);
	strncpy(guess_copy, row->guess, CODE_LENGTH);

	for (i = 0; i < CODE_LENGTH; i++)
	{
		if (guess_copy[i] == code_copy[i])
		{
			++count_correct;
			code_copy[i] = 'q';
			guess_copy[i] = 'a';
		}
	}
	for (i = 0; i < CODE_LENGTH; i++)
	{
		int j;
		for (j = 0; j < CODE_LENGTH; j++)
		{
			if (guess_copy[i] == code_copy[j])
			{
				++count_color_correct;
				code_copy[j] = 'q';
				guess_copy[i] = 'a';
				break;
			}
		}
	}
	set_pebles(row, count_correct, count_color_correct);
	return 0;
}

/**
 * @brief Create a game
 * @details This will create a new game for a given playername.
 * @param username The name of the player for the current game
 * @return game_t* The new game object
 */
game_t *game_new(char *username)
{
	int i;

	game_t *game = malloc(sizeof(game_t));
	game->player = create_player(username);
	game->code = calloc(1, CODE_LENGTH + 1);

	game->rows = malloc(MAX_PLAYER_LIVES * sizeof(node_t *));
	for (i = 0; i < MAX_PLAYER_LIVES; i++)
		game->rows[i] = create_row();

	game->current_state = GENERATE_CODE;

	return game;
}