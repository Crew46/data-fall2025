#ifndef _LIST_H
#define _LIST_H

#include "doubly_node.h"

////////////////////////////////////////////////////////////////////////////////////
//
//  Doubly Linked List struct and helpers
//
struct List
{
    Node *head;
    Node *tail;
    int   qty;
};

////////////////////////////////////////////////////////////////////////////////////
//
//  append(): add a newNode into myList after indicated place
//
List *append (List *myList, Node *place, Node *newNode)
{
    if (myList              == NULL)
    {
        myList               = (List *) malloc (sizeof (List));
    }

    if ((myList             != NULL) &&
        (newNode            != NULL))
    {
        Node *tmp            = NULL;

        if (myList -> head  == NULL)
        {
            myList -> head   = newNode;
            myList -> tail   = newNode;
        }
        else if (place      == myList -> tail)
        {
            tmp              = myList -> tail;
            tmp -> next      = newNode;
            newNode -> prev  = tmp;
            myList -> tail   = newNode;
        }
        else
        {
            tmp              = place -> next;
            tmp -> prev      = newNode;
            newNode -> prev  = place;
            place -> next    = newNode;
            newNode -> next  = tmp;
        }
        myList -> qty        = myList -> qty + 1;
    }

    return (myList);
}

////////////////////////////////////////////////////////////////////////////////////
//
//  insert(): add a newNode into myList before indicated place
//
List *insert (List *myList, Node *place, Node *newNode)
{
    if (myList              == NULL)
    {
        myList               = (List *) malloc (sizeof (List));
    }

    if ((myList             != NULL) &&
        (newNode            != NULL))
    {
        Node *tmp            = NULL;

        if (myList -> head  == NULL)
        {
            myList -> head   = newNode;
            myList -> tail   = newNode;
        }
        else if (place      == myList -> head)
        {
            tmp              = myList -> head;
            tmp -> prev      = newNode;
            newNode -> next  = tmp;
            myList -> head   = newNode;
        }
        else
        {
            tmp              = place -> prev;
            tmp -> next      = newNode;
            newNode -> next  = place;
            place -> prev    = newNode;
            newNode -> prev  = tmp;
        }

        myList -> qty        = myList -> qty + 1;
    }

    return (myList);
}

////////////////////////////////////////////////////////////////////////////////////
//
//  obtain(): take thatNode and disconnect it (while maintaining list integrity)
//            from myList.
//
List *obtain (List *myList, Node *thatNode)
{
    if (!myList || !thatNode || !(thatNode))
        return (myList);

    // Only one node
    if (myList -> head           == thatNode &&
        myList -> tail           == thatNode)
    {
        myList -> head            = NULL;
        myList -> tail            = NULL;
    }
    else if (thatNode            == myList -> head)
    {
        myList -> head            = thatNode -> next;
        myList -> head -> prev    = NULL;
    }
    else if (thatNode            == myList -> tail)
    {
        myList -> tail            = thatNode -> prev;
        myList -> tail -> next    = NULL;
    }
    else
    {
        thatNode -> next -> prev  = thatNode -> prev;
        thatNode -> prev -> next  = thatNode -> next;
    }

    myList -> qty                 = myList -> qty - 1;

    return (myList);
}

////////////////////////////////////////////////////////////////////////////////////
//
//  createList(): allocate and initialize a new list
//
List *createList ()
{
    List *myList        = (List*) malloc (sizeof (List));
    if (myList         != NULL)
    {
        myList -> head  = NULL;
        myList -> tail  = NULL;
        myList -> qty   = 0;
    }

    return (myList);
}

////////////////////////////////////////////////////////////////////////////////////
//
//  clearList(): sanely obtain and deallocate all nodes in myList, leaving an
//               empty list
//
List *clearList (List *myList)
{
    Node *tmp         = NULL;
    if (myList       != NULL)
    {
        tmp           = myList -> head;
        while (tmp   != NULL)
        {
            myList    = obtain (myList, tmp);
            tmp       = deleteNode (tmp);
            tmp       = myList -> head;
        }
    }

    return (myList);
}

////////////////////////////////////////////////////////////////////////////////////
//
//  deleteList(): clear and deallocate a list, returning a NULL
//
List *deleteList (List *oldList)
{
    if (oldList      != NULL)
    {
        oldList       = clearList (oldList);
        free (oldList);
        oldList       = NULL;
    }

    return (oldList);
}

#endif
