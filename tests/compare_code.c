/* 
BUG YYBB GBRV 0 2 should be 0 1
TODO Access most recent GUESS
TODO remove main function (included for testing purposes) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CODELENGTH 4
#define USED_A 'q' /* this char indicates, that this peg has been accounted for during comparison for black pegs */
#define USED_B 'a' /* this char indicates, that this peg has been accounted for during comparison for white pegs */
int compare_code(int *count_correct, int *count_color_correct, const char guess[], const char code[]);

int main()
{
    char guess[] = "VRRY";
    char code[] = "GBRV";
    int richtig = 0;
    int fast_richtig = 0;
    compare_code(&richtig, &fast_richtig, guess, code);

    printf("Guess: %s\nKey: %s\nBlack pegs: %i\nWhite pegs: %i\n", guess, code, richtig, fast_richtig);
}

int compare_code(int *count_correct, int *count_color_correct, const char guess[], const char code[])
/* Function which compares the guess string with the secret code string and determines the number of black pegs (correct char and index) and white pegs (correct char , wrong index).
Input: address to store black pegs, address to store white pegs, guess string, secret code string
Saves: number of black and white pegs to corresponding addresses.
Returns: 0 if everything went fine. */
{
    int i;
    /* create copies of key and guess. As CODELENGTH will always be a comparebly small number, I don't
    use dynamic array, which would have performance advantages with big arrays. */
    char code_copy[CODELENGTH];
    char guess_copy[CODELENGTH];
    strncpy(code_copy, code, CODELENGTH);
    strncpy(guess_copy, guess, CODELENGTH);

    *count_correct = 0;
    *count_color_correct = 0;
    for (i = 0; i < CODELENGTH; i++)
    {
        if (guess_copy[i] == code_copy[i])
        {
            ++(*count_correct);
            guess_copy[i] = USED_A;
        }
    }
    for (i = 0; i < CODELENGTH; i++)
    {
        int j;
        for (j = 0; j < CODELENGTH; j++)
        {
            if (guess_copy[i] == code_copy[j])
            {
                ++(*count_color_correct);
                code_copy[j] = USED_B;
                break;
            }
        }
    }
    return 0;
}
