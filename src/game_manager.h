#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "misc.h"
#include "player/player.h"

struct GameState {
    Menu
};

struct GameManager {
    GameState state; // Current game state
};

GameManager* CreateGameManager()
{
    return (GameManager*)malloc(sizeof(GameManager));
}

void UpdateGameManager(GameManager* manager) 
{
    //update invaders
    for(int i = 0; i < manager->invaderCount; i++)
    {
        UpdateInvader(&manager->invaders[i]);
    }
}

void InitializeGameManager(GameManager* manager) 
{
}

void DeinitializeGameManager(GameManager* manager) 
{
    for(int i = 0; i < manager->invaderCount; i++) 
    {
        DeinitializeInvader(&manager->invaders[i]);
    }
    free(manager);
}

#endif // GAME_MANAGER_H