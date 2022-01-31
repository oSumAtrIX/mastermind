#include <stdlib.h>
#include "node.h"

/**
 * @brief Create a new node
 * 
 * @param data The data to store in the node
 * @return node_t* The created node
 */
node_t *node_new(void *data)
{
	node_t *node = malloc(sizeof(node_t));
	node->data = data;
	node->next = NULL;
	return node;
}

/**
 * @brief Append a node to the end of a list
 * 
 * @param head The head of the list
 * @param data The data to store in the node
 */
void append_node(node_t *head, void *data)
{
	while (head->next)
		head = head->next;
	head->next = node_new(data);
}

/**
 * @brief Free the entire list and all its nodes from and inclusive a head node
 * 
 * @param head The head of the list
 * @param data_destroy The function to call to destroy the data
 */
void nodes_destroy(node_t *head, void (*data_destroy)(void *))
{
	while (head)
	{
		node_t *tmp = head;
		data_destroy(head->data);
		head = head->next;
		free(tmp);
	}
}