#ifndef PLAYER_H
#define PLAYER_H
#include "misc.h"
#include "video.h"
#include "input.h"
#include "../vector/vector2.h"
#include "../object.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../weapon/weapon.h"

/** 
 * SUMMARY:
 * this entire file is split into different sections for different concerns regarding the player,
 * including part 1: the model, part 2: visual functions, part 3: logical connections between the two,
 * and part 4: management of multiple instances
**/

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 1: PLAYER MODEL////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This is the model of the player: ie. the fundamental properties and behaviors of the player that server to 
 * represent the player's data and functions.
**/

///////////////////////////////////////////////
///////////1: Player Struct////////////////////
///////////////////////////////////////////////

enum PlayerMovementState
{
    PLAYER_MOVEMENT_STATE_IDLE,
    PLAYER_MOVEMENT_STATE_MOVING
};


struct Player 
{
    Object* object;
    int gamepadID;
    float maxShootCooldownTime; //shoot cooldown in seconds
    float shootCooldownElapsed; //seconds elapsed since last shot
    PlayerMovementState state; // Current state of the player
    WeaponType weaponType;
};

////////////////////////////////////////////////
///////////1: Constructor and Deconstructor/////
////////////////////////////////////////////////

//constructor
Player* CreatePlayer(Object* object, float maxShootCooldownTime, int gamepadID)
{
    //allocate memory for player
    Player* player = (Player*)malloc(sizeof(Player));
    //player properties initialization
    player->object = object;
    player->gamepadID = gamepadID;
    player->maxShootCooldownTime = maxShootCooldownTime;
    player->shootCooldownElapsed = 0; // Start with no cooldown
    player->state = PLAYER_MOVEMENT_STATE_IDLE; // Start in idle state
    player->weaponType = WEAPON_TYPE_LASER_CANNON; // Default weapon type
    //return pointer to player
    return player;
}

//deconstructor
void DeconstructPlayer(Player* player)
{
    //free player struct
    free(player);
}

///////////////////////////////////////////////
///////////1: Player Behavioural Functions/////
///////////////////////////////////////////////

//move player in a direction, where then direction is scaled by the player's speed
void PlayerMoveInDirection(Player* player, Vector2* direction)
{
    //add player position and direction to player position
    Vector2* movementVector = CreateVector2(direction->x, direction->y); // Create a new vector for movement
    MultiplyVector2ByScalar(movementVector, player->object->speed); // Scale the movement vector by the player's speed
    AddVector2Components(player->object->position, movementVector, player->object->position);
    DeconstructVector2(movementVector); // Free the movement vector after use
}

//shoot selected weapon
void PlayerShoot(Player* player)
{
    //if not in cooldown, shoot
    if(player->shootCooldownElapsed == 0)
    {
        //shoot logic here
        

        // Reset cooldown
        player->shootCooldownElapsed = player->maxShootCooldownTime;
    }
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
    select_texture(player->object->textureID);
    select_region(player->object->regionID);
    draw_region_at(player->object->position->x, player->object->position->y);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This part is the glue to making the player model, player view, and input work together. 
 * ie the logic that connects the player's model, view, and input.
**/

void HandleInput(Player* player)
{
    //select the gamepad mapped to this player controller
    //select_gamepad(player->gamepadID);
    Vector2* movement = CreateVector2(0, 0); 
    gamepad_direction_normalized(&movement->x, &movement->y); //get the direction from the gamepad
    PlayerMoveInDirection(player, movement);
    DeconstructVector2(movement);
}

void PlayerUpdate(Player* player)
{
    //handle input every frame
    HandleInput(player);    

    // Update the player view every frame
    DrawPlayer(player);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This file keeps tracks of all the instances of player controller in a linked list
 * also provides functions to do things with those players in the list
**/

//create linked list
DoublyLinkedList* playerControllerList = CreateDoublyLinkedList();

//update all player controller in instances list
void UpdateAllPlayers()
{
    //loop through all player controller instances
    //for(int i = 0; i < instancesOfPlayerController; i++)
    //{
        //PlayerControllerUpdate();
    //}
}

void DeconstructAllPlayers()
{
    //loop through all player controller instances
    //for(int i = 0; i < instancesOfPlayerController; i++)
    //{
        //DeconstructPlayerController();
    //}
}

#endif // PLAYER_H 