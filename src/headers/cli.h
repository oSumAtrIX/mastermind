#ifndef CLI_H_INCLUDE
#define CLI_H_INCLUDE

#define CLEAR_SCREEN() printf("\033[2J\033[1;1H")
#define PRINT_HELP() printf("..")

// Todo: CLI prototypes
void get_input(const char input[4]);
#endif