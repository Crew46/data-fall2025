#ifndef SHIP_CONTROLLER_MANAGER_C
#define SHIP_CONTROLLER_MANAGER_C
#include "ship_controller_manager.h"
#include "../../architecture/component/component_manager.h"
#include "../audio/audio_manager.h"
#include "../input/input_controller_manager.h"
#include "../../tools/debugger.c"
#include "video.h"
#include "ship_strategies/ship_strategy_dispatcher.c"

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER CONSTRUCTION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeShipController(ShipController* controller)
{
    CM_InitializeComponent((Component*)controller, SHIP_CONTROLLER_COMPONENT);
    controller->state = PLAYER_MOVEMENT_STATE_IDLE;
    controller->type = SHIP_TYPE_DEFAULT;
    controller->speed = 1;
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
    DispatchShipStrategy(controller);
}

//=========================================================
///////////////////////////////////////////////////////////
/////////////GETTERS & SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

#endif //SHIP_CONTROLLER_MANAGER_C