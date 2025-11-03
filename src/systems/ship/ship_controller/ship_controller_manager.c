#ifndef SHIP_CONTROLLER_MANAGER_C
#define SHIP_CONTROLLER_MANAGER_C
#include "ship_controller_manager.h"
#include "../../../architecture/component/component_manager.h"
#include "../../../architecture/game_object/game_object_manager.h"
#include "../../audio/audio_manager.h"
#include "../../input/input_controller_manager.h"
#include "../../weapon/weapon/weapon_controller_manager.h"
#include "../../../tools/debugger.c"
#include "video.h"
#include "../ship_movement_controller/ship_movement_controller_manager.h"

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER CONSTRUCTION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeShipController(ShipController* controller)
{
    CM_InitializeComponent((Component*)controller, SHIP_CONTROLLER_COMPONENT);
    ShipControllerSet_DescriptiveData(controller, SHIP_TYPE_DEFAULT);
    controller->state = PLAYER_MOVEMENT_STATE_IDLE;
}

ShipController* ConstructShipController()
{
    ShipController* controller = (ShipController*)malloc(sizeof(ShipController));
    InitializeShipController(controller);
    return controller;
}

//player controller deconstructor
void DeconstructShipController(ShipController* controller)
{
    CM_DeconstructComponent((Component*)controller);
    free(controller);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////BEHAVIOURAL FUNCTIONS///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdateShipController(ShipController* controller)
{
    ShipControllerUpdateMovement(controller);
}

void ShipControllerUpdateMovement(ShipController* controller)
{
    ShipMovementController* movementController = (ShipMovementController*)GOM_GetComponentFromComponent((Component*)controller, SHIP_MOVEMENT_CONTROLLER_COMPONENT);
    if(movementController != NULL)
    {
        SMCM_ShipMovementController_Update(movementController);
    }
}

void ShipControllerShootWeapon(ShipController* controller)
{
}

//=========================================================
///////////////////////////////////////////////////////////
/////////////GETTERS & SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void ShipControllerSet_DescriptiveData(ShipController* controller, ShipType type)
{
    controller->type = type;
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


#endif //SHIP_CONTROLLER_MANAGER_C