/* BUG results in segmentation error
TODO count color correct
TODO remove main function (included for testing purposes) */
#include <stdio.h>

#define CODELENGTH 4

int compare_code(int *count_correct, int *count_color_correct, const char guess[], const char key[]);

int main()
{
    char guess[] = "BGVR";
    char key[] = "BRVG";
    int richtig = 0;
    int fast_richtig = 0;
    int *p = &richtig;

    compare_code(p, &fast_richtig, guess, key);

    printf("Guess: %s\nKey: %s\nBlack pegs: %i\nWhite pegs: %i\n", key, guess, richtig, fast_richtig);
}

int compare_code(int *count_correct, int *count_color_correct, const char guess[], const char key[])
{
    int i;
    count_correct =0;
    count_color_correct = 0;
    for (i = 0; i < CODELENGTH; i++) {
        if (guess[i] == key[i])
            ++(*count_correct);
    }
    return 0;
}
