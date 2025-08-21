#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "misc.h"
#include "player/player_controller.h"

//temporary player controller
PlayerController* playerController;
float deltaTime;

////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////
///////////////////////////////////////////////////////////

enum GameState {
    Menu
};

struct GameManager {
    GameState state; // Current game state
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

//constructor
GameManager* CreateGameManager()
{
    GameManager* gameManager = (GameManager*)malloc(sizeof(GameManager));
    InitializeGameManager(gameManager);
    return gameManager;
}

void InitializeGameManager(GameManager* manager) 
{
    playerController = CreatePlayerController(0, 0, 1.0f, 10); // Create player controller with initial values
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
    PlayerControllerUpdate(playerController, deltaTime); // Update player controller
}

#endif // GAME_MANAGER_H