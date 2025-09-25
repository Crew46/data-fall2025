#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "doubly_node.h"

struct DoublyLinkedList
{
  DoublyNode* head;
  DoublyNode* tail;
};

DoublyLinkedList* ConstructDoublyLinkedList();

void DeconstructDoublyLinkedList(DoublyLinkedList* doublyLinkedList);

//insert to tail
void DoublyLinkedListInsertToTail(DoublyLinkedList* doublyLinkedList, Object* data);

//append to tail
void DoublyLinkedListAppendToHead(DoublyLinkedList* doublyLinkedList, Object* data);

//detach node from list and return
DoublyNode* Detatch();

//leave node, but return to peak into
DoublyNode* Peak();

#endif // DOUBLY_LINKED_LIST_H