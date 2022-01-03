/* 
BUG YYBB GBRV 0 2 should be 0 1
TODO use set_pebles function
TODO Access most recent GUESS
TODO remove main and set_pebles function (included for testing purposes) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <row.h>
#include <gamerules.h>

#define USED_A 'q' /* this char indicates, that this peg has been accounted for during comparison for black pegs */
#define USED_B 'a' /* this char indicates, that this peg has been accounted for during comparison for white pegs two different are necessary as otherwise false positives will be indicated */
int compare_code(row_t *row);

void set_pebles(row, count_correct, count_color_correct) {
    printf("row: %i, Black Pegs: %i, White Pegs: %i\n", row, count_correct, count_color_correct);
}

int main()
{
    char code[] = "GBRV";
    char guess[] = "RRVY";
    compare_code(guess, code);

    printf("Guess: %s\nKey: %s\n", guess, code);
}

int compare_code(row_t *row)
/* Function which compares the guess string with the secret code string and determines the number of black pegs (correct char and index) and white pegs (correct char , wrong index).
Input: address to store black pegs, address to store white pegs, guess string, secret code string
Saves: number of black and white pegs to corresponding addresses.
Returns: 0 if everything went fine. */
{
    int i;
    /* create copies of key and guess. As CODELENGTH will always be a comparebly small number, I don't
    use dynamic array, which would have performance advantages with big arrays. */
    char code_copy[CODE_LENGTH];
    char guess_copy[CODE_LENGTH];
    strncpy(code_copy, row->code, CODE_LENGTH);
    strncpy(guess_copy, row->guess, CODE_LENGTH);

    unsigned short count_correct = 0;
    unsigned short count_color_correct = 0;
    for (i = 0; i < CODE_LENGTH; i++)
    {
        if (guess_copy[i] == code_copy[i])
        {
            ++count_correct;
            code_copy[i] = USED_A;
            guess_copy[i] = USED_B;
        }
    }
    for (i = 0; i < CODE_LENGTH; i++)
    {
        int j;
        for (j = 0; j < CODE_LENGTH; j++)
        {
            if (guess_copy[i] == code_copy[j])
            {
                ++count_color_correct;
                code_copy[j] = USED_A;
                guess_copy[i] = USED_B;
                break;
            }
        }
    }
    int row = 1; /* FOR TESTING - REMOVE BEFORE RELEASE */
    set_pebles(row, count_correct, count_color_correct);
    return 0;
}
