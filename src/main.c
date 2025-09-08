#include "input.h"
#include "misc.h"
#include "video.h"
#include "time.h"

#define  BACKGROUND_TEXTURE 0
#define  PLAYER_TEXTURE     1
#define  ENEMYA_TEXTURE     2
#define  LASER_TEXTURE		3

#define  BACKGROUND_REGION  0
#define  PLAYER_REGION      1
#define  ENEMYA_REGION      2
#define	 LASER_REGION		3



#define LASERSPEED			1
int  xpos;
int  ypos;
int  position;
int spawn;
int i;
int status; // This will be used for checking
int mask;	// This is used to find out what bits we need.
int value;  // This will be used to reset status after a check.
// status will be divided like this 00000000
//  first 0 is game active the next 000 will be used for an enemy counter.
int counter;
int max;
struct Object
{
    int     x;
    int     y;
    int     xdir;
    int     ydir;//// DO NOT PUT ANY MORE INTS HERE. IT WILL CRASH
// danger area 
    bool    isActive;
	bool	laser;
	bool	laserFired;
    int     speed;
	int		height;
	int		width;// Ints after here seem to work.
    Object *next;
};
////////////////////////////////////////////////////////////////////////////////////

// Prepping what we need.
Object *headEnemyA;
Object *laser;
// This function will create a single EnemyA everytime it is used.
void appendEnemyA (Object *headEnemyA)
{
    Object *tmp         = NULL;
                
    tmp                 = headEnemyA;
    while (tmp -> next != NULL)
    {
        tmp             = tmp -> next;
    }    

    Object *EnemyA      = (Object *) malloc (sizeof (Object));
    EnemyA -> next      = NULL;
    EnemyA -> x         = xpos;
    EnemyA -> y         = ypos;
	EnemyA -> height	= 10;
	EnemyA -> width		= 10;
	EnemyA -> isActive	= true;
    tmp    -> next      = EnemyA;    
    xpos                = xpos + 20;
	if(xpos > 610)
		{
			xpos = 10;
		}
}

// The delete function used to delete enemies.

void deleteEnemyA (Object * headEnemyA)
{
    Object *tmp           = headEnemyA;
    Object *deletetmp     = headEnemyA;

    if (tmp ->next-> isActive == false) 
    {
		appendEnemyA(headEnemyA);
        deletetmp         = tmp -> next;
        tmp -> next       = deletetmp -> next;
        free (deletetmp);
        tmp               = tmp -> next;
    }
}


void insertEnemyA ( Object * headEnemyA, int position)
{
i = 0;
	Object *tmp			  = headEnemyA;
		while(i != position)
			{
				i = i+1;
				tmp = tmp->next;	
			}
		Object *EnemyA      = (Object *) malloc (sizeof (Object));
		EnemyA ->next		= NULL;
		EnemyA -> x			= xpos;
		EnemyA -> y			= ypos;
		EnemyA -> height	= 10;
		EnemyA -> width		= 10;
		EnemyA -> isActive 	= true;
		xpos = xpos + 20;
		if (xpos > 610)
			{
				xpos = 10;
			}
		Object *deletetmp 	= tmp->next;
		tmp ->next = EnemyA;
		tmp = tmp -> next;
		tmp->next = deletetmp;	
}

///////////////////////////////////////////////////////////////////////////////// Time for collision detection
bool collision( Object* Thing1, Object * Thing2)
{
// if Thing1 X > Thing2 X + width/2 + width there is no collision
	if (( Thing1->x - Thing1->width/2) >= (Thing2->x + Thing2->width/2) )
		return false;
// if Thing1 X + width/2 < Thing2 there is no collision
	if (( Thing1->x + Thing1->width/2) <= (Thing2->x - Thing2->width/2) )
		return false;
// if Thing1 Y > Thing2Y + height/2 there is no collision
	if (( Thing1->y - Thing1->height/2) >= (Thing2->y + Thing2->height/2) )
		return false;
// if Thing1 + height/2 < Thing2 y there is no collision
	if (( Thing1->y + Thing1->height/2) <= (Thing2->y - Thing2->height/2) )
		return false;
// If it makes it here then there is a collision
	return true;
}

