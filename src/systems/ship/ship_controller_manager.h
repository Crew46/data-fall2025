#ifndef SHIP_CONTROLLER_MANAGER_H
#define SHIP_CONTROLLER_MANAGER_H
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "ship_controller.h"

void InitializeShipController(ShipController* player);
ShipController* ConstructShipController();
void DeconstructShipController(ShipController* player);
void UpdateShipController(ShipController* player);


#endif //SHIP_CONTROLLER_MANAGER_H