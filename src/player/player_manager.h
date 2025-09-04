#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H
#include "player_controller.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

//player linked list
DoublyLinkedList* playerList = CreateDoublyLinkedList();

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This part keeps tracks of all the instances of player controller in a linked list, and provides functions to manage,
 * create, destroy, and update all player controllers.
**/

//return linked list of player controllers
DoublyLinkedList* GetPlayerList()
{
    return playerList; 
}

//update all player controller in instances list
void UpdateAllPlayerControllers()
{
    DoublyNode* currentNode = playerList->head;
    Object* currentData = NULL;
    while(currentNode != NULL)
    {
        currentData = currentNode->data;
        if(currentData != NULL)
        {
            PlayerControllerUpdate((PlayerController*)currentData);
        }
        currentNode = currentNode->next;
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER MODEL CONSTRUCTION///////////////////////
///////////////////////////////////////////////////////////
//=========================================================



#endif //PLAYER_MANAGER_H