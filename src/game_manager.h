#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "misc.h"
#include "video.h"
#include "player/player_controller.h"
#include "laser/laser_controller.h"
#include "laser/laser_controller_manager.h"
#include "player/player_controller_manager.h"


//temporary region definitions
#define REGION_PLAYER 1

//temporary player controller
PlayerController* playerController;
//temporary deltatime
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
///////////INITIALIZE (CALLED IN CONSTRUCTOR)//////////////
///////////////////////////////////////////////////////////

void InitializeGameManager(GameManager* manager) 
{
    //we should create a way to deserialize game state from a file, to load sprites, and player data
    //into the player controller

    //temporary player controller initialization
    //select player texture
    select_texture(1);
    select_region(REGION_PLAYER);
    define_region(0, 0, 31, 31, 0, 0); // Player sprite
    // create sprite array that player view will use, will use 1 sprites for now
    Sprite** sprites = (Sprite**)malloc(sizeof(Sprite*) * 1);
    sprites[0] = CreateSprite(REGION_PLAYER, 1); // Example sprite

    //params: inititial pos x, y, max shoot cooldown time, max lasers, speed, gamepadID, sprite array, number of sprites
    playerController = CreatePlayerController(screen_width / 2, screen_height / 2, 1, 10, 10, 0, sprites, 1); // Create player controller with initial values
    // Initialize game state
    manager->state = Menu;
}

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

//deconstructor
void DeconstructGameManager(GameManager* manager) 
{
    //deconstruct all laser and player controllers
    DeconstructAllLaserControllers();
    DeconstructAllPlayerControllers();
    free(manager);
}

///////////////////////////////////////////////////////////
///////////UPDATE GAME MANAGER/////////////////////////////
///////////////////////////////////////////////////////////

void UpdateGameManager(GameManager* manager) 
{
    //temporary player controller update
    PlayerControllerUpdate(playerController, deltaTime);

    //will update all once linked list data structure is made, in order to store instances and update iteratively
    //UpdateAllLaserControllers(deltaTime);
    //UpdateAllPlayerControllers(deltaTime);
}

#endif // GAME_MANAGER_H