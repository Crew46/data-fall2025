#include "input.h"
#include "misc.h"
#include "video.h"
#include "time.h"
#include "Object.h"
#include "visuals.h"
#include "functions.h"
#define LASERSPEED			1

// Prepping what we need.
doublyLinkedList * listA;
Object * tmp;
Object * tmp2;
Object * tmp3;
Object * newNode;
Object * laser;
// This function will create a single EnemyA everytime it is used.
doublyLinkedList * appendNode (doublyLinkedList * listA, Object * tmp, Object * newNode )
{

// If there is no head make one.
	if(listA->head 		== NULL)
	{
		listA->head 		= newNode;
	} 		
	else
{
// If there is a head append an enemy to the end of the list.
	tmp						= listA->head;
    while (tmp -> next != NULL)
    {
    tmp             	= tmp -> next;
    }   
// if there is no tail then make one.
	if(tmp->next			== NULL)
	{
		tmp->next			= newNode;
		listA->tail			= tmp->next;
		tmp->next->prev		= tmp;
	}

}
return(listA);
}
// rmnode checks
Object * rmNode(Object *thatNode)
{
	if((thatNode) ->isActive 	== false)
	{
		free(thatNode);
		if((thatNode) 			!= NULL)
		{
		(thatNode) 				= NULL;
		}
	
	}	
return(thatNode);	
}



// The obtain function that is currently used to delete enemies.

doublyLinkedList * obtainNode(doublyLinkedList * listA, Object **thatNode)
{
// Edge case where head is inactive and needs to be replaced after being
// marked for deletion.
	if((*thatNode) == listA->head)
		{
			listA->head   		= (*thatNode)->next;
			(*thatNode)->next->prev		= NULL;
			(*thatNode)->next			= NULL;
		}
// If there is no edge case continue as normal.
	if((*thatNode) == listA->tail)
		{
			listA->tail				= (*thatNode)->prev;
			listA->tail->next		= NULL;
			(*thatNode)->prev		= NULL;
		}
	if((*thatNode) != listA->head && (*thatNode) != listA->tail)    
		{	
			(*thatNode)->prev->next		= (*thatNode)->next;
			(*thatNode)->next->prev		= (*thatNode)->prev;
			(*thatNode)->next			= NULL;
			(*thatNode)->prev			= NULL;
		}
return(listA);
}
// Empty the list
doublyLinkedList * clearList(doublyLinkedList * listA)
	{
		Object * tmp					= NULL;
		if(listA 	!= NULL)
		{
		tmp								= listA->head;
		while(tmp	!= NULL)
			{
				listA	= obtainNode(listA, &tmp);	
				tmp		= rmNode(tmp);
				tmp		= listA->head;
			}
		}
	return(listA);
}







// This will insert the enemy at the desired position.
doublyLinkedList * insertNode ( doublyLinkedList * listA ,Object * tmp, Object * newNode, int position)
{
	// Edge case where we want to replace the head.


	tmp						= listA->head;
	if(position		 		== 0)
	{
	listA->head			= newNode;
	listA->head->next 	= tmp;
	listA->head->next->prev = listA->head;
	}
// If there is no edge case then insert at a certain spot.
	else
	{
	i = 0;
	tmp			  			= listA->head;
	while(i != position)
		{
		i = i+1;
		tmp = tmp->next;	
		}
	Object *tmp2 		= tmp->next;
	tmp ->next 			= newNode;
	tmp	->next->prev	= tmp;
	tmp 				= tmp -> next;
	tmp->next			= tmp2;	
	tmp2->prev 			= tmp;
	}
return(listA);
}
// delete the list function
doublyLinkedList * deleteList(doublyLinkedList * listA)
	{
		if(listA != NULL)
		{
			listA	= clearList(listA);
			free(listA);
			listA		= NULL;
		}
	return(listA);
	}



