#ifndef _NODE_H
#define _NODE_H

#include "../../object.h"

////////////////////////////////////////////////////////////////////////////////////
//
// doubly linked node API
// ======================
//
// Node *createNode (Object *data);
// Node *deleteNode (Node   *oldNode);
//
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
//
//  Node struct and helpers
//
struct Node
{
    Object *data;
    Node   *next;
    Node   *prev;
};

////////////////////////////////////////////////////////////////////////////////////
//
// createNode(): allocate and initialize a new Node
//
Node *createNode (Object *data)
{
    Node *newNode        = (Node *) malloc (sizeof (Node));
    if (newNode         != NULL)
    {
        newNode -> data  = data;
        newNode -> next  = NULL;
        newNode -> prev  = NULL;
    }

    return (newNode);
}

////////////////////////////////////////////////////////////////////////////////////
//
// deleteNode(): deallocate an existing node (setting pointer to NULL)
//
Node *deleteNode (Node *oldNode)
{
    if (oldNode         != NULL)
    {
        free (oldNode);
        oldNode          = NULL;
    }

    return (oldNode);
}

#endif
