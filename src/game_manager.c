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
    
    CreateShipGameObject("player0", 0, INPUT_CONTROLLER_TYPE_GAMEPAD, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 300, 300); 
    CreateShipGameObject("cpu0", 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 400, 300); 
    CreateShipGameObject("cpu1", 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 500, 300); 
    CreateShipGameObject("cpu2", 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 400, 300); 
    CreateShipGameObject("cpu3", 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 500, 300); 
    CreateShipGameObject("cpu4", 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 400, 300); 
    CreateShipGameObject("cpu5", 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 500, 300); 
    CreateShipGameObject("cpu6", 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 400, 300); 
    CreateShipGameObject("cpu7", 0, INPUT_CONTROLLER_TYPE_SHIP_CPU, PLAYER_REGION, PLAYER_SPRITES_TEXTURE, 300, 300); 
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

    //PrintGameObjectDataAt(0, 50, player); 
    //PrintGameObjectDataAt(400, 50, player1); 

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