#ifndef PLAYER_MANAGER_C
#define PLAYER_MANAGER_C
#include "misc.h"
#include "player_manager.h"
#include "player_controller.h"
#include "player_model.h"
#include "player_view.h"
#include "../../architecture/component/component_manager.h"
#include "../../architecture/object/object_manager.h"
#include "../../architecture/game_object/game_object_manager.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

PlayerManager* playerManager;

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER MANAGER INITIALIZATION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializePlayerManager()
{
    playerManager = (PlayerManager*)malloc(sizeof(PlayerManager));
}

void DeinitializePlayerManager(PlayerManager* playerManager)
{
    //free linked list
    free(playerManager);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER CONSTRUCTION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializePlayer(Player* player, float speed)
{
    InitializeObject((Object*)player);
    player->speed = speed;
    player->state = PLAYER_MOVEMENT_STATE_IDLE;
}

Player* ConstructPlayerController(float speed)
{
    Player* player = (Player*)malloc(sizeof(Player));
    InitializePlayer(player);
    return player;
}

//player controller deconstructor
void DeconstructPlayerController(Player* player)
{
}

#endif //PLAYER_MANAGER_C