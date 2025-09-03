#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H
#include "player_model.h"

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

void HandleInput(PlayerModel* player)
{
    //select the gamepad mapped to this player controller
    select_gamepad(player->gamepadID);
    float deltaX;
    float deltaY;
    gamepad_direction_normalized(&deltaX, &deltaY); //get the direction from the gamepad
    player->object.xdir = deltaX;
    player->object.ydir = deltaY;
    PlayerMoveInDirection(player);
}

void PlayerUpdate(PlayerModel* player)
{
    if(player->object.isActive)
    {
        //handle input every frame
        HandleInput(player);    

        // Update the player view every frame
        DrawPlayer(player);
    }
}

#endif //PLAYER_CONTROLLER_H