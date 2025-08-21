#ifndef PLAYER_H
#define PLAYER_H
#include "misc.h"
#include "../vector/vector2.h"
#include "../laser/laser_controller.h"

/** 
 * SUMMARY:
 * This file defines the Player struct and its associated functions.
 * This is the model of the player: the fundamental properties and behaviors of the player.
**/

////////////////////////////////////////////////////////////
///////////Player Struct////////////////////////////////////
///////////////////////////////////////////////////////////

struct Player 
{
    int maxLasers; // Maximum number of lasers the player can have
    LaserController* laser; // Player's laser list
    Vector2* position;
    float maxShootCooldownTime; //seconds
    float currentShootCooldownTime; //seconds
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

Player* CreatePlayer(int x, int y, float maxShootCooldownTime, int maxLasers)
{
    //allocate memory for player
    Player* player = (Player*)malloc(sizeof(Player));

    //player properties initialization
    player->maxLasers = maxLasers;
    player->laser = (LaserController*)malloc(sizeof(LaserController) * maxLasers); // Initialize laser controller array of size maxLasers
    player->maxShootCooldownTime = maxShootCooldownTime;
    player->currentShootCooldownTime = 0; // Start with no cooldown
    player->position = CreateVector2(x, y);
    return player;
}

//player deconstructor
void DeinitializePlayer(Player* player)
{
    //deinitialize player position vector
    DeinitializeVector2(player->position);

    //deinitialize each laser controller in the array
    for(int i = 0; i < player->maxLasers; i++)
    {
        DeinitializeLaserController(&player->laser[i]);
    }

    //free player struct
    free(player);
}

///////////////////////////////////////////////////////////
///////////Player Functions////////////////////////////////
///////////////////////////////////////////////////////////

void MovePlayer(Player* player, Vector2* direction)
{
    //add player position and direction to player position
    AddVector2Components(player->position, direction, player->position);
}

void UpdateShootCooldown(Player* player, float deltaTime)
{
    if(player->currentShootCooldownTime > 0)
    {
        player->currentShootCooldownTime -= deltaTime;
        if(player->currentShootCooldownTime < 0)
        {
            player->currentShootCooldownTime = 0;
        }
    }
}

void PlayerShoot(Player* player)
{
    //if not in cooldown, shoot
    if(player->currentShootCooldownTime == 0)
    {
        //shoot logic here
        

        // Reset cooldown
        player->currentShootCooldownTime = player->maxShootCooldownTime;
    }
}

#endif // PLAYER_H 