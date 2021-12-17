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
			{
				printf("%s, please enter your guess: ", game->player->name);
				get_input(guess);
				add_guess(game, guess);
				continue;
			}
			case EVALUATE_RESULT:
				printf("Evaluating result for %s\n", game->player->name);
				evaluate_result(game);
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