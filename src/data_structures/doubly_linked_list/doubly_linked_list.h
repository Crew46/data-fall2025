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

//append & insert data to node
bool DoublyLinkedListAppendToNode(DoublyLinkedList* list, DoublyNode* place, Object* data);
bool DoublyLinkedListInsertToNode(DoublyLinkedList* list, DoublyNode* place, Object* data);

//apend & insert data to head and tail
bool DoublyLinkedListInsertToTail(DoublyLinkedList* doublyLinkedList, Object* data);
bool DoublyLinkedListAppendToHead(DoublyLinkedList* doublyLinkedList, Object* data);

void RemoveDoublyNodeFromList(DoublyLinkedList* list, DoublyNode* node);

DoublyNode* GetDoublyNodeOfData(DoublyLinkedList* list, Object* data);

void RemoveDataFromDoublyLinkedList(DoublyLinkedList* list, Object* data);

#endif // DOUBLY_LINKED_LIST_H