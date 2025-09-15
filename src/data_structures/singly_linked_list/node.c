#ifndef NODE_C
#define NODE_C
#include "node.h"

void AppendNodeToNode(Node* nodeToAppendAfter, Node* newNode)
{
    nodeToAppendAfter->next = newNode; 
}

void InsertNodeToNode(Node* nodeToInsertBefore, Node* newNode)
{

}

void RemoveNode(Node* node)
{

}

#endif //NODE_C