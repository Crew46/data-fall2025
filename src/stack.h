#ifndef STACK_H_
#define STACK_H_
#include "functions.h"
stack * mkStack()
{
stack * myStack = (stack *) malloc(sizeof(stack));
	if(myStack == NULL)
		{
			exit();
		}
myStack->top == NULL;
return(myStack);
}
// This will check to make sure the stack has something in it.
bool isEmpty(stack * myStack)
{	
	return(myStack->top == NULL);
}	



// Push a node into the stack.
stack * push(stack * myStack, Object * newNode)
{
	if(isEmpty(myStack) == false)
	{
	newNode->next		= myStack->top;
	myStack->top		= newNode;
	return(myStack);
	}
}

// pop a node from the stack. 
Object * pop(stack **myStack)
{
	if(isEmpty(*myStack) == false)
	{
	newNode			= (*myStack)->top;
	(*myStack)->top	= newNode->next;
	return(newNode);
	}
}















#endif // STACK_H_