void main (void)
{        
    Object *tmp          = NULL;
	laser 				 = NULL;
    headEnemyA           = NULL;
    xpos                 = 20;
    ypos                 = 0;
	max					 = 0;
	status				 = 0x10000000;
    // creating the head and malloc it.
    Object *headEnemyA   = (Object *) malloc (sizeof (Object));
    if (headEnemyA      == NULL)
    {
        exit ();
    }
    headEnemyA -> next   = NULL;

/// Creating the laser.
	Object * laser = (Object *)malloc(sizeof(Object));
	laser -> next = NULL;
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Prepping these for later use. tmp is a temporary node that will traverse
    // the list and deletetmp will be used to free nodes.
    //    
    appendEnemyA (headEnemyA);
    appendEnemyA (headEnemyA);
    appendEnemyA (headEnemyA);
    appendEnemyA (headEnemyA);
    appendEnemyA (headEnemyA);
	appendEnemyA (headEnemyA);
	insertEnemyA (headEnemyA, 0);
	insertEnemyA (headEnemyA, 3);
	insertEnemyA (headEnemyA, 1);
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Create our player instance
    //
    Object *player       = (Object *) malloc (sizeof (Object) * 1); 
    player -> next       = NULL;
    player -> x          = 360;
    player -> y          = 300;
	player -> isActive 	 = true;
	player -> height	 = 32;
	player -> width		 = 32;

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
    define_region_center (0, 0, 31, 31);
 
    ///////////////////////////////////////////////////////////////////////////////////
    //
    // Define the enemy texture and region
    select_texture (ENEMYA_TEXTURE);
    select_region (ENEMYA_REGION);
    define_region_center (0, 0 , 9, 9 );
///////////////////////////////////////////////////////////////////////////////////////
	select_texture (LASER_TEXTURE);
	select_region (LASER_REGION);
	define_region_center (0 ,0 , 19, 9);


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
	// If the player is inactive. Stop the game
	if(player->isActive == false)
		{
		clear_screen(color_black);
		draw_region();
		set_drawing_point( 200, 180);
		print( " You have died. Restart to try again");
		exit();
		}







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
        player -> x      = player -> x + player -> xdir * 3;
        player -> y      = player -> y + player -> ydir * 3;
// player laser will fire if x is pressed pressed. Only 1 laser can be fired.
		if((gamepad_button_a() == 1))
			{
			laser->laserFired = true;
			}		
			if(laser->laserFired && !laser->isActive)				
				{
					laser->isActive = true;
					laser->height = 20;
					laser->width  = 10;
					laser->x = player->x + 4;	
					laser->y = player->y;
					laser->laserFired = false;
				}
			// This will move the laser up. it will deactivate once it goes far enough.
			if(laser->isActive == true)
		{ 
			laser->y = laser->y - 10;
			if(laser->y < 20)
			{
				laser->isActive = false;
				free(laser);
			}
		}
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
        select_texture (PLAYER_TEXTURE);
        select_region  (PLAYER_REGION);
        draw_region_at (player -> x, player -> y);
    
       ///////////////////////////////////////////////////////////////////////////////
	if(laser != NULL)
	{
		if(laser->isActive)
			{
		select_texture(LASER_TEXTURE);
		select_region(LASER_REGION);
		draw_region_at(laser->x, laser->y);
			}
	}




        ////////////////////////////////////////////////////////////////////////////////
        //
        // Adjust enemy positions based on randomness
        //	
        tmp                = headEnemyA;
        while(tmp -> next != NULL)
        {
            tmp = tmp->next;
		if( tmp -> y > 300)
			{
				tmp -> isActive = false;
			}
		if(tmp->isActive == true)
			{
            tmp -> xdir    = rand () % 3 - 1;
            tmp -> ydir    = 1; //rand () % 3 - 1;
            tmp -> x       = tmp -> x + tmp -> xdir;
            tmp -> y       = tmp -> y + tmp -> ydir;
            select_texture (ENEMYA_TEXTURE);
            select_region  (ENEMYA_REGION);
            draw_region_at (tmp  -> x, tmp  -> y);
		
        	}
		}  

        // use the deleteEnemyA function to delete nodes that hit a certain Y value.
      tmp = headEnemyA; 
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
			 if(laser->isActive == true && tmp->isActive == true && collision(laser, tmp) )
			{	
				laser->isActive = false;
				tmp->isActive = false;
				counter = counter + 8; // Defeat an enemy and add one to the counter.
			}
			if(player->isActive == true && tmp->isActive == true && collision(player, tmp ) )
			{
				player->isActive = false;
			}
		}




		deleteEnemyA (headEnemyA);


// After defeating a certain amount of enemies add another one to the max.


// I do know that this code is slightly pointless. I just want to mess with bit masking.
if(counter >= 8 && max != 8)
	{
		value = status;
		mask = 0x01000000;
		status = status | mask;
			if (status == 0x11000000) // check the second bit to see if an enemy can be added.
				{
					appendEnemyA(headEnemyA);
					max = max + 1;
					status = value;
				}
// If the player is inactive then the game ends.
		
		counter = 0;
	}
        end_frame ();
    }
}
