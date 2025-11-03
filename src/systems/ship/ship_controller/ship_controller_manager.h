#ifndef SHIP_CONTROLLER_MANAGER_H
#define SHIP_CONTROLLER_MANAGER_H
#include "../../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "ship_controller.h"

void InitializeShipController(ShipController* player);
ShipController* ConstructShipController();
void DeconstructShipController(ShipController* player);
void UpdateShipController(ShipController* player);
void ShipControllerShootWeapon(ShipController* controller);

void ShipControllerUpdateMovement(ShipController* controller);

//=========================================================
///////////////////////////////////////////////////////////
/////////////GETTERS & SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

ShipType ShipControllerSet_Type(ShipController* controller, ShipType type);
ShipType ShipControllerGet_Type(ShipController* controller);

ShipMovementState ShipControllerGet_State(ShipController* controller);

void ShipControllerSet_DescriptiveData(ShipController* controller, ShipType type);


#endif //SHIP_CONTROLLER_MANAGER_H