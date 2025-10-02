#ifndef _NODE_H
#define _NODE_H
#include "../../object.h"

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

Node *createNode (Object *data)
{
	Node *node    = (Node *) malloc (sizeof (Node));
	node -> data  = data;
	node -> next  = NULL;
	node -> prev  = NULL;

	return node;
}

Node *deleteNode (Node *oldNode)
{
	if (oldNode  != NULL)
	{
		free (oldNode);
		oldNode   = NULL;
	}

	return (oldNode);
}

#endif
