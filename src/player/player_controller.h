#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H
#include "input.h"
#include "misc.h"
#include "player.h"
#include "../object.h"
#include "player_view.h"
#include "../vector/vector2.h"

/** 
 * SUMMARY:
 * This file is the glue to making the player model, player view, and input work together. 
 * ie the logic that connects the player's functions, view, and input.
**/

////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////
///////////////////////////////////////////////////////////

struct PlayerController
{
    Player* player; // Pointer to the player model
    PlayerView* view; // Pointer to the player view
    int gamepadID; // ID of the gamepad associated with this player controller
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

//constructor
PlayerController* CreatePlayerController(Object* object, float maxShootCooldownTime, float speed, int gamepadID, Sprite** sprites, int numSprites)
{
    // Create the player model
    Player* player = CreatePlayer(object, maxShootCooldownTime, speed);

    //create the player view
    PlayerView* view = CreatePlayerView(sprites, numSprites);

    //create the player controller, and set its model and view
    PlayerController* controller = (PlayerController*)malloc(sizeof(PlayerController));
    controller->player = player;
    controller->view = view;
    controller->gamepadID = gamepadID;

    return controller;
}

//deconstructor
void DeconstructPlayerController(PlayerController* controller)
{
    // Deinitialize the player model and view
    DeconstructPlayer(controller->player);
    DeconstructPlayerView(controller->view);

    free(controller);
}

///////////////////////////////////////////////////////////
///////////Player_Controller Behavioural Functions/////////
///////////////////////////////////////////////////////////

void PlayerControllerShoot(PlayerController* playerController)
{
    PlayerShoot(playerController->player);
}

void PlayerControllerMove(PlayerController* playerController, Vector2* movementVector)
{
    PlayerMoveInDirection(playerController->player, movementVector);
}

void HandleInput(PlayerController* playerController)
{
    //select the gamepad mapped to this player controller
    select_gamepad(playerController->gamepadID);
    Vector2* movement = CreateVector2(0, 0); 
    gamepad_direction_normalized(&movement->x, &movement->y); //get the direction from the gamepad
    PlayerControllerMove(playerController, movement);


    DeconstructVector2(movement);
}

void PlayerControllerUpdate(PlayerController* playerController)
{
    HandleInput(playerController);    

    // Update the player view
    DrawPlayer(playerController->view, playerController->player);
}

#endif // PLAYER_CONTROLLER_H
