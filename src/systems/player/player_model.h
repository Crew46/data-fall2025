#ifndef PLAYER_MODEL_H
#define PLAYER_MODEL_H
//standard libraries
#include "misc.h"
#include "video.h"
#include "input.h"
#include "math.h"
//custom libraries
#include "../../architecture/object/object.h"
#include "../weapon/weapon.h"

//=========================================================
///////////////////////////////////////////////////////////
/////////// PLAYER MODEL///////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This is the model of the player: ie. the fundamental 
 * behaviors and properties that define the player
**/

enum PlayerMovementState
{
    PLAYER_MOVEMENT_STATE_IDLE,
    PLAYER_MOVEMENT_STATE_MOVING
};

//is an object
struct PlayerModel 
{
    //object is not a pointer, in order to imbed to struct for upcasting & downcasting.
    Object base;
    float maxShootCooldownTime; //shoot cooldown in seconds
    float shootCooldownElapsed; //seconds elapsed since last shot
    PlayerMovementState state; // Current state of the player
    Vector2 inputDirection; //input vector
};

//=========================================================
///////////////////////////////////////////////////////////
/////////// PLAYER MODEL BEHAVIOURS ///////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//move player in a direction, where then direction is scaled by the player's speed
void PlayerModelMoveInDirection(PlayerModel* playerModel)
{
    //Vector2* results = CreateVector2(0, 0);
    //add player position and direction to player position
    //MultiplyVector2ByScalar(&playerModel->inputDirection, playerModel->speed, results); // Scale the movement vector by the player's speed
    //AddVector2Components(results, &playerModel->object.position, &playerModel->object.position);
    //free(results);
}

//shoot selected weapon
void PlayerModelUseWeapon(PlayerModel* playerModel)
{
    //if not in cooldown, shoot
    if(playerModel->shootCooldownElapsed == 0)
    {
        //shoot logic here 

        // Reset cooldown
        playerModel->shootCooldownElapsed = playerModel->maxShootCooldownTime;
    }
}


#endif // PLAYER_MODEL_H 