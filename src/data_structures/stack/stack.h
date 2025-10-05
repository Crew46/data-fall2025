#ifndef _STACK_H
#define _STACK_H

#include "../doubly_linked_list/doubly_linked_list.h"

struct Stack
{
	Node* head;
	int   size;
};

void push(Stack* stack, Node* newNode)
{
	if(newNode != NULL)
	{
		if(stack->head != NULL)
		{
			stack->head->prev = newNode;
			newNode->next = stack->head;
		}
		stack->head = newNode;
		stack->size++;
	}
}

Node* pop(Stack* stack)
{
	if(stack->head != NULL)
	{
		Node* tmp = stack->head;

		stack->size--;
		stack->head = stack->head->next;
		stack->head->prev = NULL;
		tmp->next = NULL;

		return tmp;
	}

	return NULL;
}

Stack* createStack()
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->head = NULL;
	stack->size = 0;
}
#endif
