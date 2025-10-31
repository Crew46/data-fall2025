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

GameObject* player = NULL;
GameObject* player1 = NULL;

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
    
    //player creation
    player = GOM_ConstructGameObject();
    GOM_GameObjectSet_Name(player, "player0");
    GOM_AddComponentToGameObject(player, TRANSFORM_COMPONENT);
    GOM_AddComponentToGameObject(player, RENDER_COMPONENT);
    GOM_AddComponentToGameObject(player, SHIP_CONTROLLER_COMPONENT);
    GOM_AddComponentToGameObject(player, INPUT_CONTROLLER_COMPONENT);
    GOM_AddComponentToGameObject(player, HEALTH_CONTROLLER_COMPONENT);

    //set gamepad of player controller component
    ICM_InputControllerSet_Gamepad((InputController*)GOM_GameObjectGet_ComponentByType(player, INPUT_CONTROLLER_COMPONENT), 0);
    ICM_InputControllerSet_Type((InputController*)GOM_GameObjectGet_ComponentByType(player, INPUT_CONTROLLER_COMPONENT), INPUT_CONTROLLER_TYPE_GAMEPAD);
    //ship
    ShipControllerSet_Speed((ShipController*)GOM_GameObjectGet_ComponentByType(player, SHIP_CONTROLLER_COMPONENT), 8);

    //set the region and texture of the render component
    SetRenderComponentRegion((RenderComponent*)GOM_GameObjectGet_ComponentByType(player, RENDER_COMPONENT), PLAYER_REGION);
    SetRenderComponentTexture((RenderComponent*)GOM_GameObjectGet_ComponentByType(player, RENDER_COMPONENT), PLAYER_SPRITES_TEXTURE);
    //set position of the transform
    TransformComponentSetGlobalPosition((TransformComponent*)GOM_GameObjectGet_ComponentByType(player, TRANSFORM_COMPONENT), 300, 300);
    
    //player creation
    player1 = GOM_ConstructGameObject();
    GOM_GameObjectSet_Name(player1, "player1");
    GOM_AddComponentToGameObject(player1, TRANSFORM_COMPONENT);
    GOM_AddComponentToGameObject(player1, RENDER_COMPONENT);
    GOM_AddComponentToGameObject(player1, SHIP_CONTROLLER_COMPONENT);
    GOM_AddComponentToGameObject(player1, INPUT_CONTROLLER_COMPONENT);
    ICM_InputControllerSet_Type((InputController*)GOM_GameObjectGet_ComponentByType(player1, INPUT_CONTROLLER_COMPONENT), INPUT_CONTROLLER_TYPE_SHIP_CPU);
    //ship
    ShipControllerSet_Speed((ShipController*)GOM_GameObjectGet_ComponentByType(player1, SHIP_CONTROLLER_COMPONENT), 2);
    //set the region and texture of the render component
    SetRenderComponentRegion((RenderComponent*)GOM_GameObjectGet_ComponentByType(player1, RENDER_COMPONENT), PLAYER_REGION);
    SetRenderComponentTexture((RenderComponent*)GOM_GameObjectGet_ComponentByType(player1, RENDER_COMPONENT), PLAYER_SPRITES_TEXTURE);
    //set position of the transform
    TransformComponentSetGlobalPosition((TransformComponent*)GOM_GameObjectGet_ComponentByType(player1, TRANSFORM_COMPONENT), 400, 300);
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