#ifndef _STACK_H
#define _STACK_H
#include "functions.h"

// This will create the stack.
stack * mkStack (doublyLinkedList * myList)
{
stack * myStack = (stack *) malloc(sizeof(stack));
    if(myStack == NULL)
        {
            exit();
        }
myStack->data	 = myList; 
myStack->top     = myStack->data->head;
myStack->size    = 0;// Infinite stack
return(myStack);
}
// This will check to make sure the stack has something in it.
bool stackIsEmpty(stack * myStack)
{    
    return(myStack->top == NULL);
}    



// Push a node into the stack.
stack *push (stack *myStack, Object *newNode)
{
    if (myStack -> size            != 0)
    {
        if (myStack -> data -> qty <  myStack -> size)
        {
            myStack -> data         = insertNode (myStack -> data, myStack->data->head, newNode);
            myStack -> top          = myStack -> data -> head;
        }
    }
   	if (myStack-> size				== 0)
    {
 		myStack -> data         = insertNode (myStack -> data, myStack->data->head, newNode);
		myStack -> top			= myStack -> data ->head;
	}
    return (myStack);
}

// pop a node from the stack. 
stack *pop (stack *myStack, Object **thatNode)
{
	if (stackIsEmpty (myStack) == true)
	{
		exit ();
	}
    myStack -> data             = obtainNode (myStack -> data, &(myStack -> top));
    (*thatNode)					= myStack->top;
	myStack -> top				= myStack -> data -> head;
    return (myStack);
}
stack *	deleteStack (stack * myStack)
{
	if (myStack->data != NULL)
	{
		myStack->data = clearList (myStack->data);
	}
	free(myStack);
	myStack		  = NULL;
	return (myStack);
}
// This is all a work in progress.

#endif // _STACK_H
