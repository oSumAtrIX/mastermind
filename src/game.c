#include "cli.h"

struct Game {
	struct Player *player;

	unsigned short state;

	unsigned short *code;
	unsigned short **guess;
	unsigned short guess_count;
};