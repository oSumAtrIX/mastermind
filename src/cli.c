#include <stdio.h>
#include "cli.h"
#include "gamerules.h"
#include "row.h"
#include <stdlib.h>

void clear()
{
	system("@cls||clear");
}

void write_line(char *str)
{
	printf("%s", str);
}

void draw(char *frame)
{
	printf("%s\n", frame);
}


int validate_input(char *input, int length)
{
	int i, j;

	for (i = 0; i < length; i++)
	{
		int invalid = 1;
		char current_char = input[i];

		for (j = 0; j < count_pegs; j++)
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

/**
 * @brief Flush the current stdio buffer
 */
void flush_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

/**
 * @brief Read input from the console
 * 
 * @param input The input to write to
 * @param length The length of the input determined by the game type (including \0)
 */
void read_input(char input[], int length)
{
	char c = getchar();
	int i = 0;
	while (c != '\n') {
		if (i > length - 1){
			input[i] = 0;
			flush_buffer();
			return;
		}
		if (c == EOF) return;

		input[i++] = c;
		c = getchar();
	}
	input[i] = 0;
	return;
}