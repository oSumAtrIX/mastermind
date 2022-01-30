#ifndef ROW_H_INCLUDE
#define ROW_H_INCLUDE

typedef struct {
	char *guess;
	int c_right_pegs;
	int c_almost_right_pegs;
} row_t;

void destroy_row(row_t *row);
row_t *create_row();
void set_guess(row_t *row, char *guess);
void set_pebles(row_t *row, int c_right_pegs, int c_almost_right_pegs);

#endif