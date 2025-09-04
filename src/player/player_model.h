#ifndef PLAYER_MODEL_H
#define PLAYER_MODEL_H
//standard libraries
#include "misc.h"
#include "video.h"
#include "input.h"
#include "math.h"
//custom libraries
#include "../component/component_manager.h"
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
    Component object;
    float maxShootCooldownTime; //shoot cooldown in seconds
    float shootCooldownElapsed; //seconds elapsed since last shot
    PlayerMovementState state; // Current state of the player
    int speed; //speed in scene
    Vector2 inputDirection; //input vector
};

//=========================================================
///////////////////////////////////////////////////////////
/////////// PLAYER MODEL BEHAVIOURS ///////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//move player in a direction, where then direction is scaled by the player's speed
void PlayerModelMoveInDirection(PlayerModel* playerModel)
{
    Vector2* results = CreateVector2(0, 0);
    //add player position and direction to player position
    MultiplyVector2ByScalar(&playerModel->inputDirection, playerModel->speed, results); // Scale the movement vector by the player's speed
    AddVector2Components(results, &playerModel->object.position, &playerModel->object.position);
    free(results);
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
void InitializePlayerModel(PlayerModel* playerModel, int* name, int speed, float maxShootCooldownTime)
{
    //player object properties initialization
    ComponentManagerInitializeComponent(&playerModel->object, name);    

    //initialize passed in properties
    playerModel->maxShootCooldownTime = maxShootCooldownTime;
    playerModel->speed = speed;

    //intialize garbage values
    playerModel->state = PLAYER_MOVEMENT_STATE_IDLE; // Start in idle state
    playerModel->inputDirection.x = 0;
    playerModel->inputDirection.y = 0;
    playerModel->shootCooldownElapsed = 0; // Start with no cooldown
}

//construct player model
PlayerModel* CreatePlayerModel(int* name, int speed, float maxShootCooldownTime)
{
    //allocate memory for player model
    PlayerModel* playerModel = (PlayerModel*)malloc(sizeof(PlayerModel));
    //initialize player model
    InitializePlayerModel(playerModel, name, speed, maxShootCooldownTime);
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