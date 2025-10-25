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
  DoublyNode* current = doublyLinkedList->head;
  while (current != NULL)
  {
    DoublyNode* next = current->next;
    RemoveDoublyNodeFromList(doublyLinkedList, current);
    DeconstructDoublyNode(current);
    current = next;
  }
  free(doublyLinkedList);
}

////////////////////////////////////////////////////////////
///////////INSERTION////////////////////////////////////////
////////////////////////////////////////////////////////////

bool DoublyLinkedListInsertToNode(DoublyLinkedList* list, DoublyNode* place, Object* data)
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

bool DoublyLinkedListAppendToNode(DoublyLinkedList* list, DoublyNode* place, Object* data)
{
  if(data == NULL || list == NULL) return false;
  
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
}

bool DoublyLinkedListInsertToTail(DoublyLinkedList* doublyLinkedList, Object* data)
{
  return DoublyLinkedListInsertToNode(doublyLinkedList, doublyLinkedList->tail, data);
}

bool DoublyLinkedListAppendToHead(DoublyLinkedList* doublyLinkedList, Object* data)
{
  return DoublyLinkedListAppendToNode(doublyLinkedList, doublyLinkedList->head, data);
}

void RemoveDoublyNodeFromList(DoublyLinkedList* list, DoublyNode* node)
{
  if(node == list->head && node == list->tail)
  {
    list->head = NULL;
    list->tail = NULL;
    RemoveDoublyNodeFromChain(node);
  }
  else if(node == list->tail)
  {
    list->tail = node->prev;
    RemoveDoublyNodeFromChain(node);
  }
  else if(node == list->head)
  {
    list->head = node->next;
    RemoveDoublyNodeFromChain(node);
  }
  else
  {
    RemoveDoublyNodeFromChain(node);
  }
}

//remove data from the list
void RemoveDataFromDoublyLinkedList(DoublyLinkedList* list, Object* data)
{
  DoublyNode* nodeOfData = GetDoublyNodeOfData(list, data);
  RemoveDoublyNodeFromList(list, nodeOfData);
  DeconstructDoublyNode(nodeOfData);
}

//get the doubly node that contains the given data
DoublyNode* GetDoublyNodeOfData(DoublyLinkedList* list, Object* data)
{
  DoublyNode* current = list->head;
  while(current != NULL)
  {
    if(current->data == data)
    {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

#endif // DOUBLY_LINKED_LIST_C