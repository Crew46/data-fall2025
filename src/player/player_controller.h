#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H
#include "player_model.h"
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
};


///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

//constructor
void CreatePlayerController(int x, int y, float maxShootCooldownTime, int maxLasers)
{
    // Create the player model
    Player* player = (Player*)malloc(sizeof(Player));
    CreatePlayer(x, y, maxShootCooldownTime, maxLasers);
}

//deconstructor
void DeinitializePlayerController(PlayerController* controller)
{
    // Deinitialize the player model
    DeinitializePlayer(controller->player);
    free(controller);
}

///////////////////////////////////////////////////////////
///////////Player_Controller Functions/////////////////////
///////////////////////////////////////////////////////////

void PlayerShoot()
{

}

#endif