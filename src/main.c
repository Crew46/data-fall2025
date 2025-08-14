#include "gamemanager.h"

GameManager* gameManager;

void main (void)
{
	//create and initialize Game Manager
	gameManager = CreateGameManager();
	InitializeGameManager(gameManager);
	
	//Game Loop
	while (true)
	{
		//Update Game Manager
		UpdateGameManager(gameManager);

		end_frame ();
	}

	//Deinitialize Game Manager
	DeinitializeGameManager(gameManager);
}
