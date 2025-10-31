#ifndef SHIP_CONTROLLER_MANAGER_H
#define SHIP_CONTROLLER_MANAGER_H
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "ship_controller.h"

void InitializeShipController(ShipController* player);
ShipController* ConstructShipController();
void DeconstructShipController(ShipController* player);
void UpdateShipController(ShipController* player);

//=========================================================
///////////////////////////////////////////////////////////
/////////////GETTERS & SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void ShipControllerSet_Speed(ShipController* controller, int speed);
int ShipControllerGet_Speed(ShipController* controller);

ShipType ShipControllerSet_Type(ShipController* controller, ShipType type);
ShipType ShipControllerGet_Type(ShipController* controller);

void ShipControllerSet_State(ShipController* controller, ShipMovementState state);
ShipMovementState ShipControllerGet_State(ShipController* controller);

#endif //SHIP_CONTROLLER_MANAGER_H