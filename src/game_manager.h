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
//linked list
#include "data_structures/doubly_linked_list/doubly_linked_list.h"
//other managers
#include "systems/audio/audio_manager.h"
#include "architecture/game_object/game_object_manager.h"
#include "architecture/component/component_manager.h"
#include "architecture/object/object_manager.h"

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

ObjectManager* objectManager;
ComponentManager* componentManager;
GameObjectManager* gameObjectManager;

GameObject* player;

//=========================================================
///////////////////////////////////////////////////////////
///////////INITIALIZATION//////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeGameManager() 
{
    //initialize regions
    InitializeRegions();
    InitializeAudioManager();

    // Initialize object manager
    objectManager = ConstructObjectManager();
    // Initialize component manager
    componentManager = ConstructComponentManager(objectManager);
    // Initialize game object manager
    gameObjectManager = ConstructGameObjectManager(componentManager, objectManager);

    player = GameObjectManagerConstructGameObject(gameObjectManager, "Player");
    GameObjectManagerAddComponentToGameObject(gameObjectManager, player, "player position", TRANSFORM_COMPONENT);
    
    // Initialize game state
    currentState = GAMESTATE_MENU;
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

    UpdateAllGameObjects(gameObjectManager);

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