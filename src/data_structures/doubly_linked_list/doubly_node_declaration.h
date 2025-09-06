#ifndef DOUBLY_NODE_DECLARATION_H
#define DOUBLY_NODE_DECLARATION_H
#include "misc.h"
#include "../../architecture/object/object_declaration.h"

struct DoublyNode
{
  Object* data;
  DoublyNode* next;
  DoublyNode* previous;
};

DoublyNode* CreateDoublyNode(Object* data);
void DeconstructDoublyNode(DoublyNode* doublyNode);
void InsertDoublyNodeAfterDoublyNode(DoublyNode* nodeToInsertAfter, DoublyNode* newNode);
void InsertDoublyNodeBeforeDoublyNode(DoublyNode* nodeToInsertBefore, DoublyNode* newNode);
void DeleteDoublyNode(DoublyNode* node);

#endif // DOUBLY_NODE_DECLARATION_H