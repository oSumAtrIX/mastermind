#include <stdlib.h>
#include <stdio.h>
#include "game_manager.h"
#include "screen_manager.h"
#include "node.h"

void start()
{
	/* Initialize the game manager */
	game_manager_t *game_manager = create_game_manager();
	return;
	/* add games */
	add_game(game_manager, "Ohan");
	add_game(game_manager, "Alex");

	/* start games */
	start(game_manager);
}

void exit_script()
{
	exit(0);
}

int main()
{
	screen_t *main_screen, *help_screen, *about_screen, *game_screen, *result_screen, *exit_screen;

	screen_manager_t *screen_manager = create_screen_manager();

	/* 0 main menu */
	{
		node_t *main_screen_main_option_node = node_new(create_option('h', "help menu", 1));
		append_node(main_screen_main_option_node, create_option('a', "about menu", 2));
		append_node(main_screen_main_option_node, create_option('s', "start game", 3));
		append_node(main_screen_main_option_node, create_option('e', "exit", 5));

		main_screen = create_screen(0, " __  __           _                      _           _ \r\n|  \\/  | __ _ ___| |_ ___ _ __ _ __ ___ (_)_ __   __| |\r\n| |\\/| |/ _` / __| __/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` |\r\n| |  | | (_| \\__ \\ ||  __/ |  | | | | | | | | | | (_| |\r\n|_|  |_|\\__,_|___/\\__\\___|_|  |_| |_| |_|_|_| |_|\\__,_|\r\n\r\nPlease press a key below to continue.", main_screen_main_option_node, NULL);
		add_screen(screen_manager, main_screen);
	}

	/* 1 help menu */
	{
		help_screen = create_screen(1, " _   _      _       \r\n| | | | ___| |_ __  \r\n| |_| |/ _ \\ | \'_ \\ \r\n|  _  |  __/ | |_) |\r\n|_| |_|\\___|_| .__/ \r\n             |_|    ", node_new(create_option('b', "back", 0)), NULL);
		add_screen(screen_manager, help_screen);
	}

	/* 2 about menu */
	{
		about_screen = create_screen(2, "    _    _                 _   \r\n   / \\  | |__   ___  _   _| |_ \r\n  / _ \\ | \'_ \\ / _ \\| | | | __|\r\n / ___ \\| |_) | (_) | |_| | |_ \r\n/_/   \\_\\_.__/ \\___/ \\__,_|\\__|\r\n\r\nCreated by Alexander Krendl & Ohan Melkonyan\r\n\r\nNote from Ohan: \r\nWhen I began this project, I thought,\r\nthat we would finish it in less than a week...\r\nWe were done hours before the deadline ;)", node_new(create_option('b', "back", 0)), NULL);
		add_screen(screen_manager, about_screen);
	}

	/* 3 start game */
	{
		game_screen = create_screen(3, "game", NULL, start);
		add_screen(screen_manager, game_screen);
	}

	/* 4 result screen */
	{
		result_screen = create_screen(4, " ____                 _ _       \r\n|  _ \\ ___  ___ _   _| | |_ ___ \r\n| |_) / _ \\/ __| | | | | __/ __|\r\n|  _ <  __/\\__ \\ |_| | | |_\\__ \\\r\n|_| \\_\\___||___/\\__,_|_|\\__|___/\r\n", node_new(create_option('m', "main menu", 0)), start);
		add_screen(screen_manager, result_screen);
	}

	/* 5 exit */
	{
		exit_screen = create_screen(5, " _____ _                 _              \r\n|_   _| |__   __ _ _ __ | | _____       \r\n  | | | \'_ \\ / _` | \'_ \\| |/ / __|      \r\n  | | | | | | (_| | | | |   <\\__ \\\r\n  |_| |_| |_|\\__,_|_| |_|_|\\_\\___(_|_|_)\r\n\r\n...for playing Mastermind.", node_new(create_option('c', "confirm to exit", -1)), exit_script);
		add_screen(screen_manager, exit_screen);
	}

	show_screen(screen_manager, 0);
	return 0;
}