#ifndef PLAYER_MANAGER_C
#define PLAYER_MANAGER_C
#include "player_controller.h"
#include "player_model.h"
#include "player_view.h"
#include "../../architecture/component/component_manager.h"
#include "../../architecture/object/object_manager.h"
#include "../../architecture/game_object/game_object_manager.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"


//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER MANAGER INITIALIZATION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializePlayerManager()
{
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER CONSTRUCTION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializePlayerController(PlayerController* playerController, int* name, PlayerModel* playerModel, int gamepadID)
{
}

PlayerController* ConstructPlayerController(float speed, float maxShootCooldownTime, int gamepadID)
{
}

//player controller deconstructor
void DeconstructPlayerController(PlayerController* playerController)
{
}

#endif //PLAYER_MANAGER_C