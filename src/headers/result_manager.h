#ifndef RESULT_MANAGER_H_INCLUDE
#define RESULT_MANAGER_H_INCLUDE

#include "node.h"
#include "result.h"

typedef struct
{
	node_t *result_list;
} result_manager_t;

result_manager_t *result_manager_new(char *from);
void save_results(result_manager_t *result_manager, char* to);
void add_result(result_manager_t *result_manager, result_t *result);
void update_result(result_manager_t *result_manager, char *username, short wins, short loses);
void print_results(result_manager_t *result_manager);
void result_manager_destroy(result_manager_t *result_manager);

#endif