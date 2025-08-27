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
    select_channel(0);
    play_sound(THE_INITIUM_CAVERNS_MUSIC);
    //initialize regions
    InitializeRegions();

    //create a generic object that the player will utilize
    Object* playerObject = CreateObject(PLAYER_SPRITES_TEXTURE, PLAYER_REGION, 0, screen_width / 2, screen_height / 2, true, 10); 
    //create player controller: params: generic object instance, maxshootingcooldowntime, speed, gamepadID, sprite array, num sprites 
    player = CreatePlayer(playerObject, 1, 0); // Create player controller with initial values

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

    //clear screen
	clear_screen(get_color_red(0));	
    //drawing the background
    select_texture ( BACKGROUND_TEXTURE );
    select_region ( BACKGROUND_REGION );
    draw_region_at( 0, 0 );
    PlayerUpdate(player);
}

#endif // GAME_MANAGER_H