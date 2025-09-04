#include "input.h"
#include "misc.h"
#include "video.h"
#include "time.h"

<<<<<<< HEAD
void main(void)
{
    InitializeGameManager();
=======
#define  BACKGROUND_TEXTURE 0
#define  PLAYER_TEXTURE     1

#define  BACKGROUND_REGION  0
#define  PLAYER_REGION      1

////////////////////////////////////////////////////////////////////////////////////////
//
// Essence struct - what could describe the essence of all in-game items
//
struct Essence
{
    int      textureID;
    int      regionID;
    int      id;
    int      x;
    int      y;
    int      xdir;
    int      ydir;
    bool     isActive;
    int      speed;
    Essence *next;
};
>>>>>>> c347161d6bd93ebf9fa64b00ae2770a2ee448b06

////////////////////////////////////////////////////////////////////////////////////////
//
// main() function - where everything starts
//
void main (void)
{        
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Create our player instance
    //
    Essence *player      = (Essence *) malloc (sizeof (Essence) * 1); 
    player -> next       = NULL;
    player -> x          = 360;
    player -> y          = 300;
    player -> textureID  = PLAYER_TEXTURE;
    player -> regionID   = PLAYER_REGION;

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
    select_texture (PLAYER_TEXTURE);
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
<<<<<<< HEAD
        //update game manager
        UpdateGameManager();
        end_frame();
=======
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
        // Select texture and region for the player, and draw it
        //
        select_texture (player -> textureID);
        select_region  (player -> regionID);
        draw_region_at (player -> x, player -> y);
       
        end_frame ();
>>>>>>> c347161d6bd93ebf9fa64b00ae2770a2ee448b06
    }
}
