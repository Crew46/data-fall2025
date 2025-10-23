#ifndef  _VIDEO_MANAGER_H
#define  _VIDEO_MANAGER_H
#include "video.h"
#include "object.h"
#include "data_structures/doubly_linked_list/doubly_linked_list.h"
#include "data_structures/queue/queue.h"
#include "data_structures/stack/stack.h"

void drawList (List *myList)
{
    Node *currentNode       = NULL;

    if (myList             != NULL)
    {
        currentNode         = myList -> head;

        while (currentNode != NULL)
        {
            drawObject (currentNode -> data);
            currentNode     = currentNode -> next;
        }
    }
}

void drawQueue (Queue *myQueue)
{
    drawList (myQueue -> data);
}

void drawStack (Stack *myStack)
{
    drawList (myStack -> data);
}

#endif // _VIDEO_MANAGER_H
