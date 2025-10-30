#ifndef SHIP_CPU_INPUT_CONTROLLER_STRATEGY_C
#define SHIP_CPU_INPUT_CONTROLLER_STRATEGY_C
#include "../input_controller_manager.h"
#include "video.h"
#include "math.h"
#include "misc.h"

void UpdateShipCPUInput(InputController* inputController)
{
    int rand = rand() % 1000;
    if(get_frame_counter() % 20 == 0)
    {
        inputController->input.normalizedMovementDirection.x = cos(rand); 
    }
}

#endif //SHIP_CPU_INPUT_CONTROLLER_STRATEGY_C
