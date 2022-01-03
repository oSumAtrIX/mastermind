#include <string.h>

#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "player.c"
#include "gamerules.h"
#include "row.c"
#include "node.h"

#define USED_A 'q' /* this char indicates, that this peg has been accounted for during comparison for black pegs */
#define USED_B 'a' /* this char indicates, that this peg has been accounted for during comparison for white pegs two different are necessary as otherwise false positives will be indicated */

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

void set_code(game_t *game)
{
	int i;

	srand(time(NULL));

	for (i = 0; i < CODE_LENGTH; i++)
		game->code[i] = available_colors[rand() % C_PEGS];

	game->current_state = GUESS;
}

int add_guess(game_t *game, char *guess)
{
	set_guess(game->rows[PLAYER_LIVES - game->player->lives], guess);
	
	game->current_state = EVALUATE_RESULT;
	return 0;
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

int compare_code(char *code, row_t *row)
/* Function which compares the guess string with the secret code string and determines the number of black pegs (correct char and index) and white pegs (correct char , wrong index).
Input: address to store black pegs, address to store white pegs, guess string, secret code string
Saves: number of black and white pegs to corresponding addresses.
Returns: 0 if everything went fine. */
{
	int i;
	/* create copies of key and guess. As CODELENGTH will always be a comparebly small number, I don't
    use dynamic array, which would have performance advantages with big arrays. */
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