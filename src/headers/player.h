#ifndef PLAYER_H_INCLUDE
#define PLAYER_H_INCLUDE

typedef struct {
	char *name;
	int score;
	int lives;
} player_t;

player_t *create_player(char *username);
void destroy_player(player_t *player);

#endif