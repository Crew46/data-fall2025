#ifndef SHIP_CONTROLLER_H
#define SHIP_CONTROLLER_H
#include "../../architecture/component/component.h"

enum ShipMovementState
{
    PLAYER_MOVEMENT_STATE_IDLE,
    PLAYER_MOVEMENT_STATE_MOVING
};

enum ShipType
{
    SHIP_TYPE_DEFAULT,
    SHIP_TYPE_TANK
};

//is an object
struct ShipController 
{
    Component base;
    ShipMovementState state; // Current state of the player
    ShipType type;
    int speed;
};

void ShipControllerSet_Speed(ShipController* controller, int speed)
{
    controller->speed = speed;
}
int ShipControllerGet_Speed(ShipController* controller)
{
    return controller->speed;
}

ShipType ShipControllerSet_Type(ShipController* controller, ShipType type)
{
    controller->type = type; 
}
ShipType ShipControllerGet_Type(ShipController* controller)
{
    return controller->type;
}

void ShipControllerSet_State(ShipController* controller, ShipMovementState state)
{
    controller->state = state;
}
ShipMovementState ShipControllerGet_State(ShipController* controller)
{
    return controller->state;
}

#endif //SHIP_CONTROLLER