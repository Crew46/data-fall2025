#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
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
#include "systems/player/player_manager.c"
#include "vector/vector2.h"
//other implementations
#include "data_structures/doubly_linked_list/doubly_linked_list.c"
#include "data_structures/singly_linked_list/linked_list.c"
#include "tools/debugger.c"

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

//=========================================================
///////////////////////////////////////////////////////////
///////////INITIALIZATION//////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeGameManager() 
{
    //temporary
    select_gamepad(0);



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
    InitializeTransformManager();
    InitializeRenderManager();



    //player creation
    player = ConstructGameObject();
    SetObjectName((Object*)player, "player");
    AddComponentToGameObject(player, TRANSFORM_COMPONENT);
    AddComponentToGameObject(player, RENDER_COMPONENT);
    AddComponentToGameObject(player, PLAYER_CONTROLLER_COMPONENT);
    //set the region and texture of the render component
    SetRenderComponentRegion((RenderComponent*)GameObjectGetComponentByType(player, RENDER_COMPONENT), PLAYER_REGION);
    SetRenderComponentTexture((RenderComponent*)GameObjectGetComponentByType(player, RENDER_COMPONENT), PLAYER_SPRITES_TEXTURE);
    //set position of the transform
    TransformComponentSetGlobalPosition((TransformComponent*)GameObjectGetComponentByType(player, TRANSFORM_COMPONENT), 300, 300);
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

    //updates all gameobject in scenes, allong with the attatched components
    UpdateAllGameObjects();

    //PrintGameObjectDataAt(20, 50, player); 
    //PrintGameObjectDataAt(380, 50, gameObjectManager->root); 

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