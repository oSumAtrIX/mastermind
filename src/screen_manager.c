#include "screen_manager.h"
#include "screen.c"
#include "node.c"
#include "stdio.h"

screen_manager_t *create_screen_manager()
{
	screen_manager_t *screen_manager = malloc(sizeof(screen_manager_t));
	return screen_manager;
}

void read_config(screen_manager_t *screen_manager, char *from_file)
{
	/* TODO: from_file */
}

void add_screen(screen_manager_t *screen_manager, screen_t *screen)
{
	if (screen_manager->screen_list)
	{
		append_node(screen_manager->screen_list, screen);
		return;
	}

	screen_manager->screen_list = node_new(screen);
}

void show_screen(screen_manager_t *screen_manager, unsigned short id)
{
	node_t *current_screen;
	for (current_screen = screen_manager->screen_list; current_screen; current_screen = current_screen->next)
	{
		screen_t *screen = (screen_t *)current_screen->data;
		if (screen->id == id)
		{
			int result = run_screen(screen);
			if (result > 0)
				show_screen(screen_manager, result);
			return;
		}
	}
}

void destroy_screen_manager(screen_manager_t *screen_manager)
{
	node_t *current_screen;
	for (current_screen = screen_manager->screen_list; current_screen; current_screen = current_screen->next)
	{
		screen_t *screen = (screen_t *)current_screen->data;
		destroy_screen(screen);
	}
	free(screen_manager);
}
