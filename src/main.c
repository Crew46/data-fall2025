#include "game_manager.h"
#include "time.h"

GameManager* gameManager;

void main (void)
{
    // create and initialize the game manager
    gameManager     = CreateGameManager ();
	Object *player  = (Object *) malloc (sizeof (Object) * 1); 

    //game loop
    while (true)
    {
		//clear screen
		clear_screen (get_color_red (0));	

		//drawing the background
		select_texture (BACKGROUND_TEXTURE);
		select_region (BACKGROUND_REGION);
		draw_region_at (0, 0);


		//select the gamepad mapped to this player controller
		select_gamepad (playerController -> gamepadID);
		gamepad_direction (&player -> xdir, &player -> ydir); //get the direction from the gamepad
		player -> x = player -> x + player -> xdir;
		player -> y = player -> y + player -> ydir;

	    if (player -> x >  358)
	    {
            player -> x  = 357;
        }

        if (player -> x <  2)
		{
            player -> x  = 3;
		}

		if (player -> y >  640)
		{
            player -> y  = 649;
		}

		if (player -> y <  0)
		{
		    player -> y  = 1;
		}

        end_frame();
    }

	//Deinitialize game manager before exiting
	DeconstructGameManager (gameManager);
}

