#ifndef DOUBLY_LINKED_LIST_DECLARATION_H
#define DOUBLY_LINKED_LIST_DECLARATION_H
#include "doubly_node_declaration.h"

struct DoublyLinkedList
{
  DoublyNode* head;
  DoublyNode* tail;
};

DoublyLinkedList* CreateDoublyLinkedList();
void DoublyLinkedListInsertAtTail(DoublyLinkedList* doublyLinkedList, Object* data);
void DoublyLinkedListInsertAtHead(DoublyLinkedList* doublyLinkedList, Object* data);

#endif // DOUBLY_LINKED_LIST_DECLARATION_H