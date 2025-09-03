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
#include "../tools/debugger.h"

//=========================================================
///////////////////////////////////////////////////////////
/////////// PLAYER MODEL///////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

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

struct PlayerModel 
{
    //object is not a pointer, in order to imbed to struct for upcasting & downcasting.
    Object object;
    int gamepadID; 
    float maxShootCooldownTime; //shoot cooldown in seconds
    float shootCooldownElapsed; //seconds elapsed since last shot
    PlayerMovementState state; // Current state of the player
    WeaponType weaponType; //weapon that player has equipped
};


/** 
 * SUMMARY:
 * This is the model of the player: ie. the fundamental 
 * behaviors of the player. logical connection between these functions is in part 3
**/

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
void PlayerShoot(PlayerModel* player)
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