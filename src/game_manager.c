#include <stdlib.h>
#include <stdio.h>

#include "game_manager.h"
#include "node.c"
#include "game.c"
#include "cli.c"


game_manager_t *create_game_manager()
{
	return malloc(sizeof(game_manager_t));
}

void add_game(game_manager_t *game_manager, const char *foruser)
{
	game_t *game = create_game(foruser);

	if (game_manager->game_list)
	{
		append_node(game_manager->game_list, game);
		return;
	}

	game_manager->game_list = node_new(game);
}

void run_game_manager(game_manager_t *game_manager)
{	
	while (1)
	{
		node_t *current;
		for (current = game_manager->game_list; current; current = current->next)
		{	
			game_t *game = (game_t *)current->data;

			char guess[CODE_LENGTH + 1];
			switch (game->current_state)
			{
				case GENERATE_CODE:
					set_code(game);
					continue;
				case GUESS:
					do {
						get_input(guess, CODE_LENGTH);
						if (validate_input(guess, CODE_LENGTH))
							break;
						printf("Invalid input \"%s\", please try again.\n", guess);
					} while (1);
					add_guess(game, guess);
					continue;
				case EVALUATE_RESULT:
					printf("%s\n", game->code);
					game->result = evaluate_result(game);
					if (game->result == -1)
						printf("You have %d lives left.\n", game->player->lives);
					continue;
				default:
					if (game->result == 1)
						printf("Congratulations, you won!\n");
					else
						printf("Sorry, you lost.\n");
					return; /* TODO: remove & fix multiplayer */
			}
		}
	}
}