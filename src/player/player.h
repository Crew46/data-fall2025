#ifndef PLAYER_H
#define PLAYER_H
#include "misc.h"
#include "../vector/vector2.h"
#include "../laser/laser_controller.h"
#include "../object.h"

/** 
 * SUMMARY:
 * This file defines the Player struct and its associated functions.
 * This is the model of the player: ie. the fundamental properties and behaviors of the player.
**/

////////////////////////////////////////////////////////////
///////////Player Struct////////////////////////////////////
///////////////////////////////////////////////////////////

enum PlayerMovementState
{
    PLAYER_MOVEMENT_STATE_IDLE,
    PLAYER_MOVEMENT_STATE_MOVING
};

enum PlayerWeaponType
{
    PLAYER_WEAPON_TYPE_LASER
};

struct Player 
{
    Object* object;
    float maxShootCooldownTime; //shoot cooldown in seconds
    float shootCooldownElapsed; //seconds elapsed since last shot
    float speed; // Speed of the player
    PlayerMovementState state; // Current state of the player
    PlayerWeaponType weaponType; // Current weapon type of the player
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

//constructor
Player* CreatePlayer(Object* object, float maxShootCooldownTime, float speed)
{
    //allocate memory for player
    Player* player = (Player*)malloc(sizeof(Player));
    //player properties initialization
    player->object = object;
    player->maxShootCooldownTime = maxShootCooldownTime;
    player->speed = speed;

    player->shootCooldownElapsed = 0; // Start with no cooldown
    player->state = PLAYER_MOVEMENT_STATE_IDLE; // Start in idle state
    player->weaponType = PLAYER_WEAPON_TYPE_LASER; // Default weapon type
    //return pointer to player
    return player;
}

//deconstructor
void DeconstructPlayer(Player* player)
{
    //deinitialize & free player position vector
    DeconstructVector2(player->object->position);
    //free player struct
    free(player);
}

///////////////////////////////////////////////////////////
///////////Player Behavioural Functions////////////////////
///////////////////////////////////////////////////////////

//move player in a direction, where then direction is scaled by the player's speed
void PlayerMoveInDirection(Player* player, Vector2* direction)
{
    //add player position and direction to player position
    Vector2* movementVector = CreateVector2(direction->x, direction->y); // Create a new vector for movement
    MultiplyVector2ByScalar(movementVector, player->speed); // Scale the movement vector by the player's speed
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

#endif // PLAYER_H 