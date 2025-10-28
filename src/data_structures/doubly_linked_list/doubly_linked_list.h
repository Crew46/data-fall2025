#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "doubly_node.h"

struct DoublyLinkedList
{
  DoublyNode* head;
  DoublyNode* tail;
  int qty;
};

//creation
DoublyLinkedList* ConstructDoublyLinkedList();
void DeconstructDoublyLinkedList(DoublyLinkedList* doublyLinkedList);

//NODE MANIPULATIONS
bool _DoublyLinkedListAppendElementToNode(DoublyLinkedList* list, DoublyNode* place, Object* data);
bool _DoublyLinkedListInsertElementToNode(DoublyLinkedList* list, DoublyNode* place, Object* data);
DoublyNode* _GetDoublyNodeAtIndex(DoublyLinkedList* list, int index);
void _DetatchDoublyNodeFromDoublyLinkedList(DoublyLinkedList* list, DoublyNode* node);
void _DestroyNodeOfDoublyLinkedList(DoublyLinkedList* list, DoublyNode* nodeToDestroy);


//EXPOSED INTERFACES
bool DoublyLinkedListAppendElement(DoublyLinkedList* list, int index, Object* data);
bool DoublyLinkedListInsertElement(DoublyLinkedList* list, int index, Object* data);
bool DoublyLinkedListInsertElementToTail(DoublyLinkedList* doublyLinkedList, Object* data);
bool DoublyLinkedListAppendElementToHead(DoublyLinkedList* doublyLinkedList, Object* data);

Object* RemoveElementFromDoublyLinkedList(DoublyLinkedList* list, int index);
Object* RemoveElementAtHeadFromDoublyLinkedList(DoublyLinkedList* list);
Object* RemoveElementAtTailFromDoublyLinkedList(DoublyLinkedList* list);





#endif // DOUBLY_LINKED_LIST_H