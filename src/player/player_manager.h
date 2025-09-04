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
            //change to player model
            //PlayerUpdate((PlayerModel*)currentData);
        }
        currentNode = currentNode->next;
    }
}

void DeconstructAllPlayerControllers()
{
    //loop through all player controller instances
    //for(int i = 0; i < instancesOfPlayerController; i++)
    //{
        //DeconstructPlayerController();
    //}
}

//create a player controller, add to linked list, and return pointer to it

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER MODEL CONSTRUCTION///////////////////////
///////////////////////////////////////////////////////////
//=========================================================



#endif //PLAYER_MANAGER_H