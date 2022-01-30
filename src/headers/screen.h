#ifndef SCREEN_H_INCLUDE
#define SCREEN_H_INCLUDE

#include "node.h"

typedef void (*screenScript)();

typedef struct {
	char key;
	char *screen_name;
	
	unsigned short screen_id;
} screen_option_t;

typedef struct {
	unsigned short id;
	char *frame;
	screenScript screen_script;
	node_t *screen_options;
} screen_t;

void screen_script();

screen_option_t *create_option(char, char *, unsigned short);
screen_t *create_screen(unsigned short, char *, node_t *, screenScript);
int run_screen(screen_t *);
void destroy_screen(screen_t *);


#endif