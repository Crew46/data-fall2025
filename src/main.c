#include "game_manager.h"
#include "time.h"

void main(void)
{
    InitializeGameManager();

    //game loop
    while(true)
    {
        //update game manager
        UpdateGameManager();
        end_frame();
    }
}