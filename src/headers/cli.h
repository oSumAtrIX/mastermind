#ifndef CLI_H_INCLUDE
#define CLI_H_INCLUDE

#include "row.h"

int flush_buffer();
void print_row(row_t *row);
void draw(char *frame);
int validate_input(char *input, int length);
void get_input(char *input, int length);
void clear();

#endif