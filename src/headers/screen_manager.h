#ifndef SCREEN_MANAGER_H_INCLUDE
#define SCREEN_MANAGER_H_INCLUDE

#include "screen.h"
#include "node.h"

typedef struct {
	node_t *screen_list;
} screen_manager_t;

screen_manager_t *screen_manager_new();
void read_config(screen_manager_t *screen_manager, char* from_file);
void add_screen(screen_manager_t *screen_manager, screen_t *screen);
void show_screen(screen_manager_t *screen_manager, unsigned short id);

void screen_manager_destroy(screen_manager_t *screen_manager);
#endif