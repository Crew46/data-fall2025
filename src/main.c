#include "input.h"
#include "misc.h"
#include "video.h"
#include "time.h"
#include "Object.h"
#define  BACKGROUND_TEXTURE 0
#define  PLAYER_TEXTURE     1
#define  ENEMYA_TEXTURE     2
#define  LASER_TEXTURE		3
#define	 ENEMYB_TEXTURE     4

#define  BACKGROUND_REGION  0
#define  PLAYER_REGION      1
#define  ENEMYA_REGION      2
#define	 LASER_REGION		3
#define  ENEMYB_REGION		4


#define LASERSPEED			1



// I don't know why I didn't make this sooner '_'
// This makes a node and returns EnemyA (Will be modified later for different cases for different enemies.
Object * mknode()
	{
	a = rand() % ( 100 - 0 + 1);
	xpos = rand() % (639 - 2 + 1);
	if(a <= 80)
	{
	Object * EnemyA			= (Object *) malloc (sizeof (Object));
	EnemyA ->next			= NULL;
	EnemyA ->prev			= NULL;
	EnemyA ->tail			= NULL;
	EnemyA -> x				= xpos;
	EnemyA -> y				= ypos;
	EnemyA -> height		= 10;
	EnemyA -> width			= 10;
	EnemyA -> isActive		= true;
	EnemyA -> hp			= 1;
	EnemyA -> texture 		= ENEMYA_TEXTURE;
	EnemyA -> region  		= ENEMYA_REGION;
	return EnemyA;
	}
	if(a > 80)
	{
	Object * EnemyB			= (Object *) malloc (sizeof(Object));
	EnemyB -> next			= NULL;
	EnemyB -> prev			= NULL;
	EnemyB -> tail			= NULL;
	EnemyB -> x				= xpos;
	EnemyB -> y				= ypos;
	EnemyB -> height		= 20;
	EnemyB -> width			= 20;
	EnemyB -> isActive		= true;
	EnemyB -> hp			= 3;
	EnemyB -> texture	    = ENEMYB_TEXTURE;
	EnemyB -> region		= ENEMYB_REGION;
	return EnemyB;
	}




	}








// Prepping what we need.
Object *enemyList;
Object *laser;
// This function will create a single EnemyA everytime it is used.
void appendEnemyA (Object *enemyList)
{
    Object *tmp         	= NULL;
	Object *tmp2			= NULL;
// If there is no head make one.
	if(enemyList->head 		== NULL)
	{
	enemyList->head 		= mknode();
	} 		
	else
{
// If there is a head append an enemy to the end of the list.
	tmp						= enemyList->head;
    while (tmp -> next !	= NULL)
    {
        tmp             	= tmp -> next;
    }   
// if there is no tail then make one.
	if(tmp->tail			== NULL)
	{
		tmp->tail			= mknode();
		enemyList->tail		= tmp->tail;
		tmp->tail->prev		= tmp;
	}
// if there is a tail then we will make a new tail.
	else
	{
	tmp2					= tmp->tail;
	tmp->next				= tmp2;
	tmp->tail			 	= NULL;
	tmp->next->prev			= tmp;
	tmp->next->tail			= mknode();
	tmp->next->tail->prev	= tmp->next;
	enemyList->tail			= tmp->next->tail;
	}
}
}
// rmnode checks
void rmnode(Object * tmp2)
	{
		if(tmp2 ->isActive 	== false)
		{
		free(tmp2);
		if(tmp2 			!= NULL)
		{
		tmp2 				= NULL;
		}
		}
	}



// The obtain function that is currently used to delete enemies.

