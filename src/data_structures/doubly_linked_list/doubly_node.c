#ifndef DOUBLY_NODE_C
#define DOUBLY_NODE_C
#include "doubly_node.h"

DoublyNode* ConstructDoublyNode(Object* data)
{
  DoublyNode* node = (DoublyNode*)malloc(sizeof(DoublyNode));
  node->next = NULL;
  node->prev = NULL;
  node->data = data;
  return node;
}

void DeconstructDoublyNode(DoublyNode* doublyNode)
{
  free(doublyNode);
}

void AppendDoublyNodeToDoublyNode(DoublyNode* place, DoublyNode* newNode)
{
  DoublyNode* tmp = place->next;

  if(tmp != NULL)
  {
    tmp->prev = newNode;
  }

  newNode->prev = place;
  place->next = newNode;
  newNode->next = tmp;
}

void InsertDoublyNodeToDoublyNode(DoublyNode* place, DoublyNode* newNode)
{
  DoublyNode* tmp = place->prev;

  if(tmp != NULL)
  {
    tmp->next = newNode;
  }

  newNode->next = place;
  place->prev = newNode;
  newNode->prev = tmp;
}

void DetatchDoublyNodeFromChain(DoublyNode* node)
{
  if(node->prev != NULL)
  {
    node->prev->next = node->next;
  }

  if(node->next != NULL)
  {
    node->next->prev = node->prev;
  }

  node->prev = NULL;
  node->next = NULL;
}

#endif //DOUBLY_NODE_C