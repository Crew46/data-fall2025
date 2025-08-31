#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
//vircon standard library
#include "misc.h"
#include "audio.h"
#include "video.h"
//include texture and regions definitions and configuration vales
#include "configuration/texture_configurations.h"
#include "configuration/region_configurations.h"
#include "configuration/sound_configurations.h"
//objects
#include "object.h"
#include "player/player.h"
//linked list
#include "data_structures/doubly_linked_list/doubly_linked_list.h"

//=========================================================
///////////////////////////////////////////////////////////
///////////DECLARATIONS////////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//player instance
Player* player;

enum GameState
{
    MENU,
    INGAME
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

    //player intialize temporary location
    select_sound(THE_ABYSS_MUSIC);
    select_channel(0);
    assign_channel_sound(get_selected_channel(), get_selected_sound());
    play_channel(get_selected_channel());
    set_channel_loop(true);

    //create player, which is an extension of object
    player = CreatePlayer(PLAYER_SPRITES_TEXTURE, PLAYER_REGION, 0, screen_width / 2, screen_height / 2, true, 5, 1, 0);

    // Initialize game state
    currentState = MENU;
}

//=========================================================
///////////////////////////////////////////////////////////
///////////GAME LOOP///////////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdateGameManager() 
{
    clear_screen(make_color_rgb(0, 0, 0));
    //clear screen
    //drawing the background
    select_texture ( BACKGROUND_TEXTURE );
    select_region ( BACKGROUND_REGION );
    draw_region_at( 0, 0 );

    PlayerUpdate(player);
    
    select_texture(UI_TEXTURES);
    select_region(PLAY_GAME_REGION);
    draw_region_at(20, 40);
    select_region(EXIT_GAME_REGION);
    draw_region_at(200, 40);
}

#endif // GAME_MANAGER_H