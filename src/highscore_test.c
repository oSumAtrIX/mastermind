/* High-Score
This will print a High-Score List
TODO change into function
HEADSUP scores will be altered in the process
*/
#include <stdio.h>
#include <string.h>

#define PLAYERNUMBER 5
#define NAMELENGTH 32
#define SCORE_USED -1
int main(void)
{
    char sorted_players[PLAYERNUMBER][NAMELENGTH];
    int sorted_scores[PLAYERNUMBER];

    char players[PLAYERNUMBER][NAMELENGTH] = {"Alex", "Cornelius", "Ohan", "Robert", "Lorenz"};
    int scores[PLAYERNUMBER] = {25, 32, 29, 15, 45};

    int i, j, k, max;
    printf("=====UNSORTED======\n");
    for (i = 0; i < PLAYERNUMBER; i++){
        printf("%32s\t%i\n", players[i], scores[i]);
    }

    for(j = 0; j < PLAYERNUMBER; j++) { /*iterate through sorted_scores */
        /* Sort Scores and store in sorted_scores */
        max = scores[j];
        for (i = 0; i < PLAYERNUMBER; i++){ /* iterate through scores */
            max = max > scores[i] ? max : scores[i];
        }
        sorted_scores[j] = max;

        /* find Scores, get corresponding playername and store in sorted_players */
        for (k = 0; (scores[k] != max); k++) { /*iterate through scores */
            ;
        }
        strncpy(sorted_players[j], players[k], NAMELENGTH);
        scores[k] = SCORE_USED; /* to mark it as "used" */
    }

    printf("=====SORTED======\n");
    for (i = 0; i < PLAYERNUMBER; i++){
        printf("%32s\t%i\n", sorted_players[i], sorted_scores[i]);
    }
    return 0;
}
