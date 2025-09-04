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

//=========================================================
///////////////////////////////////////////////////////////
/////////// PLAYER MODEL BEHAVIOURS ///////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//move player in a direction, where then direction is scaled by the player's speed
void PlayerModelMoveInDirection(PlayerModel* playerModel)
{
    float resultX;
    float resultY;
    //add player position and direction to player position
    MultiplyVector2ByScalar(playerModel->object.xdir, playerModel->object.ydir, playerModel->object.speed, &resultX, &resultY); // Scale the movement vector by the player's speed
    float resultsX2;
    float resultsY2;
    AddVector2Components(resultX, playerModel->object.x, resultY, playerModel->object.y, &resultsX2, &resultsY2);
    playerModel->object.x = round(resultsX2);
    playerModel->object.y = round(resultsY2);
}

//shoot selected weapon
void PlayerModelUseWeapon(PlayerModel* playerModel)
{
    //if not in cooldown, shoot
    if(playerModel->shootCooldownElapsed == 0)
    {
        //shoot logic here 

        // Reset cooldown
        playerModel->shootCooldownElapsed = playerModel->maxShootCooldownTime;
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER MODEL CONSTRUCTION///////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//initialize player model
void InitializePlayerModel(PlayerModel* playerModel, int* name, int textureID, int regionID, int id, int x, int y, bool isActive, int speed, float maxShootCooldownTime)
{
    //player object properties initialization
    InitializeObject(&playerModel->object, name, textureID, regionID, id, x, y, isActive, speed);    

    //initialize passed in properties
    playerModel->maxShootCooldownTime = maxShootCooldownTime;
    playerModel->shootCooldownElapsed = 0; // Start with no cooldown

    //intialize garbage values
    playerModel->state = PLAYER_MOVEMENT_STATE_IDLE; // Start in idle state
}

//construct player model
PlayerModel* CreatePlayerModel(int* name, int textureID, int regionID, int id, int x, int y, bool isActive, int speed, float maxShootCooldownTime)
{
    //allocate memory for player model
    PlayerModel* playerModel = (PlayerModel*)malloc(sizeof(PlayerModel));
    //initialize player model
    InitializePlayerModel(playerModel, name, textureID, regionID, id, x, y, isActive, speed, maxShootCooldownTime);
    //return player model
    return playerModel;
}

//deconstruct player model
void DeconstructPlayerModel(PlayerModel* playerModel)
{
    //free player model
    free(playerModel);
}

#endif // PLAYER_MODEL_H 