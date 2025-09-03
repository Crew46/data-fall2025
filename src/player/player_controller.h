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
    PlayerModel* playerModel;
    int gamepadID; 
};

void ReactToInput(PlayerController* playerController)
{
    //select the gamepad mapped to this player controller
    select_gamepad(playerController->gamepadID);
    float deltaX;
    float deltaY;
    gamepad_direction_normalized(&deltaX, &deltaY); //get the direction from the gamepad
    player->object.xdir = deltaX;
    player->object.ydir = deltaY;
    //delegate movement to player model
    PlayerMoveInDirection(playerController);
}

void PlayerControllerUpdate(PlayerController* playerController)
{
    //if the player is active, update it
    if(playerController->playerModel->object.isActive)
    {
        //react to input
        ReactToInput(playerController);    

        //delegate drawing of the mode to player view
        DrawPlayer(playerController->playerModel);
    }
}

#endif //PLAYER_CONTROLLER_H