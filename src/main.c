#include "time.h"
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
List* objectList;

void main (void)
{
    //initialize regions
    InitializeRegions ();
    InitializeAudioManager ();
    
    // MANY INSTANCES OF PLAYER, WHEN  PLAYER IS CREATED, THE PLAYER FILE
    // HAS STORED  IT IN A LINKED  LIST TO UPDATE ALL  INSTANCES, ALL YOU
    // HAVE TO  CALL IS  UpdateAllPlayers(); create  player, which  is an
    // extension of object, so need to pass in object params.

    //           texture,                region,        x,                    y,                      status, shootCooldown, gamepadID
    CreatePlayer (PLAYER_SPRITES_TEXTURE, PLAYER_REGION, screen_width / 2,     screen_height / 2,      0x00000001, 1.0, 0);
    CreatePlayer (PLAYER_SPRITES_TEXTURE, PLAYER_REGION, screen_width / 2 -40, screen_height / 2,      0x00000001, 1.0, 1);
    CreatePlayer (PLAYER_SPRITES_TEXTURE, PLAYER_REGION, screen_width / 2 +40, screen_height / 2,      0x00000005, 1.0, 1);
    CreatePlayer (PLAYER_SPRITES_TEXTURE, PLAYER_REGION, screen_width / 2 -80, screen_height / 2 +80,  0x00000009, 1.0, 0);
    CreatePlayer (PLAYER_SPRITES_TEXTURE, PLAYER_REGION, screen_width / 2 +80, screen_height / 2 +100, 0x0000000D, 1.0, 1);

    // Initialize game state
    currentState = GAMESTATE_MENU;

    //game loop
    while (true)
    {
		//clear screen
		clear_screen(make_color_rgb (0, 0, 0));
		//drawing the background
		select_texture (BACKGROUND_TEXTURE);
		select_region (BACKGROUND_REGION);
		draw_region_at (0, 0);
		UpdateAudioManager ();

		//updates all players in players list
		UpdateAllPlayers ();
		UpdateAllWeapons ();
		UpdateAllLasers ();

		//main menu UI
		if (currentState == GAMESTATE_MENU)
		{
			select_texture (UI_TEXTURES);
			select_region (EXIT_GAME_REGION);
			draw_region_at (20, 40);
			select_region (PLAY_GAME_REGION);
			draw_region_at (220, 40);
			select_region (CREDITS_REGION);
			draw_region_at (420, 40);
		}

		VisualizeLinkedList (GetPlayerList ());
		//print statistics
		PrintObjectDataAt (10, 60, GetPlayerList () -> head -> data);
		PrintObjectDataAt (screen_width - 180, 60, GetPlayerList () -> head -> next -> next -> next -> data);
        end_frame ();
    }
}
