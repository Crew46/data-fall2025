#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H
#include "player.h"
#include "player_view.h"


/** 
 * SUMMARY:
 * This file is the logical glue between the player model and it's visual representation. 
 * This file is a facade for the player model, 
 * controlling the interaction between the player model and it's view.
**/

////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////
///////////////////////////////////////////////////////////

struct PlayerController
{
    Player* player; // Pointer to the player model
    PlayerView* view; // Pointer to the player view
};


///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

//constructor
void CreatePlayerController(int x, int y, float maxShootCooldownTime, int maxLasers)
{
    // Create the player model
    Player* player = CreatePlayer(x, y, maxShootCooldownTime, maxLasers);

    //create the player view
    PlayerView* view = CreatePlayerView();

    //create the player controller
    PlayerController* controller = (PlayerController*)malloc(sizeof(PlayerController));
    controller->player = player;
    controller->view = view;
}

//deconstructor
void DeinitializePlayerController(PlayerController* controller)
{
    // Deinitialize the player model and view
    DeinitializePlayer(controller->player);
    DeinitializePlayerView(controller->view);

    free(controller);
}

///////////////////////////////////////////////////////////
///////////Player_Controller Functions/////////////////////
///////////////////////////////////////////////////////////

void PlayerShoot()
{

}

#endif