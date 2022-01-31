#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "result_manager.h"
#include "node.h"
#include "result.h"

/**
 * @brief Read a file and return the content
 * @note The file must be in the same directory as the executable and the content string has to be freed afterwards
 * @return char* The content of the file
 */
char *read_file(char *from)
{
	char *buffer = NULL;
	int length, read_count;
	FILE *handler = fopen(from, "r");

	if (handler)
	{
		fseek(handler, 0, SEEK_END);
		length = ftell(handler);
		rewind(handler);

		buffer = (char *)malloc(length + 1);

		read_count = fread(buffer, 1, length, handler);
		buffer[length] = '\0';
		if (length != read_count)
		{
			free(buffer);
			buffer = NULL;
		}

		fclose(handler);
	}

	return buffer;
}

/**
 * @brief Create a new result manager
 * 
 * @param from The file to read existing results from
 * @return result_manager_t* The result manager object
 */
result_manager_t *result_manager_new(char *from)
{
	result_manager_t *result_manager = calloc(1, sizeof(result_manager_t));

	char *save_file = read_file(from);

	char *line = strtok(save_file, "\n");
	if (line)
	{
		node_t *lines = node_new(line);
		node_t *current;

		while (1)
		{
			line = strtok(NULL, "\n");
			if (!line)
				break;
			append_node(lines, line);
		}

		current = lines;
		while (current)
		{
			char *line = current->data;

			char *username = strtok(line, "|");
			short wins = atoi(strtok(NULL, "|"));
			short loses = atoi(strtok(NULL, "|"));

			add_result(result_manager, result_new(username, wins, loses));

			current = current->next;
		}

		/* free the allocated buffer */
		while (lines)
		{
			node_t *tmp = lines;
			lines = lines->next;
			free(tmp);
		}
	}
	
	/* free the allocated buffer */
	free(save_file);

	return result_manager;
}

/**
 * @brief Add a result to the result manager
 * 
 * @param result_manager The result manager
 * @param result The result to add
 */
void add_result(result_manager_t *result_manager, result_t *result)
{
	if (!result_manager->result_list)
	{
		result_manager->result_list = node_new(result);
	}
	else
	{
		append_node(result_manager->result_list, result);
	}
}

/**
 * @brief Update the results of a player
 * @details If the player already exists in the result manager, the result is updated else a new result is added
 * @param result_manager The result manager
 * @param username The username of the player
 * @param with_result The new result
 */
void update_result(result_manager_t *result_manager, char *username, short wins, short loses)
{
	node_t *node = result_manager->result_list;
	while (node)
	{
		result_t *result = node->data;
		if (!strcmp(result->username, username))
		{
			result->wins += wins;
			result->loses += loses;
			return;
		}
		node = node->next;
	}

	add_result(result_manager, result_new(username, wins, loses));
}

/**
 * @brief Save the results to a file
 * 
 * @param result_manager The manager to save the results from
 * @param to The file to save to
 */
void save_results(result_manager_t *result_manager, char *to)
{
	FILE *handler = fopen(to, "w");
	node_t *node = result_manager->result_list;
	while (node)
	{
		result_t *result = node->data;
		fprintf(handler, "%s|%d|%d\n", result->username, result->wins, result->loses);
		node = node->next;
	}

	fclose(handler);
}

/**
 * @brief Print all the results
 * 
 * @param result_manager The result manager to print the results from
 */
void print_results(result_manager_t *result_manager)
{
	node_t *node = result_manager->result_list;
	printf("| Wins | Loses | Username\n");
	while (node)
	{
		result_t *result = (result_t *)node->data;
		printf("| %i    | %i     | %s\n", result->wins, result->loses, result->username);
		node = node->next;
	}
}

/**
 * @brief Destroy the result manager
 * 
 * @param result_manager The result manager to destroy
 */
void result_manager_destroy(result_manager_t *result_manager)
{
	nodes_destroy(result_manager->result_list, result_destroy);
	free(result_manager);
}