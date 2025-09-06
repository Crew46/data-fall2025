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

ObjectManager* objectManager;
ComponentManager* componentManager;
GameObjectManager* gameObjectManager;

TransformManager* transformManager;

GameObject* player;
GameObject* player1;

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


    //systems managagers
    transformManager = ConstructTransformManager(componentManager);

    //create player with components
    player = GameObjectManagerConstructGameObject(gameObjectManager, "Player");
    GameObjectManagerAddComponentToGameObject(gameObjectManager, player, "PlayerTransform", TRANSFORM_COMPONENT);
    GameObjectManagerAddComponentToGameObject(gameObjectManager, player, "PlayerRigidbody", RIGIDBODY_COMPONENT);
    GameObjectManagerAddComponentToGameObject(gameObjectManager, player, "PlayerRenderer", RENDER_COMPONENT);
    //create another player with components
    player1 = GameObjectManagerConstructGameObject(gameObjectManager, "Player1");
    GameObjectManagerAddComponentToGameObject(gameObjectManager, player1, "PlayerRigidbody", RIGIDBODY_COMPONENT);
    GameObjectManagerAddComponentToGameObject(gameObjectManager, player1, "PlayerRenderer", RENDER_COMPONENT);
    GameObjectManagerAddComponentToGameObject(gameObjectManager, player1, "PlayerTransform", TRANSFORM_COMPONENT);
    
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

    PrintGameObjectDataAt(10, 50, player);
    PrintGameObjectDataAt(350, 50, player1);

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