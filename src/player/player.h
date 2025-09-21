#ifndef PLAYER_H
#define PLAYER_H
//standard libraries
#include "misc.h"
#include "video.h"
#include "input.h"
#include "math.h"
//custom libraries
#include "../object.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../weapon/weapon.h"
#include "../tools/debugger.h"

/** 
 * SUMMARY:
 * this entire file is split into different sections for different concerns regarding the player,
 * including part 1: the model, part 2: visual functions, part 3: logical connections between model and view,
 * part 4: instance management, part 5: construction and desconstruction
**/

//declarations

DoublyLinkedList* playerList = CreateDoublyLinkedList();

enum PlayerMovementState
{
    PLAYER_MOVEMENT_STATE_IDLE,
    PLAYER_MOVEMENT_STATE_MOVING
};

struct Player 
{
    //object is not a pointer, in order to imbed to struct for upcasting & downcasting.
    Object object;
    int gamepadID; 
    PlayerMovementState state; // Current state of the player
    Weapon* weapon; //weapon that player has equipped
};

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 1: PLAYER MODEL////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This is the model of the player: ie. the fundamental 
 * behaviors of the player. logical connection between these functions is in part 3
**/

//move player in a direction, where then direction is scaled by the player's speed
void PlayerMoveInDirection(Player* player)
{
    ObjectMoveInDirection(&player->object);
}


//=========================================================
///////////////////////////////////////////////////////////
///////////PART 2: VISUAL FUNCTIONS////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * this part is for visualizing the data of the model
**/

void DrawPlayer(Player* player)
{
    DrawObject(&player->object);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This part is the glue to making the player model, player 
 * view, and input work together. ie the logic that connects 
 * the player's model, view, and input.
**/

void HandleInput(Player* player)
{
    //select the gamepad mapped to this player controller
    select_gamepad(player->gamepadID);
    float deltaX;
    float deltaY;
    gamepad_direction_normalized(&deltaX, &deltaY); //get the direction from the gamepad
    player->object.xdir = deltaX;
    player->object.ydir = deltaY;
    PlayerMoveInDirection(player);

    if(player->weapon != NULL)
    {
        player->weapon->object.x = player->object.x;
        player->weapon->object.y = player->object.y;

        if(gamepad_button_a() > 0)
        {
            player->weapon->isFiring = true;
        }
        else
        {
            player->weapon->isFiring = false;
        }
    }
}

void PlayerUpdate(Player* player)
{
    if(player->object.status & IsActiveFlag)
    {
        //handle input every frame
        HandleInput(player);

        // Update the player view every frame
        DrawPlayer(player);
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: CONSTRUCTION////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//constructor
Player* CreatePlayer(int* name, int textureID, int regionID, int id, int x, int y, bool isActive, int team, int speed, float maxShootCooldownTime, int gamepadID)
{
    //allocate memory for player
    Player* player = (Player*)malloc(sizeof(Player));

    //player object properties initialization
    InitializeObject(&player->object, name, textureID, regionID, id, x, y, isActive, team, speed);

    //player properties initialization
    player->gamepadID = gamepadID;
    player->state = PLAYER_MOVEMENT_STATE_IDLE; // Start in idle state
    player->weapon = CreateWeapon("gun", WEAPON_TEXTURES, WEAPON_REGION, 0, player->object.x, player->object.y, true, team, player->object.speed, WEAPON_TYPE_LASER_CANNON, maxShootCooldownTime, 2.0);// Default weapon type

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

void DeconstructPlayerAndWeapon(Player* player)
{
    if(player->weapon != NULL)
    {
        DoublyNode* weaponNode = DoublyLinkedListFindDataFromHead(GetWeaponList(), &player->weapon->object);
        DeconstructWeapon(player->weapon);
        DoublyLinkedListDeleteNode(GetWeaponList(), weaponNode);
    }
    DeconstructPlayer(player);
}

void DeconstructAllPlayers()
{
    //loop through all instances of players
    DoublyNode* currentNode = playerList->head;
    DoublyNode* next;

    while(currentNode != NULL)
    {
        next = currentNode->next;
        DeconstructPlayer((Player*)currentNode->data);
        DoublyLinkedListDeleteNode(playerList, currentNode);

        currentNode = next;
    }
}

void DeconstructAllPlayersAndWeapons()
{
    //loop through all instances of players
    DoublyNode* currentNode = playerList->head;
    DoublyNode* next;

    while(currentNode != NULL)
    {
        next = currentNode->next;
        DeconstructPlayerAndWeapon((Player*)currentNode->data);
        DoublyLinkedListDeleteNode(playerList, currentNode);

        currentNode = next;
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 5: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/**
 * SUMMARY: //NOT FULLY IMPLEMENTED UNTIL THE COMPLETION OF LINKED LIST
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
    DoublyNode* nextNode;

    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        if(currentNode->data != NULL)
        {
            PlayerUpdate((Player*)currentNode->data);
            if(currentNode->data->status & DeletionMarkFlag)
            {
                DeconstructPlayerAndWeapon((Player*)currentNode->data);
                DoublyLinkedListDeleteNode(playerList, currentNode);
            }
        }
        currentNode = nextNode;
    }
}


#endif // PLAYER_H 