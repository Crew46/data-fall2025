#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "misc.h"

////////////////////////////////////////////////////////////
///////////Structs///////////////////////////////////////////
///////////////////////////////////////////////////////////

struct DoublyNode
{
  void* data;
  DoublyNode* next;
  DoublyNode* previous;
};

struct DoublyLinkedList
{
  DoublyNode* head;
  DoublyNode* tail;
  int size;
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

DoublyNode* CreateDoublyNode(void* data)
{
  DoublyNode* node = (DoublyNode*)malloc(sizeof(DoublyNode));
  node->next = NULL;
  node->previous = NULL;
  node->data = data;
  return node;
}

DoublyLinkedList* CreateDoublyLinkedList()
{
  DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
  list->head = CreateDoublyNode(NULL);
  list->tail = CreateDoublyNode(NULL);
  list->size = 0;
}

////////////////////////////////////////////////////////////
///////////INSERTION////////////////////////////////////////
////////////////////////////////////////////////////////////

void InsertDoublyNodeAfterDoublyNode(DoublyNode* nodeToInsertAfter, DoublyNode* newNode)
{
  nodeToInsertAfter->next->previous = newNode;

  newNode->next = nodeToInsertAfter->next; 
  newNode->previous = nodeToInsertAfter;

  nodeToInsertAfter->next = newNode;
}

void InsertDoublyNodeBeforeDoublyNode(DoublyNode* nodeToInsertBefore, DoublyNode* newNode)
{
  nodeToInsertBefore->previous->next = newNode;

  newNode->previous = nodeToInsertBefore->previous;

  newNode->next = nodeToInsertBefore;

  nodeToInsertBefore->previous = newNode;
}

void InsertDataAtTail(DoublyLinkedList* doublyLinkedList, void* data)
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

void InsertDataAtHead(DoublyLinkedList* doublyLinkedList, void* data)
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
