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
void destroy_game(game_t *game)
{
	int i;
	destroy_player(game->player);
	free(game->code);
	for (i = 0; i < PLAYER_LIVES; i++)
	{
		destroy_row(game->rows[i]);
	}
	free(game);
}

/**
 * @brief Set the current game's code which will be used to check the players guesses
 * 
 * @param game The game to set the code for
 */
void set_code(game_t *game)
{
	int i;

	srand(time(NULL));

	for (i = 0; i < CODE_LENGTH; i++)
		game->code[i] = available_colors[rand() % C_PEGS];

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
	set_guess(game->rows[PLAYER_LIVES - game->player->lives], guess);

	game->current_state = EVALUATE_RESULT;
}

int evaluate_result(game_t *game)
{
	row_t *row;
	compare_code(game->code, row = (row_t *)game->rows[PLAYER_LIVES - game->player->lives--]);

	if (row->c_right_pegs == CODE_LENGTH)
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
 * 
 * @param code The code to compare against
 * @param row The row to compare the guess of
 * @return int Always returns 0
 */
int compare_code(char *code, row_t *row)
{
	int i;
	char code_copy[CODE_LENGTH];
	char guess_copy[CODE_LENGTH];
	unsigned short count_correct = 0;
	unsigned short count_color_correct = 0;

	strncpy(code_copy, code, CODE_LENGTH);
	strncpy(guess_copy, row->guess, CODE_LENGTH);

	for (i = 0; i < CODE_LENGTH; i++)
	{
		if (guess_copy[i] == code_copy[i])
		{
			++count_correct;
			code_copy[i] = USED_A;
			guess_copy[i] = USED_B;
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
				code_copy[j] = USED_A;
				guess_copy[i] = USED_B;
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
 * @param playername The name of the player for the current game
 * @return game_t* The new game object
 */
game_t *create_game(const char *playername)
{
	int i;

	game_t *game = malloc(sizeof(game_t));
	game->player = create_player(playername);
	game->code = malloc(sizeof(char) * CODE_LENGTH);

	game->rows = malloc(PLAYER_LIVES * sizeof(node_t *));
	for (i = 0; i < PLAYER_LIVES; i++)
		game->rows[i] = create_row();

	game->current_state = GENERATE_CODE;

	return game;
}