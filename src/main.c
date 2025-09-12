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
int i;
int status; // This will be used for checking
int mask;	// This is used to find out what bits we need.
int value;  // This will be used to reset status after a check.
// status will be divided like this 00000000
//  first 0 is game active the next 000 will be used for an enemy counter.
int counter;
int max;
int position;
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
    Object *head;
	Object *tail;
	Object *next;
	Object *previous;
};
////////////////////////////////////////////////////////////////////////////////////

// Prepping what we need.
Object *enemyList;
Object *laser;
// This function will create a single EnemyA everytime it is used.
void appendEnemyA (Object *enemyList)
{
    Object *tmp         = NULL;
                
    tmp                 = enemyList;
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
	if(xpos > 610)
		{
			xpos = 10;
		}
	xpos = xpos + 35;
}
// rmnode checks
void rmnode(Object * tmp2)
	{
		if(tmp2 ->isActive == false)
	{
		free(tmp2);
		if(tmp2 != NULL)
		{
		tmp2 = NULL;
		}
	}
	}



// The obtain function that is currently used to delete enemies.

void obtainEnemyA (Object * enemyList)
{

	Object *tmp           = enemyList;
    Object *tmp2     	  = enemyList;
	while( tmp-> next != NULL)
	{
    if (tmp ->next-> isActive == false) 
    	{	
		appendEnemyA(enemyList);
        tmp2         	  = tmp -> next;
        tmp -> next       = tmp2 -> next;
        rmnode(tmp2);
    	}
	tmp = tmp->next;
	}
}

// This will insert the enemy at the desired position.
void insertEnemyA ( Object * enemyList, int position)
{
i = 0;
	Object *tmp			  = enemyList;
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

		if (xpos > 610)
			{
				xpos = 10;
			}
		xpos = xpos + 35;
		Object *tmp2 	= tmp->next;
		tmp ->next = EnemyA;
		tmp = tmp -> next;
		tmp->next = tmp2;	
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
    enemyList            = NULL;
    xpos                 = 20;
    ypos                 = 0;
	max					 = 0;
	position			 = 0;
	status				 = 0x10000000;
    // creating the head and malloc it.
    Object *enemyList   = (Object *) malloc (sizeof (Object));
    if (enemyList       == NULL)
    {
        exit ();
    }
    enemyList -> next   = NULL;

/// Creating the laser.
	Object * laser = (Object *)malloc(sizeof(Object));
	laser -> next = NULL;
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // 
    // 
    // We are spawning and inserting the enemies.   
    appendEnemyA (enemyList);
    appendEnemyA (enemyList);
    appendEnemyA (enemyList);
    appendEnemyA (enemyList);
    appendEnemyA (enemyList);
	appendEnemyA (enemyList);
	insertEnemyA (enemyList, 0);
	insertEnemyA (enemyList, 3);
	insertEnemyA (enemyList, 1);
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
	//
	// Define the laser texture and region
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
	mask = 0x10000000;
	value = status & mask;
	if(value != 0x10000000) // The first bit represents that the game is active.
		
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
        // I am multiplying ydir and xdir by 3 to make the ship move faster.
        player -> x      = player -> x + player -> xdir * 3;
        player -> y      = player -> y + player -> ydir * 3;
// player laser will fire if x is pressed pressed. Only 1 laser can be fired.
		if((gamepad_button_a() == 1))
			{
			laser->laserFired = true;
			}		
			// FIRING THE LASER!!!!!
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
	// This draws the laser if it is active.
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
        // Adjust enemy positions based on randomness and draw them.
        //	
        tmp                = enemyList;
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

        // use the obtainEnemyA function to delete nodes that hit a certain Y value.
      tmp = enemyList; 
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
			 if(laser->isActive == true && tmp->isActive == true && collision(laser, tmp) )
			{	
				laser->isActive = false;
				tmp->isActive = false;
				counter = counter + 8; // Defeat an enemy and add one to the counter.
			}
// This checks for player and enemy collision. If they collide the game ends.
			if(player->isActive == true && tmp->isActive == true && collision(player, tmp ) )
			{
				player->isActive = false;
				status = 0x00000000;
			}
		}



// This will obtain the enemy and delete them
		obtainEnemyA (enemyList);


// After defeating a certain amount of enemies add another one to the max.


// I do know that this code is slightly pointless. I just want to mess with bit masking.
if(counter >= 8 && max != 8)
	{
		mask = 0x01000000;
		value = status | mask;
			if (value == 0x11000000) // check the second bit to see if an enemy can be added.
				{
					appendEnemyA(enemyList);
					max = max + 1;
					status = value;
				}
// If the player is inactive then the game ends.
		
		counter = 0;
	}
        end_frame ();
    }
}
