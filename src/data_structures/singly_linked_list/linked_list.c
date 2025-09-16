#ifndef LINKED_LIST_C
#define LINKED_LIST_C
#include "linked_list.h"
#include "node.c"
#include "../../architecture/game_object/game_object_manager.h"

Node* RemoveNodeFromLinkedList(LinkedList* linkedList, Node* node)
{
    Node* currentNode = linkedList->head;
    Node* previousNode = NULL;
    while(currentNode->next != node) 
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    previousNode->next = currentNode->next;
    currentNode->next = NULL;
    return currentNode;
}

#endif //LINKED_LIST_C