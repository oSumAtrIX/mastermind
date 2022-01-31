#ifndef CLI_H_INCLUDE
#define CLI_H_INCLUDE

#include "row.h"
#include "gamerules.h"

void flush_buffer();
void draw(char *frame);
int validate_input(char *input, int length);
void read_input(char input[], int length);
void write_line(char *str);
void clear();
#endif