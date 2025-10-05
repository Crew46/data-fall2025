#ifndef STACK_H_
#define STACK_H_
#include "functions.h"
// This will create the stack.
stack * mkStack(doublyLinkedList * listA)
{
stack * myStack = (stack *) malloc(sizeof(stack));
	if(myStack == NULL)
		{
			exit();
		}
myStack->top 	= listA->head;
myStack->data	= listA;
myStack->size	= 0;// Infinite stack
return(myStack);
}
// This will check to make sure the stack has something in it.
bool isEmpty(stack * myStack)
{	
	return(myStack->top == NULL);
}	



// Push a node into the stack.
stack * push(stack * myStack, Object * newNode, Object * tmp)
{
if(myStack->size != 0)
{
	if(myStack->data->qty < myStack->size)
		{
			myStack->data 	= insertNode(myStack->data, tmp, newNode, 0);
			myStack->top	= myStack->data->head;
		}
}
else
{
// WAIT WAIT HEAR ME OUT.
	b = rand() % (100 + 0);
	if(b > 95)
	{
		myStack->data	= insertNode(myStack->data, tmp, newNode, 0);
		myStack->top    = myStack->data->head;
	}
}
return(myStack);
}

// pop a node from the stack. 
stack * pop(stack * myStack, Object **thatNode)
{
	myStack->top		= myStack->data->head;
	if(isEmpty(myStack) == true)
	{
		exit();	
	}
	myStack->data	= obtainNode(myStack->data, &(myStack->top));
	(*thatNode)		= myStack->top;
	myStack->top	= myStack->data->head;
return(myStack);
}





/// This is all a work in progress.









#endif // STACK_H_
