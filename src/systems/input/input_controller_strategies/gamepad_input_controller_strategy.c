#ifndef GAMEPAD_INPUT_CONTROLLER_STRATEGY_C
#define GAMEPAD_INPUT_CONTROLLER_STRATEGY_C
#include "../input_controller_manager.h"
#include "input.h"
#include "video.h"

void UpdateGamepadInput(InputController* inputController)
{
    select_gamepad(inputController->gamepad);
    Input* input = &inputController->input;
    input->buttonA = gamepad_button_a();  
    input->buttonB = gamepad_button_b();
    input->buttonX = gamepad_button_x();
    input->buttonY = gamepad_button_y();
    input->buttonL = gamepad_button_l();
    input->buttonR = gamepad_button_r();
    input->buttonStart = gamepad_button_start();
    int deltaX = 0;
    int deltaY = 0;
    gamepad_direction(&deltaX, &deltaY);
    input->movementDirection.x = deltaX;
    input->movementDirection.y = deltaY;
}

#endif