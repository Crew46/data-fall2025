#ifndef PLAYER_MODEL_H
#define PLAYER_MODEL_H
//custom libraries
#include "../../architecture/component/component.h"

enum PlayerMovementState
{
    PLAYER_MOVEMENT_STATE_IDLE,
    PLAYER_MOVEMENT_STATE_MOVING
};

//is an object
struct Player 
{
    Component base;
    PlayerMovementState state; // Current state of the player
};

#endif // PLAYER_MODEL_H 