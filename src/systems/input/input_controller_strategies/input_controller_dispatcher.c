#ifndef INPUT_CONTROLLER_DISPATCHER
#define INPUT_CONTROLLER_DISPATCHER
#include "../input_controller.h"
#include "gamepad_input_controller_strategy.c"
   
void DispatchInputStrategy(InputController* inputController)
{
    switch (inputController->type)
    {
    case INPUT_CONTROLLER_TYPE_GAMEPAD:
        UpdateGamepadInput(inputController);
        break;
    case INPUT_CONTROLLER_TYPE_SHIP_CPU:
        break;
    default:
        break;
    }
}

#endif