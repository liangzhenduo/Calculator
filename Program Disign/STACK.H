#ifndef __STACK_H__
#define __STACK_H__

#define STACK_INIT_SIZE 8

typedef struct
{
	void * content;
	size_t el_size;
	size_t size;
	size_t top;
} Stack;

Stack * stack_new(size_t el_size);
void stack_free(Stack * s);
void push(Stack * s, void * val);
int pop(Stack * s, void * ret);
int peek(Stack * s, void * ret);

#endif
