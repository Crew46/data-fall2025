#ifndef PLAYER_MODEL_H
#define PLAYER_MODEL_H
//standard libraries
#include "misc.h"
#include "video.h"
#include "input.h"
#include "math.h"
//custom libraries
#include "../object.h"
#include "../weapon/weapon.h"

//=========================================================
///////////////////////////////////////////////////////////
/////////// PLAYER MODEL///////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This is the model of the player: ie. the fundamental 
 * behaviors and properties that define the player
**/

enum PlayerMovementState
{
    PLAYER_MOVEMENT_STATE_IDLE,
    PLAYER_MOVEMENT_STATE_MOVING
};

struct PlayerModel 
{
    //object is not a pointer, in order to imbed to struct for upcasting & downcasting.
    Object object;
    float maxShootCooldownTime; //shoot cooldown in seconds
    float shootCooldownElapsed; //seconds elapsed since last shot
    PlayerMovementState state; // Current state of the player
};

//move player in a direction, where then direction is scaled by the player's speed
void PlayerMoveInDirection(PlayerModel* player)
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
void UseWeapon(PlayerModel* player)
{
    //if not in cooldown, shoot
    if(player->shootCooldownElapsed == 0)
    {
        //shoot logic here 

        // Reset cooldown
        player->shootCooldownElapsed = player->maxShootCooldownTime;
    }
}

#endif // PLAYER_MODEL_H 