void main (void)
{   
	b			     = get_time();
	srand(b);     
   	tmp         			= NULL;
	tmp2					= NULL;
	tmp3					= NULL;
	laser 				 	= NULL;
    xpos                 	= NULL;
    ypos                 	= 0;
	max					 	= 0;
	position			 	= 2; 
	a 					 	= NULL;
	status				 	= 0x10000000;
    // creating the head and malloc it.
    listA = mkList();

/// Creating the laser.
	Object * laser = (Object *)malloc(sizeof(Object));
	laser -> next = NULL;
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // 
    // 
    // We are spawning and inserting the enemies.   
	newNode = mkNode();
	listA	= appendNode (listA, tmp, newNode);
	newNode = mkNode();
    listA 	= appendNode (listA, tmp, newNode);
	newNode = mkNode();
    listA	= appendNode (listA, tmp, newNode);
	newNode = mkNode();
    listA   = appendNode (listA, tmp, newNode);
	newNode = mkNode();
    listA	= appendNode (listA, tmp, newNode);
	newNode = mkNode();
	listA	= appendNode (listA, tmp, newNode);
	newNode = mkNode();
	listA	= insertNode (listA, tmp, newNode, 0);
	newNode = mkNode();
	listA	= insertNode (listA, tmp, newNode, 2);
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
    // 
    //Visuals will define and select textures.
	visuals();
 
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
		tmp = listA->head;
		while(tmp	!= NULL)
		{
			tmp->isActive	= false;
			tmp				= tmp->next;
		}
		//Game over fella. Erase everything.
		player		= NULL;
		laser		= NULL;	
		free(player);
		free(laser);
		listA				= clearList(listA);
		listA				= deleteList(listA);
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
if(player != NULL)
{
        gamepad_direction (&player -> xdir, &player -> ydir);
}
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Adjust player position based on recently obtained gamepad information
        // I am multiplying ydir and xdir by 3 to make the ship move faster.
if(player != NULL)
{
        player -> x      = player -> x + player -> xdir * 3;
        player -> y      = player -> y + player -> ydir * 3;
}
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
if(player != NULL)
{
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
}       
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Select texture and region for the player, and draw it
        //
if(player != NULL)
{
        select_texture (PLAYER_TEXTURE);
        select_region  (PLAYER_REGION);
        draw_region_at (player -> x, player -> y);
}
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
	if(listA !=NULL)
	{
        tmp                	= listA->tail;
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
	}
// This is here to make sure clearlist() and deleteList() is working.
// Currently works!
		mask    = 0x10000000;
		value   = status & mask;
		if(value != 0x10000000)
			{
				draw_region();
				set_drawing_point( 200, 180);
				print( " You have died. Restart to try again");
				exit();
			}


        // use the obtainEnemyA function to delete nodes that hit a certain Y value.
	if(listA != NULL)
	{
      	tmp = listA->head; 
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
		tmp						= tmp->next;
		}
}
	


// This will obtain the enemy and delete them
if(listA != NULL)
{
		tmp					= listA->head;
		while(tmp != NULL)
	{
// If we delete a node we need to move tmp before tmp3 deletes the node.
		if(tmp->isActive == false)
		{
		tmp3				= tmp;
		tmp=tmp->next;
		listA 				= obtainNode (listA, &tmp3);
		tmp3 				= rmNode(tmp3);
		newNode				= mkNode();
		listA  				= appendNode(listA, tmp, newNode);
		tmp					= listA->head;
		}
		// If we didn't delete a node move on.
		else
		{
			tmp 			= tmp->next;
		}
	}
}
// I do know that this code is slightly pointless. I just want to mess with bit masking.
if(counter >= 5 && max != 8)
	{
		mask = 0x01000000;
		value = status | mask;
			if (value == 0x11000000) // check the second bit to see if an enemy can be added.
				{
					max 		= max + 1;
					status 		= value;
					newNode		= mkNode();
					listA = appendNode(listA, tmp, newNode);	
					
				}
// If the player is inactive then the game ends.
		
		counter = 0;
	}

		


        end_frame ();
    }
}
