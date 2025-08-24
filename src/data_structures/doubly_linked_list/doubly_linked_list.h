#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "misc.h"
#include "doubly_node.h"

////////////////////////////////////////////////////////////
///////////Structs///////////////////////////////////////////
///////////////////////////////////////////////////////////

struct DoublyLinkedList
{
  DoublyNode* head;
  DoublyNode* tail;
  int size;
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

DoublyLinkedList* CreateDoublyLinkedList()
{
  DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
  list->head = CreateDoublyNode(NULL);
  list->tail = CreateDoublyNode(NULL);
  list->size = 0;
}

void DeconstructDoublyLinkedList(DoublyLinkedList* list)
{
}

////////////////////////////////////////////////////////////
///////////INSERTION////////////////////////////////////////
////////////////////////////////////////////////////////////

void DoublyLinkedListPushBack(DoublyLinkedList* doublyLinkedList, void* data)
{
  if(doublyLinkedList->tail->data != NULL)
  {
    InsertDoublyNodeAfterDoublyNode(doublyLinkedList->tail, CreateDoublyNode(data));
  }
  else
  {
    doublyLinkedList->tail->data = data;
  }
}

void DoublyLinkedListPushFront(DoublyLinkedList* doublyLinkedList, void* data)
{
  if(doublyLinkedList->head->data != NULL)
  {
    InsertDoublyNodeBeforeDoublyNode(doublyLinkedList->head, CreateDoublyNode(data));
  }
  else
  {
    doublyLinkedList->head->data = data;
  }
}

////////////////////////////////////////////////////////////
///////////ACCESS///////////////////////////////////////////
////////////////////////////////////////////////////////////

void* DoublyLinkedListPopFront(DoublyLinkedList* list)
{
  void* data = list->head->data; 
  DoublyNode* newHead = list->head->next;
  DeleteDoublyNode(list->head);
  list->head = newHead;
  return data;
}

void* DoublyLinkedListPopBack(DoublyLinkedList* list)
{
  void* data = list->tail->data;
  DoublyNode* newTail = list->tail->previous;
  DeleteDoublyNode(list->tail);
  list->tail = newTail;
  return data;
}



DoublyNode* FindDoublyNodeOfData(DoublyLinkedList* doublyLinkedList, void* data)
{
  DoublyNode* selectedNode = doublyLinkedList->head;
  while(selectedNode != NULL)
  {
    //if desired data matches data of a node
    if(selectedNode->data == data)
    {
      return selectedNode;
    }

    selectedNode = selectedNode->next;
  }
  
  return NULL;
}

#endif // LINKED_LIST_H
