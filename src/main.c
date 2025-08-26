#include "game_manager.h"
#include "time.h"

GameManager* gameManager;

void main (void)
{
    // create and initialize the game manager
//    gameManager     = CreateGameManager ();
    Object *player  = (Object *) malloc (sizeof (Object) * 1); 

    // Getting the Background
    select_texture( BACKGROUND_TEXTURE );
    select_region ( BACKGROUND_REGION );
    define_region_topleft( 0,0, 639,359);
    
    //player
    select_texture(PLAYER_SPRITES_TEXTURE);
    select_region(PLAYER_REGION);
    define_region(0, 0, 31, 31, 0, 0); // Player sprite
									   //
	player -> x     = 360;
	player -> y     = 300;
	player -> textureID  = 1;
	player -> regionID   = 1;

    //game loop
    while (true)
    {
        //clear screen
        clear_screen (get_color_red (0));    

        //drawing the background
        select_texture (BACKGROUND_TEXTURE);
        select_region (BACKGROUND_REGION);
        draw_region_at (0, 0);

        //select the gamepad mapped to this player controller
        select_gamepad (playerController -> gamepadID);
        gamepad_direction (&player -> xdir, &player -> ydir); //get the direction from the gamepad
        player -> x = player -> x + player -> xdir;
        player -> y = player -> y + player -> ydir;

        if (player -> x >  640)
        {
            player -> x  = 639;
        }

        if (player -> x <  0)
        {
            player -> x  = 1;
        }

        if (player -> y >  360)
        {
            player -> y  = 359;
        }

        if (player -> y <  0)
        {
            player -> y  = 1;
        }
        
        //select texture and region for first sprite in sprite array
        select_texture (player -> textureID); // Select the player's texture
        select_region (player -> regionID); // Select the player's sprite region

        //draw the sprite at the player's position
        draw_region_at (player -> x, player -> y); // Draw the sprite at the player's position

        end_frame ();
    }

    //Deinitialize game manager before exiting
//    DeconstructGameManager (gameManager);
}

