#include <stdlib.h>
#include <stdio.h>

#include "game_manager.h"
#include "node.c"
#include "game.c"
#include "cli.c"

game_manager_t *game_manager;

/* create new game_manager if not done already*/
void game_manager_init()
{
	if (!game_manager)
		game_manager = (game_manager_t *)malloc(sizeof(game_manager_t));
}

void add_game(const char *foruser)
{
	game_t *game = create_game(foruser);

	if (game_manager->game_list)
	{
		prepend_node(game_manager->game_list, game);
		return;
	}

	game_manager->game_list = node_new(game);
}

void start()
{		
	int result;
	while (1)
	{
		node_t *current;
		for (current = game_manager->game_list; current != NULL; current = current->next)
		{
			game_t *game = (game_t *)current->data;
			char guess[CODE_LENGTH + 1];
			switch (game->current_state)
			{
			case GENERATE_CODE:
				printf("Generating code for %s\n", game->player->name);
				set_code(game);
				continue;
			case GUESS:
				printf("%s, please enter your guess: ", game->player->name);
				do {
					get_input(guess, CODE_LENGTH);
					if (validate_input(guess, CODE_LENGTH))
						break;
					printf("Invalid input \"%s\", please try again.\n", guess);
				} while (1);
				add_guess(game, guess);
				continue;
			case EVALUATE_RESULT:
				printf("Evaluating result for %s\n", game->player->name);
				printf("\n%s, your guess was %s\n", game->player->name, ((row_t *)game->rows[PLAYER_LIVES - game->player->lives].data)->guess);
				printf("%s, your code was %s\n", game->player->name, game->code);
				result = evaluate_result(game);
				if (result == 1) printf("%s, you won!\n", game->player->name);
				else if (result == 0) printf("%s, you lost!\n", game->player->name);
				else printf("%s, you lost!\n", game->player->name);
				continue;
			default:
				printf("%s, you lost!\n", game->player->name);
				destroy_game(game);
				remove_node(game_manager->game_list, current);
				continue;
			}
		}
	}
}