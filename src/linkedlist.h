#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

// This will make the list
doublyLinkedList *mkList ()
{
    doublyLinkedList *myList  = NULL;
    
    myList                    = (doublyLinkedList *) malloc (sizeof (doublyLinkedList));
    if(myList                == NULL)
    {
        exit();
    }

    myList -> head            = NULL;
    myList -> tail            = NULL;
    myList -> qty             = 0;

    return (myList);
}

// This function will create a single EnemyA everytime it is used.
doublyLinkedList *appendNode (doublyLinkedList *myList, Object *place, Object *newNode)
{
    if (myList                == NULL)
    {
        myList                 = (doublyLinkedList *) malloc (sizeof (doublyLinkedList));
    }
    
    if ((myList               != NULL) &&
        (newNode              != NULL))
    {
        Object *tmp            = NULL;
    
        if (myList -> head    == NULL)
        {
            myList -> head     = newNode;
            myList -> tail     = newNode;
        }
        else if (place        == myList -> tail)
        {
            tmp                = myList -> tail;
            tmp -> next        = newNode;
            newNode -> prev    = tmp;
            myList -> tail     = newNode;
        }
        else
        {
            tmp                = place -> next;
            tmp-> prev         = place;
            place -> next      = newNode;
            newNode -> next    = tmp;
        }
    }

    myList -> qty              = myList -> qty + 1;

    return (myList);
}

//rmNode frees up nodes that we want gone.
doublyLinkedList *rmNode (Object **thatNode, doublyLinkedList *myList)
{
    if((*thatNode)    != NULL)
    {
        free(*thatNode);
        (*thatNode)     = NULL;
    }
    return (myList);
}


// The obtain function disconnects nodes.
doublyLinkedList *obtainNode (doublyLinkedList *myList, Object **thatNode)
{
    // Obtaining the head edge case.
    if ((*thatNode)                 == myList -> head)
    {
        myList -> head               = (*thatNode) -> next;
        (*thatNode) -> next -> prev  = NULL;
        (*thatNode) -> next          = NULL;
    }
    // Obtain the tail edge case.
    if ((*thatNode)                 == myList -> tail)
    {
        myList -> tail               = (*thatNode) -> prev;
        myList -> tail -> next       = NULL;
        (*thatNode) -> prev          = NULL;
    }    
    // No edge cases. Proceed.
    if (((*thatNode)                != myList -> head) &&
        ((*thatNode)                != myList -> tail))
    {
        (*thatNode) -> prev -> next  = (*thatNode) -> next;
        (*thatNode) -> next -> prev  = (*thatNode) -> prev;
        (*thatNode) -> next          = NULL;
        (*thatNode) -> prev          = NULL;
    }

    myList -> qty                    = myList -> qty + 1;

    return (myList);
}


//Empty the list.
doublyLinkedList *clearList (doublyLinkedList *myList)
{
    Object *tmp      = NULL;
    if (myList      != NULL)
    {
        while (tmp  != NULL)
        {
            myList   = obtainNode (myList, &tmp);
            myList   = rmNode (&tmp, myList);
            tmp      = myList -> head;
        }
    }

    return (myList);
}

// Insert will insert a node before a node.
doublyLinkedList *insertNode (doublyLinkedList *myList, Object *place, Object *newNode)
{
    if(myList                 == NULL)
    {
        myList                 = (doublyLinkedList *) malloc(sizeof(doublyLinkedList));
    }
    
    if ((myList               != NULL) &&
        (newNode              != NULL))
    {
        Object *tmp            = NULL;
        
        if (myList -> head    == NULL)
        {
            myList -> head     = newNode;
            myList -> tail     = newNode;
        }
        else if (place        == myList -> head)
        {
            tmp                = myList -> head;
            tmp -> prev        = newNode;
            newNode -> next    = tmp;
            myList -> head     = newNode;
        }    
        else
        {
            tmp                = place -> prev;
            tmp -> next        = newNode;
            newNode -> next    = place;
            place -> prev      = newNode;
            newNode -> prev    = tmp;
        }
    }

    myList -> qty              = myList -> qty + 1;

    return (myList);
}


// This will delete a list when we no longer need it.
doublyLinkedList *deleteList (doublyLinkedList *myList)
{
    if (myList  != NULL)
    {
        myList   = clearList (myList);
        free (myList);
        myList   = NULL;
    }
    return (myList);
}

#endif  // _LINKEDLIST_H
