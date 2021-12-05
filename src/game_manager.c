#include <stdlib.h>
#include <stdio.h>

#include "game.c"
#include "player.c"
#include "node.c"

struct GameManager {
	struct Node *games;
};

struct GameManager *game_manager;

void add_game(char* name){
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	struct Game *game = (struct Game *)malloc(sizeof(struct Game));
	node->data = game;
	
	if (game_manager->games) {
		node->next = game_manager->games;
		game_manager->games = node;
	} else {
		game_manager->games = node;
	}
	
	game->player =  (struct Player *)malloc(sizeof(struct Player));
	game->player->name = name; 
}

void start(){
	struct Node *games = game_manager->games;
	
	while (1){
		struct Node *current;
		for(current=games; current!=NULL; current=current->next){
			struct Game *game = (struct Game *)current->data;

			printf("%s\n", game->player->name);
			getchar();
			/* TODO: start game */ 
			/* TODO: routines */ 
		}
	}
	
}