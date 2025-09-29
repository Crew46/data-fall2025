#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H
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

#endif // PLAYER_CONTROLLER_H 