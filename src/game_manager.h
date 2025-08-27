#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "misc.h"
#include "video.h"
#include "object.h"
#include "player/player.h"
//include texture and regions definitions and configuration vales
#include "configuration/texture_configurations.h"
#include "configuration/region_configurations.h"

//player
Player* player;

enum GameState
{
    MENU,
    INGAME
};

GameState currentState;

///////////////////////////////////////////////////////////
///////////INITIALIZE (CALLED IN CONSTRUCTOR)//////////////
///////////////////////////////////////////////////////////

void InitializeGameManager() 
{
    //initialize regions
    InitializeRegions();

    //create a generic object that the player will utilize
    Object* playerObject = CreateObject(PLAYER_SPRITES_TEXTURE, PLAYER_REGION, 0, screen_width / 2, screen_height / 2, true, 10); 
    //create player controller: params: generic object instance, maxshootingcooldowntime, speed, gamepadID, sprite array, num sprites 
    player = CreatePlayer(playerObject, 1, 0); // Create player controller with initial values

    // Initialize game state
    currentState = MENU;
}


///////////////////////////////////////////////////////////
///////////UPDATE GAME MANAGER/////////////////////////////
///////////////////////////////////////////////////////////

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