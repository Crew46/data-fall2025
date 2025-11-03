#ifndef SHIP_STRATEGY_DISPATCHER_C
#define SHIP_STRATEGY_DISPATCHER_C
#include "../ship_controller_manager.h"
#include "default_enemy_ship_strategy.c"

void DispatchShipStrategy(ShipController* shipController)
{
    switch (shipController->type)
    {
    case SHIP_TYPE_DEFAULT:
        UpdateDefaultShipStrategy(shipController);
        break;
    default:
        break;
    }
}

#endif //SHIP_STRATEGY_DISPATCHER_C
