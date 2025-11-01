#ifndef SHIP_CONTROLLER_H
#define SHIP_CONTROLLER_H
#include "../../architecture/component/component.h"
#include "../weapon/weapon/weapon_controller.h"

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

#endif //SHIP_CONTROLLER