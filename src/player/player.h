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

List* playerList = createList();

struct Player 
{
    //object is not a pointer, in order to imbed to struct for upcasting & downcasting.
    Object object;
    int gamepadID; 
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
void movePlayer(Player* player)
{
    moveObject(&player->object);
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
    drawObject(&player->object);
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
    player->object.dx = round(deltaX * (float)player->object.vx);
    player->object.dy = round(deltaY * (float)player->object.vy);

    movePlayer(player);

    if(player->weapon != NULL)
    {
        if(gamepad_button_b() > 10)
        {
            player->weapon = NULL;
        }
        else
        {
            player->weapon->object.x = player->object.x;
            player->weapon->object.y = player->object.y;

            int xOffset = -10;
            int yOffset = -5;

            int team = player->object.status & TeamFlagMask >> TeamFlagMask;

            if(team      == 0)
            {
                player->weapon->object.x += xOffset;
                player->weapon->object.y += yOffset;
            }
            else if(team == 1)
            {
                player->weapon->object.x -= yOffset;
                player->weapon->object.y += xOffset;
            }
            else if(team == 1)
            {
                player->weapon->object.x -= xOffset;
                player->weapon->object.y -= yOffset;
            }
            else if(team == 1)
            {
                player->weapon->object.x += yOffset;
                player->weapon->object.y -= xOffset;
            }

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
    else
    {
        if(gamepad_button_b() > 0)
        {
            Node* currentNode = GetWeaponList()->head;
            Node* nextNode;
            while(currentNode != NULL)
            {
                nextNode = currentNode->next;

                if(collisionCheck(&player->object, currentNode->data))
                {
                    player->weapon = (Weapon*)currentNode->data;
                    int newStatus  = player->weapon->object.status & (~TeamFlagMask);
                    newStatus     |= player->object.status & TeamFlagMask;
                    player->weapon->object.status = newStatus;
                    break;
                }

                currentNode = nextNode;
            }
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

    List* lasers = GetLaserList();
    Node* currentNode = lasers->head;
    Node* nextNode;
    while(currentNode != NULL)
    {
        nextNode = currentNode->next;

        if(((currentNode->data->status ^ player->object.status) & TeamFlagMask) != 0)
        {
            if(collisionCheck(&player->object, currentNode->data))
                player->object.status |= DeletionMarkFlag;
        }

        currentNode = nextNode;
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: CONSTRUCTION////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//constructor
Player* CreatePlayer(int textureID, int regionID, int x, int y, int status, float maxShootCooldownTime, int gamepadID)
{
    //allocate memory for player
    Player* player = (Player*)malloc(sizeof(Player));

    //player object properties initialization
    initObject(&player->object, Object_Type_Entity, textureID, regionID, x, y, status);

    //player properties initialization
    player->gamepadID = gamepadID;
    player->weapon = CreateWeapon(WEAPON_TEXTURES, WEAPON_REGION, player->object.x, player->object.y, status, WEAPON_TYPE_LASER_CANNON, maxShootCooldownTime, 2.0);

    append(playerList, playerList->tail, createNode(&player->object));

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
        player->weapon->object.status |= DeletionMarkFlag;
    }
    DeconstructPlayer(player);
}

void DeconstructAllPlayers()
{
    //loop through all instances of players
    Node* currentNode = playerList->head;
    Node* next;

    while(currentNode != NULL)
    {
        next = currentNode->next;
        DeconstructPlayer((Player*)currentNode->data);
        obtain(playerList, currentNode);
        deleteNode(currentNode);

        currentNode = next;
    }
}

void DeconstructAllPlayersAndWeapons()
{
    //loop through all instances of players
    Node* currentNode = playerList->head;
    Node* next;

    while(currentNode != NULL)
    {
        next = currentNode->next;
        DeconstructPlayerAndWeapon((Player*)currentNode->data);
        obtain(playerList, currentNode);
        deleteNode(currentNode);

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
List* GetPlayerList()
{
    return playerList;
}

//update all player controller in instances list
void UpdateAllPlayers()
{
    Node* currentNode = playerList->head;
    Node* nextNode;

    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        if(currentNode->data != NULL)
        {
            PlayerUpdate((Player*)currentNode->data);
            if(currentNode->data->status & DeletionMarkFlag)
            {
                DeconstructPlayerAndWeapon((Player*)currentNode->data);
                obtain(playerList, currentNode);
                deleteNode(currentNode);
            }
        }
        currentNode = nextNode;
    }
}


#endif // PLAYER_H 