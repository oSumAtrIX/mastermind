#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "node.h"
#include "cli.h"

/**
 * @brief Create a screen
 * 
 * @param id The id of the screen
 * @param frame The frame or contents of the screen which will be drawn
 * @param options The options of the screen to navigate to other screens or execute scripts
 * @param script The script to execute when the screen is shown
 * @return screen_t* The created screen object
 */
screen_t *screen_new(unsigned short id, char *frame, node_t *options, void (*script_before)(), void (*script)())
{
	screen_t *screen = malloc(sizeof(screen_t));
	screen->id = id;
	screen->frame = frame;
	screen->screen_options = options;
	screen->screen_script_before = script_before;
	screen->screen_script = script;
	return screen;
}

/**
 * @brief Create an option
 * 
 * @param key The key to press to navigate to the option
 * @param screen_name A name for the option
 * @param screen_id The id of the screen to navigate to
 * @return screen_option_t* The created option
 */
screen_option_t *create_option(char key, char *screen_name, unsigned short screen_id)
{
	screen_option_t *screen_option = malloc(sizeof(screen_option_t));
	screen_option->key = key;
	screen_option->screen_id = screen_id;
	screen_option->screen_name = screen_name;
	return screen_option;
}

/**
 * @brief Helper function to loop over all options in a screen and execute a function in the loop
 * @details If the function returns anything other than -1, the loop will be stopped and the function return value will be returned
 * @param screen The screen to loop over
 * @param function The function to execute in the loop
 * @param function_param Additional parameter to pass to the function (can be discarded)
 * @return int The return value of the function which is executed in the loop or -1 if the loop was not halted
 */
int loop_and_execute_inner(screen_t *screen, int (*function)(screen_option_t *, char), char function_param)
{
	node_t *current_option;
	for (current_option = screen->screen_options; current_option; current_option = current_option->next)
	{
		screen_option_t *option = (screen_option_t *)current_option->data;
		int result = function(option, function_param);
		if (result != -1) {
			return result;
		}
	}
	return -1;
}

/**
 * @brief Helper function to be used with loop_and_execute_inner to pretty print the current option
 * 
 * @param option The option to print
 * @param _unused Unused parameter needed for the function signature of the loop_and_execute_inner function
 * @return int Always returns -1
 */
int print_option(screen_option_t *option, char _unused)
{
	/* 
	This needs to be set in order to prevent a warning
	Reason for that is, 
	that the function signature has the match the function type definitions signature
	*/
	_unused = _unused; 

	/* TODO: offload to cli.c */
	printf(" <%c> %s |", option->key, option->screen_name);
	return -1;
}

/**
 * @brief Helper function to be used with loop_and_execute_inner to get the screen id and terminate the caller loop
 * @details If the selection does not match the option key, the function will return -1 for the caller function to continue the loop
 * @param option The option to get the screen id from
 * @param selection The key which was pressed to select the option
 * @return int The screen id of the option or -1
 */
int get_screen_id(screen_option_t *option, char selection){
	return option->key == selection ? option->screen_id : -1;
}

/**
 * @brief Execute the current screen
 * @details This function will print the frame of the screen, its options and then execute the screen script if present
 * @param screen The screen to execute
 * @return int The return value of the screen script
 */
int run_screen(screen_t *screen)
{
	int selected_screen_id;
	clear();

	/* draw screen */
	draw(screen->frame);

	/* run script of screen */
	if (screen->screen_script_before) screen->screen_script_before();

	if (screen->screen_options) {
		/* draw options */
		char selection;
		
		printf("\n|");
		loop_and_execute_inner(screen, print_option, 0);
		printf("\n> ");

		selection = getchar();
		if (selection != '\n') flush_buffer();
		selected_screen_id = loop_and_execute_inner(screen, get_screen_id, selection);

	}
	
	/* run script of screen */
	if (screen->screen_script) screen->screen_script();

	return selected_screen_id;
}

void option_destroy(void *option){
	screen_option_t *option_to_free = (screen_option_t *)option;
	free(option_to_free);
}

/**
 * @brief Free the memory of a screen
 * @details This function will free the memory of a screen and all its options
 * @param screen The screen to free
 */
void screen_destroy(void *screen)
{
	screen_t *screen_to_free = (screen_t *)screen;
	nodes_destroy(screen_to_free->screen_options, option_destroy);
	free(screen_to_free);
}