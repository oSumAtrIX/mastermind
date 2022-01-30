#include <stdio.h>
#include "cli.h"
#include "gamerules.h"
#include "row.h"
#include <stdlib.h>

void clear()
{
	system("@cls||clear");
}

/* TODO: add interface with pebles */
void print_row(row_t *row) {
	printf("%s r:%i fast: %i", row->guess, row->c_right_pegs, row->c_almost_right_pegs);
}

int validate_input(char *input, int length)
{
	int i, j;

	for (i = 0; i < length; i++)
	{
		int invalid = 1;
		char current_char = input[i];

		for (j = 0; j < C_PEGS; j++)
			if (current_char == available_colors[j])
			{
				invalid = 0;
				break;
			}

		if (invalid)
			return 0;
	}
	return 1;
}

int flush_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
	return c != EOF;
}

void get_input(char *input, int length)
{
	char c;
	int i;
	for (i = 0; i < length; i++)
	{
		c = getchar();
		if (c == '\n' || c == EOF) {
			input[i] = '\0';
			break;
		}		
		input[i] = c;
	}
	if (i >= length) flush_buffer();
}