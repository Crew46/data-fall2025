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
  list->head = CreateDoublyNode(NULL);
  list->tail = NULL;
  return list;
}

////////////////////////////////////////////////////////////
///////////INSERTION////////////////////////////////////////
////////////////////////////////////////////////////////////

void DoublyLinkedListInsertAtTail(DoublyLinkedList* doublyLinkedList, Object* data)
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
    //tail data has nothing in it
    else
    {
      doublyLinkedList->tail->data = data;
    }
  }
  //if tail doesn't exist
  else
  {
    //if head exists
    if(doublyLinkedList->head != NULL)
    {
      //if head data is empty
      if(doublyLinkedList->head->data == NULL)
      {
        doublyLinkedList->head->data = data;
      }
      //need to create tail node
      else
      {
        doublyLinkedList->tail = CreateDoublyNode(data);
        doublyLinkedList->tail->previous = doublyLinkedList->head;
        doublyLinkedList->head->next = doublyLinkedList->tail;
      }
    }
    //if head doesn't exist
    else
    {
      doublyLinkedList->head = CreateDoublyNode(data);
    }
  }
}

void DoublyLinkedListInsertAtHead(DoublyLinkedList* doublyLinkedList, Object* data)
{
  //if head exists
  if(doublyLinkedList->head != NULL)
  {
    //if head has has data in it already
    if(doublyLinkedList->head->data != NULL)
    {
      DoublyNode* newNode = CreateDoublyNode(data);
      InsertDoublyNodeBeforeDoublyNode(doublyLinkedList->head, newNode);
      //set head of list to the new node
      doublyLinkedList->head = newNode;
    }
    //if head doesn't have data in it
    else
    {
      doublyLinkedList->head->data = data;
    }
  }
  //if head doesn't exist
  else
  {
    doublyLinkedList->head = CreateDoublyNode(data);
  }
}

////////////////////////////////////////////////////////////
///////////ACCESS///////////////////////////////////////////
////////////////////////////////////////////////////////////

Object* DoublyLinkedListGetObjectAtHead(DoublyLinkedList* list)
{
  return list->head->data;
}

Object* DoublyLinkedListGetObjectAtTail(DoublyLinkedList* list)
{
  return list->tail->data;
}

#endif // LINKED_LIST_H
