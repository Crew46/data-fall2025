#ifndef DOUBLY_NODE_H
#define DOUBLY_NODE_H
#include "../../architecture/object/object.h"

struct DoublyNode
{
  Object* base;
  DoublyNode* next;
  DoublyNode* previous;
};

DoublyNode* ConstructDoublyNode();
void DeconstructDoublyNode(DoublyNode* doublyNode);
void InsertDoublyNodeAfterDoublyNode(DoublyNode* nodeToInsertAfter, DoublyNode* newNode);
void InsertDoublyNodeBeforeDoublyNode(DoublyNode* nodeToInsertBefore, DoublyNode* newNode);

#endif // DOUBLY_NODE_H