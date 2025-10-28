#include "input.h"
#include "misc.h"
#include "video.h"
#include "time.h"
#include "string.h"
#include "audio.h"
#include "Object.h"
#include "visuals.h"
#include "node.h"
#include "linkedlist.h"
#include "stack.h"
#include "functions.h"
#include "sounds.h"
#include "queue.h"
#define LASERSPEED            1


void main (void)
{   
    int               byb          	= 1;
//  int               byn          	= 1;
    int               frame        	= 0;
    int               score        	= 0;
    int              *scoreResult  	= NULL;
    Object           *newNode      	= NULL;
    doublyLinkedList *listA        	= mkList (); // Main enemy list.
	doublyLinkedList *laserList	   	= mkList (); // laser list.
	doublyLinkedList *listB			= mkList (); // queue list.
	doublyLinkedList *listC			= mkList (); // stack list.
	queue  *myQueue					= mkQueue (listB);
	stack  *myStack					= mkStack (listC);
    Object *tmp             = NULL;
	Object *tmp2			= NULL;
    Object *tmp3            = NULL;
    max                     = 0; 

    srand (get_time ());     

    scoreResult             = (int *) malloc (sizeof (int) * 10);

   
		

 

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // 
    // 
    // We are spawning and inserting the enemies.   
	newNode = mkNode ();
	listA   = appendNode (listA, listA->tail, newNode);
	newNode = mkNode ();
	listA   = appendNode (listA, listA->tail, newNode);
	newNode = mkNode ();
    listA   = appendNode (listA, listA->tail, newNode);
    newNode = mkNode ();
    listA   = appendNode (listA, listA->tail, newNode);
    newNode = mkNode ();
    listA   = appendNode (listA, listA->tail, newNode);
    newNode = mkNode ();
    listA   = appendNode (listA, listA->tail, newNode);
    newNode = mkNode();
    listA   = insertNode (listA, listA->head, newNode);
    newNode = mkNode();
    listA   = insertNode (listA, listA->head, newNode);
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Create our player instance
    //
    Object *player       = (Object *) malloc (sizeof (Object) * 1); 
    player -> next       = NULL;
    player -> x          = 360;
    player -> y          = 300;
    player -> isActive   = true;
    player -> height     = 32;
    player -> width      = 32;
	player -> texture	 = PLAYER_TEXTURE;
	player -> region     = PLAYER_REGION;
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
	playAudio (0, 0, true, 1.0);
while (status == 0x00000000)
{
	select_texture ( BACKGROUND_TEXTURE);
	select_region ( BACKGROUND_REGION);
	draw_region_at ( 0 , byb);
	draw_region ();
	set_drawing_point ( 200, 150);
	print ( " PRESS ENTER TO START ");
	draw_region ();
	set_drawing_point ( 200, 250);
	print ( " X TO FIRE LASER ");
	if (gamepad_button_start () == true)
		{
			status = 0x00000001;
		}

}




    while (true)
    {
        // If the player is inactive. Stop the game
        if ( bitMasking (0x00000001, 0)	!= 0x00000001) // The first bit represents that the game is active.
        {
            //Game over fella. Erase everything.
            free (player);
            player               = NULL;


            listA                = clearList(listA);
            listA                = deleteList(listA);
			laserList			 = clearList(laserList);
			laserList			 = deleteList(laserList);
			myQueue				 = deleteQueue(myQueue);
			myStack				 = deleteStack(myStack);
        }


        ////////////////////////////////////////////////////////////////////////////////
        //
        // Draw the background
        //
        clear_screen (color_black);
        select_texture (BACKGROUND_TEXTURE);
        select_region (BACKGROUND_REGION);
		draw_region_at (0, byb);
/*      if ((frame % 8) == 0)
      {
            byb  = byb + 1;
            if (byb > 664)
                byb  = 1;
        }

        select_texture (NEBULA_TEXTURE);
        select_region (NEBULA_REGION);
        draw_region_at (0, byn);
//        if ((frame % 3) == 0)
//        {
        byn  = byn + 1;
        if (byn > 360)
            byn  = 1;
//        }
*/
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Obtain directional information (per axis) from selected gamepad
        //
		if(player != NULL)
        {
            gamepad_direction (&player -> xdir, &player -> ydir);
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Adjust player position based on recently obtained gamepad information
        // I am multiplying ydir and xdir by 3 to make the ship move faster.
            player -> x            = player -> x + player -> xdir * 3;
            player -> y            = player -> y + player -> ydir * 3;
        }

// player laser will fire if x is pressed pressed.
	if(laserList != NULL)
	{	 
        // FIRING THE LASER!!!!!
        if(gamepad_button_a () == true)                
        {
            newNode		= mkLaser (player);
			laserList	= appendNode (laserList, laserList->tail, newNode);
			playAudio (1, 1, false, 0.1);	
        }
        // This will move the laser up. it will deactivate once it goes far enough.
		tmp				= laserList->head;
		while(tmp != NULL)
		{
		if (tmp -> isActive     == true)
        	{ 
            	tmp -> y             = tmp -> y - 10;
            	if (tmp -> y        <  -40)
            	{
					tmp->isActive 	= false;
            	}
				tmp						= tmp->next;
        	}
		
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

            ////////////////////////////////////////////////////////////////////////////////
            //
            // Select texture and region for the player, and draw it
            //
				if (bitMasking (0x00000010, 0) == 0x00000010)
					{
						player->region = PLAYERSHIELD_REGION;
					}	
					if (bitMasking (0x00000010,0)  == 0x00000010)
					{
						if( time < get_time ())
						{
							player->region = PLAYER_REGION;
							status = bitMasking (0x11111101, 0);
						}
					}

            	select_texture (player->texture);
            	select_region  (player->region);
				draw_region_at (player -> x, player -> y);
			
			
        }

        ///////////////////////////////////////////////////////////////////////////////
        // This draws the laser if it is active.
     	if(laserList 	!= NULL)
		{	
				tmp				= laserList->head;
        		while(tmp 		!= NULL)
				{
				
            		if(tmp->isActive)
            		{
					
                		select_texture(LASER_TEXTURE);
               			select_region(LASER_REGION);
                		draw_region_at(tmp->x, tmp->y);
            		}
				tmp	= tmp->next;	
				}
			
			
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Adjust enemy positions based on randomness and draw them.
        //    
        if(listA !=NULL)
        {
            tmp                    	= listA->head;
            while(tmp != NULL)
            {
    
                if( tmp -> y > 400)
                {
                    tmp -> isActive = false;
                }

                if(tmp->isActive 	== true)
                {
                    tmp -> xdir    	= rand () % 3 - 1;
                    tmp -> ydir    	= 1; //rand () % 3 - 1;
                    tmp -> x       	= tmp -> x + tmp -> xdir;
                    tmp -> y       	= tmp -> y + tmp -> ydir;
                    select_texture (tmp->texture);
                    select_region  (tmp->region);
                    draw_region_at (tmp  -> x, tmp  -> y);
                }
                tmp                 = tmp->next;
            }  
        }

        // This is here to make sure clearlist() and deleteList() is working.
        // Currently works!
        if (bitMasking (0x00000001, 0)  != 0x00000001)
        {
            draw_region ();
            set_drawing_point (200, 180);
            print ("You have died. CTRL+R to restart.");
            exit ();
        }
        draw_region ();
        set_drawing_point (200, 10);
        print ("SCORE");

        draw_region ();    
        itoa (score, scoreResult, 10);
        print_at (250, 10, scoreResult);

        // Make sure that the enemy list and laser lists are not NULL.
        if (listA      != NULL && laserList != NULL)
        {
			tmp	= listA->head;
				while(tmp != NULL)
				{
					tmp2	= laserList->head;
					while(tmp2 != NULL)
					{
// This checks the enemy to make sure it is not a powerup and that it is active.
            			if(tmp2->isActive == true && tmp->powerup == false && tmp->isActive == true && collision(tmp2, tmp) )
                		{    
                    	tmp->hp         = tmp->hp - 1;
                    	tmp2->isActive 	= false;
							if(tmp->hp == 0)
                    		{
							score	= score + tmp->points;
                        	tmp->isActive = false;
                        	counter = counter + 8;
							playAudio(2, 2, false, 0.1);
// Explosion texture and rng powerups.	
							select_texture ( EXPLOSION_TEXTURE);
							select_region ( EXPLOSION_REGION);
							draw_region_at (tmp-> x, tmp->y);	
							b = rand () % ( 100 + 1);
							if( b  > 95)
							{
							newNode	= mkPowerup (tmp);		
							myStack	= push (myStack, newNode);
							myStack = pop  (myStack, &(tmp3));
							listA	= appendNode ( listA, listA->tail, tmp3);
							}
						
							}
						}
					tmp2 = tmp2->next;
					}
					tmp = tmp->next;	
				}		
		}
		

		if(listA != NULL)
		{
			tmp = listA->head;
			while( tmp	!= NULL)
			{
      	// This checks for player and enemy collision. If they collide the game ends.
               if(player->isActive == true && tmp->isActive == true && collision(player, tmp ) )
                {
					value = bitMasking (0x00000010, 0);
					if (tmp->powerup == false && value != 0x0000010)// The second bit will represent being immortal. (shield powerup)
					{
                    player->isActive 	= false;
                    status = 0x00000000;
					playAudio (2, 2, false, 0.1);
					}
					if (value == 0x00000010)
					{
						tmp->isActive = false;
						select_texture (EXPLOSION_TEXTURE);
						select_region (EXPLOSION_REGION);
						draw_region_at (tmp->x,tmp->y);
						score = score + tmp->points;
						playAudio (2, 2, false, 0.1);
					}
						
					// If you touch the power up you will become immortal for 5 seconds (For now);
					if (tmp -> powerup == true)
					{
					status = bitMasking ( 0x00000010, 1);
					tmp -> isActive	 	= false;
					time	= get_time () + 5;
					}
                }
                tmp                        	= tmp->next;
         	}		
        }
		
        // This will obtain the enemy and delete them
        if(listA != NULL)
        {
            tmp                    = listA->head;
            while(tmp != NULL)
            {
                // If we delete a node we need to move tmp before tmp3 deletes the node.
                if(tmp->isActive == false)
                {
                    tmp3                	= tmp;
                    tmp						= tmp->next;
                    listA                 	= obtainNode (listA, &tmp3);
                    listA                 	= rmNode (&tmp3, listA);
                    tmp                   	= listA->head;
                }
                // If we didn't delete a node move on.
                else
                {
                    tmp             = tmp->next;
                }
            }
        }
		// This is used to delete inactive lasers
		if(laserList != NULL)
		{
			tmp 					= laserList->head;
			while(tmp 	!=	NULL)
			{

				if(tmp->isActive == false)
				{
					tmp3                = tmp;
					tmp					= tmp->next;
					laserList			= obtainNode ( laserList, &tmp3);
					laserList			= rmNode ( &tmp3, laserList);
					tmp					= laserList->head;
				}
				else
				{
					tmp				= tmp->next;
				}
			}
		}

// spawning mechanism    
        newNode    = mkNode();
        if (92    <  (rand () % (100 + 0)))
        {
            listA  = insertNode (listA, listA -> head, newNode);
        }
	if (listA != NULL)
	{
		tmp = listA->head;
		while (tmp != NULL)   
		{
			tmp = updateVisuals (tmp);
			tmp = tmp -> next;
		}
 	}
// If the score is divisible by 110 then spawn enemies from a queue.
	if ( score % 110 == 0)
	{
		if(score != check)
		{
			check = score;
			for ( i = 0; i < 14; i++)
				{
					newNode			= mkNode ();
					myQueue	= enqueue (myQueue, newNode);
					myQueue = dequeue (myQueue, &(tmp3));
					listA   = appendNode (listA, listA->tail, tmp3);	
					draw_region ();
					set_drawing_point ( 260, 150);
					print( " INVASION ");
				}
		}
	}
        end_frame ();
        frame = frame + 1;
    }
}
