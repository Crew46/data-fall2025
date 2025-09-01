#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
//vircon standard library
#include "misc.h"
#include "audio.h"
#include "video.h"
#include "string.h"
//include texture, region, and audio definitions and configuration values
#include "configuration/texture_configurations.h"
#include "configuration/region_configurations.h"
#include "configuration/sound_configurations.h"
//objects
#include "object.h"
#include "player/player.h"
//linked list
#include "data_structures/doubly_linked_list/doubly_linked_list.h"
//other managers
#include "audio_manager.h"

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
DoublyLinkedList* objectList;

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

    //create player, which is an extension of object, so need to pass in object params.

    //           name,     texture,                region,       id, x,                y,    isActive, speed, shootCooldown, gamepadID
    CreatePlayer("Player0", PLAYER_SPRITES_TEXTURE, PLAYER_REGION, 0, screen_width / 2, screen_height / 2, true, 8, 1, 0);
    CreatePlayer("Player1", PLAYER_SPRITES_TEXTURE, PLAYER_REGION, 1, screen_width / 2 -40, screen_height / 2, true, 4, 1, 1);
    CreatePlayer("Player2", PLAYER_SPRITES_TEXTURE, PLAYER_REGION, 2, screen_width / 2 + 40, screen_height / 2, true, 3, 1, 1);
    CreatePlayer("Player3", PLAYER_SPRITES_TEXTURE, PLAYER_REGION, 3, screen_width / 2 -80, screen_height / 2 + 80, true, 2, 1, 0);
    CreatePlayer("Player4", PLAYER_SPRITES_TEXTURE, PLAYER_REGION, 4, screen_width / 2 + 80, screen_height / 2 + 100, true, 4, 1, 1);

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

    VisualizeLinkedList(GetPlayerList());
    //print statistics
    //PrintObjectDataAt(10, 60, GetPlayerList()->head->data);
    //PrintObjectDataAt(screen_width - 180, 60, GetPlayerList()->head->next->next->next->data);
}

#endif // GAME_MANAGER_H