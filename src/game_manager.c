#ifndef GAME_MANAGER_C
#define GAME_MANAGER_C
//vircon standard library
#include "misc.h"
#include "audio.h"
#include "video.h"
#include "string.h"
#include "input.h"
#include "math.h"
//include texture, region, and audio definitions and configuration values
#include "configuration/texture_configurations.h"
#include "configuration/region_configurations.h"
#include "configuration/sound_configurations.h"
//architecture implementations
#include "architecture/game_object/game_object_manager.c"
#include "architecture/component/component_manager.c"
#include "architecture/object/object_manager.c"
//systems implementations
#include "systems/audio/audio_manager.c"
#include "systems/rendering/render_manager.c"
#include "systems/transform/transform_manager.c"
#include "systems/ship/ship_controller_manager.c"
#include "vector/vector2.h"
#include "systems/weapon/weapon/weapon_controller_manager.c"
//physics systems implementations
#include "systems/physics/collider/collider_manager.c"
#include "systems/physics/rigidbody/rigidbody_manager.c"
#include "systems/physics/tools/raycast_tool.c"
#include "systems/input/input_controller_manager.c"
#include "systems/health/health_controller_manager.c"
//other implementations
#include "data_structures/doubly_linked_list/doubly_linked_list.c"
#include "data_structures/singly_linked_list/linked_list.c"
#include "tools/debugger.c"

//prefabrication
#include "systems/ship/ship_game_object_factory.c"

//=========================================================
///////////////////////////////////////////////////////////
///////////DECLARATIONS////////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

enum GameState
{
    GAMESTATE_MENU,
    GAMESTATE_INGAME
};

GameState currentState = GAMESTATE_MENU;
GameObject* ship = NULL;

//=========================================================
///////////////////////////////////////////////////////////
///////////INITIALIZATION//////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeGameManager() 
{
    //initialize regions
    InitializeRegions();

    //component-based architecture initialization
    //object manager
    OM_Initialize();
    //component manager
    CM_Initialize();
    //game-object manager
    GOM_Initialize();
    //systems initialization
    InitializeAudioManager();
    ship = CreateShipGameObject("player", 300, 300, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 0, 0, INPUT_CONTROLLER_TYPE_GAMEPAD, 100, 5, SHIP_TYPE_DEFAULT, 5, WEAPON_CONTROLLER_TYPE_LASER_CANNON); 
    CreateShipGameObject("cpu", 300, 300, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 0, 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, 100, 5, SHIP_TYPE_DEFAULT, 1, WEAPON_CONTROLLER_TYPE_LASER_CANNON); 
    CreateShipGameObject("cpu", 300, 300, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 0, 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, 100, 5, SHIP_TYPE_DEFAULT, 1, WEAPON_CONTROLLER_TYPE_LASER_CANNON); 
    CreateShipGameObject("cpu", 300, 300, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 0, 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, 100, 5, SHIP_TYPE_DEFAULT, 1, WEAPON_CONTROLLER_TYPE_LASER_CANNON); 
    CreateShipGameObject("cpu", 300, 300, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 0, 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, 100, 5, SHIP_TYPE_DEFAULT, 1, WEAPON_CONTROLLER_TYPE_LASER_CANNON); 
    CreateShipGameObject("cpu", 300, 300, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 0, 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, 100, 5, SHIP_TYPE_DEFAULT, 1, WEAPON_CONTROLLER_TYPE_LASER_CANNON); 
    CreateShipGameObject("cpu", 300, 300, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 0, 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, 100, 5, SHIP_TYPE_DEFAULT, 1, WEAPON_CONTROLLER_TYPE_LASER_CANNON); 
    CreateShipGameObject("cpu", 300, 300, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 0, 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, 100, 5, SHIP_TYPE_DEFAULT, 1, WEAPON_CONTROLLER_TYPE_LASER_CANNON); 
    CreateShipGameObject("cpu", 300, 300, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 0, 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, 100, 5, SHIP_TYPE_DEFAULT, 1, WEAPON_CONTROLLER_TYPE_LASER_CANNON); 
    CreateShipGameObject("cpu", 300, 300, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 0, 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, 100, 5, SHIP_TYPE_DEFAULT, 1, WEAPON_CONTROLLER_TYPE_LASER_CANNON); 
}

void DeinitializeGameManager()
{
    //deinitialize
}

//=========================================================
///////////////////////////////////////////////////////////
///////////GAME LOOP///////////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdateGameManager() 
{
    //clear screen
    clear_screen(make_color_rgb(0, 0, 0));
    //drawing the background
    select_texture ( BACKGROUND_TEXTURE );
    select_region ( BACKGROUND_REGION );
    draw_region_at( 0, 0 );

    //updates all gameobject in scene, allong with the attatched components to those gameobjects
    GOM_UpdateAllGameObjects();

    PrintGameObjectDataAt(0, 50, ship); 
    PrintGameObjectDataAt(300, 50, GOM_GetRootGameObject()); 

    //main menu UI
    if(currentState == GAMESTATE_MENU)
    {
        select_texture(UI_TEXTURES);
        select_region(EXIT_GAME_REGION);
        draw_region_at(20, 40);
        select_region(PLAY_GAME_REGION);
        draw_region_at(220, 40);
        select_region(CREDITS_REGION);
        draw_region_at(420, 40);
    }
}

#endif // GAME_MANAGER_C