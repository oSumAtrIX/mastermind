#include <stdlib.h>
#include "node.h"

node_t *node_new(void *data)
{
	node_t *node = malloc(sizeof(node_t));
	node->data = data;
	node->next = NULL;
	return node;
}

void prepend_node(node_t *head, void *data)
{
	node_t *node = node_new(data);
	node->next = head;
	*head = *node;
}

void remove_node(node_t *head, node_t *node)
{
	node_t *current = head;
	while (current->next != node)
		current = current->next;
	current->next = node->next;
	free(node);
}
