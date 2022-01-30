#ifndef SCREEN_H_INCLUDE
#define SCREEN_H_INCLUDE

#include "node.h"

typedef struct {
	char key;
	char *screen_name;
	
	unsigned short screen_id;
} screen_option_t;

typedef struct {
	unsigned short id;
	char *frame;
	void (*screen_script)();
	node_t *screen_options;
} screen_t;

void screen_script();
int loop_and_execute_inner(screen_t *screen, int (*inner)(screen_option_t *, char), char function_parameter);
screen_option_t *create_option(char key, char *screen_name, unsigned short screen_id);
screen_t *create_screen(unsigned short id, char *name, node_t *options, void (*script)());
int run_screen(screen_t *screen);
void destroy_screen(screen_t *screen);

#endif