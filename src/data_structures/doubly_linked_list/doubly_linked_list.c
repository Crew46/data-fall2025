#ifndef DOUBLY_LINKED_LIST_C
#define DOUBLY_LINKED_LIST_C
#include "doubly_linked_list.h"
#include "doubly_node.c"

//////////////////////////////////
/*

API:

void ConstructDoublyLinkedList();

void DeconstructDoublyLinkedList();

bool DoublyLinkedListAppendElement()

bool DoublyLinkedListInsertElement()

bool DoublyLinkedListInsertElementToHead()

bool DoublyLinkedListInsertElementToTail()

Object* RemoveElementFromDoublyLinkedList()

Object* RemoveElementAtTailFromDoublyLinkedList()

Object* RemoveElementAtHeadFromDoublyLinkedList()


*/

DoublyLinkedList* ConstructDoublyLinkedList()
{
  DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
  list->head = NULL;
  list->tail = NULL;
  list->qty = 0;
  return list;
}

void DeconstructDoublyLinkedList(DoublyLinkedList* doublyLinkedList)
{
  DoublyNode* current = doublyLinkedList->head;
  while (current != NULL)
  {
    DoublyNode* next = current->next;
    _DestroyNodeOfDoublyLinkedList(doublyLinkedList, current);
    current = next;
  }
  free(doublyLinkedList);
}

//node

bool _DoublyLinkedListInsertElementToNode(DoublyLinkedList* list, DoublyNode* place, Object* data)
{
  if(data == NULL || list == NULL) return false;

  DoublyNode* newNode = ConstructDoublyNode(data);

  //list is empty
  if (list->head == NULL)
  {
    list->head = newNode;
    list->tail = newNode;
  }
  //place is head
  else if (place == list->head)
  {
    InsertDoublyNodeToDoublyNode(place, newNode);
    list->head = newNode;
  }
  //default case
  else
  {
    InsertDoublyNodeToDoublyNode(place, newNode); 
  }

  list->qty = list->qty + 1;
  return true;
}

bool _DoublyLinkedListAppendElementToNode(DoublyLinkedList* list, DoublyNode* place, Object* data)
{
  if(data == NULL || list == NULL ) return false;
  
  DoublyNode* newNode = ConstructDoublyNode(data);

  //list is empty
  if (list->head == NULL)
  {
    list->head = newNode;
    list->tail = newNode;
  }
  //place is tail
  else if (place == list->tail)
  {
    AppendDoublyNodeToDoublyNode(place, newNode);
    list->tail = newNode;
  }
  //default case
  else
  {
    AppendDoublyNodeToDoublyNode(place, newNode);
  }

  list->qty = list->qty + 1;
  return true;
}

void _DetatchDoublyNodeFromDoublyLinkedList(DoublyLinkedList* list, DoublyNode* node)
{
  if(list == NULL || node == NULL)
  {
    return;
  }
  else if(node == list->head && node == list->tail)
  {
    list->head = NULL;
    list->tail = NULL;
    DetatchDoublyNodeFromChain(node);
  }
  else if(node == list->tail)
  {
    list->tail = node->prev;
    DetatchDoublyNodeFromChain(node);
  }
  else if(node == list->head)
  {
    list->head = node->next;
    DetatchDoublyNodeFromChain(node);
  }
  else
  {
    DetatchDoublyNodeFromChain(node);
  }
  list->qty = list->qty - 1;
}

void _DestroyNodeOfDoublyLinkedList(DoublyLinkedList* list, DoublyNode* nodeToDestroy)
{
  _DetatchDoublyNodeFromDoublyLinkedList(list, nodeToDestroy);
  DeconstructDoublyNode(nodeToDestroy);
}

DoublyNode* _GetDoublyNodeAtIndex(DoublyLinkedList* list, int index)
{
  DoublyNode* currentNode = list->head;
  int currentIndex = 0;
  while(currentNode != NULL)
  {
    if(currentIndex == index)
    {
      return currentNode;
    }
    currentNode = currentNode->next;
    currentIndex++;
  }
  return NULL;
}


//INTERFACE

bool DoublyLinkedListAppendElement(DoublyLinkedList* list, int index, Object* data)
{
  DoublyNode* nodeToAppendTo = _GetDoublyNodeAtIndex(list, index);
  return _DoublyLinkedListAppendElementToNode(list, nodeToAppendTo, data);
}

bool DoublyLinkedListInsertElement(DoublyLinkedList* list, int index, Object* data)
{
  DoublyNode* nodeToInsertTo = _GetDoublyNodeAtIndex(list, index);
  return _DoublyLinkedListInsertElementToNode(list, nodeToInsertTo, data);
}

bool DoublyLinkedListInsertElementToTail(DoublyLinkedList* doublyLinkedList, Object* data)
{
  return _DoublyLinkedListInsertElementToNode(doublyLinkedList, doublyLinkedList->tail, data);
}

bool DoublyLinkedListAppendElementToHead(DoublyLinkedList* doublyLinkedList, Object* data)
{
  return _DoublyLinkedListAppendElementToNode(doublyLinkedList, doublyLinkedList->head, data);
}

Object* RemoveElementFromDoublyLinkedList(DoublyLinkedList* list, int index)
{
  DoublyNode* nodeToDestroy = _GetDoublyNodeAtIndex(list, index);
  Object* objectToReturn = nodeToDestroy->data;
  _DestroyNodeOfDoublyLinkedList(list, nodeToDestroy);
  return objectToReturn;
}

Object* RemoveElementAtHeadFromDoublyLinkedList(DoublyLinkedList* list)
{

}

Object* RemoveElementAtTailFromDoublyLinkedList(DoublyLinkedList* list)
{

}

#endif // DOUBLY_LINKED_LIST_C