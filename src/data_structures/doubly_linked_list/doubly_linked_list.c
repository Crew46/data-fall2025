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

void DoublyLinkedListInsert(DoublyLinkedList* list, DoublyNode* place, DoublyNode* newNode)
{
  if ((list != NULL) && (newNode != NULL))
  {
    DoublyNode *tmp = NULL;

    if (list->head == NULL)
    {
      list->head = newNode;
      list->tail = newNode;
    }
    else if (place == list->head)
    {
      tmp = list->head;
      tmp->prev = newNode;
      newNode->next = tmp;
      list->head = newNode;
    }
    else
    {
      tmp = place->prev;
      tmp->next = newNode;
      newNode->next = place;
      place->prev = newNode;
      newNode->prev = tmp;
    }

    list->qty = list->qty + 1;
  }
}

void DoublyLinkedListAppend(DoublyLinkedList* list, DoublyNode* place, DoublyNode* newNode)
{
  if ((list != NULL) && (newNode != NULL))
  {
    DoublyNode *tmp = NULL;

    if (list->head == NULL)
    {
      list->head = newNode;
      list->tail = newNode;
    }
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

void DoublyLinkedListInsertToTail(DoublyLinkedList* doublyLinkedList, DoublyNode* node)
{
  DoublyLinkedListInsert(doublyLinkedList, doublyLinkedList->tail, node);
}

void DoublyLinkedListAppendToHead(DoublyLinkedList* doublyLinkedList, DoublyNode* node)
{
  DoublyLinkedListAppend(doublyLinkedList, doublyLinkedList->head, node);
}

#endif // DOUBLY_LINKED_LIST_C