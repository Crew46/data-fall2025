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
int xpos = 20;
int ypos = 0;
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
////////////////////////////////////////////////////////////////////////////////////
 

// Prepping what we need.
	Object * headEnemyA = NULL;
	Object * tmp = NULL;
	Object * deletetmp = NULL;
// This function will create a single EnemyA everytime it is used.
void createEnemyA(void)
	{
				tmp = headEnemyA;
				while(tmp->next != NULL);
				{
				tmp=tmp->next;
				}	
					Object * EnemyA = (Object *)malloc (sizeof(Object));
					EnemyA -> next = NULL;
					EnemyA -> x = xpos;
					EnemyA -> y = ypos;
					EnemyA -> textureID = ENEMYA_TEXTURE;
					EnemyA -> regionID = ENEMYA_REGION;
					tmp -> next = EnemyA;	
					xpos = xpos + 10;
	}

void main (void)
{		
	
// creating the head and malloc it.
Object * headEnemyA = (Object *)malloc(sizeof(Object));
	if(headEnemyA == NULL);
	{
	exit();
	}
headEnemyA->next == NULL;
// Prepping these for later use. tmp is a temporary node that will traverse
// the list and deletetmp will be used to free nodes.
Object * deletetmp = (Object *)malloc (sizeof(Object));
Object * tmp = (Object *) malloc (sizeof (Object));
createEnemyA();
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
		// Getting the textures and drawing the enemies at their positions.
		//	
	tmp = headEnemyA->next;
	while(tmp->next != NULL)
	{
		select_texture (ENEMYA_TEXTURE);
		select_region (ENEMYA_REGION);
		draw_region_at (tmp -> x , tmp -> y);
		tmp = tmp->next;
	}
	
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Adjust enemy positions based on randomness
        //

	tmp = headEnemyA->next;
	while(tmp->next != NULL)
	{
		
        tmp  -> xdir   = rand () % 3 - 1;
        tmp  -> ydir   = 1; //rand () % 3 - 1;
        tmp  -> x      = tmp  -> x + tmp  -> xdir;
        tmp  -> y      = tmp  -> y + tmp  -> ydir;

		if (tmp->next->y > 300)
		{
			deletetmp = tmp->next;
			tmp->next = deletetmp->next;
			free(deletetmp);
		}
		tmp=tmp->next;
	}   
        ////////////////////////////////////////////////////////////////////////////////
        //
        //
        //
	
 
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Select texture and region for enemies, and draw it
        //	
	tmp = headEnemyA->next;

	while(tmp->next !=NULL)
	{
        select_texture (ENEMYA_TEXTURE);
        select_region  (ENEMYA_REGION);
        draw_region_at (tmp  -> x, tmp  -> y);
		tmp = tmp->next;
	}
     
	   end_frame ();
    }
}
