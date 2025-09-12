#ifndef PLAYER_MODEL_H
#define PLAYER_MODEL_H
//custom libraries
#include "../../architecture/object/object.h"

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
};

#endif // PLAYER_MODEL_H 