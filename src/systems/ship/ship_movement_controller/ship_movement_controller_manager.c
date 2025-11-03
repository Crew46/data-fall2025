#ifndef SHIP_MOVEMENT_CONTROLLER_MANAGER_C
#define SHIP_MOVEMENT_CONTROLLER_MANAGER_C
#include "ship_movement_controller_manager.h"
#include "../../../architecture/component/component_manager.h"

void SMCM_ShipMovementController_Initialize(ShipMovementController* controller)
{
    CM_InitializeComponent((Component*)controller, SHIP_MOVEMENT_CONTROLLER_COMPONENT);
    controller->type = SHIP_MOVEMENT_CONTROLLER_TYPE_DEFAULT;
}

ShipMovementController* SMCM_ShipMovementController_Construct()
{
    ShipMovementController* controller = (ShipMovementController*)malloc(sizeof(ShipMovementController)); 
    SMCM_ShipMovementController_Initialize(controller);
    return controller;
}

void SMCM_ShipMovementController_Deconstruct(ShipMovementController* controller)
{
    CM_DeconstructComponent(&controller->component);
    free(controller);
}

void SMCM_ShipMovementController_Update(ShipMovementController* controller)
{

}

#endif //SHIP_MOVEMENT_CONTROLLER_MANAGER_C