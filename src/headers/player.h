#ifndef PLAYER_H_INCLUDE
#define PLAYER_H_INCLUDE

typedef struct {
	const char *name;
	int score;
	int lives;
} player_t;

player_t *create_player(const char *name);
void destroy_player(player_t *player);

#endif