#ifndef QUEUE_H
#define QUEUE_H
#include "../doubly_linked_list/doubly_linked_list.h"

struct Queue
{
    DoublyLinkedList* list;
    int size;
    int count;
};

//add node to queue
bool Enqueue(Queue* queue, DoublyNode* doublyNode);

//remove node from queue and return it
DoublyNode* Dequeue(Queue* queue);

//peaks to see the next node in queue
DoublyNode* Peak();

#endif //QUEUE_H