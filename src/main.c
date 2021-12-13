#include <stdlib.h>
#include <stdio.h>
#include "game_manager.c"

int main()
{		
	/* Initialize the game manager */
	game_manager_init();

	/* add games */
	add_game(manager, "ohan");
	add_game(manager, "alex");
	
	/* start games */
	start();
	return 0;
}
