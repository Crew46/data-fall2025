#include "misc.h"
#include "video.h"
#include "time.h"

#define  BACKGROUND_REGION 0
#define  PLAYER_REGION     1

struct Object
{
    int     textureID;
    int     regionID;
    int     id;
    int     x;
    int     y;
    int     xdir;
    int     ydir;
    bool    isActive;
    int     speed;
    Object *next;
};

void main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Create our player instance
    //
    Object *player       = (Object *) malloc (sizeof (Object) * 1); 
    player -> next       = NULL;
    player -> x          = 360;
    player -> y          = 300;
    player -> textureID  = 1;
    player -> regionID   = 1;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Define the background texture and region
    //
    select_texture (BACKGROUND_TEXTURE);
    select_region (BACKGROUND_REGION);
    define_region_topleft (0, 0, 639, 359);
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Define the player texture and region
    //
    select_texture (PLAYER_SPRITES_TEXTURE);
    select_region (PLAYER_REGION);
    define_region (0, 0, 31, 31, 0, 0);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Select the first gamepad
    //
    select_gamepad (0);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Game loop
    //
    while (true)
    {
        //clear screen -- do we really need this?
        clear_screen (get_color_red (0));    

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Draw the background
        //
        select_texture (BACKGROUND_TEXTURE);
        select_region (BACKGROUND_REGION);
        draw_region_at (0, 0);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Obtain directional information (per axis) from selected gamepad
        //
        gamepad_direction (&player -> xdir, &player -> ydir);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Adjust player position based on recently obtained gamepad information
        //
        player -> x      = player -> x + player -> xdir;
        player -> y      = player -> y + player -> ydir;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Player/playfield bounds checking
        //
        if (player -> x <  0) // left side
        {
            player -> x  = 1;
        }

        if (player -> x >  640) // right side
        {
            player -> x  = 639;
        }

        if (player -> y <  0) // top of screen
        {
            player -> y  = 1;
        }

        if (player -> y >  360) // bottom of screen
        {
            player -> y  = 359;
        }
        
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Select texture and region for the player
        //
        select_texture (player -> textureID);
        select_region (player -> regionID);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Draw the player the screen at is current x, y coordinates
        //
        draw_region_at (player -> x, player -> y);

        end_frame ();
    }
}
