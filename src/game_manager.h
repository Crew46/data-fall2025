#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "misc.h"
#include "player/player.h"

enum GameState {
    Menu
};

struct GameManager {
    GameState state; // Current game state
};


//constructor
GameManager* CreateGameManager()
{
    return (GameManager*)malloc(sizeof(GameManager));
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