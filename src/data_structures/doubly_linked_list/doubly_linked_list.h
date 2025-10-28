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
bool _DoublyLinkedListAppendElementToDoublyNode(DoublyLinkedList* list, DoublyNode* place, Object* data);
bool _DoublyLinkedListInsertElementToDoublyNode(DoublyLinkedList* list, DoublyNode* place, Object* data);
DoublyNode* _GetDoublyNodeAtIndex(DoublyLinkedList* list, int index);
void _DetatchDoublyNodeFromDoublyLinkedList(DoublyLinkedList* list, DoublyNode* node);
void _DestroyDoublyNodeOfDoublyLinkedList(DoublyLinkedList* list, DoublyNode* nodeToDestroy);
DoublyNode* _GetDoublyNodeOfElement(DoublyLinkedList* list, Object* data);


//EXPOSED INTERFACES
bool DoublyLinkedListAppendElement(DoublyLinkedList* list, int index, Object* data);
bool DoublyLinkedListInsertElement(DoublyLinkedList* list, int index, Object* data);
bool DoublyLinkedListInsertElementToTail(DoublyLinkedList* doublyLinkedList, Object* data);
bool DoublyLinkedListAppendElementToHead(DoublyLinkedList* doublyLinkedList, Object* data);

Object* RemoveElementAtIndexFromDoublyLinkedList(DoublyLinkedList* list, int index);
Object* RemoveElementFromDoublyLinkedList(DoublyLinkedList* list, Object* data);
Object* RemoveElementAtHeadFromDoublyLinkedList(DoublyLinkedList* list);
Object* RemoveElementAtTailFromDoublyLinkedList(DoublyLinkedList* list);





#endif // DOUBLY_LINKED_LIST_H