#ifndef PLAYER_H
#define PLAYER_H
#include "misc.h"
#include "../vector/vector2.h"
#include "../laser/laser_controller.h"

struct Player 
{
    int maxLasers; // Maximum number of lasers the player can have
    Laser* laser; // Player's laser list
    Vector2* position;
    float maxShootCooldownTime; //seconds
    float currentShootCooldownTime; //seconds
};

Player* CreatePlayer()
{
    return (Player*)malloc(sizeof(Player));
}

void InitializePlayer(Player* player, int x, int y, float maxShootCooldownTime, int maxLasers)
{
    player->maxLasers = maxLasers;
    player->laser = (Laser*)malloc(sizeof(Laser) * maxLasers); // Initialize laser array
    player->maxShootCooldownTime = maxShootCooldownTime;
    player->currentShootCooldownTime = 0; // Start with no cooldown
    player->position = CreateVector2(x, y);
}

void DeinitializePlayer(Player* player)
{
    free(player->position);
    free(player);
}

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