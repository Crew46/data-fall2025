#include "game_manager.c"
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
    DeinitializeGameManager();
}
