#include "game.h"
#include "player.c"
#include "utils.h"

char *get_code(game_t *game)
{
	return game->code;
}

void generate_code(game_t *game)
{ 
	game->code = malloc(sizeof(char) * 4);
	game->code[0] = rand() % 6 + 1; //TODO: peble colors
	game->code[1] = rand() % 6 + 1; //TODO: peble colors
	game->code[2] = rand() % 6 + 1; //TODO: peble colors
	game->code[3] = rand() % 6 + 1; //TODO: peble colors

	game->current_state = GUESS;
}

int make_guess(game_t *game, const char *guess)
{	
	game->guess_count++;
	game->current_state = EVALUATE_RESULT;
	return compare_string(game->code, guess);
}

void evaluate_result(game_t *game)
{

}

void create_game(const char* playername) {
	game_t *game = malloc(sizeof(game_t));
	game->player = create_player(playername);
	generate_code(game);

	game->player = create_player();
	game->map = create_map();
	game->current_state = GENERATE_CODE;
}