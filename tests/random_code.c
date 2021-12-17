/*
TODO: remove main
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int random_code(const char colors[], char code[], const int codelength)
/* Creates a random secret code.
Input: Available chars, Address where the code should be stored, desired length of the code
Saves: secret code string to code
Returns: 0 if everything went fine
*/
{
    int i;
    srand(time(0));

    for (i = 0; i < codelength; i++)
        code[i] = colors[(rand() % codelength)];
    code[i] = '\0';
    return 0;
}
/*FORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLY*/
#define CODELENGTH 4

int main(void)
{
    char colors[] = "BGVRYO";
    char code[CODELENGTH + 1];
    random_code(colors, code, CODELENGTH);
    printf("%s\n", code);
    return 0;
}
/*FORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLYFORTESTONLY*/
