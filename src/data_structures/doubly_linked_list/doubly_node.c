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

void AppendDoublyNodeToDoublyNode(DoublyNode* nodeToAppendTo, DoublyNode* nodeToAppend)
{

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

#endif //DOUBLY_NODE_C