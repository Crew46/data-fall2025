#include "game_manager.h"
#include "time.h"
#include "tools/debugger.c"

void get1(int* outValue)
{
    *outValue = 1;
}

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