void obtainEnemyA (Object * enemyList)
{
// Edge case where head is inactive and needs to be replaced after being
// marked for deletion.
	Object *tmp			  	= enemyList;
	Object *tmp2		  	= enemyList;
	if(enemyList->head->isActive == false)
		{
		appendEnemyA(enemyList);
		tmp2			  	= enemyList->head;
		enemyList->head   	= tmp2->next;
		tmp2->next->prev  	= NULL;
		rmnode(tmp2);
		}

// If there is no edge case continue as normal.
	tmp           			= enemyList->head;
    tmp2     	  			= enemyList->head;
	while( tmp-> next 		!= NULL)
	{
    if (tmp ->next-> isActive == false) 
    	{	
		appendEnemyA(enemyList);
        tmp2         	  	= tmp -> next;
        tmp -> next       	= tmp2 -> next;
		tmp2->next->prev  	= tmp;
        rmnode(tmp2);
    	}
// if tail is inactive we will have to remove it.
	if(tmp->next->tail != NULL)
	{
		if(tmp->next->tail->isActive == false)
		{
		tmp2                = tmp->next;
		tmp->tail           = tmp2;
		tmp->next			= NULL;
		tmp2				= tmp2->tail;
		tmp2->prev			= NULL;
		tmp->tail->tail		= NULL;
		enemyList->tail		= tmp->tail;
		rmnode(tmp2);
		appendEnemyA(enemyList);
		}	
	}

tmp = tmp->next;
	}
}

// This will insert the enemy at the desired position.
void insertEnemyA ( Object * enemyList, int position)
{
	// Edge case where we want to replace the head.


	Object * tmp			= enemyList->head;
	if(position		 		== 0)
	{
		enemyList->head		= mknode();
		enemyList->head->next = tmp;
		enemyList->head->next->prev = enemyList->head;
	}
// If there is no edge case then insert at a certain spot.
	else
	{
	i = 0;
	tmp			  			= enemyList->head;
		while(i != position)
			{
			i = i+1;
			tmp = tmp->next;	
			}
		Object *tmp2 		= tmp->next;
		tmp ->next 			= mknode();
		tmp	->next->prev	= tmp;
		tmp 				= tmp -> next;
		tmp->next			= tmp2;	
		tmp2->prev 			= tmp;
	}
}

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
	position			 = 2; 
	a 					 = NULL;
	status				 = 0x10000000;
    // creating the head and malloc it.
    Object *enemyList   = (Object *) malloc (sizeof (Object));
    if (enemyList       == NULL)
    {
        exit ();
    }
    enemyList -> head   = NULL;

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
	insertEnemyA (enemyList, 2);
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
    // Define the ENEMYA texture and region
    select_texture (ENEMYA_TEXTURE);
    select_region (ENEMYA_REGION);
    define_region_center (0, 0 , 9, 9 );
///////////////////////////////////////////////////////////////////////////////////////
	//
	// Define the laser texture and region
	select_texture (LASER_TEXTURE);
	select_region (LASER_REGION);
	define_region_center (0 ,0 , 19, 9);
///////////////////////////////////////////////////////////////////////////////////////
	select_texture (ENEMYB_TEXTURE);
	select_region  (ENEMYB_REGION);
	define_region_center ( 0, 0 , 19, 19);

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
        tmp                	= enemyList->tail;
        while(tmp != NULL)
        {
	
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
            select_texture (tmp->texture);
            select_region  (tmp->region);
            draw_region_at (tmp  -> x, tmp  -> y);
		
        	}
		tmp					= tmp->prev;
		}  

        // use the obtainEnemyA function to delete nodes that hit a certain Y value.
      tmp = enemyList->tail; 
		while(tmp != NULL)
		{
			 if(laser->isActive == true && tmp->isActive == true && collision(laser, tmp) )
			{	
				tmp->hp 		= tmp->hp - 1;
				laser->isActive = false;
			if(tmp->hp == 0)
				{
				tmp->isActive = false;
				counter = counter + 8;
				}
			 // Defeat an enemy and add one to the counter.
			}



// This checks for player and enemy collision. If they collide the game ends.
			if(player->isActive == true && tmp->isActive == true && collision(player, tmp ) )
			{
				player->isActive = false;
				status = 0x00000000;
			}
		tmp						= tmp->prev;
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
