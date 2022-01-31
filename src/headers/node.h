#ifndef NODE_H_INCLUDE
#define NODE_H_INCLUDE

typedef struct node {
	void *data;
	struct node *next;
} node_t;

node_t *node_new(void *data);
void append_node(node_t *head, void *data);
void nodes_destroy(node_t *head, void (*data_destroy)(void *));

#endif