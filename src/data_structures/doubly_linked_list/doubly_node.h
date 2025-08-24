#ifndef DOUBLY_NODE_H
#define DOUBLY_NODE_H
#include "misc.h"

struct DoublyNode
{
  void* data;
  DoublyNode* next;
  DoublyNode* previous;
};

DoublyNode* CreateDoublyNode(void* data)
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

void DeleteDoublyNode(DoublyNode* node)
{
    node->next->previous = node->previous;
    node->previous->next = node->next;
    DeconstructDoublyNode(node);
}

#endif //DOUBLY_NODE_H