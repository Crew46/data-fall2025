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
//implementations
#include "data_structures/doubly_linked_list/doubly_linked_list.c"
#include "data_structures/singly_linked_list/linked_list.c"
#include "systems/audio/audio_manager.c"
#include "architecture/game_object/game_object_manager.c"
#include "architecture/component/component_manager.c"
#include "architecture/object/object_manager.c"
#include "tools/debugger.c"
//systems implementations
#include "systems/rendering/render_manager.c"
#include "systems/transform/transform_manager.c"
#include "vector/vector2.h"

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
GameObject* player2;

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


    //game object creation
    player = ConstructGameObject();
    AddComponentToGameObject(player, TRANSFORM_COMPONENT);
    AddComponentToGameObject(player, RENDER_COMPONENT);
    ObjectManagerSetObjectName((Object*)player, "player");
    TransformComponentSetGlobalPosition((TransformComponent*)GameObjectGetComponentByType(player, TRANSFORM_COMPONENT), 300, 300);


    player1 = ConstructGameObject();
    AddComponentToGameObject(player1, TRANSFORM_COMPONENT);
    ObjectManagerSetObjectName((Object*)player1, "player1");
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
    PrintGameObjectDataAt(20, 50, player); 
    PrintGameObjectDataAt(200, 50, player1); 
    PrintGameObjectDataAt(380, 50, gameObjectManager->root); 

    //test
    TransformComponent* transform = (TransformComponent*)GameObjectGetComponentByType(player, TRANSFORM_COMPONENT);
    Vector2* movement = CreateVector2(0, 0);
    gamepad_direction_normalized(&movement->x, &movement->y);
    Vector2* result = CreateVector2(0, 0);
    int speed = 8;
    MultiplyVector2ByScalar(movement, speed, result);
    Vector2* result2 = CreateVector2(0, 0);
    AddVector2Components(&transform->position, result, result2);
    TransformComponentSetGlobalPosition(transform, result2->x, result2->y);
    free(result);
    free(result2);


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