#ifndef PLAYER_H
#define PLAYER_H
//standard libraries
#include "misc.h"
#include "video.h"
#include "input.h"
#include "math.h"
//custom libraries
#include "../object.h"
#include "../weapon/weapon.h"
#include "../tools/debugger.h"

/** 
 * SUMMARY:
 * this entire file is split into different sections for different concerns regarding the player,
 * including part 1: the model, part 2: visual functions, part 3: logical connections between model and view,
 * part 4: instance management, part 5: construction and desconstruction
**/

enum PlayerMovementState
{
    PLAYER_MOVEMENT_STATE_IDLE,
    PLAYER_MOVEMENT_STATE_MOVING
};

struct Player 
{
    //object is not a pointer, in order to imbed to struct for upcasting & downcasting.
    Object object;
    int gamepadID; 
    float maxShootCooldownTime; //shoot cooldown in seconds
    float shootCooldownElapsed; //seconds elapsed since last shot
    PlayerMovementState state; // Current state of the player
    WeaponType weaponType; //weapon that player has equipped
};

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 1: PLAYER MODEL////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This is the model of the player: ie. the fundamental 
 * behaviors of the player. logical connection between these functions is in part 3
**/

//move player in a direction, where then direction is scaled by the player's speed
void PlayerMoveInDirection(Player* player)
{
    float resultX;
    float resultY;
    //add player position and direction to player position
    MultiplyVector2ByScalar(player->object.xdir, player->object.ydir, player->object.speed, &resultX, &resultY); // Scale the movement vector by the player's speed
    float resultsX2;
    float resultsY2;
    AddVector2Components(resultX, player->object.x, resultY, player->object.y, &resultsX2, &resultsY2);
    player->object.x = round(resultsX2);
    player->object.y = round(resultsY2);
}

//shoot selected weapon
void PlayerShoot(Player* player)
{
    //if not in cooldown, shoot
    if(player->shootCooldownElapsed == 0)
    {
        //shoot logic here 

        // Reset cooldown
        player->shootCooldownElapsed = player->maxShootCooldownTime;
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 2: VISUAL FUNCTIONS////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * this part is for visualizing the data of the model
**/

void DrawPlayer(Player* player)
{
    select_texture(player->object.textureID);
    select_region(player->object.regionID);
    draw_region_at(player->object.x, player->object.y);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This part is the glue to making the player model, player 
 * view, and input work together. ie the logic that connects 
 * the player's model, view, and input.
**/

void HandleInput(Player* player)
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

void PlayerUpdate(Player* player)
{
    if(player->object.isActive)
    {
        //handle input every frame
        HandleInput(player);    

        // Update the player view every frame
        DrawPlayer(player);
    }
}

#endif // PLAYER_H 