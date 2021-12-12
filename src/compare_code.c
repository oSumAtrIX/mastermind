/* 
BUG YYBB GBRV 0 2 should be 0 1
TODO remove main function (included for testing purposes) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CODELENGTH 4
#define USED_A 'q' /* this char indicates, that this peg has been accounted for during comparison for black pegs */
#define USED_B 'a' /* this char indicates, that this peg has been accounted for during comparison for white pegs */
int compare_code(int *count_correct, int *count_color_correct, const char guess[], const char key[]);

int main()
{
    char guess[] = "VRRY";
    char key[] = "GBRV";
    int richtig = 0;
    int fast_richtig = 0;
    int *p = &richtig;

    compare_code(p, &fast_richtig, guess, key);

    printf("Guess: %s\nKey: %s\nBlack pegs: %i\nWhite pegs: %i\n", guess, key, richtig, fast_richtig);
}

int compare_code(int *count_correct, int *count_color_correct, const char guess[], const char key[])
{
    int i;
    /* create copies of key and guess. As CODELENGTH will always be a comparebly small number, I don't
    use dynamic array, which would have performance advantages with big arrays. */
    char key_copy[CODELENGTH];
    char guess_copy[CODELENGTH];
    strncpy(key_copy, key, CODELENGTH);
    strncpy(guess_copy, guess, CODELENGTH);

    *count_correct = 0;
    *count_color_correct = 0;
    for (i = 0; i < CODELENGTH; i++) {
            if (guess_copy[i] == key_copy[i]) {
                ++(*count_correct);
                guess_copy[i] = USED_A;
            }
    }
    for (i = 0; i < CODELENGTH; i++) {
        int j;
        for (j = 0; j < CODELENGTH; j++) {
            if (guess_copy[i] == key_copy[j]) {
                ++(*count_color_correct);
                key_copy[j] = USED_B;
                break;
            }
        }
    }
    return 0;
}
