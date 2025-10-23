#ifndef _STACK_H
#define _STACK_H

#include "../doubly_linked_list/doubly_linked_list.h"

////////////////////////////////////////////////////////////////////////////////////
//
// doubly linked stack API
// =======================
//
// Stack *createStack (int size);
// Stack *push        (Stack *myStack, Node *newNode)
// Node  *pop         (Stack *myStack);
//
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
//
// Stack struct: embedded list does the bulk of heavy listing. Stack just adds
//               restrictions to list access
//
struct Stack
{
    int   size;
    List *data;
    Node *top;
};

////////////////////////////////////////////////////////////////////////////////////
//
// createStack(): given a size, allocate resources for a new stack (and its
//                embedded list)
//
Stack *createStack (int size)
{
    Stack *myStack       = (Stack *) malloc (sizeof (Stack));
    if (myStack         != NULL)
    {
        myStack -> data  = createList ();
        myStack -> size  = size;
        myStack -> top   = NULL;
    }

    return (myStack);
}

////////////////////////////////////////////////////////////////////////////////////
//
// push(): add newNode onto myStack (via insert()'ing into the embedded list)
//
Stack *push (Stack *myStack, Node *newNode)
{
    Node *tmp                  = NULL;
    if (newNode               != NULL)
    {
        if ((myStack -> size  >  myStack -> data -> qty) ||
            (myStack -> size  <  1))
        {
            tmp                = myStack -> data -> head;
            myStack -> data    = insert (myStack -> data, tmp, newNode);
            myStack -> top     = myStack -> data -> head;
        }
    }

    return (myStack);
}

////////////////////////////////////////////////////////////////////////////////////
//
// pop(): grab the top node off the stack (via obtain()'ing from the list)
//
Node *pop (Stack *myStack)
{
    Node *poppedNode     = NULL;

    if (myStack -> top  != NULL)
    {
        poppedNode       = myStack -> top;
        myStack -> data  = obtain (myStack -> data, &poppedNode);
        myStack -> top   = myStack -> data -> head;
    }

    return (poppedNode);
}

#endif
