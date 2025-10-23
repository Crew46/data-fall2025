// vircon standard library
#include "audio.h"
#include "misc.h"
#include "string.h"
#include "time.h"
#include "video.h"

//definitions
#define  HALFWAY_ACROSS (screen_width/2)
#define  HALFWAY_DOWN   (screen_height/2)

#define  FRAME_SLICES            5 // frame offset categories

#define  SCREEN_REDRAWING_FRAME  0
#define  AUDIO_PROCESSING_FRAME  1
#define  PLAYER_PROCESSING_FRAME 2
#define  ENEMY_PROCESSING_FRAME  3
#define  WEAPON_PROCESSING_FRAME 4

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
#include "audio_manager.h"
#include "video_manager.h"
#include "weapon/laser.h"
#include "weapon/weapon.h"
#include "object_manager.h"
#include "title_screen.h"

void main (void)
{
    bool       alreadyrun                  = false;
    bool       start                       = false;
    int        cycles                      = 0;
    int        position                    = 0;
    int        frame                       = 0;
    int  [7]   creport;
    int  [12]  sreport;
    int  [2]   vreport;

    max_obj_vy                             = 1;
    min_obj_vy                             = 1;
    vy_obj_factor                          = 0;
    objectList                             = NULL;
    currentState                           = GAMESTATE_TITLE;
    half_seconds                           = 0;

    // initialize regions
    InitializeRegions ();
    InitializeAudioManager ();
    
    srand (get_time ());

    ////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize moving celestial object nodes, inserting into list
    //
    CreateCelestials ();

    // Initialize game state
    //currentState                           = GAMESTATE_MENU;
    select_gamepad (0);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // main game loop
    //
    while (true)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // GAMESTATE processing (per frame)
        //
        switch (currentState)
        {
            case GAMESTATE_TITLE:

                ////////////////////////////////////////////////////////////////////////
                //
                // Clear the screen
                //
                clear_screen (make_color_rgb (0, 0, 0));

                ////////////////////////////////////////////////////////////////////////
                //
                // Do an iteration of the title screen logic
                //
                title_screen (&alreadyrun);

                ////////////////////////////////////////////////////////////////////////
                //
                // Iterate through each node in the list for processing/display
                //
                UpdateAllObjects (titleList);
                UpdateAllObjects (objectList);
                drawList (titleList);
                drawList (GetObjectList ());

                position                   = get_channel_position (0);
                if (position              <  220000)
                {
                    vy_obj_factor          = 0;
                }
                else if (position         <  350000)
                {
                    vy_obj_factor          = 1;
                }
                else if (position         <  575000)
                {
                    max_obj_vy             = 4;
                    min_obj_vy             = 1;
                }
                else
                {
                    vy_obj_factor          = 2;
                }

                start                      = (gamepad_button_start () >  0);
                if (start                 == true)
                {
                    titleList              = deleteList (titleList);
                    alreadyrun             = false;
                    currentState           = GAMESTATE_GAMEPLAY;
                    pause_channel  (0);
                    stop_channel   (0);
                    select_sound   (BETTER_THAN_FASTER_THAN_MUSIC);
                    select_channel (0);
                    assign_channel_sound (get_selected_channel (), get_selected_sound ());
                    play_channel (get_selected_channel ());
                    set_channel_loop (true);
                    position               = 0;
                    max_obj_vy             = 1;
                    min_obj_vy             = 1;
                    vy_obj_factor          = 0;

                    // MANY INSTANCES OF PLAYER,  WHEN PLAYER IS CREATED,
                    // THE PLAYER FILE HAS STORED  IT IN A LINKED LIST TO
                    // UPDATE  ALL INSTANCES,  ALL  YOU HAVE  TO CALL  IS
                    // UpdateAllPlayers();  create  player, which  is  an
                    // extension  of object,  so need  to pass  in object
                    // params.

                    CreatePlayer (PLAYER_TEXTURE,                  // texture ID
                                  PLAYER_FRAME_0,                  // region ID
                                  HALFWAY_ACROSS,                  // starting X
                                  HALFWAY_DOWN,                    // starting Y
                                  IS_ACTIVE_FLAG,                  // status flag bits
                                  1.0,                             // shootCooldown
                                  PLAYER_ONE);                     // gamepad ID
                }
                break;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // frame offset processing
        //
        switch (frame % FRAME_SLICES)
        {
            case SCREEN_REDRAWING_FRAME:
                switch (currentState)
                {
                    case GAMESTATE_INTRO:
                        break;

                    case GAMESTATE_TITLE:
                        break;

                    ////////////////////////////////////////////////////////////////////
                    //
                    // GAMESTATE: main menu interface, selecting game mode and options
                    //
                    case GAMESTATE_MENU:
                        select_texture (UI_TEXTURES);
                        select_region  (EXIT_GAME_REGION);
                        draw_region_at (20,  40);
                        select_region  (PLAY_GAME_REGION);
                        draw_region_at (220, 40);
                        select_region  (CREDITS_REGION);
                        draw_region_at (420, 40);
                        break;

                    ////////////////////////////////////////////////////////////////////
                    //
                    // GAMESTATE: gameplay
                    //
                    case GAMESTATE_GAMEPLAY:

                        ////////////////////////////////////////////////////////////////
                        //
                        // clear the screen before repainting everything
                        //
                        clear_screen (make_color_rgb (0, 0, 0));

                        ////////////////////////////////////////////////////////////////
                        //
                        // draw the background
                        //
                        select_texture (BACKGROUND_TEXTURE);
                        select_region  (BACKGROUND_REGION);
                        draw_region_at (0, 0);

                        ////////////////////////////////////////////////////////////////
                        //
                        // render gameplay elements, note that rendering order will
                        // influence display layering priority (first being most
                        // backgrounded, last being most foregrounded)
                        //
                        drawList (GetObjectList ());
                        drawList (GetPlayerList ());
                        drawList (GetEnemyList  ());
                        drawList (GetWeaponList ());
                        drawList (GetLaserList  ());

                        ////////////////////////////////////////////////////////////////
                        //
                        // music position object speed adjustment
                        //
                        position           = get_channel_position (0);
                        if (position      <  100000)
                        {
                            vy_obj_factor  = 0;
                        }
                        else if (position <  315000)
                        {
                            vy_obj_factor  = 1;
                        }
                        else if (position <  600000)
                        {
                            max_obj_vy     = 4;
                            min_obj_vy     = 1;
                        }
                        else
                        {
                            vy_obj_factor  = 2;
                        }
                        break;

                    ////////////////////////////////////////////////////////////////////
                    //
                    // GAMESTATE: PAUSE
                    //
                    // The pause screen, a sub-transition only from the GAMEPLAY
                    // state (stop most gameplay activities, except for music)
                    //
                    case GAMESTATE_PAUSE:
                        break;

                    ////////////////////////////////////////////////////////////////////
                    //
                    // GAMESTATE: PLAYAGAIN
                    //
                    // When the player dies/is out of lives, do we just restart or
                    // return to the menu/title
                    //
                    case GAMESTATE_PLAYAGAIN:
                        break;

                    ////////////////////////////////////////////////////////////////////
                    //
                    // GAMESTATE: CREDITS
                    //
                    // Sequence displaying game credits (accessible from MENU)
                    //
                    case GAMESTATE_CREDITS:
                        break;

                    ////////////////////////////////////////////////////////////////////
                    //
                    // GAMESTATE: DEMO
                    //
                    // If all else fails, drop into demo mode
                    //
                    default:
                        if (alreadyrun  == false)
                        {
                            alreadyrun   = true;

                            CreatePlayer (PLAYER_TEXTURE,                  // texture ID
                                          PLAYER_FRAME_1,                  // region ID
                                          HALFWAY_ACROSS - 40,             // starting X
                                          HALFWAY_DOWN,                    // starting Y
                                          IS_ACTIVE_FLAG,                  // status flag bits
                                          1.0,                             // shootCooldown
                                          PLAYER_TWO);                     // gamepad ID

                            CreatePlayer (PLAYER_TEXTURE,                  // texture ID
                                          PLAYER_FRAME_2,                  // region ID
                                          HALFWAY_ACROSS + 40,             // starting X
                                          HALFWAY_DOWN,                    // starting Y
                                          IS_ACTIVE_FLAG | ODD_TEAM_FLAG,  // status flag bits
                                          1.0,                             // shootCooldown
                                          PLAYER_TWO);                     // gamepad ID

                            CreatePlayer (PLAYER_TEXTURE,                  // texture ID
                                          PLAYER_FRAME_3,                  // region ID
                                          HALFWAY_ACROSS - 80,             // starting X
                                          HALFWAY_DOWN + 80,               // starting Y
                                          IS_ACTIVE_FLAG | HIGH_TEAM_FLAG, // status flag bits
                                          1.0,                             // shootCooldown
                                          PLAYER_ONE);                     // gamepad ID

                            CreatePlayer (PLAYER_TEXTURE,                  // texture ID
                                          PLAYER_FRAME_0,                  // region ID
                                          HALFWAY_ACROSS + 80,             // starting X
                                          HALFWAY_DOWN + 100,              // starting Y
                                          IS_ACTIVE_FLAG | ODD_HIGH_FLAG,  // status flag bits
                                          1.0,                             // shootCooldown
                                          PLAYER_TWO);                     // gamepad ID
                        }
                        VisualizeLinkedList (GetPlayerList ());
                        // print statistics
                        PrintObjectDataAt (10, 60, GetPlayerList () -> head -> data);
                        PrintObjectDataAt ((screen_width - 180),
                                           60,
                                           GetPlayerList () -> head -> next -> next -> next -> data);
                        break;
                    }
                break;

            case PLAYER_PROCESSING_FRAME:
                break;

            case ENEMY_PROCESSING_FRAME:
                if (currentState         == GAMESTATE_GAMEPLAY)
                {
                    if (enemyList -> qty <  8)
                    {
                        CreateEnemy (ENEMY_TEXTURE,                   // texture ID
                                     ENEMY_REGION,                    // region ID
                                     rand () % screen_width,          // starting X
                                     rand () % 120 - 240,             // starting Y
                                     IS_ACTIVE_FLAG | HIGH_TEAM_FLAG, // status bits
                                     1.0);                            // cooldown
                    }
                    UpdateAllEnemies ();
                }
                break;

            case AUDIO_PROCESSING_FRAME:
                UpdateAudioManager ();
                break;

            case WEAPON_PROCESSING_FRAME:
                UpdateAllWeapons ();
                UpdateAllLasers  ();
                break;
        }

        UpdateAllObjects (objectList);
        UpdateAllPlayers ();
    
        if (frame                       == 0)
        {
            cycles                       = get_cycle_counter ();
            itoa (cycles, creport, 10);
        }

        print_at (0,   340, "cycles per second:");
        print_at (190, 340, creport);

        if (frame                       == 0)
        {
            position                     = get_channel_position (0);
            itoa (position, sreport, 10);
        }

        print_at (0,   320, "channel position:");
        print_at (190, 320, sreport);

        if (frame                       == 0)
        {
            itoa (vy_obj_factor, vreport, 10);
        }

        print_at (0,   300, "vy_obj_factor:");
        print_at (190, 300, vreport);

        end_frame ();

        frame                            = (frame + 1) % 60;
        if ((get_frame_counter () % 30) == 0)
        {
            half_seconds                 = half_seconds + 1;
        }
    }
}
