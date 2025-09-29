#ifndef PLAYER_MANAGER_C
#define PLAYER_MANAGER_C
#include "player_manager.h"
#include "../../architecture/component/component_manager.h"

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

void DeinitializePlayerManager()
{
    //free linked list
    free(playerManager);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER CONSTRUCTION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializePlayer(Player* player)
{
    InitializeComponent((Component*)player, PLAYER_CONTROLLER_COMPONENT);
    player->state = PLAYER_MOVEMENT_STATE_IDLE;
}

Player* ConstructPlayerController()
{
    Player* player = (Player*)malloc(sizeof(Player));
    InitializePlayer(player);
    return player;
}

//player controller deconstructor
void DeconstructPlayerController(Player* player)
{
    DeconstructComponent((Component*)player);
    free(player);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////BEHAVIOURAL FUNCTIONS///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdatePlayerController(Player* player)
{
    print_at(screen_width / 2, screen_height / 2 + 150, "Updating Player");
}

#endif //PLAYER_MANAGER_C