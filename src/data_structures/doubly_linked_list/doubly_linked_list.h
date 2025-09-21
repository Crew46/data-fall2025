#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "doubly_node.h"

struct DoublyLinkedList
{
  DoublyNode* head;
  DoublyNode* tail;
};

DoublyLinkedList* CreateDoublyLinkedList();

void DoublyLinkedListInsertAtTail(DoublyLinkedList* doublyLinkedList, Object* data);

#endif // DOUBLY_LINKED_LIST_H