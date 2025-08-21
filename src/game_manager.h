#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "misc.h"
#include "player/player_controller.h"

enum GameState {
    Menu
};

struct GameManager {
    GameState state; // Current game state
};

//constructor
GameManager* CreateGameManager()
{
    GameManager* gameManager = (GameManager*)malloc(sizeof(GameManager));
    InitializeGameManager(gameManager);
    return gameManager;
}

void InitializeGameManager(GameManager* manager) 
{
    // Initialize game state
    manager->state = Menu;
}

//deconstructor
void DeinitializeGameManager(GameManager* manager) 
{
    free(manager);
}


void UpdateGameManager(GameManager* manager) 
{
}

#endif // GAME_MANAGER_H