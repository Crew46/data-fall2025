#ifndef DOUBLY_NODE_H
#define DOUBLY_NODE_H
#include "../../architecture/object/object.h"

struct DoublyNode
{
  Object* data;
  DoublyNode* next;
  DoublyNode* prev;
};

DoublyNode* ConstructDoublyNode(Object* data);

void DeconstructDoublyNode(DoublyNode* doublyNode);

void AppendDoublyNodeToDoublyNode(DoublyNode* nodeToAppendTo, DoublyNode* nodeToAppend);

void InsertDoublyNodeToDoublyNode(DoublyNode* nodeToInsertTo, DoublyNode* nodeToInsert);

void DetatchDoublyNodeFromChain(DoublyNode* doublyNode);

#endif // DOUBLY_NODE_H