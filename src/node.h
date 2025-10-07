#ifndef NODE_H // node.h
#define NODE_H

////////////////////////////////////////////////////////////////////////////////////
//
//  Node struct and helpers
//
struct Node
{
  Object* data;
  Node* next;
  Node* prev;
};

Node* createNode(Object* data)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node->data = data;
  node->next = NULL;
  node->prev = NULL;

  return node;
}

#endif 
