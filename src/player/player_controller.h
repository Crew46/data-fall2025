#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H
#include "player.h"
#include "player_view.h"
#include "../vector/vector2.h"

/** 
 * SUMMARY:
 * This file is a facade for the player model, and the player view. 
 * it's responsibility is controlling the interaction between the player model and it's view.
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
PlayerController* CreatePlayerController(int x, int y, float maxShootCooldownTime, int maxLasers, Sprite** sprites)
{
    // Create the player model
    Player* player = CreatePlayer(x, y, maxShootCooldownTime, maxLasers);

    //create the player view
    PlayerView* view = CreatePlayerView(sprites);

    //create the player controller, and set its model and view
    PlayerController* controller = (PlayerController*)malloc(sizeof(PlayerController));
    controller->player = player;
    controller->view = view;

    return controller;
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

void PlayerControllerShoot(PlayerController* playerController)
{
    PlayerShoot(playerController->player);
}

void PlayerControllerMove(PlayerController* playerController, Vector2* direction)
{
    PlayerMove(playerController->player, direction);
}

void PlayerControllerUpdate(PlayerController* playerController, float deltaTime)
{
    // Update the player's shoot cooldown
    UpdateShootCooldown(playerController->player, deltaTime);

    // Update the player view
    DrawPlayer(playerController->view, playerController->player);
}
#endif