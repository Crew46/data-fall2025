#include "game_manager.h"
#include "time.h"

GameManager* gameManager;

void main(void)
{
    // create and initialize the game manager
    gameManager = CreateGameManager();

    //game loop
    while(true)
    {
        //update game manager
        UpdateGameManager(gameManager);
        end_frame();
    }

    // Deinitialize game manager before exiting
    DeinitializeGameManager(gameManager);
}

