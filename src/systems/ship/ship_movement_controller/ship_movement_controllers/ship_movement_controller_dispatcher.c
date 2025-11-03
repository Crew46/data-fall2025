#ifndef SHIP_MOVEMENT_CONTROLLER_DISPATCHER_C
#define SHIP_MOVEMENT_CONTROLLER_DISPATCHER_C
#include "../ship_movement_controller.h"
#include "default_ship_movement_controller.c"
#include "scout_ship_movement_controller.c"
#include "tank_ship_movement_controller.c"

void DispatchUpdateShipMovementController(ShipMovementController* controller)
{
    switch (controller->type)
    {
    case SHIP_MOVEMENT_CONTROLLER_TYPE_DEFAULT:
        DefaultShipMovementControllerUpdate((DefaultShipMovementController*)controller);
        break;
    case SHIP_MOVEMENT_CONTROLLER_TYPE_TANK:
        TankShipMovementControllerUpdate((TankShipMovementController*)controller);
        break;
    case SHIP_MOVEMENT_CONTROLLER_TYPE_SCOUT:
        ScoutShipMovementControllerUpdate((ScoutShipMovementController*)controller);
        break;
    default:
        break;
    }
}

#endif //SHIP_MOVEMENT_CONTROLLER_DISPATCHER_C