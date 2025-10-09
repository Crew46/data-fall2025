#ifndef _STACK_H
#define _STACK_H

#include "../doubly_linked_list/doubly_linked_list.h"

struct Stack
{
	List* list;
	int   size;
	int   count;
};

void push(Stack* stack, Node* newNode)
{
	if(newNode != NULL)
	{
		if(stack->count < stack->size || stack->size < 1)
		{
			insert(stack->list, stack->list->head, newNode);
			stack->count++;
		}
	}
}

Node* pop(Stack* stack)
{
	if(stack->list->head != NULL)
	{
		Node* node = stack->list->head;
		obtain(stack->list, stack->list->head);
		stack->count--;
		return node;
	}
	else
	{
		return NULL;
	}
}

Stack* createStack(int size)
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->list  = createList();
	stack->size  = size;
	stack->count = 0;

	return stack;
}


#endif
