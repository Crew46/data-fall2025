// vircon standard library
#include "audio.h"
#include "misc.h"
#include "string.h"
#include "time.h"
#include "video.h"
// include texture, region, and audio definitions and configuration values
#include "configuration/game_configurations.h"
#include "configuration/gamepad_configurations.h"
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
#include "title_screen.h"
#include "audio_manager.h"
#include "video_manager.h"
#include "weapon/laser.h"
#include "weapon/weapon.h"

#define  HALFWAY_ACROSS (screen_width/2)
#define  HALFWAY_DOWN   (screen_height/2)

#define  FRAME_SLICES            5 // frame offset categories

#define  SCREEN_REDRAWING_FRAME  0
#define  AUDIO_PROCESSING_FRAME  1
#define  PLAYER_PROCESSING_FRAME 2
#define  ENEMY_PROCESSING_FRAME  3
#define  WEAPON_PROCESSING_FRAME 4

// list of all objects in scene
List      *objectList;

void main (void)
{
    bool       begin                     = false;
    bool       start                     = false;
    int        cycles                    = 0;
    int        frame                     = 0;
    int        x                         = 0;
    int        xdir                      = 0;
    int        y                         = 0;
    int        ydir                      = 0;
    int        direction                 = 0;
    int  [7]   report;

    objectList                           = NULL;
    currentState                         = GAMESTATE_TITLE;
    seconds                              = 0;

    // initialize regions
    InitializeRegions ();
    InitializeAudioManager ();
    
    srand (get_time ());

    // MANY INSTANCES OF PLAYER, WHEN  PLAYER IS CREATED, THE PLAYER FILE
    // HAS STORED  IT IN A LINKED  LIST TO UPDATE ALL  INSTANCES, ALL YOU
    // HAVE TO  CALL IS  UpdateAllPlayers(); create  player, which  is an
    // extension of object, so need to pass in object params.

    CreatePlayer (PLAYER_TEXTURE,                  // texture ID
                  PLAYER_REGION,                   // region ID
                  HALFWAY_ACROSS,                  // starting X
                  HALFWAY_DOWN,                    // starting Y
                  IS_ACTIVE_FLAG,                  // status flag bits
                  1.0,                             // shootCooldown
                  PLAYER_ONE);                     // gamepad ID

    CreatePlayer (PLAYER_TEXTURE,                  // texture ID
                  PLAYER_REGION,                   // region ID
                  HALFWAY_ACROSS - 40,             // starting X
                  HALFWAY_DOWN,                    // starting Y
                  IS_ACTIVE_FLAG,                  // status flag bits
                  1.0,                             // shootCooldown
                  PLAYER_TWO);                     // gamepad ID

    CreatePlayer (PLAYER_TEXTURE,                  // texture ID
                  PLAYER_REGION,                   // region ID
                  HALFWAY_ACROSS + 40,             // starting X
                  HALFWAY_DOWN,                    // starting Y
                  IS_ACTIVE_FLAG | ODD_TEAM_FLAG,  // status flag bits
                  1.0,                             // shootCooldown
                  PLAYER_TWO);                     // gamepad ID

    CreatePlayer (PLAYER_TEXTURE,                  // texture ID
                  PLAYER_REGION,                   // region ID
                  HALFWAY_ACROSS - 80,             // starting X
                  HALFWAY_DOWN + 80,               // starting Y
                  IS_ACTIVE_FLAG | HIGH_TEAM_FLAG, // status flag bits
                  1.0,                             // shootCooldown
                  PLAYER_ONE);                     // gamepad ID

    CreatePlayer (PLAYER_TEXTURE,                  // texture ID
                  PLAYER_REGION,                   // region ID
                  HALFWAY_ACROSS + 80,             // starting X
                  HALFWAY_DOWN + 100,              // starting Y
                  IS_ACTIVE_FLAG | ODD_HIGH_FLAG,  // status flag bits
                  1.0,                             // shootCooldown
                  PLAYER_TWO);                     // gamepad ID

    // Initialize game state
    //currentState                         = GAMESTATE_MENU;
    select_gamepad (0);

    // main game loop
    while (true)
    {
        cycles                  = get_cycle_counter ();
        if (currentState       == GAMESTATE_TITLE)
        {
            // clear screen
            clear_screen (make_color_rgb (0, 0, 0));

            title_screen (&begin);
        }

        if ((get_frame_counter () % 60) == 0)
        {
            itoa (report, cycles, 10);
            print_at (0, 0, report);
        }

        if ((frame % FRAME_SLICES)      == SCREEN_REDRAWING_FRAME)
        {
            if (currentState            == GAMESTATE_INTRO)
            {
                ;
            }
            else if (currentState       == GAMESTATE_TITLE)
            {
                ;
            }
            else if (currentState       == GAMESTATE_MENU)
            {
                // main menu UI
                select_texture (UI_TEXTURES);
                select_region (EXIT_GAME_REGION);
                draw_region_at (20, 40);
                select_region (PLAY_GAME_REGION);
                draw_region_at (220, 40);
                select_region (CREDITS_REGION);
                draw_region_at (420, 40);
            }
            else if (currentState       == GAMESTATE_INGAME)
            {
                // clear screen
                clear_screen (make_color_rgb (0, 0, 0));

                // drawing the background
                select_texture (BACKGROUND_TEXTURE);
                select_region (BACKGROUND_REGION);
                draw_region_at (0, 0);

                // draw all objects list
                drawList (GetPlayerList ());
                drawList (GetEnemyList ());
                drawList (GetWeaponList ());
                drawList (GetLaserList ());
            }
            else if (currentState       == GAMESTATE_PLAYAGAIN)
            {
                ;
            }
            else if (currentState       == GAMESTATE_CREDITS)
            {
                ;
            }
            else
            {
                VisualizeLinkedList (GetPlayerList ());
                // print statistics
                PrintObjectDataAt (10, 60, GetPlayerList () -> head -> data);
                PrintObjectDataAt ((screen_width - 180),
                                   60,
                                   GetPlayerList () -> head -> next -> next -> next -> data);
            }
        }
        else if ((frame % FRAME_SLICES) == AUDIO_PROCESSING_FRAME)
        {
            UpdateAudioManager ();
        }
        else if ((frame % FRAME_SLICES) == PLAYER_PROCESSING_FRAME)
        {
            if (currentState            == GAMESTATE_INGAME)
            {
                UpdateAllPlayers ();
            }
            else if (currentState       == GAMESTATE_TITLE)
            {
                start                    = (gamepad_button_start () >  0);
                if (start               == true)
                {
                    currentState         = GAMESTATE_INGAME;
                    pause_channel (0);
                    stop_channel (0);
                    select_sound (BETTER_THAN_FASTER_THAN_MUSIC);
                    select_channel (0);
                    assign_channel_sound (get_selected_channel (), get_selected_sound ());
                    play_channel (get_selected_channel ());
                    set_channel_loop (true);
                }
            }
        }
        else if ((frame % FRAME_SLICES) == ENEMY_PROCESSING_FRAME)
        {
            if (enemyList -> qty        == 0)
            {
                CreateEnemy (ENEMY_TEXTURE,          // texture ID
                             ENEMY_REGION,           // region ID
                             rand () % screen_width, // starting X
                             0,                      // starting Y
                             IS_ACTIVE_FLAG,         // status bits
                             1.0);                   // cooldown
            }
            UpdateAllEnemies ();
        }
        else if ((frame % FRAME_SLICES) == WEAPON_PROCESSING_FRAME)
        {
            UpdateAllWeapons ();
            UpdateAllLasers ();
        }

        cycles                  = get_cycle_counter () - cycles;

        end_frame ();

        frame                            = (frame + 1) % 60;
        if ((get_frame_counter () % 30) == 0)
        {
            seconds                      = seconds + 1;
        }
    }
}
