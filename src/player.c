#include <stdlib.h>
#include "player.h"
#include "gamerules.h"

player_t *create_player(const char* name){
	player_t *player = (player_t*)malloc(sizeof(player_t));
	player->name = name;
	player.lives = PLAYER_LIVES;
	return player;
}

void destroy_player(player_t *player) {
	free(player);
}