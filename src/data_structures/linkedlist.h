#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "misc.h"

////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////
///////////////////////////////////////////////////////////

struct DoublyNode
{
  void* data;
  DoublyNode* next;
  DoublyNode* previous;
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

DoublyNode* CreateDoublyNode()
{
  DoublyNode* node = malloc(sizeof(DoublyNode));
  node->next = NULL;
  node->previous = NULL;
  node->data = NULL;
  return node;
}

void DeconstructDoublyLinkedList(DoublyNode* firstNode)
{
}

////////////////////////////////////////////////////////////
///////////Linked List Functions////////////////////////////
////////////////////////////////////////////////////////////

void InsertDoublyNodeAfterDoublyNode(DoublyNode* nodeToInsertAfter, DoublyNode* newNode)
{
  nodeToInsertAfter->next->previous = newNode;

  newNode->next = nodeToInsertAfter->next; 
  newNode->previous = nodeToInsertAfter;

  nodeToInsertAfter->next = newNode;
}

DoublyNode* FindDoublyNodeOfData(DoublyNode* head, void* data)
{
  DoublyNode* selectedNode = head;
  while(selectedNode != NULL)
  {
    //if desired data matches data of a node
    if(selectedNode->data == data)
    {
      return selectedNode;
    }

    selectedNode = selectedNode->next;
  }
  
  return NULL;
}

void AddDataToDoublyLinkedList(void* data)
{

}

void SetDataAtIndex(int index, void* data)
{

}

void* GetDataAtIndex(int index)
{
  //check in forward direction
  if(index >= 0)
  {

  }
  //check in backwards direction
  if(index < 0)
  {

  }
}



#endif // LINKED_LIST_H
