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
	// Declaring variables and a single linked list.
	//
int i;

// These variables will allow enemies to spawn (A way to improve it will be to use rand();
int ypos = 0;
int xpos = 20;
// Make the head connect it to the first EnemyA Once that is done connect tmp, so that it can start connecting new nodes.
	Object * headEnemyA = NULL;	
	headEnemyA = (Object *)malloc(sizeof(Object));	
	headEnemyA->next = NULL;	
	
	Object * EnemyA = (Object *) malloc (sizeof (Object) * 1);	
	headEnemyA->next = EnemyA;

	Object * tmp = (Object *) malloc (sizeof (Object) * 1);
	tmp= headEnemyA -> next;
	
// The delete tmp will be used to delete nodes.
	Object * deletetmp = (Object *)malloc (sizeof(Object) * 1);
	
	
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
    // Create multiple enemies for a single linked list
    //
i = 0;
for(i = 0; i < 12; i++)
{     
    EnemyA = (Object *) malloc(sizeof(Object));

	EnemyA  -> next       = NULL;
    EnemyA  -> x          = xpos;	//rand () % 630;
    EnemyA  -> y          = ypos;
	ypos = ypos + 10;
	xpos = xpos + 10;
    EnemyA  -> textureID  = ENEMYA_TEXTURE;
    EnemyA  -> regionID   = ENEMYA_REGION;
	tmp->next = EnemyA;
	tmp = tmp->next;
		

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

	tmp = headEnemyA;
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
	tmp = headEnemyA;
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
	
	tmp = headEnemyA;

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
