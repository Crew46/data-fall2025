#ifndef SHIP_CONTROLLER_H
#define SHIP_CONTROLLER_H
#include "../../architecture/component/component.h"

enum ShipMovementState
{
    PLAYER_MOVEMENT_STATE_IDLE,
    PLAYER_MOVEMENT_STATE_MOVING
};

//is an object
struct ShipController 
{
    Component base;
    ShipMovementState state; // Current state of the player
};

#endif // SHIP_CONTROLLER_H