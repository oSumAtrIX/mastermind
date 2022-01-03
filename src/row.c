#include "row.h"
#include <stdlib.h>

void destroy_row(row_t *row)
{
	free(row);
}
row_t *create_row()
{
	row_t *row = malloc(sizeof(row_t));
	return row;
}
void set_guess(row_t *row, char *guess)
{
	row->guess = guess;
}
void set_pebles(row_t *row, short c_right_pegs, short c_almost_right_pegs)
{
	row->c_right_pegs = c_right_pegs;
	row->c_almost_right_pegs = c_almost_right_pegs;
}
