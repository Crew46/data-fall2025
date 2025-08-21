#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H
#include "misc.h"

struct Node
{
  void *ptrData;
  Node *ptrNext;
};

Node *GetLastNode(Node *ptrFirstNode)
{
  Node *ptrCurrentNode = ptrFirstNode;
  //loop until node is last node 
  while(ptrCurrentNode->ptrNext != NULL)
  {
    ptrCurrentNode = ptrCurrentNode->ptrNext;
  }
  return ptrCurrentNode;
}

Node *CreateLinkedList()
{
  Node *ptrNode = malloc(sizeof(Node));
  ptrNode->ptrNext = NULL;
  ptrNode->ptrData = NULL;
  return ptrNode;
}
//free all nodes
void FreeLinkedList(Node *ptrFirstNode)
{
  Node *ptrCurrentNode = ptrFirstNode;
  Node *ptrPreviousNode = NULL;
  while(ptrCurrentNode->ptrNext != NULL)
  {
    if(ptrPreviousNode != NULL)
    {
      free(ptrPreviousNode);
    }
    ptrPreviousNode = ptrCurrentNode;
  }
  //free last two nodes, as they are not done in the while loop
  free(ptrPreviousNode);
  free(ptrCurrentNode);
}

void LinkedListAddData(Node *ptrFirstNode, void *ptrData)
{ 
  if(ptrFirstNode->ptrNext == NULL && ptrFirstNode->ptrData == NULL)
  {
    ptrFirstNode->ptrData = ptrData; 
  }
  else 
  {  
    //create new node
    Node *ptrNewNode = malloc(sizeof(Node));
    ptrNewNode->ptrData = ptrData;
    ptrNewNode->ptrNext = NULL;
    Node *ptrLastNode = GetLastNode(ptrFirstNode); 
    ptrLastNode->ptrNext = ptrNewNode;
  } 
}
//linked list doesn't free the data, only the node
void FreeNodeOfData(Node *ptrFirstNode, void *ptrData)
{
  Node *ptrPreviousNode = NULL;
  Node *ptrCurrentNode = ptrFirstNode;
  
  while(ptrCurrentNode->ptrData != ptrData)
  {
    ptrPreviousNode = ptrCurrentNode;
    ptrCurrentNode = ptrCurrentNode->ptrNext;
  }

  if(ptrCurrentNode == ptrFirstNode)
  {
    //need to replace first node with new node
    free(ptrFirstNode);
    ptrFirstNode = malloc(sizeof(Node));
  }
  else
  { 
    //set the previous nodes next to the next of this node
    ptrPreviousNode->ptrNext = ptrCurrentNode->ptrNext;
    ptrCurrentNode->ptrNext = NULL;
    //free memory of node
    free(ptrCurrentNode);
  }
}
void FreeLastNode(Node *ptrFirstNode)
{
  Node *ptrPreviousNode = NULL;
  Node *ptrCurrentNode = ptrFirstNode;
  while(ptrCurrentNode->ptrNext != NULL)
  {
    ptrPreviousNode = ptrCurrentNode;
    ptrCurrentNode = ptrCurrentNode->ptrNext;
  }
  //set new last node to have null
  ptrPreviousNode->ptrNext = NULL;
  //set removed node to be free
  free(ptrCurrentNode);
}

void *GetDataAtIndex(Node *ptrFirstNode, int index)
{
  int currentIndex = 0;
  Node *ptrCurrentNode = ptrFirstNode;
  //continue moving up chain as long as index is less than desired, and the next isn't null
  while(currentIndex < index && ptrCurrentNode->ptrNext != NULL)
  {
    ptrCurrentNode = ptrCurrentNode->ptrNext;
    currentIndex++;
  }
  if(currentIndex == index)
  {
    return ptrCurrentNode->ptrData;
  }
  return NULL;
}

#endif // !LINKED_LIST_FUNCTIONS_H
