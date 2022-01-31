#ifndef ROW_H_INCLUDE
#define ROW_H_INCLUDE

typedef struct {
	char *guess;
	int black_pegs;
	int white_pegs;
} row_t;

void row_destroy(row_t *row);
row_t *create_row();
void set_guess(row_t *row, char *guess);
void set_pebles(row_t *row, int black_pegs, int white_pegs);

#endif