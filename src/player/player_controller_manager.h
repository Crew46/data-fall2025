#ifndef PLAYER_CONTROLLER_MANAGER_H
#define PLAYER_CONTROLLER_MANAGER_H
#include "../data_structures/linkedlist.h"

/** 
 * SUMMARY:
 * This file keeps tracks of all the instances of player controller in a linked list
 * also provides functions to do things with those players in the list
**/

//initialize instances list
DoublyNode* playerControllerList = CreateDoublyNode();
int instancesOfPlayerController = 0;

//update all player controller in instances list
void UpdateAllPlayerControllers(float deltaTime)
{
    //loop through all player controller instances
    for(int i = 0; i < instancesOfPlayerController; i++)
    {
        //PlayerControllerUpdate();
    }
}

void DeconstructAllPlayerControllers()
{
    //loop through all player controller instances
    for(int i = 0; i < instancesOfPlayerController; i++)
    {
        //DeconstructPlayerController();
    }
}

#endif //PLAYER_CONTROLLER_MANAGER_H