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

void InitializeGameManager(GameManager* manager) 
{
    // create sprite array that player view will use, will use 2 sprites for now
    Sprite** sprites = (Sprite**)malloc(sizeof(Sprite*) * 2);
    sprites[0] = CreateSprite(1); // Example sprite
    sprites[1] = CreateSprite(4); // Example sprite

    playerController = CreatePlayerController(20, 10, 1, 10, sprites, 2); // Create player controller with initial values
    // Initialize game state
    manager->state = Menu;
}

//constructor
GameManager* CreateGameManager()
{
    GameManager* gameManager = (GameManager*)malloc(sizeof(GameManager));
    InitializeGameManager(gameManager);
    return gameManager;
}


//deconstructor
void DeinitializeGameManager(GameManager* manager) 
{
    free(manager);
}

///////////////////////////////////////////////////////////
///////////UPDATE GAME MANAGER/////////////////////////////
///////////////////////////////////////////////////////////

void UpdateGameManager(GameManager* manager) 
{
    PlayerControllerUpdate(playerController, deltaTime); // Update player controller
}

#endif // GAME_MANAGER_H