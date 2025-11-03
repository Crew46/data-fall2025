#ifndef SHIP_MOVEMENT_CONTROLLER_H
#define SHIP_MOVEMENT_CONTROLLER_H
#include "../../../architecture/component/component.h"

enum ShipMovementControllerType
{
    SHIP_MOVEMENT_CONTROLLER_TYPE_DEFAULT,
    SHIP_MOVEMENT_CONTROLLER_TYPE_TANK,
    SHIP_MOVEMENT_CONTROLLER_TYPE_SCOUT
};

struct ShipMovementController
{
    Component component;
    ShipMovementControllerType type;
    int speed;
};

#endif //SHIP_MOVEMENT_CONTROLLER_H