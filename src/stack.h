#ifndef _STACK_H
#define _STACK_H
#include "functions.h"

// This will create the stack.
stack * mkStack(doublyLinkedList * myList)
{
stack * myStack = (stack *) malloc(sizeof(stack));
    if(myStack == NULL)
        {
            exit();
        }
myStack->top     = myList->head;
myStack->data    = myList;
myStack->top    = myStack->data->head;
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
    int     b                       = 0;

    if (myStack -> size            != 0)
    {
        if (myStack -> data -> qty <  myStack -> size)
        {
            myStack -> data         = insertNode (myStack -> data, myStack->data->head, newNode);
            myStack -> top          = myStack -> data -> head;
        }
    }
    else
    {
// This would be used if we store enemies. (Subject to change depending on what we plan to do with the stack.)
        b                           = rand () % (100 + 0);
        if (b                      >  92)
        {
            myStack -> data         = insertNode (myStack -> data, myStack->data->tail, newNode);
        }
    }
    myStack -> top                  = myStack -> data -> head;
    return (myStack);
}

// pop a node from the stack. 
stack *pop (stack *myStack, Object **thatNode)
{
    myStack -> top              = myStack -> data -> head;
    if (stackIsEmpty (myStack) == true)
    {
        exit ();    
    }

    myStack -> data             = obtainNode (myStack -> data, &(myStack -> top));
    (*thatNode)                 = myStack -> top;
    myStack -> top              = myStack -> data -> head;
    return (myStack);
}

// This is all a work in progress.

#endif // _STACK_H
