#ifndef DOUBLY_LINKED_LIST_C
#define DOUBLY_LINKED_LIST_C
#include "doubly_linked_list.h"
#include "doubly_node.c"

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

}

////////////////////////////////////////////////////////////
///////////INSERTION////////////////////////////////////////
////////////////////////////////////////////////////////////

bool DoublyLinkedListInsertToNode(DoublyLinkedList* list, DoublyNode* place, Object* data)
{
  if( data == NULL || list == NULL ) return false;

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

bool DoublyLinkedListAppendToNode(DoublyLinkedList* list, DoublyNode* place, Object* data)
{
  DoublyNode* newNode = ConstructDoublyNode(data);

  if ((list != NULL))
  {
    DoublyNode *tmp = NULL;

    if (list->head == NULL)
    {
      list->head = newNode;
      list->tail = newNode;
    }
    //if place is tail
    else if (place == list->tail)
    {
      tmp = list->tail;
      tmp->next = newNode;
      newNode->prev = tmp;
      list->tail = newNode;
    }
    else
    {
        tmp = place->next;
        tmp->prev = newNode;
        newNode->prev = place;
        place->next = newNode;
        newNode->next = tmp;
    }
    list->qty = list->qty + 1;
  }
}

bool DoublyLinkedListInsertToTail(DoublyLinkedList* doublyLinkedList, Object* data)
{
  return DoublyLinkedListInsertToNode(doublyLinkedList, doublyLinkedList->tail, data);
}

bool DoublyLinkedListAppendToHead(DoublyLinkedList* doublyLinkedList, Object* data)
{
  return DoublyLinkedListAppendToNode(doublyLinkedList, doublyLinkedList->head, data);
}

void RemoveDataFromDoublyLinkedList(DoublyLinkedList* doublyLinkedList, Object* data)
{

}

#endif // DOUBLY_LINKED_LIST_C