#include "row.h"
#include <stdlib.h>

/**
 * @brief Free the row object
 * @details This will free the row object and all of its primitive children
 * @param row The row object to free
 */
void destroy_row(row_t *row)
{
	free(row);
}

/**
 * @brief Create a row object
 * 
 * @return row_t* The created row object
 */
row_t *create_row()
{
	row_t *row = malloc(sizeof(row_t));
	return row;
}

/**
 * @brief Set the current guess for the given row
 * 
 * @param row The row to set the guess for
 * @param guess The guess to set
 */
void set_guess(row_t *row, char *guess)
{
	row->guess = guess;
}

/**
 * @brief Set the pebles for the given row
 * 
 * @param row The row to set the pebles for
 * @param c_right_pegs The number of correct pebles
 * @param c_almost_right_pegs The number of almost correct pebles
 */
void set_pebles(row_t *row, int c_right_pegs, int c_almost_right_pegs)
{
	row->c_right_pegs = c_right_pegs;
	row->c_almost_right_pegs = c_almost_right_pegs;
}
