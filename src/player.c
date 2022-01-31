#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "gamerules.h"

player_t *create_player(char *name)
{
	player_t *player = (player_t *)malloc(sizeof(player_t));

	player->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(player->name, name);

	player->lives = MAX_PLAYER_LIVES;
	return player;
}

void destroy_player(player_t *player)
{
	free(player->name);
	free(player);
}