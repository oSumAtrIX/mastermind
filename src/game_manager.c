#include <stdlib.h>
#include <stdio.h>

#include "game_manager.h"
#include "node.h"
#include "game.h"
#include "cli.h"
#include "gamerules.h"

/**
 * @brief Create a game manager
 * @details The game manager holds a list of games
 * @return game_manager_t* The created game manager object
 */
game_manager_t *game_manager_new()
{
	game_manager_t *game_manager = calloc(1, sizeof(game_manager_t));
	game_manager->result_manager = result_manager_new("results.txt");
	
	return game_manager;
}

/**
 * @brief Add a game to the game manager
 *
 * @param game_manager The game manager to add the game to
 * @param username The username of the player
 */
void add_game(game_manager_t *game_manager, char *username)
{
	game_t *game = game_new(username);
	game_manager->count_players++;

	if (game_manager->game_list)
	{
		append_node(game_manager->game_list, game);
		return;
	}

	game_manager->game_list = node_new(game);
}

/**
 * @brief Destroy a game manager object
 * 
 * @param game_manager The game manager to destroy
 */
void game_manager_destroy(game_manager_t *game_manager)
{
	nodes_destroy(game_manager->game_list, game_destroy);
	result_manager_destroy(game_manager->result_manager);
	free(game_manager);
}

/**
 * @brief Handle a game inside the game manager
 * 
 * @param game_manager The game manager to handle the game in
 * @param game The game to handle
 * @return int 0 if the game is not finished, 1 if the game is finished
 */
int handle_game_logic(game_manager_t *game_manager, game_t *game)
{
	char guess[CODE_LENGTH + 1];
	switch (game->current_state)
	{
	case GENERATE_CODE:
		if (game_manager->count_players > 1)
		{
			char code[CODE_LENGTH + 1];
			do
			{
				printf("[%s] Let your opponent chose a code for you [length %i]:\n", game->player->name, CODE_LENGTH);
				read_input(code, CODE_LENGTH + 1);
				if (validate_input(code, CODE_LENGTH))
					break;
				printf("\"%s\" invalid. Please try again.\n", code);
			} while (1);

			set_code(game, code);
		}
		else
		{
			set_code(game, NULL);
		}
		clear();
		return 0;
	case GUESS:
	{
		int i;
		clear();
		for (i = 0; i < (MAX_PLAYER_LIVES - game->player->lives); i++)
		{
			row_t *current_row = (row_t *)game->rows[i];
			printf("| %s | Black: %i | White: %i |\n", current_row->guess, current_row->black_pegs, current_row->white_pegs);
		}
		do
		{
			printf("\n[%s] Guess: ", game->player->name);

			read_input(guess, CODE_LENGTH);
			if (validate_input(guess, CODE_LENGTH))
				break;

			printf("\"%s\" invalid.", guess);
		} while (1);

		add_guess(game, guess);
		return 0;
	}
	case EVALUATE_RESULT:
	{
		short win = 0, lose = 0;
		game->result = evaluate_result(game);

		if (game->result == -1)
		{
			clear();
			printf("[%s] %d lives left. Enter to continue", game->player->name, game->player->lives);
			getchar();
			return 0;
		}

		if (game->result == 1)
		{
			printf("[%s] You won! Enter to continue.", game->player->name);
			win = 1;
		}else {
			printf("%s, you lost! Your code was %s. Enter to continue.", game->player->name, game->code);
			lose = 1;
		}

		update_result(game_manager->result_manager, game->player->name, win, lose);
		getchar();
		return 1;
	}
	default:
		return 0;
	}
}

/** 
 * @brief Run the game manager
 * @details This will loop over all games and execute the current games state.
 * @param game_manager The game manager to run
 */
void run_game_manager(game_manager_t *game_manager)
{
	while (1)
	{
		node_t *current;
		for (current = game_manager->game_list; current; current = current->next)
		{
			game_t *game = (game_t *)current->data;
			if (handle_game_logic(game_manager, game)){
				save_results(game_manager->result_manager, "results.txt");
				return;
			}
		}
	}
}