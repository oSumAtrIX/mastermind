#ifndef NODE_H_INCLUDE
#define NODE_H_INCLUDE

typedef struct {
	void *data;
	node_t *next;
} node_t;

node_t *node_new(void *data);
void prepend_node(node_t *head, void *data);
void node_free(node_t *node);

#endif