#ifndef GAME_H_INCLUDE
#define GAME_H_INCLUDE

typedef enum
{
	GENERATE_CODE,
	GUESS,
	EVALUATE_RESULT
} game_state_t;

typedef struct
{
	struct player_t *player;
	enum game_state_t current_state;

	unsigned const char *code;
	unsigned char **guesses;
	unsigned short guess_count;
} game_t;

void create_game(game_t *game);
char *get_code(game_t *game);
void generate_code(game_t *game);
int make_guess(game_t *game, const char *guess);
void evaluate_result(game_t *game);

#endif