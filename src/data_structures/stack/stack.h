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
			stack->head->next = newNode;
			newNode->prev = stack->head;
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
		stack->head = stack->head->prev;
		stack->head->next = NULL;
		tmp->prev = NULL;


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
