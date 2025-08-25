#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "misc.h"
#include "video.h"
#include "player/player_controller.h"
#include "laser/laser_controller.h"
#include "laser/laser_controller_manager.h"
#include "player/player_controller_manager.h"

//include texture and regions definitions and configuration vales
#include "configuration/textures_configurations.h"
#include "configuration/regions_configurations.h"

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
    //initialize regions
    InitializeRegions();

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
	clear_screen(get_color_red(0));	
    //drawing the background
    select_texture ( BACKGROUND_TEXTURE );
    select_region ( BACKGROUND_REGION );
    draw_region_at( 0, 0 );

    //temporary player controller update
    PlayerControllerUpdate(playerController, deltaTime);

    //will update all once linked list data structure is made, in order to store instances and update iteratively
    //UpdateAllLaserControllers(deltaTime);
    //UpdateAllPlayerControllers(deltaTime);
}

#endif // GAME_MANAGER_H