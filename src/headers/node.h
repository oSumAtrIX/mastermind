#ifndef NODE_H_INCLUDE
#define NODE_H_INCLUDE

typedef struct node {
	void *data;
	struct node *next;
} node_t;

node_t *node_new(void *data);
void prepend_node(node_t *head, void *data);
void remove_node(node_t *head, node_t *node);

#endif