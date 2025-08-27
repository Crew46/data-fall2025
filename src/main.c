#include "input.h"
#include "misc.h"
#include "video.h"
#include "time.h"

#define  BACKGROUND_TEXTURE 0
#define  PLAYER_TEXTURE     1
#define  ENEMYA_TEXTURE      2

#define  BACKGROUND_REGION  0
#define  PLAYER_REGION      1
#define  ENEMYA_REGION       2

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
    player -> textureID  = PLAYER_TEXTURE;
    player -> regionID   = PLAYER_REGION;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Create an enemy instance
    //
    Object *enemyA        = (Object *) malloc (sizeof (Object) * 1); 
    enemyA  -> next       = NULL;
    enemyA  -> x          = rand () % 630;
    enemyA  -> y          = 300;
    enemyA  -> textureID  = ENEMYA_TEXTURE;
    enemyA  -> regionID   = ENEMYA_REGION;

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
    
 
	///////////////////////////////////////////////////////////////////////////////////
	//
	// Define the enemy texutre and region
	select_texture (ENEMYA_TEXTURE);
	select_region (ENEMYA_REGION);
	define_region_topleft (0, 0 , 9, 9 );




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
        // Select texture and region for the player, and draw it
        //
        select_texture (player -> textureID);
        select_region  (player -> regionID);
        draw_region_at (player -> x, player -> y);
	
		///////////////////////////////////////////////////////////////////////////////
		//
		//
		// Getting the textures and drawing the enemy at their position.
		//
		select_texture (enemyA -> textureID);
		select_region (enemyA -> regionID);
		draw_region_at (enemyA -> x , enemyA -> y);

		
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Adjust enemy position based on randomness
        //
        enemyA  -> xdir   = rand () % 3 - 1;
        enemyA  -> ydir   = 1; //rand () % 3 - 1;
        enemyA  -> x      = enemyA  -> x + enemyA  -> xdir;
        enemyA  -> y      = enemyA  -> y + enemyA  -> ydir;
        
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Enemy/playfield bounds checking
        //

 
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Select texture and region for the enemy, and draw it
        //
        select_texture (enemyA  -> textureID);
        select_region  (enemyA  -> regionID);
        draw_region_at (enemyA  -> x, enemyA  -> y);

        end_frame ();
    }
}
