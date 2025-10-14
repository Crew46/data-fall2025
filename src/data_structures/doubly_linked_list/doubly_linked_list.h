#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "doubly_node.h"

struct DoublyLinkedList
{
  DoublyNode* head;
  DoublyNode* tail;
  int qty;
};

//create doubly linked list
DoublyLinkedList* ConstructDoublyLinkedList();

//deconstruct doubly linked list
void DeconstructDoublyLinkedList(DoublyLinkedList* doublyLinkedList);

void DoublyLinkedListAppend(DoublyLinkedList* list, DoublyNode* place, DoublyNode* newNode);

void DoublyLinkedListInsert(DoublyLinkedList* list, DoublyNode* place, DoublyNode* newNode);

//insert to tail
void DoublyLinkedListInsertToTail(DoublyLinkedList* doublyLinkedList, DoublyNode* node);

//append to tail
void DoublyLinkedListAppendToHead(DoublyLinkedList* doublyLinkedList, DoublyNode* node);

#endif // DOUBLY_LINKED_LIST_H