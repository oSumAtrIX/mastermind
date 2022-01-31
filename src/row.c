#include <stdlib.h>
#include <string.h>
#include "row.h"
#include "gamerules.h"

/**
 * @brief Free the row object
 * @details This will free the row object and all of its primitive children
 * @param row The row object to free
 */
void row_destroy(row_t *row)
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
	row->guess = calloc(1, CODE_LENGTH + 1);
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
	strcpy(row->guess, guess);
}

/**
 * @brief Set the pebles for the given row
 * 
 * @param row The row to set the pebles for
 * @param black_pegs The number of correct pebles
 * @param white_pegs The number of almost correct pebles
 */
void set_pebles(row_t *row, int black_pegs, int white_pegs)
{
	row->black_pegs = black_pegs;
	row->white_pegs = white_pegs;
}
