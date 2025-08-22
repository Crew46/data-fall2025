#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "misc.h"
#include "video.h"
#include "player/player_controller.h"


//temporary region definitions
#define REGION_PLAYER 1

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
    //temporary player controller initialization
    //select player texture
    select_texture(1);
    select_region(REGION_PLAYER);
    define_region(0, 0, 64, 64, 32, 32); // Player sprite
    // create sprite array that player view will use, will use 2 sprites for now
    Sprite** sprites = (Sprite**)malloc(sizeof(Sprite*) * 2);
    sprites[0] = CreateSprite(REGION_PLAYER, 1); // Example sprite

    playerController = CreatePlayerController(20, 10, 1, 10, 10, 0, sprites, 2); // Create player controller with initial values
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