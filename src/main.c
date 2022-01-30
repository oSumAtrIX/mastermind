#include <stdlib.h>
#include <stdio.h>
#include "game_manager.c"
#include "screen_manager.c"

void start(){
	/* Initialize the game manager */
	game_manager_t *game_manager = create_game_manager();

	/* add games */
	add_game(game_manager, "Ohan");
	add_game(game_manager, "Alex");

	/* start games */
	start(game_manager);
}

void exit_script(){
	exit(0);
}

int main()
{
	screen_manager_t *screen_manager = create_screen_manager();
		
	/* 0 main menu */
	{
		node_t *main_screen_main_option_node = create_node(create_option('h', "help menu", 3));
		append_node(main_screen_main_option_node, create_option('a', "about menu", 3));
		append_node(main_screen_main_option_node, create_option('s', "start game", 3));
		append_node(main_screen_main_option_node, create_option('e', "exit", 5));

		screen_t *main_screen = create_screen(0, "content", main_screen_main_option_node, NULL);
		add_screen(screen_manager, main_screen);
	}

	/* 1 help menu */
	{
		screen_t *help_screen = create_screen(1, "help instructions", create_node(create_option('b', "back", 0)), NULL);
		add_screen(screen_manager, help_screen);
	}

	/* 2 about menu */
	{
		screen_t *about_screen = create_screen(2, "about", create_node(create_option('b', "back", 0)), NULL);
		add_screen(screen_manager, about_screen);
	}

	/* 3 start game */
	{
		node_t *game_screen_main_option_node = create_node(create_option('r', "result screen", 4));
		append_node(game_screen_main_option_node, create_option('m', "main menu", 0));

		screen_t *game_screen = create_screen(3, "game", game_screen_main_option_node, start);
		add_screen(screen_manager, game_screen);
	}

	/* 5 exit */
	{
		screen_t *exit_screen = create_screen(5, "exit", NULL, exit_script);
		add_screen(screen_manager, exit_screen);
	}

	show_screen(screen_manager, 0);
	return 0;
}