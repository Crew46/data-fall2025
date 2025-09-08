#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
//vircon standard library
#include "misc.h"
#include "audio.h"
#include "video.h"
#include "string.h"
#include "math.h"
//include texture, region, and audio definitions and configuration values
#include "configuration/texture_configurations.h"
#include "configuration/region_configurations.h"
#include "configuration/sound_configurations.h"
//implementations
#include "data_structures/doubly_linked_list/doubly_linked_list.c"
#include "systems/audio/audio_manager.c"
#include "architecture/game_object/game_object_manager.c"
#include "architecture/component/component_manager.c"
#include "architecture/object/object_manager.c"
#include "tools/debugger.c"
//systems implementations
#include "systems/transform/transform_manager.c"

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

GameState currentState;

GameObject* player;
GameObject* player1;

//=========================================================
///////////////////////////////////////////////////////////
///////////INITIALIZATION//////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeGameManager() 
{
    // Initialize game manager state
    currentState = GAMESTATE_MENU;

    //initialize regions
    InitializeRegions();
    InitializeAudioManager();
    //component-based architecture initialization
    InitializeObjectManager();
    InitializeComponentManager();
    InitializeGameObjectManager();
    //systems initialization


    //game object creation
    player = GameObjectManagerConstructGameObject();
    GameObjectManagerAddComponentToGameObject(player, TRANSFORM_COMPONENT);
    player1 = GameObjectManagerConstructGameObject();
    GameObjectManagerAddComponentToGameObject(player1, TRANSFORM_COMPONENT);
}

void DeinitializeGameManager()
{

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
    UpdateAudioManager();


    PrintGameObjectDataAt(20, 50, player); 
    PrintGameObjectDataAt(300, 50, player1); 

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

#endif // GAME_MANAGER_H