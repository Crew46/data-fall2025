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
//objects
#include "object.h"
#include "player/player_controller.h"
//linked list
#include "data_structures/doubly_linked_list/doubly_linked_list.h"
//other managers
#include "audio_manager.h"
#include "player/player_manager.h"

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

//list of all objects in scene
DoublyLinkedList* allObjectsList = CreateDoublyLinkedList();

DoublyLinkedList* GetObjectList()
{
    return allObjectsList;
}

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
    
    //MANY INSTANCES OF PLAYER, WHEN PLAYER IS CREATED, THE PLAYER FILE HAS STORED IT IN A LINKED LIST
    //TO UPDATE ALL INSTANCES, ALL YOU HAVE TO CALL IS UpdateAllPlayers();

    //create player, cast to object, and put in tobject list. player is an extension of object, so need to pass in object params.

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

    //updates all players in players list
    UpdateAllPlayers();

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