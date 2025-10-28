#ifndef QUEUE_C
#define QUEUE_C
#include "queue.h"
#include "../doubly_linked_list/doubly_linked_list.h"

void Enqueue(Queue* queue, Object* data)
{
    DoublyLinkedListInsertElementToTail(queue->list, data);
}

Object* Dequeue(Queue* queue)
{
    return RemoveElementAtHeadFromDoublyLinkedList(queue->list);
}

#endif