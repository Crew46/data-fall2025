#ifndef DOUBLY_NODE_C
#define DOUBLY_NODE_C
#include "doubly_node.h"
#include "../../architecture/object/object_manager.h"

DoublyNode* ConstructDoublyNode()
{
  DoublyNode* node = (DoublyNode*)malloc(sizeof(DoublyNode));
  node->base = ObjectManagerConstructObject(); 
  node->next = NULL;
  node->previous = NULL;
  node->data = data;
  return node;
}

void DeconstructDoublyNode(DoublyNode* doublyNode)
{
  ObjectManagerDeconstructObject(doublyNode->base);
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

#endif //DOUBLY_NODE_C