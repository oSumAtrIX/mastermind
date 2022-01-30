#include <stdlib.h>
#include "node.h"

node_t *node_new(void *data)
{
	node_t *node = malloc(sizeof(node_t));
	node->data = data;
	node->next = NULL;
	return node;
}

void append_node(node_t *head, void *data)
{
	while (head->next)
		head = head->next;
	head->next = node_new(data);
}

void remove_node(node_t *head, node_t *node)
{
	node_t *current = head;
	while (current->next != node)
		current = current->next;
	current->next = node->next;
	free(node->data);
	free(node);
}
