#include <stdlib.h>
#include <stdio.h>
#include "game_manager.h"
#include "screen_manager.h"
#include "node.h"
#include "gamerules.h"
#include "cli.h"

game_manager_t *game_manager;

void read_results() {
	result_manager_t *result_manager = result_manager_new("results.txt");
	print_results(result_manager);
	result_manager_destroy(result_manager);
}

void start()
{	
	int i = 1;
	char choice;

	/* initialize the game manager */
	game_manager = game_manager_new();

	/* multiplayer or singleplayer */
	write_line("Start in multiplayer mode? (y/n)\n> ");
	choice = getchar();
	flush_buffer();
	clear();

	/* playername input */
	for (i = 0; i <= (choice == 'y'); i++){
		char input[MAX_INPUT];
		printf("[Player %i] Enter your name:\n> ", i + 1);
		read_input(input, MAX_INPUT);
		if (!input[0]) {
			continue;
		}
		add_game(game_manager, input);
	}
	
	clear();

	/* supermastermind or mastermind */
	write_line("Do you want to play Supermastermind instead of regular Mastermind? (y/n)\n> ");
	choice = getchar();
	flush_buffer();
	clear();

	if (choice == 'y') {
		count_pegs = 8;
	}
	
	/* start games */
	run_game_manager(game_manager);
	
	clear();

	/* free memory */
	game_manager_destroy(game_manager);

	/* show end frame before displaying options*/
	draw(" _____           _ \r\n| ____|_ __   __| |\r\n|  _| | \'_ \\ / _` |\r\n| |___| | | | (_| |\r\n|_____|_| |_|\\__,_|\r\n\r\nYou can now chose one of the options below.");
}

void exit_script()
{
	exit(0);
}

int main()
{
	screen_t *main_screen, *help_screen, *about_screen, *game_screen, *result_screen, *exit_screen;

	screen_manager_t *screen_manager = screen_manager_new();

	/* 0 main menu */
	{
		node_t *main_screen_main_option_node = node_new(create_option('h', "help menu", 1));
		append_node(main_screen_main_option_node, create_option('a', "about menu", 2));
		append_node(main_screen_main_option_node, create_option('s', "start game", 3));
		append_node(main_screen_main_option_node, create_option('r', "result screen", 4));
		append_node(main_screen_main_option_node, create_option('e', "exit", 5));

		main_screen = screen_new(0, " __  __           _                      _           _ \r\n|  \\/  | __ _ ___| |_ ___ _ __ _ __ ___ (_)_ __   __| |\r\n| |\\/| |/ _` / __| __/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` |\r\n| |  | | (_| \\__ \\ ||  __/ |  | | | | | | | | | | (_| |\r\n|_|  |_|\\__,_|___/\\__\\___|_|  |_| |_| |_|_|_| |_|\\__,_|\r\n\r\nPlease press a key below to continue.", main_screen_main_option_node, NULL, NULL);
		add_screen(screen_manager, main_screen);
	}

	/* 1 help menu */
	{
		help_screen = screen_new(1, " _   _      _       \r\n| | | | ___| |_ __  \r\n| |_| |/ _ \\ | \'_ \\ \r\n|  _  |  __/ | |_) |\r\n|_| |_|\\___|_| .__/ \r\n             |_|    \r\n\r\nColor codes:\nB Blue\r\nG Green\r\nV Violet\r\nR Red\r\nY Yellow\r\nO Orange\r\nP Pink\r\nT Turquoise\r\n", node_new(create_option('b', "back", 0)), NULL, NULL);
		add_screen(screen_manager, help_screen);
	}

	/* 2 about menu */
	{
		about_screen = screen_new(2, "    _    _                 _   \r\n   / \\  | |__   ___  _   _| |_ \r\n  / _ \\ | \'_ \\ / _ \\| | | | __|\r\n / ___ \\| |_) | (_) | |_| | |_ \r\n/_/   \\_\\_.__/ \\___/ \\__,_|\\__|\r\n\r\nCreated by Alexander Krendl & Ohan Melkonyan\r\n\r\nNote from Ohan: \r\nWhen I began this project, I thought,\r\nthat we would finish it in less than a week...\r\nWe were done minutes before the deadline ;)", node_new(create_option('b', "back", 0)), NULL, NULL);
		add_screen(screen_manager, about_screen);
	}

	/* 3 start game */
	{

		node_t *game_screen_main_option_node = node_new(create_option('m', "main menu", 0));
		append_node(game_screen_main_option_node, create_option('r', "result screen", 4));
		game_screen = screen_new(3, "", game_screen_main_option_node, start, NULL);
		add_screen(screen_manager, game_screen);
	}

	/* 4 result screen */
	{
		result_screen = screen_new(4, " ____                 _ _       \r\n|  _ \\ ___  ___ _   _| | |_ ___ \r\n| |_) / _ \\/ __| | | | | __/ __|\r\n|  _ <  __/\\__ \\ |_| | | |_\\__ \\\r\n|_| \\_\\___||___/\\__,_|_|\\__|___/\r\n", node_new(create_option('m', "main menu", 0)), read_results, NULL);
		add_screen(screen_manager, result_screen);
	}

	/* 5 exit */
	{
		exit_screen = screen_new(5, " _____ _                 _              \r\n|_   _| |__   __ _ _ __ | | _____       \r\n  | | | \'_ \\ / _` | \'_ \\| |/ / __|      \r\n  | | | | | | (_| | | | |   <\\__ \\\r\n  |_| |_| |_|\\__,_|_| |_|_|\\_\\___(_|_|_)\r\n\r\n...for playing Mastermind.", NULL, NULL, exit_script);
		add_screen(screen_manager, exit_screen);
	}

	show_screen(screen_manager, 0);
	return 0;
}