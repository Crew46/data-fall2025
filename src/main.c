// vircon standard library
#include "audio.h"
#include "misc.h"
#include "string.h"
#include "time.h"
#include "video.h"
// include texture, region, and audio definitions and configuration values
#include "configuration/texture_configurations.h"
#include "configuration/region_configurations.h"
#include "configuration/sound_configurations.h"
// objects
#include "object.h"
#include "player/player.h"
#include "enemy/enemy.h"
// linked list
#include "data_structures/doubly_linked_list/doubly_linked_list.h"
// other managers
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

GameState  currentState;

// list of all objects in scene
List      *objectList;

void main (void)
{
    int frame             = 0;

    objectList            = NULL;

    // initialize regions
    InitializeRegions ();
    InitializeAudioManager ();
    
    // MANY INSTANCES OF PLAYER, WHEN  PLAYER IS CREATED, THE PLAYER FILE
    // HAS STORED  IT IN A LINKED  LIST TO UPDATE ALL  INSTANCES, ALL YOU
    // HAVE TO  CALL IS  UpdateAllPlayers(); create  player, which  is an
    // extension of object, so need to pass in object params.

    //            texture ID,     region ID,     x,                       y,                         status, shootCooldown, gamepadID
    CreatePlayer (PLAYER_TEXTURE, PLAYER_REGION, (screen_width / 2),      (screen_height / 2),       0x01,   1.0,           0);
    CreatePlayer (PLAYER_TEXTURE, PLAYER_REGION, (screen_width / 2) - 40, (screen_height / 2),       0x01,   1.0,           1);
    CreatePlayer (PLAYER_TEXTURE, PLAYER_REGION, (screen_width / 2) + 40, (screen_height / 2),       0x05,   1.0,           1);
    CreatePlayer (PLAYER_TEXTURE, PLAYER_REGION, (screen_width / 2) - 80, (screen_height / 2) + 80,  0x09,   1.0,           0);
    CreatePlayer (PLAYER_TEXTURE, PLAYER_REGION, (screen_width / 2) + 80, (screen_height / 2) + 100, 0x0D,   1.0,           1);

    // Initialize game state
    currentState          = GAMESTATE_MENU;

    // main game loop
    while (true)
    {
        if ((frame % 5)  == 0)
        {
            // clear screen
            clear_screen(make_color_rgb (0, 0, 0));
            // drawing the background
            select_texture (BACKGROUND_TEXTURE);
            select_region (BACKGROUND_REGION);
            draw_region_at (0, 0);

            // updates all players in players list
            UpdateAllPlayers ();

            UpdateAllWeapons ();
            // main menu UI
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
            // print statistics
            PrintObjectDataAt (10, 60, GetPlayerList () -> head -> data);
            PrintObjectDataAt (screen_width - 180, 60, GetPlayerList () -> head -> next -> next -> next -> data);
        }
        else if ((frame % 5)  == 1)
        {
            UpdateAudioManager ();
        }
        else if ((frame % 5)  == 2)
        {
            //          texture ID,     region ID,    x,                  y,                   status, shootCooldown
            //CreateEnemy (ENEMY_TEXTURE, ENEMY_REGION, (screen_width / 2), (screen_height / 2), 0x01, 1.0);
            ;
        }
        else if ((frame % 5)  == 3)
        {
            ;
        }
        else if ((frame % 5)  == 4)
        {
            UpdateAllLasers ();
        }

        end_frame ();

        frame             = (frame + 1) % 60;
    }
}
