#ifndef QUEUE_H
#define QUEUE_H
#include "../doubly_linked_list/doubly_linked_list.h"

struct Queue
{
    DoublyLinkedList* list;
};

//add node to queue
void Enqueue(DoublyNode* doublyNode);

//remove node from queue and return it
DoublyNode* Dequeue();

//peaks to see the next node in queue
DoublyNode* Peak();

#endif //QUEUE_H