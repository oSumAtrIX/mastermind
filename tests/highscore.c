/* High-Score
This will print a High-Score List
BUG type conflicts
HEADSUP variable 'scores' will be altered in the process
*/
#include <stdio.h>
#include <string.h>

#define PLAYERNUMBER 5
#define NAMELENGTH 32
#define SCORE_USED -1

int highscore(const char *players[], int scores[], int *sorted_scores, char *sorted_players, const int playernumber, const int namelength);

int main(void)
{
    int i;
    char sorted_players[PLAYERNUMBER][NAMELENGTH];
    int sorted_scores[PLAYERNUMBER];

    char players[PLAYERNUMBER][NAMELENGTH] = {"Alex", "Cornelius", "Ohan", "Robert", "Lorenz"};
    int scores[PLAYERNUMBER] = {25, 32, 29, 15, 45};

    highscore(players, scores, sorted_scores, sorted_players, PLAYERNUMBER, NAMELENGTH);

    printf("=====UNSORTED======\n");
    for (i = 0; i < PLAYERNUMBER; i++)
    {
        printf("%32s\t%i\n", players[i], scores[i]);
    }

    printf("=====SORTED======\n");
    for (i = 0; i < PLAYERNUMBER; i++)
    {
        printf("%32s\t%i\n", sorted_players[i], sorted_scores[i]);
    }
    return 0;
}

int highscore(const char *players[], int scores[], int *sorted_scores, char *sorted_players, const int playernumber, const int namelength)
{
    int i, j, k, max;
    for (j = 0; j < playernumber; j++)
    { /*iterate through sorted_scores */
        /* Sort Scores and store in sorted_scores */
        max = scores[j];
        for (i = 0; i < playernumber; i++)
        { /* iterate through scores */
            max = max > scores[i] ? max : scores[i];
        }
        sorted_scores[j] = max;

        /* find Scores, get corresponding playername and store in sorted_players */
        for (k = 0; (scores[k] != max); k++)
        { /*iterate through scores */
            ;
        }
        strncpy(&sorted_players[j], players[k], namelength);
        scores[k] = SCORE_USED; /* to mark it as "used" */
    }
    return 0;
}
