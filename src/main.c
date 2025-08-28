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
	///////////////////////////////////////////////////////////////////////////////////
	//
	// Declaring variables and an array
	//
int i;
Object * [12] EnemyAArray; 
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
    // Create multiple enemies
    //
for(i = 0; i < 12; i++)
{    
	EnemyAArray[i] = (Object *) malloc (sizeof (Object) * 1); 
    EnemyAArray[i] -> next       = NULL;
    EnemyAArray[i]  -> x          = 320;	//rand () % 630;
    EnemyAArray[i]  -> y          = 0;
    EnemyAArray[i]  -> textureID  = ENEMYA_TEXTURE;
    EnemyAArray[i]  -> regionID   = ENEMYA_REGION;
}
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
	// Define the enemy texture and region
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
		// Getting the textures and drawing the enemies at their position.
		//i
	for(i = 0; i < 12; i++)
	{
		select_texture (EnemyAArray[i] -> textureID);
		select_region (EnemyAArray[i] -> regionID);
		draw_region_at (EnemyAArray[i] -> x , EnemyAArray[i] -> y);
	}
		
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Adjust enemy positions based on randomness
        //
	for(i = 0; i < 12; i++)
	{
        EnemyAArray[i]  -> xdir   = rand () % 3 - 1;
        EnemyAArray[i]  -> ydir   = 1; //rand () % 3 - 1;
        EnemyAArray[i]  -> x      = EnemyAArray[i]  -> x + EnemyAArray[i]  -> xdir;
        EnemyAArray[i]  -> y      = EnemyAArray[i]  -> y + EnemyAArray[i]  -> ydir;
    }   
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Enemy/playfield bounds checking
        //

 
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Select texture and region for enemies, and draw it
        //
	for(i = 0; i < 12; i++)
	{
        select_texture (EnemyAArray[i]  -> textureID);
        select_region  (EnemyAArray[i]  -> regionID);
        draw_region_at (EnemyAArray[i]  -> x, EnemyAArray[i]  -> y);
	}
     
	   end_frame ();
    }
}
