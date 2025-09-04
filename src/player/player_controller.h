#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H
#include "player_model.h"
#include "player_view.h"

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER///////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This part is the glue to making the player model, player 
 * view, and input work together. ie the logic that connects 
 * the player's model, view, and input.
**/

struct PlayerController 
{
    //has a player model, which is also an object
    PlayerModel* playerModel;
    //maps to a gamepad
    int gamepadID; 
};

//=========================================================
///////////////////////////////////////////////////////////
///////////LOGIC///////////////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void ReactToInput(PlayerController* playerController)
{
    //select the gamepad mapped to this player controller
    select_gamepad(playerController->gamepadID);
    float deltaX;
    float deltaY;
    gamepad_direction_normalized(&deltaX, &deltaY); //get the direction from the gamepad
    playerController->playerModel->inputDirection.x = deltaX;
    playerController->playerModel->inputDirection.y = deltaY;
    //delegate movement to player model
    PlayerModelMoveInDirection(playerController->playerModel);
}

void PlayerControllerUpdate(PlayerController* playerController)
{
    //if the player is active, update it
    if(playerController->playerModel->object.isActive)
    {
        //react to input
        ReactToInput(playerController);    

        //delegate drawing of the mode to player view
        DrawPlayerView(playerController->playerModel);
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER MODEL CONSTRUCTION///////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializePlayerController(PlayerController* playerController, PlayerModel* playerModel, int gamepadID)
{
    playerController->playerModel = playerModel;
    playerController->gamepadID = gamepadID;
}

//player controller constructor
PlayerController* CreatePlayerController(int* name, float speed, float maxShootCooldownTime, int gamepadID)
{
    //allocate player controller
    PlayerController* playerController = (PlayerController*)malloc(sizeof(PlayerController));
    //initialize player controller
    InitializePlayerController(playerController, CreatePlayerModel(name, speed, maxShootCooldownTime), gamepadID);
    //return player controller
    return playerController;
}

//player controller deconstructor
void DeconstructPlayerController(PlayerController* playerController)
{
    //deconstruct player model
    DeconstructPlayerModel(playerController->playerModel);
    //free player controller struct
    free(playerController);
}

#endif //PLAYER_CONTROLLER_H