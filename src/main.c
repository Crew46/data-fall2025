#include "game_manager.h"
#include "time.h"

GameManager* gameManager;

void main (void)
{
    // create and initialize the game manager
    gameManager  = CreateGameManager ();

    //game loop
    while (true)
    {
        //update game manager
        //UpdateGameManager(gameManager);

		//clear screen
		clear_screen (get_color_red (0));	
		//drawing the background
		select_texture (BACKGROUND_TEXTURE);
		select_region (BACKGROUND_REGION);
		draw_region_at (0, 0);

		//temporary player controller update
		//PlayerControllerUpdate(playerController);

		//select the gamepad mapped to this player controller
		select_gamepad (playerController -> gamepadID);
		Vector2 *movement  = CreateVector2 (0, 0); 
		gamepad_direction_normalized (&movement -> x, &movement -> y); //get the direction from the gamepad
		//add player position and direction to player position
		Vector2 *movementVector  = CreateVector2 (direction -> x, direction -> y); // Create a new vector for movement
		MultiplyVector2ByScalar (movementVector, player -> speed); // Scale the movement vector by the player's speed
		AddVector2Components(player->object->position, movementVector, player->object->position);
		DeconstructVector2(movementVector); // Free the movement vector after use

		DeconstructVector2(movement);

		//will update all once linked list data structure is made, in order to store instances and update iteratively
		//UpdateAllLaserControllers();
		//UpdateAllPlayerControllers();

        end_frame();
    }

	//Deinitialize game manager before exiting
	DeconstructGameManager(gameManager);
}

