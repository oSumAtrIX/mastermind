#include "screen.h"
#include "node.h"
#include "cli.h"

typedef int (*inner)(void *, char);

screen_t *create_screen(unsigned short id, char *frame, node_t *options, screenScript script)
{
	screen_t *screen = malloc(sizeof(screen_t));
	screen->id = id;
	screen->frame = frame;
	screen->screen_options = options;
	screen->screen_script = script;
	return screen;
}

screen_option_t *create_option(char key, char *screen_name, unsigned short screen_id)
{
	screen_option_t *screen_option = malloc(sizeof(screen_option_t));
	screen_option->key = key;
	screen_option->screen_name = screen_name;
	return screen_option;
}

int loop_and_execute_inner(screen_t *screen, inner function, char function_param)
{
	node_t *current_option;
	for (current_option = screen->screen_options; current_option; current_option = current_option->next)
	{
		screen_option_t *option = (screen_option_t *)current_option->data;
		int result = function(option, function_param);
		if (result > -1) return result;
	}
	return -1;
}

int print_option(screen_option_t *option)
{
	printf("<%c> %s |", option->key, option->screen_name);
	return -1;
}

int get_screen_id(screen_option_t *option, char *selection){
	return option->key == selection ? option->screen_id : -1;
}

int run_screen(screen_t *screen)
{
	clear();
	int selected_screen_id;

	// draw screen
	draw(screen->frame);

	if (screen->screen_options) {
		// draw options
		printf("| ");
		loop_and_execute_inner(screen, print_option, NULL);
		printf("\n");

		// get user input
		selected_screen_id = loop_and_execute_inner(screen, get_screen_id, getchar());
		flush_buffer();
	}

	// run script of screen
	if (screen->screen_script) screen->screen_script();
	
	return selected_screen_id;
}



void destroy_screen(screen_t *screen)
{
	// delete list of screen_options
	node_t *current_option = screen->screen_options;
	while(current_option)
	{
		free(current_option->data);

		node_t *next = current_option->next;
		free(current_option);
		
		current_option = next;
	}
	free(screen);
}