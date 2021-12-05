#include <stdlib.h>
#include <stdio.h>

#include "game_manager.c"

int main()
{		
	/* Initialize the game manager */
	game_manager = (struct GameManager *) malloc(sizeof(struct GameManager));
	
	/* Add game */
	/* add_game("ohan"); */

	/* ..or two */
	/* add_game("alex"); */
	
	/* Run the game */
	start();
	
	return 0;
}
