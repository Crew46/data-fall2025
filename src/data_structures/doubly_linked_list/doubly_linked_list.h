#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "misc.h"
#include "doubly_node.h"
#include "../../object.h"

////////////////////////////////////////////////////////////
///////////Structs///////////////////////////////////////////
///////////////////////////////////////////////////////////

struct DoublyLinkedList
{
  DoublyNode* head;
  DoublyNode* tail;
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

DoublyLinkedList* CreateDoublyLinkedList()
{
  DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
}


////////////////////////////////////////////////////////////
///////////INSERTION////////////////////////////////////////
////////////////////////////////////////////////////////////

void DoublyLinkedListInsertAfterTail(DoublyLinkedList* doublyLinkedList, Object* data)
{
  //if tail exists
  if(doublyLinkedList->tail != NULL)
  {
    //if tail has data in it, must create new node and insert it after tail, then set new tail to new node
    if(doublyLinkedList->tail->data != NULL)
    {
      DoublyNode* newNode = CreateDoublyNode(data);
      InsertDoublyNodeAfterDoublyNode(doublyLinkedList->tail, newNode);
      //inserted node, becomes new tail
      doublyLinkedList->tail = newNode;
    }
    //tail data is pointing to null
    else
    {
      doublyLinkedList->tail->data = data;
    }
  }
  //if tail doesn't exist, create one and pass in data
  else
  {
    doublyLinkedList->tail = CreateDoublyNode(data);
  }
}

void DoublyLinkedListInsertBeforeHead(DoublyLinkedList* doublyLinkedList, Object* data)
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
  Object* data = list->head->data; 
  DoublyNode* newHead = list->head->next;
  DeleteDoublyNode(list->head);
  list->head = newHead;
  return data;
}

void* DoublyLinkedListPopBack(DoublyLinkedList* list)
{
  Object* data = list->tail->data;
  DoublyNode* newTail = list->tail->previous;
  DeleteDoublyNode(list->tail);
  list->tail = newTail;
  return data;
}

DoublyNode* FindDoublyNodeOfData(DoublyLinkedList* doublyLinkedList, Object* data)
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
