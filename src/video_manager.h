#ifndef  _VIDEO_MANAGER_H
#define  _VIDEO_MANAGER_H
#include "video.h"
#include "object.h"
#include "data_structures/doubly_linked_list/doubly_linked_list.h"
#include "data_structures/queue/queue.h"
#include "data_structures/stack/stack.h"

void drawList (List *list)
{
    Node *currentNode   = list -> head;
    Node *nextNode      = NULL;

    while (currentNode != NULL)
    {
        nextNode        = currentNode -> next;

        drawObject (currentNode -> data);

        currentNode     = nextNode;
    }
}

void drawQueue (Queue *queue)
{
    drawList (queue -> list);
}

void drawStack (Stack *stack)
{
    drawList (stack -> list);
}

#endif // _VIDEO_MANAGER_H
