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



bool DoublyLinkedListAppendToNode(DoublyLinkedList* list, DoublyNode* place, Object* data);

bool DoublyLinkedListInsertToNode(DoublyLinkedList* list, DoublyNode* place, Object* data);

//insert to tail
bool DoublyLinkedListInsertToTail(DoublyLinkedList* doublyLinkedList, Object* data);

//append to tail
bool DoublyLinkedListAppendToHead(DoublyLinkedList* doublyLinkedList, Object* data);


void RemoveDataFromDoublyLinkedList(DoublyLinkedList* doublyLinkedList, Object* data);


#endif // DOUBLY_LINKED_LIST_H