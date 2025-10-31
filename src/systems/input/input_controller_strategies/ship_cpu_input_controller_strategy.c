#ifndef SHIP_CPU_INPUT_CONTROLLER_STRATEGY_C
#define SHIP_CPU_INPUT_CONTROLLER_STRATEGY_C
#include "../input_controller_manager.h"
#include "video.h"
#include "math.h"
#include "misc.h"

void UpdateShipCPUInput(InputController* inputController)
{
    int randnum = (rand() % 60) + 60;
    if(get_frame_counter() % randnum == 0)
    {
        int randnum = rand() % 1000;
        inputController->input.normalizedMovementDirection.x = cos(randnum); 
        inputController->input.normalizedMovementDirection.y = sin(randnum); 
    }
  
    randnum = (rand() % 30 + 10) + 60;
    if(get_frame_counter() % randnum == 0) 
    {
        inputController->input.buttonA = 1;
    }
    else
    {
        inputController->input.buttonA = -1;
    }
   
    randnum = (rand() % 180 + 60) + 180;
    if(get_frame_counter() % randnum == 0)
    {
        inputController->input.buttonB = 1;
    }
    else
    {
        inputController->input.buttonB = -1;
    }
}

#endif //SHIP_CPU_INPUT_CONTROLLER_STRATEGY_C
