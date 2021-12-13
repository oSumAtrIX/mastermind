#include <stdlib.h>
#include <stdio.h>

#include "game_manager.h"
#include "node.c"
#include "cli.c"

game_manager_t *game_manager;

/* create new game_manager if not done already*/
void game_manager_init()
{
	if (!game_manager) game_manager = (game_manager_t*)malloc(sizeof(game_manager_t));
}

void add_game(const char* foruser)
{	
	game_t *game = create_game(foruser);

	if (game_manager->game_list) {
		prepend_node(game_manager->game_list, game);
	} else {
		game_manager->games = node_new(game);
	}
}

void start()
{
	while (1){
		node_t *current;
		for(current=game_manager->game_list; current!=NULL; current=current->next){
			game_t *game = (game_t*)current->data;
		
			printf("Turn: %s\n", game->player->name);

			switch (game->current_state) {
				case GENERATE_CODE:
					generate_code(game);
					break;
				case GUESS:
					const char guess[4];
					get_input(guess);
					make_guess(game, guess);
					break;
				case EVALUATE:
					evaluate(game);
					break;
				default:
					continue;
			}
		}
	}
	
}