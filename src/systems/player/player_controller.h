#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H
#include "player_model.h"
#include "player_view.h"
#include "../../architecture/component/component.h"

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

//is a component
struct PlayerController 
{
    Component component;
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

#endif //PLAYER_CONTROLLER_H