#ifndef DOUBLY_NODE_H
#define DOUBLY_NODE_H
#include "doubly_node_declaration.h"

DoublyNode* CreateDoublyNode(Object* data)
{
  DoublyNode* node = (DoublyNode*)malloc(sizeof(DoublyNode));
  node->next = NULL;
  node->previous = NULL;
  node->data = data;
  return node;
}

void DeconstructDoublyNode(DoublyNode* doublyNode)
{
  free(doublyNode);
}

void InsertDoublyNodeAfterDoublyNode(DoublyNode* nodeToInsertAfter, DoublyNode* newNode)
{
  //if nodeToInsertAfter->next doesn't exist, don't set it's previous
  if(nodeToInsertAfter->next != NULL)
  {
    nodeToInsertAfter->next->previous = newNode;
  }

  newNode->next = nodeToInsertAfter->next; 
  newNode->previous = nodeToInsertAfter;

  nodeToInsertAfter->next = newNode;
}

void InsertDoublyNodeBeforeDoublyNode(DoublyNode* nodeToInsertBefore, DoublyNode* newNode)
{
  if(nodeToInsertBefore->previous != NULL)
  {
    nodeToInsertBefore->previous->next = newNode;
  }

  newNode->previous = nodeToInsertBefore->previous;
  newNode->next = nodeToInsertBefore;

  nodeToInsertBefore->previous = newNode;
}

void DeleteDoublyNode(DoublyNode* node)
{
  if(node->next != NULL)
  {
    node->next->previous = node->previous;
  }
  if(node->previous != NULL)
  {
    node->previous->next = node->next;
  }
  DeconstructDoublyNode(node);
}

#endif //DOUBLY_NODE_H