#include "game_manager.h"
#include "time.h"
#include "video.h"


// Temporary spot to define stuff.
#define Background 0

GameManager* gameManager;

void main(void)
{
    // create and initialize the game manager
    gameManager = CreateGameManager();
	


	// Getting the Background
	select_texture( 0 );
	select_region ( Background );
	define_region_topleft( 0,0, 639,359);
		

	




    //game loop
    while(true)
    {
		clear_screen(get_color_red(0));	
		//drawing the background
		select_texture ( 0 );
		select_region ( Background );
		draw_region_at( 0, 0 );


        //update game manager
        UpdateGameManager(gameManager);
        end_frame();
    }

	//Deinitialize game manager before exiting
	DeinitializeGameManager(gameManager);
}

