#include <stdlib.h>
#include "screen_manager.h"
#include "screen.h"
#include "node.h"
#include <stdio.h>

/**
 * @brief Create a screen manager object
 * @details The screen manager holds a list of screens
 * @return screen_manager_t* The created screen manager object
 */
screen_manager_t *screen_manager_new()
{
	screen_manager_t *screen_manager = malloc(sizeof(screen_manager_t));
	return screen_manager;
}

/**
 * @brief Add a screen to the screen manager
 *
 * @param screen_manager The screen manager to add the screen to
 * @param screen The screen to add
 */
void add_screen(screen_manager_t *screen_manager, screen_t *screen)
{
	if (screen_manager->screen_list)
	{
		append_node(screen_manager->screen_list, screen);
		return;
	}

	screen_manager->screen_list = node_new(screen);
}

/**
 * @brief Show the screen with the given id
 * @details This will loop over all screens and execute the current screen
 * @param screen_manager The screen manager to show the screen in
 * @param id The id of the screen to show
 */
void show_screen(screen_manager_t *screen_manager, unsigned short id)
{
	node_t *current_screen;
	for (current_screen = screen_manager->screen_list; current_screen; current_screen = current_screen->next)
	{
		screen_t *screen = (screen_t *)current_screen->data;
		int result;
		
		if (screen->id != id)
			continue;

		result = run_screen(screen);
		/* 
		If the screen script returns something other than -1, it means, the user entered an invalid input.
		We try to minimize the amount of error which we have to report to the user, so we just go back to the main menu.
		*/
		show_screen(screen_manager, result > -1 ? result : 0);
		return;
	}
}

/**
 * @brief Free the screen manager
 * @details This will loop over all screens of the current screen manager and free them
 * @param screen_manager The screen manager to free
 */
void screen_manager_destroy(screen_manager_t *screen_manager)
{
	nodes_destroy(screen_manager->screen_list, screen_destroy);
	free(screen_manager);
}
