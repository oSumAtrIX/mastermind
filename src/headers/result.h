#ifndef RESULT_H_INCLUDE
#define RESULT_H_INCLUDE

typedef struct
{
	char *username;
	short wins, loses;
} result_t;

result_t *result_new(char *username, short wins, short loses);
void result_destroy(void *result);

#endif