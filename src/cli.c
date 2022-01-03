#include <stdio.h>
#include "cli.h"
#include "gamerules.h"

/* TODO: add interface with pebles */

/* TODO: sanitize input */

void get_input(char *input)
{
	int i;
	for (i = 0; i < CODE_LENGTH; i++)
		scanf("%c", &input[i]);
	input[CODE_LENGTH] = '\0';
	while (getchar() != '\n');
}