#include "game_manager.h"
#include "time.h"

GameManager* gameManager;

void main(void)
{
    gameManager = CreateGameManager();
    InitializeGameManager(gameManager);
    while(true)
    {
        UpdateGameManager(gameManager);
        end_frame();
    }

    DeinitializeGameManager(gameManager);
}

