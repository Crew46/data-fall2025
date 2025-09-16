#ifndef NODE_C
#define NODE_C
#include "node.h"
#include "../../architecture/game_object/game_object_manager.h"

void AppendNodeToNode(Node* nodeToAppendAfter, Node* newNode)
{
    newNode->next = nodeToAppendAfter->next;
    nodeToAppendAfter->next = newNode; 
}

#endif //NODE_C