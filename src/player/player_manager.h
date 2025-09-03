#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H
#include "player.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

//declarations

//player linked list
DoublyLinkedList* playerList = CreateDoublyLinkedList();

//=========================================================
///////////////////////////////////////////////////////////
///////////INSTANCES MANAGEMENT////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This part keeps tracks of all the instances of player in a linked list
**/

//return linked list of players
DoublyLinkedList* GetPlayerList()
{
    return playerList; 
}

//update all player controller in instances list
void UpdateAllPlayers()
{
    DoublyNode* currentNode = playerList->head;
    Object* currentData = NULL;
    while(currentNode != NULL)
    {
        currentData = currentNode->data;
        if(currentData != NULL)
        {
            PlayerUpdate((Player*)currentData);
        }
        currentNode = currentNode->next;
    }
}

void DeconstructAllPlayers()
{
    //loop through all player controller instances
    //for(int i = 0; i < instancesOfPlayerController; i++)
    //{
        //DeconstructPlayerController();
    //}
}


//=========================================================
///////////////////////////////////////////////////////////
///////////PART 5: CONSTRUCTION////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//constructor
Player* CreatePlayer(int* name, int textureID, int regionID, int id, int x, int y, bool isActive, int speed, float maxShootCooldownTime, int gamepadID)
{
    //allocate memory for player
    Player* player = (Player*)malloc(sizeof(Player));

    //player object properties initialization
    InitializeObject(&player->object, name, textureID, regionID, id, x, y, isActive, speed);    

    //player properties initialization
    player->gamepadID = gamepadID;
    player->maxShootCooldownTime = maxShootCooldownTime;
    player->shootCooldownElapsed = 0; // Start with no cooldown
    player->state = PLAYER_MOVEMENT_STATE_IDLE; // Start in idle state
    player->weaponType = WEAPON_TYPE_LASER_CANNON; // Default weapon type

    DoublyLinkedListInsertAtTail(playerList, &player->object);

    //return pointer to player
    return player;
}

//deconstructor
void DeconstructPlayer(Player* player)
{
    //free player struct
    free(player);
}
#endif //PLAYER_MANAGER_H