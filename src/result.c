#include <stdlib.h>
#include <string.h>
#include "result.h"
#include "gamerules.h"
/**
 * @brief Initializes a new result object
 * 
 * @param username The username of the player
 * @param wins The number of wins
 * @param loses The number of loses
 * @return result_t* The new result object
 */
result_t *result_new(char *username, short wins, short loses)
{
	result_t *result = calloc(1, sizeof(result_t));

	result->username = (char *)malloc(MAX_INPUT);
	strcpy(result->username, username);

	result->wins = wins;
	result->loses = loses;
	return result;
}

/**
 * @brief Free the result
 * 
 * @param result The result object to free
 */
void result_destroy(void *result)
{
	result_t *result_to_free = (result_t *)result;
	free(result_to_free->username);
	free(result_to_free);
	
}
